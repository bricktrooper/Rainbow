#ifndef CONFIG_H
#define CONFIG_H

/*
This file contains settings for the PIC configuration bits.
Please see "documentation/PIC16F15325 Configuration Settings.html" for configuration settings.
*/

// CONFIG1 //

#pragma config FCMEN = OFF       // disable fail-safe clock monitor timer
#pragma config CSWEN = ON        // allow clock settings to be changed by software
#pragma config CLKOUTEN = OFF    // disable clock output on OSC2
#pragma config RSTOSC = HFINT1   // use internal oscillator for 1 MHz clock
#pragma config FEXTOSC = OFF     // disable external oscillator

// CONFIG2 //

#pragma config STVREN = OFF     // do not reset on stack overflow or underflow
#pragma config PPS1WAY = OFF    // allow writing of PPSLOCK repeatedly in software
#pragma config ZCD = OFF        // disable zero-cross detect
#pragma config BORV = HI        // set brownout reset voltage (V_BOR) to 2.7 V
#pragma config BOREN = SBOREN   // enable brownout reset
#pragma config LPBOREN = ON     // enable brownout reset in low-power mode
#pragma config PWRTE = OFF      // disable power-up timer
#pragma config MCLRE = OFF      // disable MCLR reset functionality and use pin as GPIO input

// CONFIG3 //

#pragma config WDTCCS = HFINTOSC   // watchdog input clock is HFINTOSC
#pragma config WDTCWS = WDTCWS_0   // watchdog window
#pragma config WDTE = SWDTEN       // watchdog timer is enabled/disabled by WDTCON0.SWDTEN
#pragma config WDTCPS = WDTCPS_0   // watchdog period

// CONFIG4 //

#pragma config LVP = OFF        // disable low voltage programming
#pragma config WRTSAF = OFF     // disable write protection of storage area flash
#pragma config WRTC = OFF       // disable write protection of configuration register
#pragma config WRTB = OFF       // disable write protection of boot block
#pragma config WRTAPP = OFF     // disable write protection of application block
#pragma config SAFEN = OFF      // disable storage area flash
#pragma config BBEN = OFF       // disable boot block
#pragma config BBSIZE = BB512   // set boot block size to 512 b

// CONFIG5 //

#pragma config CP = OFF   // disable flash memory code protection

#endif // CONFIG_H //
