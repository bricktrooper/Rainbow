subtitle "Microchip MPLAB XC8 C Compiler v2.36 (Free license) build 20220127204148 Og1 "

pagewidth 120

	opt flic

	processor	16F15325
include "/Applications/microchip/xc8/v2.36/pic/include/proc/16f15325.cgen.inc"
getbyte	macro	val,pos
	(((val) >> (8 * pos)) and 0xff)
endm
byte0	macro	val
	(getbyte(val,0))
endm
byte1	macro	val
	(getbyte(val,1))
endm
byte2	macro	val
	(getbyte(val,2))
endm
byte3	macro	val
	(getbyte(val,3))
endm
byte4	macro	val
	(getbyte(val,4))
endm
byte5	macro	val
	(getbyte(val,5))
endm
byte6	macro	val
	(getbyte(val,6))
endm
byte7	macro	val
	(getbyte(val,7))
endm
getword	macro	val,pos
	(((val) >> (8 * pos)) and 0xffff)
endm
word0	macro	val
	(getword(val,0))
endm
word1	macro	val
	(getword(val,2))
endm
word2	macro	val
	(getword(val,4))
endm
word3	macro	val
	(getword(val,6))
endm
gettword	macro	val,pos
	(((val) >> (8 * pos)) and 0xffffff)
endm
tword0	macro	val
	(gettword(val,0))
endm
tword1	macro	val
	(gettword(val,3))
endm
tword2	macro	val
	(gettword(val,6))
endm
getdword	macro	val,pos
	(((val) >> (8 * pos)) and 0xffffffff)
endm
dword0	macro	val
	(getdword(val,0))
endm
dword1	macro	val
	(getdword(val,4))
endm
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
pushw	macro
	movwi fsr1++
	endm
popw	macro
	moviw --fsr1
	endm
# 111 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
INDF0 equ 00h ;# 
# 131 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
INDF1 equ 01h ;# 
# 151 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PCL equ 02h ;# 
# 171 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
STATUS equ 03h ;# 
# 234 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
FSR0L equ 04h ;# 
# 254 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
FSR0H equ 05h ;# 
# 278 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
FSR1L equ 06h ;# 
# 298 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
FSR1H equ 07h ;# 
# 318 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
BSR equ 08h ;# 
# 376 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
WREG equ 09h ;# 
# 396 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PCLATH equ 0Ah ;# 
# 416 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
INTCON equ 0Bh ;# 
# 449 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PORTA equ 0Ch ;# 
# 499 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PORTC equ 0Eh ;# 
# 549 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TRISA equ 012h ;# 
# 594 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TRISC equ 014h ;# 
# 644 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
LATA equ 018h ;# 
# 689 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
LATC equ 01Ah ;# 
# 739 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ADRES equ 09Bh ;# 
# 746 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ADRESL equ 09Bh ;# 
# 816 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ADRESH equ 09Ch ;# 
# 886 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ADCON0 equ 09Dh ;# 
# 957 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ADCON1 equ 09Eh ;# 
# 1023 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ADACT equ 09Fh ;# 
# 1075 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RC1REG equ 0119h ;# 
# 1080 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RCREG equ 0119h ;# 
# 1084 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RCREG1 equ 0119h ;# 
# 1129 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TX1REG equ 011Ah ;# 
# 1134 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TXREG1 equ 011Ah ;# 
# 1138 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TXREG equ 011Ah ;# 
# 1183 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SP1BRG equ 011Bh ;# 
# 1190 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SP1BRGL equ 011Bh ;# 
# 1195 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SPBRG equ 011Bh ;# 
# 1199 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SPBRG1 equ 011Bh ;# 
# 1203 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SPBRGL equ 011Bh ;# 
# 1260 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SP1BRGH equ 011Ch ;# 
# 1265 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SPBRGH equ 011Ch ;# 
# 1269 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SPBRGH1 equ 011Ch ;# 
# 1314 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RC1STA equ 011Dh ;# 
# 1319 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RCSTA1 equ 011Dh ;# 
# 1323 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RCSTA equ 011Dh ;# 
# 1494 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TX1STA equ 011Eh ;# 
# 1499 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TXSTA1 equ 011Eh ;# 
# 1503 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TXSTA equ 011Eh ;# 
# 1674 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
BAUD1CON equ 011Fh ;# 
# 1679 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
BAUDCON1 equ 011Fh ;# 
# 1683 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
BAUDCTL1 equ 011Fh ;# 
# 1687 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
BAUDCON equ 011Fh ;# 
# 1691 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
BAUDCTL equ 011Fh ;# 
# 1920 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SSP1BUF equ 018Ch ;# 
# 1940 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SSP1ADD equ 018Dh ;# 
# 2060 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SSP1MSK equ 018Eh ;# 
# 2130 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SSP1STAT equ 018Fh ;# 
# 2494 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SSP1CON1 equ 0190h ;# 
# 2614 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SSP1CON2 equ 0191h ;# 
# 2801 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SSP1CON3 equ 0192h ;# 
# 2863 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TMR1 equ 020Ch ;# 
# 2870 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TMR1L equ 020Ch ;# 
# 3040 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TMR1H equ 020Dh ;# 
# 3160 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T1CON equ 020Eh ;# 
# 3256 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T1GCON equ 020Fh ;# 
# 3261 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PR1 equ 020Fh ;# 
# 3452 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T1GATE equ 0210h ;# 
# 3457 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TMR1GATE equ 0210h ;# 
# 3618 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T1CLK equ 0211h ;# 
# 3623 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TMR1CLK equ 0211h ;# 
# 3760 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T2TMR equ 028Ch ;# 
# 3765 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TMR2 equ 028Ch ;# 
# 3814 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T2PR equ 028Dh ;# 
# 3819 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PR2 equ 028Dh ;# 
# 3868 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T2CON equ 028Eh ;# 
# 4014 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T2HLT equ 028Fh ;# 
# 4142 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T2CLKCON equ 0290h ;# 
# 4222 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T2RST equ 0291h ;# 
# 4302 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCPR1 equ 030Ch ;# 
# 4309 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCPR1L equ 030Ch ;# 
# 4329 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCPR1H equ 030Dh ;# 
# 4349 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCP1CON equ 030Eh ;# 
# 4467 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCP1CAP equ 030Fh ;# 
# 4535 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCPR2 equ 0310h ;# 
# 4542 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCPR2L equ 0310h ;# 
# 4562 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCPR2H equ 0311h ;# 
# 4582 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCP2CON equ 0312h ;# 
# 4700 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCP2CAP equ 0313h ;# 
# 4768 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM3DC equ 0314h ;# 
# 4775 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM3DCL equ 0314h ;# 
# 4841 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM3DCH equ 0315h ;# 
# 5011 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM3CON equ 0316h ;# 
# 5067 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM4DC equ 0318h ;# 
# 5074 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM4DCL equ 0318h ;# 
# 5140 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM4DCH equ 0319h ;# 
# 5310 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM4CON equ 031Ah ;# 
# 5366 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM5DC equ 031Ch ;# 
# 5373 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM5DCL equ 031Ch ;# 
# 5439 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM5DCH equ 031Dh ;# 
# 5609 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM5CON equ 031Eh ;# 
# 5665 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM6DC equ 038Ch ;# 
# 5672 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM6DCL equ 038Ch ;# 
# 5738 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM6DCH equ 038Dh ;# 
# 5908 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PWM6CON equ 038Eh ;# 
# 5966 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NCO1ACC equ 058Ch ;# 
# 5973 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NCO1ACCL equ 058Ch ;# 
# 6043 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NCO1ACCH equ 058Dh ;# 
# 6113 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NCO1ACCU equ 058Eh ;# 
# 6161 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NCO1INC equ 058Fh ;# 
# 6168 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NCO1INCL equ 058Fh ;# 
# 6238 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NCO1INCH equ 0590h ;# 
# 6308 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NCO1INCU equ 0591h ;# 
# 6354 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NCO1CON equ 0592h ;# 
# 6394 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NCO1CLK equ 0593h ;# 
# 6466 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TMR0L equ 059Ch ;# 
# 6471 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TMR0 equ 059Ch ;# 
# 6604 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TMR0H equ 059Dh ;# 
# 6609 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PR0 equ 059Dh ;# 
# 6858 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T0CON0 equ 059Eh ;# 
# 6923 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T0CON1 equ 059Fh ;# 
# 7034 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CWG1CLKCON equ 060Ch ;# 
# 7062 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CWG1DAT equ 060Dh ;# 
# 7108 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CWG1DBR equ 060Eh ;# 
# 7212 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CWG1DBF equ 060Fh ;# 
# 7316 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CWG1CON0 equ 0610h ;# 
# 7417 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CWG1CON1 equ 0611h ;# 
# 7495 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CWG1AS0 equ 0612h ;# 
# 7615 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CWG1AS1 equ 0613h ;# 
# 7659 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CWG1STR equ 0614h ;# 
# 7771 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIR0 equ 070Ch ;# 
# 7804 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIR1 equ 070Dh ;# 
# 7843 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIR2 equ 070Eh ;# 
# 7876 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIR3 equ 070Fh ;# 
# 7927 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIR4 equ 0710h ;# 
# 7953 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIR5 equ 0711h ;# 
# 7998 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIR6 equ 0712h ;# 
# 8024 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIR7 equ 0713h ;# 
# 8066 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIE0 equ 0716h ;# 
# 8099 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIE1 equ 0717h ;# 
# 8132 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIE2 equ 0718h ;# 
# 8165 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIE3 equ 0719h ;# 
# 8216 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIE4 equ 071Ah ;# 
# 8242 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIE5 equ 071Bh ;# 
# 8287 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIE6 equ 071Ch ;# 
# 8313 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PIE7 equ 071Dh ;# 
# 8355 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PMD0 equ 0796h ;# 
# 8400 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PMD1 equ 0797h ;# 
# 8448 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PMD2 equ 0798h ;# 
# 8493 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PMD3 equ 0799h ;# 
# 8543 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PMD4 equ 079Ah ;# 
# 8583 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PMD5 equ 079Bh ;# 
# 8622 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
WDTCON0 equ 080Ch ;# 
# 8697 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
WDTCON1 equ 080Dh ;# 
# 8791 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
WDTPSL equ 080Eh ;# 
# 8919 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
WDTPSH equ 080Fh ;# 
# 9047 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
WDTTMR equ 0810h ;# 
# 9135 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
BORCON equ 0811h ;# 
# 9162 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
VREGCON equ 0812h ;# 
# 9183 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PCON0 equ 0813h ;# 
# 9245 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PCON1 equ 0814h ;# 
# 9266 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NVMADR equ 081Ah ;# 
# 9273 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NVMADRL equ 081Ah ;# 
# 9335 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NVMADRH equ 081Bh ;# 
# 9391 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NVMDAT equ 081Ch ;# 
# 9398 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NVMDATL equ 081Ch ;# 
# 9460 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NVMDATH equ 081Dh ;# 
# 9510 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NVMCON1 equ 081Eh ;# 
# 9566 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
NVMCON2 equ 081Fh ;# 
# 9586 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CPUDOZE equ 088Ch ;# 
# 9651 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
OSCCON1 equ 088Dh ;# 
# 9721 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
OSCCON2 equ 088Eh ;# 
# 9791 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
OSCCON3 equ 088Fh ;# 
# 9831 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
OSCSTAT equ 0890h ;# 
# 9888 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
OSCEN equ 0891h ;# 
# 9939 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
OSCTUNE equ 0892h ;# 
# 9997 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
OSCFRQ equ 0893h ;# 
# 10037 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLKRCON equ 0895h ;# 
# 10102 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLKRCLK equ 0896h ;# 
# 10148 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
FVRCON equ 090Ch ;# 
# 10224 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
DAC1CON0 equ 090Eh ;# 
# 10325 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
DAC1CON1 equ 090Fh ;# 
# 10377 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ZCDCON equ 091Fh ;# 
# 10423 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CMOUT equ 098Fh ;# 
# 10428 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CMSTAT equ 098Fh ;# 
# 10501 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CM1CON0 equ 0990h ;# 
# 10581 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CM1CON1 equ 0991h ;# 
# 10621 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CM1NCH equ 0992h ;# 
# 10681 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CM1PCH equ 0993h ;# 
# 10741 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CM2CON0 equ 0994h ;# 
# 10821 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CM2CON1 equ 0995h ;# 
# 10861 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CM2NCH equ 0996h ;# 
# 10921 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CM2PCH equ 0997h ;# 
# 10981 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RC2REG equ 0A19h ;# 
# 10986 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RCREG2 equ 0A19h ;# 
# 11019 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TX2REG equ 0A1Ah ;# 
# 11024 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TXREG2 equ 0A1Ah ;# 
# 11057 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SP2BRG equ 0A1Bh ;# 
# 11064 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SP2BRGL equ 0A1Bh ;# 
# 11069 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SPBRG2 equ 0A1Bh ;# 
# 11102 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SP2BRGH equ 0A1Ch ;# 
# 11107 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SPBRGH2 equ 0A1Ch ;# 
# 11140 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RC2STA equ 0A1Dh ;# 
# 11145 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RCSTA2 equ 0A1Dh ;# 
# 11262 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TX2STA equ 0A1Eh ;# 
# 11267 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TXSTA2 equ 0A1Eh ;# 
# 11384 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
BAUD2CON equ 0A1Fh ;# 
# 11389 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
BAUDCON2 equ 0A1Fh ;# 
# 11393 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
BAUDCTL2 equ 0A1Fh ;# 
# 11534 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLCDATA equ 01E0Fh ;# 
# 11572 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC1CON equ 01E10h ;# 
# 11690 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC1POL equ 01E11h ;# 
# 11768 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC1SEL0 equ 01E12h ;# 
# 11872 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC1SEL1 equ 01E13h ;# 
# 11976 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC1SEL2 equ 01E14h ;# 
# 12080 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC1SEL3 equ 01E15h ;# 
# 12184 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC1GLS0 equ 01E16h ;# 
# 12296 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC1GLS1 equ 01E17h ;# 
# 12408 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC1GLS2 equ 01E18h ;# 
# 12520 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC1GLS3 equ 01E19h ;# 
# 12632 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC2CON equ 01E1Ah ;# 
# 12750 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC2POL equ 01E1Bh ;# 
# 12828 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC2SEL0 equ 01E1Ch ;# 
# 12932 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC2SEL1 equ 01E1Dh ;# 
# 13036 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC2SEL2 equ 01E1Eh ;# 
# 13140 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC2SEL3 equ 01E1Fh ;# 
# 13244 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC2GLS0 equ 01E20h ;# 
# 13356 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC2GLS1 equ 01E21h ;# 
# 13468 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC2GLS2 equ 01E22h ;# 
# 13580 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC2GLS3 equ 01E23h ;# 
# 13692 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC3CON equ 01E24h ;# 
# 13810 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC3POL equ 01E25h ;# 
# 13888 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC3SEL0 equ 01E26h ;# 
# 13992 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC3SEL1 equ 01E27h ;# 
# 14096 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC3SEL2 equ 01E28h ;# 
# 14200 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC3SEL3 equ 01E29h ;# 
# 14304 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC3GLS0 equ 01E2Ah ;# 
# 14416 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC3GLS1 equ 01E2Bh ;# 
# 14528 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC3GLS2 equ 01E2Ch ;# 
# 14640 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC3GLS3 equ 01E2Dh ;# 
# 14752 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC4CON equ 01E2Eh ;# 
# 14870 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC4POL equ 01E2Fh ;# 
# 14948 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC4SEL0 equ 01E30h ;# 
# 15052 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC4SEL1 equ 01E31h ;# 
# 15156 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC4SEL2 equ 01E32h ;# 
# 15260 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC4SEL3 equ 01E33h ;# 
# 15364 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC4GLS0 equ 01E34h ;# 
# 15476 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC4GLS1 equ 01E35h ;# 
# 15588 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC4GLS2 equ 01E36h ;# 
# 15700 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLC4GLS3 equ 01E37h ;# 
# 15812 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PPSLOCK equ 01E8Fh ;# 
# 15832 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
INTPPS equ 01E90h ;# 
# 15890 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T0CKIPPS equ 01E91h ;# 
# 15948 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T1CKIPPS equ 01E92h ;# 
# 16006 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T1GPPS equ 01E93h ;# 
# 16064 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
T2INPPS equ 01E9Ch ;# 
# 16122 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCP1PPS equ 01EA1h ;# 
# 16180 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CCP2PPS equ 01EA2h ;# 
# 16238 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CWG1PPS equ 01EB1h ;# 
# 16296 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLCIN0PPS equ 01EBBh ;# 
# 16354 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLCIN1PPS equ 01EBCh ;# 
# 16412 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLCIN2PPS equ 01EBDh ;# 
# 16470 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
CLCIN3PPS equ 01EBEh ;# 
# 16528 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ADACTPPS equ 01EC3h ;# 
# 16586 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SSP1CLKPPS equ 01EC5h ;# 
# 16644 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SSP1DATPPS equ 01EC6h ;# 
# 16702 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SSP1SSPPS equ 01EC7h ;# 
# 16760 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RX1DTPPS equ 01ECBh ;# 
# 16818 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TX1CKPPS equ 01ECCh ;# 
# 16876 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RX2DTPPS equ 01ECDh ;# 
# 16934 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TX2CKPPS equ 01ECEh ;# 
# 16992 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RA0PPS equ 01F10h ;# 
# 17036 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RA1PPS equ 01F11h ;# 
# 17080 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RA2PPS equ 01F12h ;# 
# 17124 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RA3PPS equ 01F13h ;# 
# 17168 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RA4PPS equ 01F14h ;# 
# 17212 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RA5PPS equ 01F15h ;# 
# 17256 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RC0PPS equ 01F20h ;# 
# 17300 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RC1PPS equ 01F21h ;# 
# 17344 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RC2PPS equ 01F22h ;# 
# 17388 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RC3PPS equ 01F23h ;# 
# 17432 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RC4PPS equ 01F24h ;# 
# 17476 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
RC5PPS equ 01F25h ;# 
# 17520 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ANSELA equ 01F38h ;# 
# 17565 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
WPUA equ 01F39h ;# 
# 17615 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ODCONA equ 01F3Ah ;# 
# 17660 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SLRCONA equ 01F3Bh ;# 
# 17705 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
INLVLA equ 01F3Ch ;# 
# 17755 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
IOCAP equ 01F3Dh ;# 
# 17805 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
IOCAN equ 01F3Eh ;# 
# 17855 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
IOCAF equ 01F3Fh ;# 
# 17905 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ANSELC equ 01F4Eh ;# 
# 17955 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
WPUC equ 01F4Fh ;# 
# 18005 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
ODCONC equ 01F50h ;# 
# 18055 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
SLRCONC equ 01F51h ;# 
# 18105 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
INLVLC equ 01F52h ;# 
# 18155 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
IOCCP equ 01F53h ;# 
# 18205 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
IOCCN equ 01F54h ;# 
# 18255 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
IOCCF equ 01F55h ;# 
# 18305 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
STATUS_SHAD equ 01FE4h ;# 
# 18345 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
WREG_SHAD equ 01FE5h ;# 
# 18365 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
BSR_SHAD equ 01FE6h ;# 
# 18385 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
PCLATH_SHAD equ 01FE7h ;# 
# 18405 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
FSR0_SHAD equ 01FE8h ;# 
# 18412 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
FSR0L_SHAD equ 01FE8h ;# 
# 18432 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
FSR0H_SHAD equ 01FE9h ;# 
# 18452 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
FSR1_SHAD equ 01FEAh ;# 
# 18459 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
FSR1L_SHAD equ 01FEAh ;# 
# 18479 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
FSR1H_SHAD equ 01FEBh ;# 
# 18499 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
STKPTR equ 01FEDh ;# 
# 18543 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TOSL equ 01FEEh ;# 
# 18613 "/Applications/microchip/xc8/v2.36/pic/include/proc/pic16f15325.h"
TOSH equ 01FEFh ;# 
	debug_source C
	FNCALL	_main,_uart_initialize
	FNCALL	_main,_uart_transmit
	FNROOT	_main
	global	_TX1REG
_TX1REG	set	0x11A
	global	_RC1STAbits
_RC1STAbits	set	0x11D
	global	_TX1STAbits
_TX1STAbits	set	0x11E
	global	_SP1BRGL
_SP1BRGL	set	0x11B
	global	_SP1BRGH
_SP1BRGH	set	0x11C
	global	_BAUD1CONbits
_BAUD1CONbits	set	0x11F
	global	_PIR3bits
_PIR3bits	set	0x70F
psect	stringtext1,class=STRCODE,delta=2,noexec
global __pstringtext1
__pstringtext1:
	
STR_1:	
	retlw	104	;'h'
	retlw	101	;'e'
	retlw	108	;'l'
	retlw	108	;'l'
	retlw	111	;'o'
	retlw	0
psect	stringtext2,class=STRCODE,delta=2,noexec
global __pstringtext2
__pstringtext2:
; #config settings
	config pad_punits      = on
	config apply_mask      = off
	config ignore_cmsgs    = off
	config default_configs = off
	config default_idlocs  = off
	file	"build/rainbow.s"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

global __initialization
__initialization:
psect cinit,class=CODE,delta=2,merge=1
global end_of_initialization,__end_of__initialization

;End of C runtime variable initialization code

end_of_initialization:
__end_of__initialization:
movlb 0
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1,noexec
global __pcstackCOMMON
__pcstackCOMMON:
?_uart_initialize:	; 1 bytes @ 0x0
??_uart_initialize:	; 1 bytes @ 0x0
?_uart_transmit:	; 1 bytes @ 0x0
?_main:	; 1 bytes @ 0x0
	global	uart_transmit@data
uart_transmit@data:	; 2 bytes @ 0x0
	ds	2
	global	uart_transmit@length
uart_transmit@length:	; 1 bytes @ 0x2
	ds	1
??_uart_transmit:	; 1 bytes @ 0x3
	ds	1
	global	uart_transmit@ch
uart_transmit@ch:	; 2 bytes @ 0x4
	ds	2
	global	uart_transmit@i
uart_transmit@i:	; 2 bytes @ 0x6
	ds	2
??_main:	; 1 bytes @ 0x8
	ds	1
;!
;!Data Sizes:
;!    Strings     6
;!    Constant    0
;!    Data        0
;!    BSS         0
;!    Persistent  32
;!    Stack       0
;!
;!Auto Spaces:
;!    Space          Size  Autos    Used
;!    COMMON           14      9       9
;!    BANK0            80      0       0
;!    BANK1            80      0       0
;!    BANK2            80      0       0
;!    BANK3            80      0       0
;!    BANK4            80      0       0
;!    BANK5            80      0       0
;!    BANK6            80      0       0
;!    BANK7            80      0       0
;!    BANK8            80      0       0
;!    BANK9            80      0       0
;!    BANK10           80      0       0
;!    BANK11           80      0       0
;!    BANK12           48      0       0

;!
;!Pointer List with Targets:
;!
;!    uart_transmit@data	PTR void  size(2) Largest target is 6
;!		 -> STR_1(CODE[6]), 
;!
;!    uart_transmit@ch	PTR unsigned char  size(2) Largest target is 6
;!		 -> STR_1(CODE[6]), 
;!


;!
;!Critical Paths under _main in COMMON
;!
;!    _main->_uart_transmit
;!
;!Critical Paths under _main in BANK0
;!
;!    None.
;!
;!Critical Paths under _main in BANK1
;!
;!    None.
;!
;!Critical Paths under _main in BANK2
;!
;!    None.
;!
;!Critical Paths under _main in BANK3
;!
;!    None.
;!
;!Critical Paths under _main in BANK4
;!
;!    None.
;!
;!Critical Paths under _main in BANK5
;!
;!    None.
;!
;!Critical Paths under _main in BANK6
;!
;!    None.
;!
;!Critical Paths under _main in BANK7
;!
;!    None.
;!
;!Critical Paths under _main in BANK8
;!
;!    None.
;!
;!Critical Paths under _main in BANK9
;!
;!    None.
;!
;!Critical Paths under _main in BANK10
;!
;!    None.
;!
;!Critical Paths under _main in BANK11
;!
;!    None.
;!
;!Critical Paths under _main in BANK12
;!
;!    None.

;;
;;Main: autosize = 0, tempsize = 1, incstack = 0, save=0
;;

;!
;!Call Graph Tables:
;!
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (0) _main                                                 1     1      0     265
;!                                              8 COMMON     1     1      0
;!                    _uart_initialize
;!                      _uart_transmit
;! ---------------------------------------------------------------------------------
;! (1) _uart_transmit                                        8     5      3     265
;!                                              0 COMMON     8     5      3
;! ---------------------------------------------------------------------------------
;! (1) _uart_initialize                                      0     0      0       0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 1
;! ---------------------------------------------------------------------------------
;!
;! Call Graph Graphs:
;!
;! _main (ROOT)
;!   _uart_initialize
;!   _uart_transmit
;!

;! Address spaces:

;!Name               Size   Autos  Total    Cost      Usage
;!BIGRAM             3F0      0       0       0        0.0%
;!NULL                 0      0       0       0        0.0%
;!CODE                 0      0       0       0        0.0%
;!BITCOMMON            E      0       0       1        0.0%
;!BITSFR0              0      0       0       1        0.0%
;!SFR0                 0      0       0       1        0.0%
;!COMMON               E      9       9       2       64.3%
;!BITSFR1              0      0       0       2        0.0%
;!SFR1                 0      0       0       2        0.0%
;!BITSFR2              0      0       0       3        0.0%
;!SFR2                 0      0       0       3        0.0%
;!STACK                0      0       0       3        0.0%
;!BITSFR3              0      0       0       4        0.0%
;!SFR3                 0      0       0       4        0.0%
;!ABS                  0      0       0       4        0.0%
;!BITBANK0            50      0       0       5        0.0%
;!BITSFR4              0      0       0       5        0.0%
;!SFR4                 0      0       0       5        0.0%
;!BANK0               50      0       0       6        0.0%
;!BITSFR5              0      0       0       6        0.0%
;!SFR5                 0      0       0       6        0.0%
;!BITBANK1            50      0       0       7        0.0%
;!BITSFR6              0      0       0       7        0.0%
;!SFR6                 0      0       0       7        0.0%
;!BANK1               50      0       0       8        0.0%
;!BITSFR7              0      0       0       8        0.0%
;!SFR7                 0      0       0       8        0.0%
;!BITBANK2            50      0       0       9        0.0%
;!BITSFR8              0      0       0       9        0.0%
;!SFR8                 0      0       0       9        0.0%
;!BANK2               50      0       0      10        0.0%
;!BITSFR9              0      0       0      10        0.0%
;!SFR9                 0      0       0      10        0.0%
;!BITBANK3            50      0       0      11        0.0%
;!BITSFR10             0      0       0      11        0.0%
;!SFR10                0      0       0      11        0.0%
;!BANK3               50      0       0      12        0.0%
;!BITSFR11             0      0       0      12        0.0%
;!SFR11                0      0       0      12        0.0%
;!BITBANK4            50      0       0      13        0.0%
;!BITSFR12             0      0       0      13        0.0%
;!SFR12                0      0       0      13        0.0%
;!BANK4               50      0       0      14        0.0%
;!BITSFR13             0      0       0      14        0.0%
;!SFR13                0      0       0      14        0.0%
;!BITBANK5            50      0       0      15        0.0%
;!BITSFR14             0      0       0      15        0.0%
;!SFR14                0      0       0      15        0.0%
;!BANK5               50      0       0      16        0.0%
;!BITSFR15             0      0       0      16        0.0%
;!SFR15                0      0       0      16        0.0%
;!BITBANK6            50      0       0      17        0.0%
;!BITSFR16             0      0       0      17        0.0%
;!SFR16                0      0       0      17        0.0%
;!BANK6               50      0       0      18        0.0%
;!BITSFR17             0      0       0      18        0.0%
;!SFR17                0      0       0      18        0.0%
;!BITBANK7            50      0       0      19        0.0%
;!BITSFR18             0      0       0      19        0.0%
;!SFR18                0      0       0      19        0.0%
;!BANK7               50      0       0      20        0.0%
;!BITSFR19             0      0       0      20        0.0%
;!SFR19                0      0       0      20        0.0%
;!BITBANK8            50      0       0      21        0.0%
;!BITSFR20             0      0       0      21        0.0%
;!SFR20                0      0       0      21        0.0%
;!BANK8               50      0       0      22        0.0%
;!BITSFR21             0      0       0      22        0.0%
;!SFR21                0      0       0      22        0.0%
;!BITBANK9            50      0       0      23        0.0%
;!BITSFR22             0      0       0      23        0.0%
;!SFR22                0      0       0      23        0.0%
;!BANK9               50      0       0      24        0.0%
;!BITSFR23             0      0       0      24        0.0%
;!SFR23                0      0       0      24        0.0%
;!BITBANK10           50      0       0      25        0.0%
;!BITSFR24             0      0       0      25        0.0%
;!SFR24                0      0       0      25        0.0%
;!BANK10              50      0       0      26        0.0%
;!BITSFR25             0      0       0      26        0.0%
;!SFR25                0      0       0      26        0.0%
;!BITBANK11           50      0       0      27        0.0%
;!BITSFR26             0      0       0      27        0.0%
;!SFR26                0      0       0      27        0.0%
;!BANK11              50      0       0      28        0.0%
;!BITSFR27             0      0       0      28        0.0%
;!SFR27                0      0       0      28        0.0%
;!BITBANK12           30      0       0      29        0.0%
;!BITSFR28             0      0       0      29        0.0%
;!SFR28                0      0       0      29        0.0%
;!BANK12              30      0       0      30        0.0%
;!BITSFR29             0      0       0      30        0.0%
;!SFR29                0      0       0      30        0.0%
;!BITSFR30             0      0       0      31        0.0%
;!SFR30                0      0       0      31        0.0%
;!DATA                 0      0       0      31        0.0%
;!BITSFR31             0      0       0      32        0.0%
;!SFR31                0      0       0      32        0.0%
;!BITSFR32             0      0       0      33        0.0%
;!SFR32                0      0       0      33        0.0%
;!BITSFR33             0      0       0      34        0.0%
;!SFR33                0      0       0      34        0.0%
;!BITSFR34             0      0       0      35        0.0%
;!SFR34                0      0       0      35        0.0%
;!BITSFR35             0      0       0      36        0.0%
;!SFR35                0      0       0      36        0.0%
;!BITSFR36             0      0       0      37        0.0%
;!SFR36                0      0       0      37        0.0%
;!BITSFR37             0      0       0      38        0.0%
;!SFR37                0      0       0      38        0.0%
;!BITSFR38             0      0       0      39        0.0%
;!SFR38                0      0       0      39        0.0%
;!BITSFR39             0      0       0      40        0.0%
;!SFR39                0      0       0      40        0.0%
;!BITSFR40             0      0       0      41        0.0%
;!SFR40                0      0       0      41        0.0%
;!BITSFR41             0      0       0      42        0.0%
;!SFR41                0      0       0      42        0.0%
;!BITSFR42             0      0       0      43        0.0%
;!SFR42                0      0       0      43        0.0%
;!BITSFR43             0      0       0      44        0.0%
;!SFR43                0      0       0      44        0.0%
;!BITSFR44             0      0       0      45        0.0%
;!SFR44                0      0       0      45        0.0%
;!BITSFR45             0      0       0      46        0.0%
;!SFR45                0      0       0      46        0.0%
;!BITSFR46             0      0       0      47        0.0%
;!SFR46                0      0       0      47        0.0%
;!BITSFR47             0      0       0      48        0.0%
;!SFR47                0      0       0      48        0.0%
;!BITSFR48             0      0       0      49        0.0%
;!SFR48                0      0       0      49        0.0%
;!BITSFR49             0      0       0      50        0.0%
;!SFR49                0      0       0      50        0.0%
;!BITSFR50             0      0       0      51        0.0%
;!SFR50                0      0       0      51        0.0%
;!BITSFR51             0      0       0      52        0.0%
;!SFR51                0      0       0      52        0.0%
;!BITSFR52             0      0       0      53        0.0%
;!SFR52                0      0       0      53        0.0%
;!BITSFR53             0      0       0      54        0.0%
;!SFR53                0      0       0      54        0.0%
;!BITSFR54             0      0       0      55        0.0%
;!SFR54                0      0       0      55        0.0%
;!BITSFR55             0      0       0      56        0.0%
;!SFR55                0      0       0      56        0.0%
;!BITSFR56             0      0       0      57        0.0%
;!SFR56                0      0       0      57        0.0%
;!BITSFR57             0      0       0      58        0.0%
;!SFR57                0      0       0      58        0.0%
;!BITSFR58             0      0       0      59        0.0%
;!SFR58                0      0       0      59        0.0%
;!BITSFR59             0      0       0      60        0.0%
;!SFR59                0      0       0      60        0.0%
;!BITSFR60             0      0       0      61        0.0%
;!SFR60                0      0       0      61        0.0%
;!BITSFR61             0      0       0      62        0.0%
;!SFR61                0      0       0      62        0.0%
;!BITSFR62             0      0       0      63        0.0%
;!SFR62                0      0       0      63        0.0%
;!BITSFR63             0      0       0      64        0.0%
;!SFR63                0      0       0      64        0.0%

	global	_main

;; *************** function _main *****************
;; Defined at:
;;		line 64 in file "main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : B3F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels required when called: 1
;; This function calls:
;;		_uart_initialize
;;		_uart_transmit
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext,global,class=CODE,delta=2,merge=1,split=1,group=0
	file	"main.c"
	line	64
global __pmaintext
__pmaintext:	;psect for function _main
psect	maintext
	file	"main.c"
	line	64
	
_main:	
;incstack = 0
	callstack 15
; Regs used in _main: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	66
	
l606:	
	fcall	_uart_initialize
	line	70
	
l608:	
	movlw	low(((STR_1)|8000h))
	movwf	(uart_transmit@data)
	movlw	high(((STR_1)|8000h))
	movwf	((uart_transmit@data))+1
	movlw	low(05h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(uart_transmit@length)
	fcall	_uart_transmit
	goto	l608
	global	start
	ljmp	start
	callstack 0
	line	72
GLOBAL	__end_of_main
	__end_of_main:
	signat	_main,89
	global	_uart_transmit

;; *************** function _uart_transmit *****************
;; Defined at:
;;		line 33 in file "main.c"
;; Parameters:    Size  Location     Type
;;  data            2    0[COMMON] PTR void 
;;		 -> STR_1(6), 
;;  length          1    2[COMMON] unsigned char 
;; Auto vars:     Size  Location     Type
;;  i               2    6[COMMON] int 
;;  ch              2    4[COMMON] PTR unsigned char 
;;		 -> STR_1(6), 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, pclath
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used: 1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1,local,class=CODE,delta=2,merge=1,group=0
	line	33
global __ptext1
__ptext1:	;psect for function _uart_transmit
psect	text1
	file	"main.c"
	line	33
	
_uart_transmit:	
;incstack = 0
	callstack 15
; Regs used in _uart_transmit: [wreg-fsr0h+status,2+pclath]
	line	34
	
l596:	
	movf	(uart_transmit@data+1),w
	movwf	(uart_transmit@ch+1)
	movf	(uart_transmit@data),w
	movwf	(uart_transmit@ch)
	line	36
	
l598:	
	clrf	(uart_transmit@i)
	clrf	(uart_transmit@i+1)
	goto	l604
	line	37
	
l22:	
	movlb 14	; select bank14
	btfss	(1807)^0700h,4	;volatile
	goto	u31
	goto	u30
u31:
	goto	l22
u30:
	line	38
	
l600:	
	movf	(uart_transmit@ch),w
	addwf	(uart_transmit@i),w
	movwf	fsr0l
	movf	(uart_transmit@ch+1),w
	addwfc	(uart_transmit@i+1),w
	movwf	fsr0h
	movf	indf0,w ;code access
	movlb 2	; select bank2
	movwf	(282)^0100h	;volatile
	line	39
	
l602:	
	movlw	01h
	addwf	(uart_transmit@i),f
	movlw	0
	addwfc	(uart_transmit@i+1),f
	
l604:	
	movf	(uart_transmit@i+1),w
	xorlw	80h
	movwf	(??_uart_transmit+0)+0
	movlw	80h
	subwf	(??_uart_transmit+0)+0,w
	skipz
	goto	u45
	movf	(uart_transmit@length),w
	subwf	(uart_transmit@i),w
u45:

	skipc
	goto	u41
	goto	u40
u41:
	goto	l22
u40:
	line	40
	
l26:	
	return
	callstack 0
GLOBAL	__end_of_uart_transmit
	__end_of_uart_transmit:
	signat	_uart_transmit,8313
	global	_uart_initialize

;; *************** function _uart_initialize *****************
;; Defined at:
;;		line 3 in file "main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used: 1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text2,local,class=CODE,delta=2,merge=1,group=0
	line	3
global __ptext2
__ptext2:	;psect for function _uart_initialize
psect	text2
	file	"main.c"
	line	3
	
_uart_initialize:	
;incstack = 0
	callstack 15
; Regs used in _uart_initialize: [wreg+status,2]
	line	17
	
l560:	
	movlb 2	; select bank2
	bsf	(287)^0100h,3	;volatile
	line	18
	
l562:	
	clrf	(284)^0100h	;volatile
	line	19
	
l564:	
	movlw	low(067h)
	movwf	(283)^0100h	;volatile
	line	22
	
l566:	
	bcf	(286)^0100h,6	;volatile
	line	23
	
l568:	
	bsf	(286)^0100h,5	;volatile
	line	24
	
l570:	
	bcf	(286)^0100h,4	;volatile
	line	25
	
l572:	
	bcf	(286)^0100h,3	;volatile
	line	26
	
l574:	
	bsf	(286)^0100h,2	;volatile
	line	28
	
l576:	
	bcf	(285)^0100h,6	;volatile
	line	29
	
l578:	
	bsf	(285)^0100h,4	;volatile
	line	30
	
l580:	
	bsf	(285)^0100h,7	;volatile
	line	31
	
l17:	
	return
	callstack 0
GLOBAL	__end_of_uart_initialize
	__end_of_uart_initialize:
	signat	_uart_initialize,89
global	___latbits
___latbits	equ	2
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp+0
	end
