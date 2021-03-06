/*******************************************************************************
 * configs/indium-f7/src/indium-f7.h
 *
 *   Copyright (C) 2016-2018 Gregory Nutt. All rights reserved.
 *   Authors: Gregory Nutt <gnutt@nuttx.org>
 *            Mark Olsson <post@markolsson.se>
 *            David Sidrane <david_s5@nscdg.com>
 *            Bob Feretich <bob.feretich@rafresearch.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef __CONFIGS_INDIUM_F7_SRC_INDIUM_F7_H
#define __CONFIGS_INDIUM_F7_SRC_INDIUM_F7_H

/*******************************************************************************
 * Included Files
 ******************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <stdint.h>

/*******************************************************************************
 * Pre-processor Definitions
 ******************************************************************************/

/* Configuration **************************************************************/
/* procfs File System */

#ifdef CONFIG_FS_PROCFS
#  ifdef CONFIG_NSH_PROC_MOUNTPOINT
#    define STM32_PROCFS_MOUNTPOINT CONFIG_NSH_PROC_MOUNTPOINT
#  else
#    define STM32_PROCFS_MOUNTPOINT "/proc"
#  endif
#endif

/* Indium F7 GPIO set/reset macro  *********************************************
 *
 * When BOOL == 1, INDIUM_GPIOSR sets the gpio bit specified by the GPR pin
 *   spec.
 * When BOOL == 0, INDIUM_GPIOSR resets the gpio bit specified by the GPR pin
 *   spec.
 *
 * The pin spec is the 20-bit encoding described in
 * arch/arm/src/stm32f7/stm32_gpio.h. For this macro, only the low order 8 bits
 * are used.
 */

#define INDIUM_GPIOSR(GPR, BOOL)  \
  *((uint32_t *)(((GPR & 0x0F0) >> 4) * STM32_GPIO_INCR + STM32_GPIOA_BSRR)) \
  = ((uint32_t)(1 << (16 * (1 - (BOOL & 0x1)) + (GPR & 0x0F))))

/* Indium F7 GPIO Pin Definitions  ********************************************/

#define GPIO_OUTPUT_INIT_TO_0  GPIO_OUTPUT_CLEAR
#define GPIO_OUTPUT_INIT_TO_1  GPIO_OUTPUT_SET

/* Oscillator I/O; When internal oscillators are used and these pins are used for GPIOs */

#define GPIO_OSC32_OUT (GPIO_INPUT | GPIO_FLOAT | GPIO_PORTC | GPIO_PIN15)
#define GPIO_PD_REQ     GPIO_OSC32_OUT
#define GPIO_OSC_IN    (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | \
                        GPIO_OUTPUT_INIT_TO_0 | GPIO_PORTH | GPIO_PIN0)
#define GPIO_VBAT_ENn  GPIO_OSC_IN
#define GPIO_OSC_OUT   (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | \
                        GPIO_OUTPUT_INIT_TO_0 | GPIO_PORTH | GPIO_PIN1)
#define GPIO_LED_RED   GPIO_OSC_OUT

/* LED
 *
 * The Indium-F7 board has three LEDs, LD1 a Green LED, LD2 a Blue LED, and
 * LD3 a Red LED, that can be controlled by software.
 */

/* GPIO_LED_RED is defined above in the Oscillator section. */

#define GPIO_LED_GREEN (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | \
                        GPIO_OUTPUT_INIT_TO_0 | GPIO_PORTC | GPIO_PIN1)
#define GPIO_LED_BLUE  (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | \
                         GPIO_OUTPUT_INIT_TO_0 | GPIO_PORTC | GPIO_PIN6)

#define GPIO_LD1       GPIO_LED_GREEN
#define GPIO_LD2       GPIO_LED_BLUE
#define GPIO_LD3       GPIO_LED_RED

#define LED_DRIVER_PATH "/dev/userleds"

/* SPI ************************************************************************/

#define GPIO_SPI_CS     (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | \
                         GPIO_OUTPUT_INIT_TO_1)
#define GPIO_SPI1_CS0   (GPIO_SPI_CS | GPIO_PORTC | GPIO_PIN13)

#define GPIO_SPI2_CS0   (GPIO_SPI_CS | GPIO_PORTB | GPIO_PIN1)
#define GPIO_SPI2_CS1   (GPIO_SPI_CS | GPIO_PORTB | GPIO_PIN12)
#define GPIO_SPI2_CS2   (GPIO_SPI_CS | GPIO_PORTA | GPIO_PIN8)
#define GPIO_SPI2_CS3   (GPIO_SPI_CS | GPIO_PORTA | GPIO_PIN4)

#define SPI_CS_EXT         GPIO_SPI1_CS0
#define SPI_CS_LSM330_ACL  GPIO_SPI2_CS0
#define SPI_CS_LSM330_GYRO GPIO_SPI2_CS1
#define SPI_CS_ADXL372     GPIO_SPI2_CS2
#define SPI_CS_FRAM        GPIO_SPI2_CS3

/* Logical SPI Chip Selects (aka devid) used to index g_spigpio */

#define INDIUM_EXTSPI_IDX_CS0     0
#define INDIUM_LSM330ACL_IDX_CS0  1
#define INDIUM_LSM330GYRO_IDX_CS1 2
#define INDIUM_ADXL372_IDX_CS2    3
#define INDIUM_FRAM_IDX_CS3       4

#if defined(CONFIG_STM32F7_SDMMC1) || defined(CONFIG_STM32F7_SDMMC2)
# define HAVE_SDIO
#endif

#if defined(CONFIG_DISABLE_MOUNTPOINT) || !defined(CONFIG_MMCSD_SDIO)
#  undef HAVE_SDIO
#endif

#define SDIO_SLOTNO 0  /* Only one slot */

#ifdef HAVE_SDIO

#  if defined(CONFIG_STM32F7_SDMMC1)
#    define GPIO_SDMMC1_NCD (GPIO_INPUT|GPIO_FLOAT|GPIO_EXTI | GPIO_PORTC | GPIO_PIN7)
#  endif

#  if defined(CONFIG_NSH_MMCSDSLOTNO) && (CONFIG_NSH_MMCSDSLOTNO != 0)
#    warning "Only one MMC/SD slot, slot 0"
#    define CONFIG_NSH_MMCSDSLOTNO SDIO_SLOTNO
#  endif

#  if defined(CONFIG_NSH_MMCSDMINOR)
#    define SDIO_MINOR CONFIG_NSH_MMCSDMINOR
#  else
#    define SDIO_MINOR 0
#  endif

/* SD card bringup does not work if performed on the IDLE thread because it
 * will cause waiting.  Use either:
 *
 *  CONFIG_LIB_BOARDCTL=y, OR
 *  CONFIG_BOARD_INITIALIZE=y && CONFIG_BOARD_INITTHREAD=y
 */

#  if defined(CONFIG_BOARD_INITIALIZE) && !defined(CONFIG_LIB_BOARDCTL) && \
     !defined(CONFIG_BOARD_INITTHREAD)
#    warning SDIO initialization cannot be perfomed on the IDLE thread
#    undef HAVE_SDIO
#  endif
#endif

/* General GPIO Definitions */
/* define GPIO_VBAT_ENn is defined in oscillator section. */
/* define GPIO_PD_REQ is defined in oscillator section. */

#define GPIO_PWR_HOLD   (GPIO_PORTC | GPIO_PIN14 | GPIO_OUTPUT_INIT_TO_0 | \
                         GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_FLOAT | GPIO_SPEED_2MHz)
#define GPIO_B5         (GPIO_PORTB | GPIO_PIN5 | GPIO_OUTPUT_INIT_TO_0 | \
                         GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_FLOAT | GPIO_SPEED_2MHz)
#define GPIO_FWENB      (GPIO_PORTB | GPIO_PIN0 | GPIO_OUTPUT_INIT_TO_0 | \
                         GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_PULLDOWN | GPIO_SPEED_50MHz)
#define GPIO_EXT_RSTn   (GPIO_PORTC | GPIO_PIN3 | GPIO_OUTPUT_INIT_TO_1 | \
                         GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_PULLDOWN | GPIO_SPEED_50MHz)
#define GPIO_INTA       (GPIO_INPUT | GPIO_PORTB | GPIO_PIN2 | GPIO_PULLDOWN)
#define GPIO_EXT_DIO    (GPIO_INPUT | GPIO_PORTC | GPIO_PIN2 | GPIO_PULLDOWN)

/* Analog Inputs */

#define GPIO_EXT_ADC    (GPIO_ANALOG | GPIO_PORTC | GPIO_PIN4)
#define GPIO_BATT_ADC   (GPIO_ANALOG | GPIO_PORTC | GPIO_PIN0)

/*******************************************************************************
 * Public data
 ******************************************************************************/

#ifndef __ASSEMBLY__

/*******************************************************************************
 * Public Functions
 ******************************************************************************/

/*******************************************************************************
 * Name: stm32_spidev_initialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the Indium-F7 board.
 *
 ******************************************************************************/

#if defined(CONFIG_SPI)
void stm32_spidev_initialize(void);

/*******************************************************************************
 * Name: board_driver_initialize
 *
 * Description:
 *   Called to register platform drivers on the Indium board.
 *
 ******************************************************************************/

# if defined(CONFIG_BOARD_INITIALIZE)
int board_spi_initialize(void);
# endif
#endif

/*******************************************************************************
 * Name: stm32_spidev_bus_test
 *
 * Description:
 *   Called to create the defined SPI buses and test them by initializing them
 *   and sending the NUCLEO_SPI_TEST (no chip select).
 *
 ******************************************************************************/

#if defined(CONFIG_NUCLEO_SPI_TEST)
int stm32_spidev_bus_test(void);
#endif

/*******************************************************************************
 * Name: board_i2c_initialize
 *
 * Description:
 *   Called to configure I2C buses.
 *
 ******************************************************************************/

#if defined(CONFIG_I2C)
int board_i2c_initialize(void);
#endif

/*******************************************************************************
 * Name: stm32_adc_setup
 *
 * Description:
 *   Called to configure Analog to Digital Converters.
 *
 ******************************************************************************/

#if defined(CONFIG_STM32F7_ADC)
int stm32_adc_setup(void);
#endif

/*******************************************************************************
 * Name: stm32_adc_indium_setup
 *
 * Description:
 *   Called to modify the standard configuration of the Analog to Digital Converters.
 *
 ******************************************************************************/

#if defined(CONFIG_STM32F7_ADC)
void stm32_adc_indium_setup(void);
#endif

/*******************************************************************************
 * Name: stm32_dma_alloc_init
 *
 * Description:
 *   Called to create a FAT DMA allocator
 *
 * Returned Value:
 *   0 on success or -ENOMEM
 *
 ******************************************************************************/

void stm32_dma_alloc_init(void);

#if defined (CONFIG_FAT_DMAMEMORY)
int stm32_dma_alloc_init(void);
#endif

/******************************************************************************
 * Name: stm32_sdio_initialize
 *
 * Description:
 *   Called at application startup time to initialize the SCMMC functionality.
 *
 ******************************************************************************/

#ifdef CONFIG_MMCSD
int stm32_sdio_initialize(void);
#endif

/*******************************************************************************
 * Name: stm32_usbinitialize
 *
 * Description:
 *   Called from stm32_usbinitialize very early in initialization to setup
 *   USB-related GPIO pins for the indium-f7 board.
 *
 ******************************************************************************/

#ifdef CONFIG_STM32F7_OTGFS
void stm32_usbinitialize(void);
#endif

/*******************************************************************************
 * Name: stm32_adc_setup
 *
 * Description:
 *   Initialize ADC and register the ADC driver.
 *
 ******************************************************************************/

#ifdef CONFIG_ADC
int stm32_adc_setup(void);
#endif

/*******************************************************************************
 * Name: stm32_bbsram_int
 ******************************************************************************/

#ifdef CONFIG_STM32F7_BBSRAM
int stm32_bbsram_int(void);
#endif

#endif /* __ASSEMBLY__ */
#endif /* __CONFIGS_INDIUM_F7_SRC_INDIUM_F7 */
