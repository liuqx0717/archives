$include (C8051F310.INC)
$include (GlobalVars.inc)
$include (KeLEDs.inc)


$include (Timer.inc)

	
PUBLIC	LEDs_Init
PUBLIC	LEDs_Next
PUBLIC	LEDs_Clear
PUBLIC	LEDs_Start
PUBLIC	LEDs_Stop
	
PUBLIC	Timer_2
	


KELEDS	SEGMENT	CODE
		RSEG	KELEDS
			
			
			
SUM		EQU		12
PATTERNS:
		DB		00111111B
		DB		10011111B
		DB		11001111B
		DB		11100111B
		DB		11110011B
		DB		11111001B
		DB		11111100B
		DB		11111001B
		DB		11110011B
		DB		11100111B
		DB		11001111B
		DB		10011111B

			
			
LEDs_Init:
		JB		INIT_LEDs,FinishInit
		SETB	INIT_LEDs
		
		LCALL	KeLEDs_Init
		MOV		LEDs_Pattern,#00H
		
FinishInit:
		RET
		
		
		
		
		
LEDs_Next:
		PUSH	DPH
		PUSH	DPL

		MOV		DPTR,#PATTERNS
		MOV		A,LEDs_Pattern
		MOVC	A,@A+DPTR
		MOV		g_LEDs,A
		LCALL	KeLEDs_Output
		
		INC		LEDs_Pattern
		CLR		C
		MOV		A,LEDs_Pattern
		SUBB	A,#SUM							;If (LEDs_Pattern) = #SUM goto RESTORE
		JNC		RESTORE
		SJMP	FINISH
		
RESTORE:
		MOV		LEDs_Pattern,#00H
		
FINISH:
		POP		DPL
		POP		DPH
		
		RET
		
		
		
LEDs_Start:
		PUSH	08H
		MOV		08H,#2
		LCALL	Timer_Start
		POP		08H
		RET
		
LEDs_Stop:
		PUSH	08H
		MOV		08H,#2
		LCALL	Timer_Stop
		POP		08H
		RET
		
LEDs_Clear:
		MOV		g_LEDs,#0FFH
		LCALL	KeLEDs_Output
		MOV		LEDs_Pattern,#00H
		RET
		
		
		
Timer_2:

		ACALL	LEDs_Next
		RET
		
		
		
		
		
		
		
		
		END
			
			
			
			
			
			
		
			
			
			