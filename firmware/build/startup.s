
	; Microchip MPLAB XC8 C Compiler V2.36
	; Copyright (C) 2022 Microchip Technology Inc.

	; Auto-generated runtime startup code for final link stage.

	;
	; Compiler options:
	;
	; -q --opt=none --chip=16f15325 -I. build/main.p1 -orainbow.hex \
	; --objdir=build --outdir=build --std=c99 --callgraph=none --warn=-3 \
	; --errformat=%f:%l:%c: error: (%n) %s \
	; --warnformat=%f:%l:%c: warning: (%n) %s \
	; --msgformat=%f:%l:%c: advisory: (%n) %s
	;


	processor	16F15325

	global	_main,start,reset_vec
	fnroot	_main
	psect	code,class=CODE,delta=2
	psect	powerup,class=CODE,delta=2
	psect	reset_vec,class=CODE,delta=2
	psect	maintext,class=CODE,delta=2
	C	set	0
	Z	set	2
	PCL	set	2
	INDF	set	0

	STATUS	equ	3
	BSR	equ	8
	PCLATH	equ	0Ah
	psect	eeprom_data,class=EEDATA,delta=2,space=3,noexec
	psect	strings,class=CODE,delta=2,reloc=256
	psect	intentry,class=CODE,delta=2
	psect	functab,class=ENTRY,delta=2
	global	intlevel0,intlevel1,intlevel2, intlevel3, intlevel4, intlevel5
intlevel0:
intlevel1:
intlevel2:
intlevel3:
intlevel4:
intlevel5:
	psect	init,class=CODE,delta=2
	psect	cinit,class=CODE,delta=2
	psect	text,class=CODE,delta=2
	psect	end_init,class=CODE,delta=2
	psect	clrtext,class=CODE,delta=2
	INDF0	set	0
	INDF1	set	1
	PCL	set	2
	STATUS	set	3
	FSR0L	set	4
	FSR0H	set	5
	FSR1L	set	6
	FSR1H	set	7
	BSR	set	8
	WREG	set	9
	PCLATH	set	10
	INTCON	set	11

	psect	reset_vec
reset_vec:
	; No powerup routine
	global start

; jump to start
	ljmp	start
	; No interrupt routine


	psect	init
start:

;Initialize the stack pointer (FSR1)
	fsr1l	equ	6
	fsr1h	equ	7
	global ___stacklo, ___stackhi
	___stacklo	equ	0
	___stackhi	equ	0


	psect	stack,class=STACK,space=2,noexec
	global ___sp,___int_sp
	___sp:
	___int_sp:

; No heap to be allocated
	psect	heap,class=HEAP,space=7,noexec
	global ___heap_lo
	___heap_lo	equ	0
	global ___heap_hi
	___heap_hi	equ	0

	psect	end_init
	global start_initialization
	ljmp start_initialization	;jump to C runtime clear & initialization

psect common,class=COMMON,space=1
psect bank0,class=BANK0,space=1
psect bank1,class=BANK1,space=1
psect bank2,class=BANK2,space=1
psect bank3,class=BANK3,space=1
psect bank4,class=BANK4,space=1
psect bank5,class=BANK5,space=1
psect bank6,class=BANK6,space=1
psect bank7,class=BANK7,space=1
psect bank8,class=BANK8,space=1
psect bank9,class=BANK9,space=1
psect bank10,class=BANK10,space=1
psect bank11,class=BANK11,space=1
psect bank12,class=BANK12,space=1
psect bank13,class=BANK13,space=1
psect bank14,class=BANK14,space=1
psect bank15,class=BANK15,space=1
psect bank16,class=BANK16,space=1
psect bank17,class=BANK17,space=1
psect bank18,class=BANK18,space=1
psect bank19,class=BANK19,space=1
psect bank20,class=BANK20,space=1
psect bank21,class=BANK21,space=1
psect bank22,class=BANK22,space=1
psect bank23,class=BANK23,space=1
psect bank24,class=BANK24,space=1
psect bank25,class=BANK25,space=1
psect bank26,class=BANK26,space=1
psect bank27,class=BANK27,space=1
psect bank28,class=BANK28,space=1
psect bank29,class=BANK29,space=1
psect bank30,class=BANK30,space=1
psect bank31,class=BANK31,space=1
psect bank32,class=BANK32,space=1
psect bank33,class=BANK33,space=1
psect bank34,class=BANK34,space=1
psect bank35,class=BANK35,space=1
psect bank36,class=BANK36,space=1
psect bank37,class=BANK37,space=1
psect bank38,class=BANK38,space=1
psect bank39,class=BANK39,space=1
psect bank40,class=BANK40,space=1
psect bank41,class=BANK41,space=1
psect bank42,class=BANK42,space=1
psect bank43,class=BANK43,space=1
psect bank44,class=BANK44,space=1
psect bank45,class=BANK45,space=1
psect bank46,class=BANK46,space=1
psect bank47,class=BANK47,space=1
psect bank48,class=BANK48,space=1
psect bank49,class=BANK49,space=1
psect bank50,class=BANK50,space=1
psect bank51,class=BANK51,space=1
psect bank52,class=BANK52,space=1
psect bank53,class=BANK53,space=1
psect bank54,class=BANK54,space=1
psect bank55,class=BANK55,space=1
psect bank56,class=BANK56,space=1
psect bank57,class=BANK57,space=1
psect bank58,class=BANK58,space=1
psect bank59,class=BANK59,space=1
psect bank60,class=BANK60,space=1
psect bank61,class=BANK61,space=1
psect bank62,class=BANK62,space=1
psect bank63,class=BANK63,space=1
psect bigram,class=BIGRAM,space=1
psect ram,class=RAM,space=1
psect abs1,class=ABS1,space=1
psect sfr0,class=SFR0,space=1
psect sfr1,class=SFR1,space=1
psect sfr2,class=SFR2,space=1
psect sfr3,class=SFR3,space=1
psect sfr4,class=SFR4,space=1
psect sfr5,class=SFR5,space=1
psect sfr6,class=SFR6,space=1
psect sfr7,class=SFR7,space=1
psect sfr8,class=SFR8,space=1
psect sfr9,class=SFR9,space=1
psect sfr10,class=SFR10,space=1
psect sfr11,class=SFR11,space=1
psect sfr12,class=SFR12,space=1
psect sfr13,class=SFR13,space=1
psect sfr14,class=SFR14,space=1
psect sfr15,class=SFR15,space=1
psect sfr16,class=SFR16,space=1
psect sfr17,class=SFR17,space=1
psect sfr18,class=SFR18,space=1
psect sfr19,class=SFR19,space=1
psect sfr20,class=SFR20,space=1
psect sfr21,class=SFR21,space=1
psect sfr22,class=SFR22,space=1
psect sfr23,class=SFR23,space=1
psect sfr24,class=SFR24,space=1
psect sfr25,class=SFR25,space=1
psect sfr26,class=SFR26,space=1
psect sfr27,class=SFR27,space=1
psect sfr28,class=SFR28,space=1
psect sfr29,class=SFR29,space=1
psect sfr30,class=SFR30,space=1
psect sfr31,class=SFR31,space=1
psect sfr32,class=SFR32,space=1
psect sfr33,class=SFR33,space=1
psect sfr34,class=SFR34,space=1
psect sfr35,class=SFR35,space=1
psect sfr36,class=SFR36,space=1
psect sfr37,class=SFR37,space=1
psect sfr38,class=SFR38,space=1
psect sfr39,class=SFR39,space=1
psect sfr40,class=SFR40,space=1
psect sfr41,class=SFR41,space=1
psect sfr42,class=SFR42,space=1
psect sfr43,class=SFR43,space=1
psect sfr44,class=SFR44,space=1
psect sfr45,class=SFR45,space=1
psect sfr46,class=SFR46,space=1
psect sfr47,class=SFR47,space=1
psect sfr48,class=SFR48,space=1
psect sfr49,class=SFR49,space=1
psect sfr50,class=SFR50,space=1
psect sfr51,class=SFR51,space=1
psect sfr52,class=SFR52,space=1
psect sfr53,class=SFR53,space=1
psect sfr54,class=SFR54,space=1
psect sfr55,class=SFR55,space=1
psect sfr56,class=SFR56,space=1
psect sfr57,class=SFR57,space=1
psect sfr58,class=SFR58,space=1
psect sfr59,class=SFR59,space=1
psect sfr60,class=SFR60,space=1
psect sfr61,class=SFR61,space=1
psect sfr62,class=SFR62,space=1
psect sfr63,class=SFR63,space=1


	end	start
