/**************************************************************************//**
 *
 * Copyright 1998-2013 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non-NetBurner Hardware.
 *   Please contact sales@Netburner.com for more information.
 *
 *   NetBurner makes no representation or warranties
 *   with respect to the performance of this computer program, and
 *   specifically disclaims any responsibility for any damages,
 *   special or consequential, connected with the use of this program.
 *
 *---------------------------------------------------------------------
 * NetBurner, Inc.
 * 5405 Morehouse Drive
 * San Diego, California 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is available: E-Mail support@netburner.com
 *
 *****************************************************************************/

#include <basictypes.h>
#include <stdio.h>
#include <constants.h>
#include <iointernal.h>
#include <iosys.h>
#include <effs_fat/fat.h>
#include <effs_fat/api_f.h>
#include <effs_fat/common.h>
#include "wavWriter.h"

struct wavWriterCxt {
    F_FILE *fp;
    bool headerWritten;
    uint16_t channels;
    uint32_t sampleRate;
    uint32_t dataLen;
};


static wavWriterCxt wavWriterData[NUM_WAV_WRITERS];
static bool cxtFree[NUM_WAV_WRITERS];
static BOOL bInit = FALSE;
static int last_free = 0;

static IoExpandStruct wavWriter_ioexpand;
static int getWavWriterCxt();
static void freeWavWriterCxt( int fd );

// Nope... No reading allowed.
static int wavRead( int fd, char *buf, int nbytes )
{
    return 0;
}


// Write the header portion of a wav file to an empty file
static int wavWriteHeader( wavWriterCxt *cxt )
{
    int bytesWritten = 0;
    char outBuf[16];
    uint32_t byteRate, blockAlign;
    if(cxt->fp)
    {
        bytesWritten = f_write("RIFF", 1, 4, cxt->fp);
        bytesWritten += f_write("\x24\x00\x00\x00", 1, 4, cxt->fp); // Initial ChunkSize
        bytesWritten += f_write("WAVEfmt \x10\x00\x00\x00", 1, 12, cxt->fp); // 0x10 == 16, PCM subchunk
        bytesWritten += f_write("\x01\x00", 1, 2, cxt->fp); // 0x01 == 1, PCM encoding
        outBuf[0] = ((uint8_t *)&cxt->channels)[1];
        outBuf[1] = ((uint8_t *)&cxt->channels)[0];
        bytesWritten += f_write(outBuf, 1, 2, cxt->fp); // channel count

        outBuf[0] = ((uint8_t *)&cxt->sampleRate)[3];
        outBuf[1] = ((uint8_t *)&cxt->sampleRate)[2];
        outBuf[2] = ((uint8_t *)&cxt->sampleRate)[1];
        outBuf[3] = ((uint8_t *)&cxt->sampleRate)[0];
        bytesWritten += f_write(outBuf, 1, 4, cxt->fp); // sample rate
        
        byteRate = cxt->sampleRate * cxt->channels * 2; // 2 bytes per sample (12 bit)
        outBuf[0] = ((uint8_t *)&byteRate)[3];
        outBuf[1] = ((uint8_t *)&byteRate)[2];
        outBuf[2] = ((uint8_t *)&byteRate)[1];
        outBuf[3] = ((uint8_t *)&byteRate)[0];
        bytesWritten += f_write(outBuf, 1, 4, cxt->fp); // byte rate

        blockAlign = cxt->channels * 2; // 2 bytes per sample (12 bit)
        outBuf[0] = ((uint8_t *)&blockAlign)[3];
        outBuf[1] = ((uint8_t *)&blockAlign)[2];
        outBuf[2] = ((uint8_t *)&blockAlign)[1];
        outBuf[3] = ((uint8_t *)&blockAlign)[0];
        bytesWritten += f_write(outBuf, 1, 2, cxt->fp); // byte rate

        bytesWritten += f_write("\x10\x00", 1, 2, cxt->fp); // bits per sample (16) (not really,  but we'll fake it)
        bytesWritten += f_write("data", 1, 4, cxt->fp); // begin data chunk
        bytesWritten += f_write("\x00\x00\x00\x00", 1, 4, cxt->fp); // data length (0, no data written)

        cxt->headerWritten = true;
    }
    return bytesWritten;
}

// Shift the data over and swap endianness
static inline int swapAndShift(uint16_t data, uint8_t shiftAmt)
{
    data <<= shiftAmt;
    uint8_t tmp = ((uint8_t *)&data)[0];
    ((uint8_t *)&data)[0] = ((uint8_t *)&data)[1];
    ((uint8_t *)&data)[1] = tmp;
    return data;
}

// Write the chunk sizes into the file headers
static void setChunkSizes( wavWriterCxt *cxt )
{
    char outBuf[4];
    int rv = F_NO_ERROR;
    uint32_t chunkSize = 36 + cxt->dataLen;
    outBuf[0] = ((uint8_t *)&chunkSize)[3];
    outBuf[1] = ((uint8_t *)&chunkSize)[2];
    outBuf[2] = ((uint8_t *)&chunkSize)[1];
    outBuf[3] = ((uint8_t *)&chunkSize)[0];
    rv = f_seek(cxt->fp, 4, F_SEEK_SET); // move fp to ChunkSize position
    if (rv != F_NO_ERROR)
    {
        printf("SEEK ERROR: %#X\r\n", rv);
        return;
    }
    f_write(outBuf, 1, 4, cxt->fp);

    outBuf[0] = ((uint8_t *)&cxt->dataLen)[3];
    outBuf[1] = ((uint8_t *)&cxt->dataLen)[2];
    outBuf[2] = ((uint8_t *)&cxt->dataLen)[1];
    outBuf[3] = ((uint8_t *)&cxt->dataLen)[0];
    f_seek(cxt->fp, 40, F_SEEK_SET); // move fp to SubChunk2Size position
    if (rv != F_NO_ERROR)
    {
        printf("SEEK ERROR: %#X\r\n", rv);
        return;
    }
    f_write(outBuf, 1, 4, cxt->fp);
    
    f_flush(cxt->fp);
    f_seek(cxt->fp, 0, F_SEEK_END); // move fp to the eof, ready to write more
}

static int wavWrite( int fd, const char *buf, int nbytes )
{
    wavWriterCxt *cxt = (wavWriterCxt *)GetExtraData( fd );
    int bytesWritten = 0;

    for (int32_t i = 0; i < nbytes/2; i+=SWPBUFFSIZE)
    {
        int16_t swapBuffer[SWPBUFFSIZE];
        int j;
        uint8_t tmp;
        for (j = 0; (j < SWPBUFFSIZE) && (j < (nbytes/2 - i)); j++)
        {
            swapBuffer[j] = ((int16_t *)buf)[i+j];
            swapBuffer[j] -= 0x4000; // > 8 bit wav files are signed data...

            // perform endian swap
            tmp = ((uint8_t *)&swapBuffer[j])[0];
            ((uint8_t *)&swapBuffer[j])[0] = ((uint8_t *)&swapBuffer[j])[1];
            ((uint8_t *)&swapBuffer[j])[1] = tmp;
        }
        bytesWritten += f_write((const char *)swapBuffer, 1, j*2, cxt->fp);
    }
    // increment the data length of the file
    cxt->dataLen += bytesWritten;

    return bytesWritten;
}

static int wavClose( int fd )
{
    wavWriterCxt *cxt = (wavWriterCxt *)GetExtraData( fd );
    setChunkSizes( cxt ); // update chunk sizes in file header
    f_close(cxt->fp); // close the file
    freeWavWriterCxt( fd ); // release the writer context
    FreeExtraFd( fd ); // release the file descriptor
    return 0;
}

int openNewWav( char *fileName, uint16_t channels, uint32_t sampleRate )
{
    F_FILE *fp = f_open( fileName, "w" );
    int fd = -1;
    int index = -1;
    if (fp)
    {
        // initialize the writer context
        index = getWavWriterCxt();
        if (index < 0 || index > NUM_WAV_WRITERS)
            return fd;
        wavWriterData[index].fp = fp;
        wavWriterData[index].headerWritten = false;
        wavWriterData[index].channels = channels;
        wavWriterData[index].sampleRate = sampleRate;
        wavWriterData[index].dataLen = 0;

        // obtain and register a file descriptor
        fd = GetExtraFD( (void *)&wavWriterData[index], &wavWriter_ioexpand );
        SetWriteAvail( fd ); // allow writing
        ClrDataAvail( fd ); // disallow reading
        ClrHaveError( fd ); // clear errors :P
    }
    
    if (fd >= 0)
        cxtFree[index] = false; // claim the context, if we have a file descriptor

    // write file header
    wavWriteHeader(&wavWriterData[index]);

    return fd;
}


static void InitExtras()
{
   wavWriter_ioexpand.read = wavRead;
   wavWriter_ioexpand.write = wavWrite;
   wavWriter_ioexpand.close = wavClose;

   for (int i = 0; i < NUM_WAV_WRITERS; i++)
   {
       cxtFree[i] = true;
   }

   bInit = TRUE;
}

// obtains a free writer context
static int getWavWriterCxt( )
{
   if ( !bInit )
   {
      InitExtras();
   }
   int index = last_free;
   if ( ( index < 0 ) || ( index > NUM_WAV_WRITERS ) || ( !cxtFree[index] ) )
   {
      index = -1;
      for ( int i = 0; i < NUM_WAV_WRITERS; i++ )
      {
         if ( cxtFree[i] )
         {
            index = i; break;
         }
      }
   }
   if ( index < 0 )
   {
      return -1;
   }
   return index;
}

// releases a writer context
static void freeWavWriterCxt( int fd )
{
    wavWriterCxt *cxt = (wavWriterCxt *)GetExtraData(fd);
    int index = cxt - wavWriterData;
    cxtFree[index] = true;
}

