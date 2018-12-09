; 08H~1FH:  local variables(arguments) & global variables
; 20H~27H:  bits (00H~3FH)
; 30H~7FH:  stack & global variables

; A,B,C:      volatile


$include (C8051F310.INC)
EXTRN CODE (MAIN)
;EXTRN CODE (INT_EXT0)
;EXTRN CODE (INT_TIM0)
;EXTRN CODE (INT_EXT1)
;EXTRN CODE (INT_TIM1)
EXTRN CODE (INT_TIM2)


	
	CSEG AT 0000H
		
	ORG		0000H
	LJMP	Init_Device 
	
	ORG		0003H
	;LJMP	INT_EXT0
	
	ORG		000BH
	;LJMP	INT_TIM0
	
	ORG		0013H
	;LJMP	INT_EXT1
	
	ORG		001BH
	;LJMP	INT_TIM1
	
	ORG		002BH         ;Timer2_Overflow
	LJMP	INT_TIM2

;------------------------------------------------------------------------
;-  Generated Initialization File                                      --
;------------------------------------------------------------------------

; Peripheral specific initialization functions,
; Called from the Init_Device label


	ORG		0100H

Mem_Init:
	MOV		R0,#02H
	MOV		R1,#26H
ClearMem:
	MOV		@R0,#00H
	INC		R0
	DJNZ	R1,ClearMem
	MOV		R0,#00H
	MOV		R1,#00H
	RET
		
		
		
PCA_Init:
    ANL  PCA0MD,    #0BFh
    MOV  PCA0MD,    #000h
    RET

Timer_Init:
    MOV  TMOD,      #001h
    MOV  CKCON,     #002h
    RET

Port_IO_Init:
    ; P0.0  -  Unassigned,  Push-Pull,  Digital
    ; P0.1  -  Unassigned,  Open-Drain, Digital
    ; P0.2  -  Unassigned,  Open-Drain, Digital
    ; P0.3  -  Unassigned,  Open-Drain, Digital
    ; P0.4  -  Unassigned,  Open-Drain, Digital
    ; P0.5  -  Unassigned,  Open-Drain, Digital
    ; P0.6  -  Unassigned,  Open-Drain, Digital
    ; P0.7  -  Unassigned,  Open-Drain, Digital

    ; P1.0  -  Unassigned,  Open-Drain, Digital
    ; P1.1  -  Unassigned,  Open-Drain, Digital
    ; P1.2  -  Unassigned,  Open-Drain, Digital
    ; P1.3  -  Unassigned,  Open-Drain, Digital
    ; P1.4  -  Unassigned,  Open-Drain, Digital
    ; P1.5  -  Unassigned,  Open-Drain, Digital
    ; P1.6  -  Unassigned,  Open-Drain, Digital
    ; P1.7  -  Unassigned,  Open-Drain, Digital
    ; P2.0  -  Unassigned,  Open-Drain, Digital
    ; P2.1  -  Unassigned,  Open-Drain, Digital
    ; P2.2  -  Unassigned,  Open-Drain, Digital
    ; P2.3  -  Unassigned,  Open-Drain, Digital


	CLR	  P0.2							;XTAL1
	CLR	  P0.3							;XTAL2
	MOV   P0MDIN,#11110011B				;P0.2 and P0.3 are analog input ports
	MOV   P0SKIP,#00001100B				;P0.2 and P0.3 are skipped by the Crossbar

    MOV  P0MDOUT,   #001h
    MOV  P3MDOUT,   #002h
    MOV  XBR1,      #040h

	
	CLR   P3.1							;BEEP
	
    RET


Clocks_Init:

	MOV   OSCICN,#11000011B				;SYSCLK derived from Internal Oscillator divided by 1
	MOV   OSCXCN,#01100111B				;Crystal Oscillator Mode

	MOV   R0,#07FH
WAIT0:
	MOV	  R1,#0FFH
WAIT1:
	DJNZ  R1,WAIT1
	DJNZ  R0,WAIT0						;Wait for the startup of the external oscillator
	RET



; Initialization function for device,
; Call Init_Device from your main program
Init_Device:
	MOV   SP,#2FH

	LCALL Mem_Init
    LCALL PCA_Init
    LCALL Port_IO_Init
	LCALL Clocks_Init
    LCALL Timer_Init


	
	
	LCALL MAIN
	SJMP	$

	END