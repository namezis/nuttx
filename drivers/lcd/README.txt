nuttx/drivers/lcd README
========================

This is the README.txt file for the drivers/lcd/ directory.

Contents
========

  - LCD Header files
    include/nuttx/lcd/lcd.h
    struct lcd_dev_s
  - Binding LCD Drivers
  - Examples: /drivers/lcd/
  - Examples: configs/
  - graphics/

LCD Header files
================

  include/nuttx/lcd/lcd.h

      Structures and APIs needed to work with LCD drivers are provided in
      this header file.  This header file also depends on some of the same
      definitions used for the frame buffer driver as provided in
      include/nuttx/video/fb.h.

  struct lcd_dev_s

      Each LCD device driver must implement an instance of struct lcd_dev_s.
      That structure defines a call table with the following methods:

      - Get information about the LCD video controller configuration and the
        configuration of each LCD color plane.

        int (*getvideoinfo)(FAR struct lcd_dev_s *dev,
                            FAR struct fb_videoinfo_s *vinfo);
        int (*getplaneinfo)(FAR struct lcd_dev_s *dev, unsigned int planeno,
                           FAR struct lcd_planeinfo_s *pinfo);

      - The following are provided only if the video hardware supports RGB
        color mapping:

        int (*getcmap)(FAR struct lcd_dev_s *dev,
                       FAR struct fb_cmap_s *cmap);
        int (*putcmap)(FAR struct lcd_dev_s *dev,
                       FAR const struct fb_cmap_s *cmap);

      - The following are provided only if the video hardware supports a
        hardware cursor:

        int (*getcursor)(FAR struct lcd_dev_s *dev,
                         FAR struct fb_cursorattrib_s *attrib);
        int (*setcursor)(FAR struct lcd_dev_s *dev,
                         FAR struct fb_setcursor_s *settings);

      - Get the LCD panel power status (0: full off - CONFIG_LCD_MAXPOWER:
        full on). On backlit LCDs, this setting may correspond to the
        backlight setting.

        int (*getpower)(struct lcd_dev_s *dev);

      - Enable/disable LCD panel power (0: full off - CONFIG_LCD_MAXPOWER:
        full on). On backlit LCDs, this setting may correspond to the
        backlight setting.

        int (*setpower)(struct lcd_dev_s *dev, int power);

      - Get the current contrast setting (0-CONFIG_LCD_MAXCONTRAST) */

        int (*getcontrast)(struct lcd_dev_s *dev);

     - Set LCD panel contrast (0-CONFIG_LCD_MAXCONTRAST)

        int (*setcontrast)(struct lcd_dev_s *dev, unsigned int contrast);

Binding LCD Drivers
===================

  LCD drivers are not normally directly accessed by user code, but are
  usually bound to another,  higher level device driver. In general, the
  binding sequence is:

  1. Get an instance of struct lcd_dev_s from the hardware-specific LCD
     device driver, and
  2. Provide that instance to the initialization method of the higher
     level device driver.

Examples: /drivers/lcd/
=======================

Re-usable LCD drivers reside in the drivers/lcd directory:

  LCDs:
  ----
  mio283qt2.c. This is a driver for the MI0283QT-2 LCD from Multi-Inno
    Technology Co., Ltd.  This LCD is based on the Himax HX8347-D LCD
    controller.

  mio283qt9a.c.  This is a driver for the MI0283QT-9A LCD from Multi-Inno
    Technology Co., Ltd.  This LCD is based on the Ilitek ILI9341 LCD
    controller.

  nokia6100.c.  Supports the Nokia 6100 display with either the Philips
    PCF883 or the Epson S1D15G10 display controller.  This LCD is used
    with the Olimex LPC1766-STK (but has not been fully integrated).

  ssd12989.c.  Generic LCD driver for LCDs based on the Solomon Systech
    SSD1289 LCD controller. Think of this as a template for an LCD driver
    that you will probably have to customize for any particular LCD
    hardware. (see also configs/hymini-stm32v/src/ssd1289.c below).

  st7567.c.  LCD Display Module, ST7567, Univision Technology Inc. Used
    with the LPCXpresso and Embedded Artists base board.

  memlcd.c.  Sharp Memory LCD Suite, LS013B7DH01, LS013B7DH03, etc.
    There are some more different models, they are basically controlled
    by similar logics, thus this driver can be extended.  Example usage:

  ra8875.c.  RAiO Technologies RA8875 LCD controller.  Contributed by
    Marten Svanfeldt.

  OLEDs:
  -----
  p14201.c.  Driver for RiT P14201 series display with SD1329 IC
    controller.  Based on the SD1329 controller.  This OLED is used with
    older versions of the TI/Luminary LM3S8962 Evaluation Kit.  Example
    usage

      configs/lm3s6965-ek/src
      configs/lm3s8962-ek/src

  ug-2864ambag01.c.  OLED Display Module, UUG-2864AMBAG01, Univision
    Technology Inc.  Based on the SH1101A controller.  Example usage:

      configs/stm32f4discovery
      configs/zp214xp

  ug-9664hswag01.c.  OLED Display Module, UG-9664HSWAG01, Univision
    Technology Inc.  Based on the SSD1305 controller.  Used with the
    LPC Xpresso and Embedded Artists base board.  Example usage:

      configs/lpcxpresso-lpc1768

  ssd1306.c.  OLED Display Modules based on the SSD1306 controllers.
    This includes the UG-2864HSWEG01 and UG2832HSWEG04, Both from Univision
    Technology Inc.  The latter is used with the OLED1 module that comes
    with the Atmel SAM4l Xplained Pro board.  Example usage:

      configs/stm32f4discovery
      configs/sam4l-xplained

  Segment LCDS (SLCDs):
  ---------------------

  pcf8574_lcd_backpack.c:  See pcf8574_lcd_backpack_readme.txt.

Examples: configs/
==================

There are additional LCD drivers in the configs/<board>/src directory
that support additional LCDs.  LCD drivers in the configuration directory
if they support some differ LCD interface (such as a parallel interface)
that makes then less re-usable:

  SSD1289 Drivers:

    configs/hymini-stm32v/src/ssd1289.c.  See also drivers/lcd/ssd1298.c
      above.
    configs/stm32f4discovery/src/stm32_ssd1289.c.  This examples is the
      bottom half for the SSD1289 driver at drivers/lcd/ssd1289.c
    configs/hymini-stm32v/src/ssd1289.c.  See also drivers/lcd/ssd1298.c
      above.
    configs/shenzhou/src/stm32_ssd1289.c

  kwikstik-k40:

    configs/kwikstik-k40/src/k40_lcd.c.  Don't waste your time.  This is
      just a stub.

  Nokia LCD Drivers:

    configs/olimex-lpc1766stk/src/lpc17_lcd.c.  This examples is the
      bottom half for the driver at drivers/lcd/nokia6100.c.
      This was never completely debugged ... there are probably issues
      with that nasty 9-bit SPI interfaces.

  HX8346:

    configs/sam3u-ek/src/sam_lcd.c.  The SAM3U-EK development board features
      a TFT/Transmissive color LCD module with touch-screen, FTM280C12D,
      with integrated driver IC HX8346.

  HX8347:

    configs/pic32mx7mmb/src/pic32_mio283qt2.c.  This driver is for the MI0283QT-2
      LCD from Multi-Inno Technology Co., Ltd. This LCD is based on the Himax
      HX8347-D LCD controller.

  ILI93xx and Similar:

    configs/stm3210e-eval/src/stm32_lcd.c. This driver supports the following
      LCDs:

      1. Ampire AM-240320LTNQW00H
      2. Orise Tech SPFD5408B
      3. RenesasSP R61580

    configs/stm3220g-eval/src/stm32_lcd.c and configs/stm3240g-eval/src/smt32_lcd.c.
      AM-240320L8TNQW00H (LCD_ILI9320 or LCD_ILI9321) and
      AM-240320D5TOQW01H (LCD_ILI9325)

    configs/shenzhou/src/stm32_ili93xx.c. Another ILI93xx driver.
    config/sam4e-ek/src/sam_ili9325.c. ILI9325 driver
    config/sam4e-ek/src/sam_ili9341.c. ILI9341 driver

  ILI9488

    configs/samv71-xult/src/sam_ili9488.c
    include/nuttx/lcd/ili9488.h

  R61505U

    configs/hymini-stm32v/src/stm32_r61505u.c

  Sharp Memory LCD:

    configs/maple/src/stm32_lcd.c

  OLEDs:

    configs/stm32f4discovery/src/stm32_ug2864ambag01.c
    configs/stm32f4discovery/src/stm32_ug2864hsweg01.c
    configs/sam4l-xplained/src/sa,_ug2832hsweg04.c
    configs/zp214xpa/src/lpc2148_ug2864ambag01.c

  LCD controllers built-into the MCU:

    arch/arm/src/lpc17xx/lpc17_lcd.c and configs/open1788/src/lpc17_lcd.c.
      RGB LCD display panel.
    configs/stm32ldiscovery/src/stm32_lcd.c.  1x6 segment LCD with bars
      using the segment LCD controller built-into the STM32L15X.

  Alphnumeric/segment LCD Displays:

    configs/skp16c26/src/m16c_lcd.c.  Untested alphanumeric LCD driver.
    configs/pcblogic-pic32mx/src/pic32mx_lcd1602.c. LCD1602 is based on the
      Hitachi HD44780U LCD controller.  This version of the driver
      uses the PIC32MX PMP interface to control the LCD.  As of this
      writing, has *NOT* been verified (mostly because I get bewildered
      by all of the jumper wires).  See include/nuttx/lcd/hd4478ou.h
      for more information about LCD1602.
    configs/sure-pic32mx/src/pic32_lcd1602.c. Another LCD1602 segment
      LCD.  This is a bit-bang version of the driver and appears to
      be fully functional.  This version of the LCD1602 driver has
      been verified and is working fine.
    configs/stm32ldiscovery/src/stm32_lcd.c.  1x6 segment LCD with bars
      using the segment LCD controller built-into the STM32L15X.

  TFT Panel Drivers:

    configs/open1788/src/lpc17_lcd.c and arch/arm/src/lpc17xx/lpc17_lcd.c
    configs/sama5d3x-ek/src and configs/sama5d4-ek/src: Use
      arch/arm/src/sama5/sam_lcd.c

graphics/
=========

  See also the usage of the LCD driver in the graphics/ directory.
