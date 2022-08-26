#ifndef  __PERIPH_CLOCKS_H
#define  __PERIPH_CLOCKS_H

#include <sim5441x.h>

// Peripheral Power Management Low Register 0
#define PERIPH_CLOCK_FLEXBUS            2
#define PERIPH_CLOCK_CAN_0              8
#define PERIPH_CLOCK_CAN_1              9
#define PERIPH_CLOCK_I2C_1              14
#define PERIPH_CLOCK_DSPI_1             15
#define PERIPH_CLOCK_DMA                17
#define PERIPH_CLOCK_INTC_0             18
#define PERIPH_CLOCK_INTC_1             19
#define PERIPH_CLOCK_INTC_2             20
#define PERIPH_CLOCK_I2C_0              22
#define PERIPH_CLOCK_DSPI_0             23
#define PERIPH_CLOCK_UART_0             24
#define PERIPH_CLOCK_UART_1             25
#define PERIPH_CLOCK_UART_2             26
#define PERIPH_CLOCK_UART_3             27
#define PERIPH_CLOCK_DMA_TMR_0          28
#define PERIPH_CLOCK_DMA_TMR_1          29
#define PERIPH_CLOCK_DMA_TMR_2          30
#define PERIPH_CLOCK_DMA_TMR_3          31

// Peripheral Power Management High Register 0
#define PERIPH_CLOCK_PIT_0              32
#define PERIPH_CLOCK_PIT_1              33
#define PERIPH_CLOCK_PIT_2              34
#define PERIPH_CLOCK_PIT_3              35
#define PERIPH_CLOCK_EDGE_PORT          36
#define PERIPH_CLOCK_ADC                37
#define PERIPH_CLOCK_DAC_0              38
#define PERIPH_CLOCK_RTC                42
#define PERIPH_CLOCK_SIM                43
#define PERIPH_CLOCK_USB_OTG            44
#define PERIPH_CLOCK_USB_HOST           45
#define PERIPH_CLOCK_DDR                46
#define PERIPH_CLOCK_SSI_0              47
#define PERIPH_CLOCK_PLL                48
#define PERIPH_CLOCK_RNG                49
#define PERIPH_CLOCK_SSI_1              50
#define PERIPH_CLOCK_SDHC               52
#define PERIPH_CLOCK_MACNET_0           53
#define PERIPH_CLOCK_MACNET_1           54
#define PERIPH_CLOCK_ETHERNET_SWITCH_0  55
#define PERIPH_CLOCK_ETHERNET_SWITCH_1  56
#define PERIPH_CLOCK_NAND_FLASH         63

// Peripheral Power Management High Register 1
#define PERIPH_CLOCK_PWM                34
#define PERIPH_CLOCK_CCM_RESET          36
#define PERIPH_CLOCK_GPIO               37

// Peripheral Power Management Low Register 1
#define PERIPH_CLOCK_1_WIRE             2
#define PERIPH_CLOCK_I2C_2              4
#define PERIPH_CLOCK_I2C_3              5
#define PERIPH_CLOCK_I2C_4              6
#define PERIPH_CLOCK_I2C_5              7
#define PERIPH_CLOCK_DSPI_2             14
#define PERIPH_CLOCK_DSPI_3             15
#define PERIPH_CLOCK_UART_4             24
#define PERIPH_CLOCK_UART_5             25
#define PERIPH_CLOCK_UART_6             26
#define PERIPH_CLOCK_UART_7             27
#define PERIPH_CLOCK_UART_8             28
#define PERIPH_CLOCK_UART_9             29

// Disable clocks in Power Management Low Register 0
#define PERIPH_DISABLE_FLEXBUS          sim2.scm.ppmsr0 = PERIPH_CLOCK_FLEXBUS
#define PERIPH_DISABLE_CAN_0            sim2.scm.ppmsr0 = PERIPH_CLOCK_CAN_0
#define PERIPH_DISABLE_CAN_1            sim2.scm.ppmsr0 = PERIPH_CLOCK_CAN_1
#define PERIPH_DISABLE_I2C_1            sim2.scm.ppmsr0 = PERIPH_CLOCK_I2C_1
#define PERIPH_DISABLE_DSPI_1           sim2.scm.ppmsr0 = PERIPH_CLOCK_DSPI_1
#define PERIPH_DISABLE_DMA              sim2.scm.ppmsr0 = PERIPH_CLOCK_DMA
#define PERIPH_DISABLE_INTC_0           sim2.scm.ppmsr0 = PERIPH_CLOCK_INTC_0
#define PERIPH_DISABLE_INTC_1           sim2.scm.ppmsr0 = PERIPH_CLOCK_INTC_1
#define PERIPH_DISABLE_INTC_2           sim2.scm.ppmsr0 = PERIPH_CLOCK_INTC_2
#define PERIPH_DISABLE_I2C_0            sim2.scm.ppmsr0 = PERIPH_CLOCK_I2C_0
#define PERIPH_DISABLE_DSPI_0           sim2.scm.ppmsr0 = PERIPH_CLOCK_DSPI_0
#define PERIPH_DISABLE_UART_0           sim2.scm.ppmsr0 = PERIPH_CLOCK_UART_0
#define PERIPH_DISABLE_UART_1           sim2.scm.ppmsr0 = PERIPH_CLOCK_UART_1
#define PERIPH_DISABLE_UART_2           sim2.scm.ppmsr0 = PERIPH_CLOCK_UART_2
#define PERIPH_DISABLE_UART_3           sim2.scm.ppmsr0 = PERIPH_CLOCK_UART_3
#define PERIPH_DISABLE_DMA_TMR_0        sim2.scm.ppmsr0 = PERIPH_CLOCK_DMA_TMR_0
#define PERIPH_DISABLE_DMA_TMR_1        sim2.scm.ppmsr0 = PERIPH_CLOCK_DMA_TMR_1
#define PERIPH_DISABLE_DMA_TMR_2        sim2.scm.ppmsr0 = PERIPH_CLOCK_DMA_TMR_2

// Enable clocks in Power Management Low Register 0
#define PERIPH_ENABLE_FLEXBUS           sim2.scm.ppmcr0 = PERIPH_CLOCK_FLEXBUS
#define PERIPH_ENABLE_CAN_0             sim2.scm.ppmcr0 = PERIPH_CLOCK_CAN_0
#define PERIPH_ENABLE_CAN_1             sim2.scm.ppmcr0 = PERIPH_CLOCK_CAN_1
#define PERIPH_ENABLE_I2C_1             sim2.scm.ppmcr0 = PERIPH_CLOCK_I2C_1
#define PERIPH_ENABLE_DSPI_1            sim2.scm.ppmcr0 = PERIPH_CLOCK_DSPI_1
#define PERIPH_ENABLE_DMA               sim2.scm.ppmcr0 = PERIPH_CLOCK_DMA
#define PERIPH_ENABLE_INTC_0            sim2.scm.ppmcr0 = PERIPH_CLOCK_INTC_0
#define PERIPH_ENABLE_INTC_1            sim2.scm.ppmcr0 = PERIPH_CLOCK_INTC_1
#define PERIPH_ENABLE_INTC_2            sim2.scm.ppmcr0 = PERIPH_CLOCK_INTC_2
#define PERIPH_ENABLE_I2C_0             sim2.scm.ppmcr0 = PERIPH_CLOCK_I2C_0
#define PERIPH_ENABLE_DSPI_0            sim2.scm.ppmcr0 = PERIPH_CLOCK_DSPI_0
#define PERIPH_ENABLE_UART_0            sim2.scm.ppmcr0 = PERIPH_CLOCK_UART_0
#define PERIPH_ENABLE_UART_1            sim2.scm.ppmcr0 = PERIPH_CLOCK_UART_1
#define PERIPH_ENABLE_UART_2            sim2.scm.ppmcr0 = PERIPH_CLOCK_UART_2
#define PERIPH_ENABLE_UART_3            sim2.scm.ppmcr0 = PERIPH_CLOCK_UART_3
#define PERIPH_ENABLE_DMA_TMR_0         sim2.scm.ppmcr0 = PERIPH_CLOCK_DMA_TMR_0
#define PERIPH_ENABLE_DMA_TMR_1         sim2.scm.ppmcr0 = PERIPH_CLOCK_DMA_TMR_1
#define PERIPH_ENABLE_DMA_TMR_2         sim2.scm.ppmcr0 = PERIPH_CLOCK_DMA_TMR_2

// Disable clocks in Power Management High Register 0
#define PERIPH_DISABLE_PIT_0            sim2.scm.ppmsr0 = PERIPH_CLOCK_PIT_0
#define PERIPH_DISABLE_PIT_1            sim2.scm.ppmsr0 = PERIPH_CLOCK_PIT_1
#define PERIPH_DISABLE_PIT_2            sim2.scm.ppmsr0 = PERIPH_CLOCK_PIT_2
#define PERIPH_DISABLE_PIT_3            sim2.scm.ppmsr0 = PERIPH_CLOCK_PIT_3
#define PERIPH_DISABLE_EDGE_PORT        sim2.scm.ppmsr0 = PERIPH_CLOCK_EDGE_PORT
#define PERIPH_DISABLE_ADC              sim2.scm.ppmsr0 = PERIPH_CLOCK_ADC
#define PERIPH_DISABLE_DAC_0            sim2.scm.ppmsr0 = PERIPH_CLOCK_DAC_0
#define PERIPH_DISABLE_RTC              sim2.scm.ppmsr0 = PERIPH_CLOCK_RTC
#define PERIPH_DISABLE_SIM              sim2.scm.ppmsr0 = PERIPH_CLOCK_SIM
#define PERIPH_DISABLE_USB_OTG          sim2.scm.ppmsr0 = PERIPH_CLOCK_USB_OTG
#define PERIPH_DISABLE_USB_HOST         sim2.scm.ppmsr0 = PERIPH_CLOCK_USB_HOST
#define PERIPH_DISABLE_DDR              sim2.scm.ppmsr0 = PERIPH_CLOCK_DDR
#define PERIPH_DISABLE_SSI_0            sim2.scm.ppmsr0 = PERIPH_CLOCK_SSI_0
#define PERIPH_DISABLE_PLL              sim2.scm.ppmsr0 = PERIPH_CLOCK_PLL
#define PERIPH_DISABLE_RNG              sim2.scm.ppmsr0 = PERIPH_CLOCK_RNG
#define PERIPH_DISABLE_SSI_1            sim2.scm.ppmsr0 = PERIPH_CLOCK_SSI_1
#define PERIPH_DISABLE_SDHC             sim2.scm.ppmsr0 = PERIPH_CLOCK_SDHC
#define PERIPH_DISABLE_MACNET_0         sim2.scm.ppmsr0 = PERIPH_CLOCK_MACNET_0
#define PERIPH_DISABLE_MACNET_1         sim2.scm.ppmsr0 = PERIPH_CLOCK_MACNET_1
#define PERIPH_DISABLE_ETHERNET_SWITCH_0  sim2.scm.ppmsr0 = PERIPH_CLOCK_ETHERNET_SWITCH_0
#define PERIPH_DISABLE_ETHERNET_SWITCH_1  sim2.scm.ppmsr0 = PERIPH_CLOCK_ETHERNET_SWITCH_1
#define PERIPH_DISABLE_NAND_FLASH       sim2.scm.ppmsr0 = PERIPH_CLOCK_NAND_FLASH

// Enable clocks in Power Management High Register 0
#define PERIPH_ENABLE_PIT_0             sim2.scm.ppmcr0 = PERIPH_CLOCK_PIT_0
#define PERIPH_ENABLE_PIT_1             sim2.scm.ppmcr0 = PERIPH_CLOCK_PIT_1
#define PERIPH_ENABLE_PIT_2             sim2.scm.ppmcr0 = PERIPH_CLOCK_PIT_2
#define PERIPH_ENABLE_PIT_3             sim2.scm.ppmcr0 = PERIPH_CLOCK_PIT_3
#define PERIPH_ENABLE_EDGE_PORT         sim2.scm.ppmcr0 = PERIPH_CLOCK_EDGE_PORT
#define PERIPH_ENABLE_ADC               sim2.scm.ppmcr0 = PERIPH_CLOCK_ADC
#define PERIPH_ENABLE_DAC_0             sim2.scm.ppmcr0 = PERIPH_CLOCK_DAC_0
#define PERIPH_ENABLE_RTC               sim2.scm.ppmcr0 = PERIPH_CLOCK_RTC
#define PERIPH_ENABLE_SIM               sim2.scm.ppmcr0 = PERIPH_CLOCK_SIM
#define PERIPH_ENABLE_USB_OTG           sim2.scm.ppmcr0 = PERIPH_CLOCK_USB_OTG
#define PERIPH_ENABLE_USB_HOST          sim2.scm.ppmcr0 = PERIPH_CLOCK_USB_HOST
#define PERIPH_ENABLE_DDR               sim2.scm.ppmcr0 = PERIPH_CLOCK_DDR
#define PERIPH_ENABLE_SSI_0             sim2.scm.ppmcr0 = PERIPH_CLOCK_SSI_0
#define PERIPH_ENABLE_PLL               sim2.scm.ppmcr0 = PERIPH_CLOCK_PLL
#define PERIPH_ENABLE_RNG               sim2.scm.ppmcr0 = PERIPH_CLOCK_RNG
#define PERIPH_ENABLE_SSI_1             sim2.scm.ppmcr0 = PERIPH_CLOCK_SSI_1
#define PERIPH_ENABLE_SDHC              sim2.scm.ppmcr0 = PERIPH_CLOCK_SDHC
#define PERIPH_ENABLE_MACNET_0          sim2.scm.ppmcr0 = PERIPH_CLOCK_MACNET_0
#define PERIPH_ENABLE_MACNET_1          sim2.scm.ppmcr0 = PERIPH_CLOCK_MACNET_1
#define PERIPH_ENABLE_ETHERNET_SWITCH_0   sim2.scm.ppmcr0 = PERIPH_CLOCK_ETHERNET_SWITCH_0
#define PERIPH_ENABLE_ETHERNET_SWITCH_1   sim2.scm.ppmcr0 = PERIPH_CLOCK_ETHERNET_SWITCH_1
#define PERIPH_ENABLE_NAND_FLASH        sim2.scm.ppmcr0 = PERIPH_CLOCK_NAND_FLASH

// Disable clocks in Power Management Low Register 1
#define PERIPH_DISABLE_1_WIRE           sim2.scm.ppmsr1 = PERIPH_CLOCK_1_WIRE
#define PERIPH_DISABLE_I2C_2            sim2.scm.ppmsr1 = PERIPH_CLOCK_I2C_2
#define PERIPH_DISABLE_I2C_3            sim2.scm.ppmsr1 = PERIPH_CLOCK_I2C_3
#define PERIPH_DISABLE_I2C_4            sim2.scm.ppmsr1 = PERIPH_CLOCK_I2C_4
#define PERIPH_DISABLE_I2C_5            sim2.scm.ppmsr1 = PERIPH_CLOCK_I2C_5
#define PERIPH_DISABLE_DSPI_2           sim2.scm.ppmsr1 = PERIPH_CLOCK_DSPI_2
#define PERIPH_DISABLE_DSPI_3           sim2.scm.ppmsr1 = PERIPH_CLOCK_DSPI_3
#define PERIPH_DISABLE_UART_4           sim2.scm.ppmsr1 = PERIPH_CLOCK_UART_4
#define PERIPH_DISABLE_UART_5           sim2.scm.ppmsr1 = PERIPH_CLOCK_UART_5
#define PERIPH_DISABLE_UART_6           sim2.scm.ppmsr1 = PERIPH_CLOCK_UART_6
#define PERIPH_DISABLE_UART_7           sim2.scm.ppmsr1 = PERIPH_CLOCK_UART_7
#define PERIPH_DISABLE_UART_8           sim2.scm.ppmsr1 = PERIPH_CLOCK_UART_8
#define PERIPH_DISABLE_UART_9           sim2.scm.ppmsr1 = PERIPH_CLOCK_UART_9

// Enable clocks in Power Management Low Register 1
#define PERIPH_ENABLE_1_WIRE            sim2.scm.ppmcr1 = PERIPH_CLOCK_1_WIRE
#define PERIPH_ENABLE_I2C_2             sim2.scm.ppmcr1 = PERIPH_CLOCK_I2C_2
#define PERIPH_ENABLE_I2C_3             sim2.scm.ppmcr1 = PERIPH_CLOCK_I2C_3
#define PERIPH_ENABLE_I2C_4             sim2.scm.ppmcr1 = PERIPH_CLOCK_I2C_4
#define PERIPH_ENABLE_I2C_5             sim2.scm.ppmcr1 = PERIPH_CLOCK_I2C_5
#define PERIPH_ENABLE_DSPI_2            sim2.scm.ppmcr1 = PERIPH_CLOCK_DSPI_2
#define PERIPH_ENABLE_DSPI_3            sim2.scm.ppmcr1 = PERIPH_CLOCK_DSPI_3
#define PERIPH_ENABLE_UART_4            sim2.scm.ppmcr1 = PERIPH_CLOCK_UART_4
#define PERIPH_ENABLE_UART_5            sim2.scm.ppmcr1 = PERIPH_CLOCK_UART_5
#define PERIPH_ENABLE_UART_6            sim2.scm.ppmcr1 = PERIPH_CLOCK_UART_6
#define PERIPH_ENABLE_UART_7            sim2.scm.ppmcr1 = PERIPH_CLOCK_UART_7
#define PERIPH_ENABLE_UART_8            sim2.scm.ppmcr1 = PERIPH_CLOCK_UART_8
#define PERIPH_ENABLE_UART_9            sim2.scm.ppmcr1 = PERIPH_CLOCK_UART_9

// Disable clocks in Power Management High Register 1
#define PERIPH_DISABLE_PWM              sim2.scm.ppmsr1 = PERIPH_CLOCK_PWM
#define PERIPH_DISABLE_CCM_RESET        sim2.scm.ppmsr1 = PERIPH_CLOCK_CCM_RESET
#define PERIPH_DISABLE_GPIO             sim2.scm.ppmsr1 = PERIPH_CLOCK_GPIO

// Enable clocks in Power Management High Register 1
#define PERIPH_ENABLE_PWM               sim2.scm.ppmcr1 = PERIPH_CLOCK_PWM
#define PERIPH_ENABLE_CCM_RESET         sim2.scm.ppmcr1 = PERIPH_CLOCK_CCM_RESET
#define PERIPH_ENABLE_GPIO              sim2.scm.ppmcr1 = PERIPH_CLOCK_GPIO


#endif   /* ----- #ifndef __PERIPH_CLOCKS_H  ----- */
