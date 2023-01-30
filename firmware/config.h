#ifndef CONFIG_H
#define CONFIG_H

/*
This file contains settings for the PIC configuration bits.
Please see docs/pic16f690.html for configuration settings.
*/

// CONFIG1 //

#pragma config FCMEN    = OFF      // Disable fail-safe clock monitor timer.
#pragma config CSWEN    = OFF      // Disable clock switching.
#pragma config CLKOUTEN = OFF      // Disable clock output on OSC2.
#pragma config RSTOSC   = HFINT1   // Use internal oscillator for 1 MHz clock.
#pragma config FEXTOSC = OFF       // Disable external oscillator.

// CONFIG2 //

#pragma config STVREN = OFF     // Do not reset on stack overflow or underflow.
#pragma config PPS1WAY = OFF    // Allow writing of PPSLOCK repeatedly in software.
#pragma config ZCD = OFF        // Disable zero-cross detect.
#pragma config BORV = HI        // Set brownout reset voltage (V_BOR) to 2.7 V.
#pragma config BOREN = SBOREN   // Enable brownout reset.
#pragma config LPBOREN = ON     // Enable brownout reset in low-power mode.
#pragma config PWRTE = OFF      // Disable power-up timer.
#pragma config MCLRE = OFF      // Disable MCLR reset functionality and use pin as GPIO input.

// CONFIG3 //

#pragma config WDTCCS = HFINTOSC   // Watchdog input clock is HFINTOSC.
#pragma config WDTCWS = WDTCWS_0   // Watchdog window.
#pragma config WDTE = SWDTEN       // Watchdog timer is enabled/disabled by WDTCON0.SWDTEN.
#pragma config WDTCPS = WDTCPS_0   // Watchdog period.

// CONFIG4 //

#pragma config LVP = OFF        // Disable low voltage programming.
#pragma config WRTSAF = OFF     // Disable write protection of storage area flash.
#pragma config WRTC = OFF       // Disable write protection of configuration register.
#pragma config WRTB = OFF       // Disable write protection of boot block.
#pragma config WRTAPP = OFF     // Disable write protection of application block.
#pragma config SAFEN = OFF      // Disable storage area flash.
#pragma config BBEN = OFF       // Disable boot block.
#pragma config BBSIZE = BB512   // Set boot block size to 512 b.

// CONFIG5 //

#pragma config CP = OFF   // Disable flash memory code protection.

#endif // CONFIG_H //
