; CALLBACK:
;     KeTimer0_CB

$include (C8051F310.INC)
$include (GlobalVars.inc)
	
PUBLIC	KeTimer2_Init
PUBLIC	KeTimer2_Start
PUBLIC	KeTimer2_Stop
PUBLIC	INT_TIM2


EXTRN	CODE	(KeTimer2_CB)

; T		        1 / (11,059,200 / 8) = 0.723379629629629629 us

;27648(6C00H) * T = 20ms
;FFFFH - 6C00H = 93FFH
CNTH	EQU		93H
CNTL	EQU		0FFH;



KETIMER2	SEGMENT	CODE
		RSEG	KETIMER2



;You need to SETB EA by yourself
;You need to call KeTimer2_Start by yourself
KeTimer2_Init:
		JB		INIT_KeTimer2,FinishInit
		SETB	INIT_KeTimer2
		
		CLR		TR2
		CLR		T2SPLIT					;Timer 2 operates as a 16-bit timer with auto-reload
		SETB	T2XCLK					;External clock / 8
		SETB	ET2						;Enable Timer2 overflow interrupt
		CLR		TF2LEN					;Don't generate an interrupt when lower 8 bits overflows
		ANL		CKCON,#11101111B		;Set T2ML to 0
		MOV		TMR2RLH,#CNTH
		MOV		TMR2RLL,#CNTL			;Reload Value
		
FinishInit:
		RET
		
		
		
		
		
KeTimer2_Start:
		SETB	TR2
		RET

KeTimer2_Stop:
		CLR		TR2
		RET
	
	
	
	
INT_TIM2:
		PUSH	ACC
		PUSH	B
		MOV		INT_C_old,C
		
		CLR		TF2H					;TF2H won't be cleared by hardware
		LCALL	KeTimer2_CB
		
		MOV		C,INT_C_old
		POP		B
		POP		ACC
		RETI
	
	
		END