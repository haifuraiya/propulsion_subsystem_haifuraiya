#!/bin/bash
#Fri Aug 30 10:00:43 EDT 2013 samudra@gwu.edu
#shell script fragment to pre-process the RD532-MAPERS-2.txt data file from MCATPE 8/2013 GWU/NASA ARC
Prefix=RD532-MAPERS-2.txt
Input=$Prefix
Data=CSV_$Prefix
Header=HDR_$Prefix
Text=TXT_$Prefix
#delete previous files
cat /dev/null >  $Data
cat /dev/null >  $Header
cat /dev/null >  $Text
#make plain text version of  original source file
awk 'BEGIN { RS="\r"} {print $0}' $Input > $Text
#parse ^M as record separator and printout out all records, then strip the 11 preamble lines to have only the data 
awk 'BEGIN { RS="\r"} {print $0}' $Input | sed '1,11d' |awk {'printf("%s,%s,%s,%s\n",$8,$1,$2,$3)'}> $Data
echo "Processed source data file ... $Input"
echo "Wrote CSV processed data file ... $Data" 
echo "(`wc -l $Data` records)"
awk ' BEGIN {RS ="\r"} {if (FNR < 11) print $0}' $Input > $Header
echo "Wrote Headers into $Header"
echo "(`wc -l $Header`)"
