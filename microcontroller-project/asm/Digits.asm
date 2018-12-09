$include (GlobalVars.inc)

$include (KeDigits.inc)
	
$include (Timer.inc)
	


PUBLIC	Digits_Init
PUBLIC	Digits_Sweep
PUBLIC	Digits_StartBlink4
PUBLIC	Digits_StartBlink3
PUBLIC	Digits_StartBlink2
PUBLIC	Digits_StartBlink1
PUBLIC	Digits_StopBlink4
PUBLIC	Digits_StopBlink3
PUBLIC	Digits_StopBlink2
PUBLIC	Digits_StopBlink1
	
PUBLIC	Timer_3


;Digits_State:
;    5~4: which digit to light (for sweeping) 
;    3~0: indicats whether the corresponding digit is blinking (0:no 1:yes)

;g_DigitState:  
;    H |S41|S40|S31|S30|S21|S20|S11|S10|
;    Sn1 Sn0:
;        00normal  01dp  10 light  11 close

;g_Digit1:    Digit1~2
;g_Digit2:    Digit3~4


;Digits_LastState:
;    Last state (for blinking)


DIGITS	SEGMENT		CODE
		RSEG		DIGITS
	
	
Digits_Init:
		PUSH	08H
		JB		INIT_Digits,FinishInit
		SETB	INIT_Digits
		
		LCALL	KeDigits_Init
		LCALL	Timer_Init
		
		MOV		g_DigitState,#0FFH
		MOV		Digits_State,#00H
		MOV		Digits_LastState,#0FFH
		
		MOV		08H,#3
		LCALL	Timer_Start
		
FinishInit:
		POP		08H
		RET
		
		
Digits_Sweep:
		PUSH	08H
		
		MOV		A,Digits_State
		ANL		A,#00110000B
		MOV		08H,A
		
DIGIT0:
		CJNE	A,#00000000B,DIGIT1
		CLR		Digits_State.5
		SETB	Digits_State.4
		MOV		A,g_Digit1
		ANL		A,#00001111B
		ORL		08H,A						;write g_Digit1 lower 4 bits to 08H
		MOV		A,08H
		MOV		C,g_DigitState.1
		MOV		ACC.7,C
		MOV		C,g_DigitState.0
		MOV		ACC.6,C
		MOV		08H,A
		LCALL	KeDigits_Output
		LJMP	FINISH
		
DIGIT1:
		CJNE	A,#00010000B,DIGIT2
		SETB	Digits_State.5
		CLR		Digits_State.4
		MOV		A,g_Digit1
		ANL		A,#11110000B
		SWAP	A
		ORL		08H,A						;write g_Digit1 higher 4 bits to 08H
		MOV		A,08H
		MOV		C,g_DigitState.3
		MOV		ACC.7,C
		MOV		C,g_DigitState.2
		MOV		ACC.6,C
		MOV		08H,A
		LCALL	KeDigits_Output
		LJMP	FINISH
		
DIGIT2:
		CJNE	A,#00100000B,DIGIT3
		SETB	Digits_State.5
		SETB	Digits_State.4
		MOV		A,g_Digit2
		ANL		A,#00001111B
		ORL		08H,A						;write g_Digit2 lower 4 bits to 08H
		MOV		A,08H
		MOV		C,g_DigitState.5
		MOV		ACC.7,C
		MOV		C,g_DigitState.4
		MOV		ACC.6,C
		MOV		08H,A
		LCALL	KeDigits_Output
		LJMP	FINISH
	
DIGIT3:
		CJNE	A,#00110000B,FINISH
		CLR		Digits_State.5
		CLR		Digits_State.4
		MOV		A,g_Digit2
		ANL		A,#11110000B
		SWAP	A
		ORL		08H,A						;write g_Digit2 higher 4 bits to 08H
		MOV		A,08H
		MOV		C,g_DigitState.7
		MOV		ACC.7,C
		MOV		C,g_DigitState.6
		MOV		ACC.6,C
		MOV		08H,A
		LCALL	KeDigits_Output
		LJMP	FINISH
		
FINISH:
		POP		08H
		RET
		
		
		
		
		
Digits_StartBlink4:
		ORL		Digits_LastState,#11000000B
		SETB	Digits_State.3
		RET
		
Digits_StartBlink3:
		ORL		Digits_LastState,#00110000B
		SETB	Digits_State.2
		RET
		
Digits_StartBlink2:
		ORL		Digits_LastState,#00001100B
		SETB	Digits_State.1
		RET
	
Digits_StartBlink1:
		ORL		Digits_LastState,#00000011B
		SETB	Digits_State.0
		RET


Digits_StopBlink4:
		CLR		Digits_State.3
		MOV		A,g_DigitState
		ANL		A,#11000000B
		CJNE	A,#11000000B,FINISHSTOP4		;if bits 7,6 of g_DigitState is not 11, goto FINISHSTOP4
		MOV		A,Digits_LastState				;bits 7,6 of g_DigitState is 11
		ANL		A,#11000000B
		CJNE	A,#11000000B,SWAPAGAIN4			;if bits 7,6 of Digits_LastState is not 11, goto SWAPAGAIN4
		SJMP	FINISHSTOP4						;bits 7,6 of Digits_LastState is 11
SWAPAGAIN4:
		ACALL	SWAP4
		SJMP	FINISHSTOP4
FINISHSTOP4:
		RET
		
		

Digits_StopBlink3:
		CLR		Digits_State.2
		MOV		A,g_DigitState
		ANL		A,#00110000B
		CJNE	A,#00110000B,FINISHSTOP3		;if bits 5,4 of g_DigitState is not 11, goto FINISHSTOP4
		MOV		A,Digits_LastState				;bits 5,4  of g_DigitState is 11
		ANL		A,#00110000B
		CJNE	A,#00110000B,SWAPAGAIN3			;if bits 5,4  of Digits_LastState is not 11, goto SWAPAGAIN4
		SJMP	FINISHSTOP3						;bits 5,4  of Digits_LastState is 11
SWAPAGAIN3:
		ACALL	SWAP3
		SJMP	FINISHSTOP3
FINISHSTOP3:
		RET
		
		
Digits_StopBlink2:
		CLR		Digits_State.1
		MOV		A,g_DigitState
		ANL		A,#00001100B
		CJNE	A,#00001100B,FINISHSTOP2		;if bits 3,2 of g_DigitState is not 11, goto FINISHSTOP4
		MOV		A,Digits_LastState				;bits 3,2 of g_DigitState is 11
		ANL		A,#00001100B
		CJNE	A,#00001100B,SWAPAGAIN2			;if bits 3,2 of Digits_LastState is not 11, goto SWAPAGAIN4
		SJMP	FINISHSTOP2						;bits 3,2 of Digits_LastState is 11
SWAPAGAIN2:
		ACALL	SWAP2
		SJMP	FINISHSTOP2
FINISHSTOP2:
		RET
		
	
Digits_StopBlink1:
		CLR		Digits_State.0
		MOV		A,g_DigitState
		ANL		A,#00000011B
		CJNE	A,#00000011B,FINISHSTOP1		;if bits 1,0 of g_DigitState is not 11, goto FINISHSTOP4
		MOV		A,Digits_LastState				;bits 1,0 of g_DigitState is 11
		ANL		A,#00000011B
		CJNE	A,#00000011B,SWAPAGAIN1			;if bits 1,0 of Digits_LastState is not 11, goto SWAPAGAIN4
		SJMP	FINISHSTOP1						;bits 1,0 of Digits_LastState is 11
SWAPAGAIN1:
		ACALL	SWAP1
		SJMP	FINISHSTOP1
FINISHSTOP1:
		RET



		
		
;swap bits 7,6 of Digits_LastState and g_DigitState
SWAP4:
		MOV		A,g_DigitState				
		
		MOV		C,Digits_LastState.7
		MOV		g_DigitState.7,C
		
		MOV		C,Digits_LastState.6
		MOV		g_DigitState.6,C
		
		MOV		C,ACC.7
		MOV		Digits_LastState.7,C
		
		MOV		C,ACC.6
		MOV		Digits_LastState.6,C
		RET
		
		
		
		
		
;swap bits 5,4 of Digits_LastState and g_DigitState
SWAP3:
		MOV		A,g_DigitState				
		
		MOV		C,Digits_LastState.5
		MOV		g_DigitState.5,C
		
		MOV		C,Digits_LastState.4
		MOV		g_DigitState.4,C
		
		MOV		C,ACC.5
		MOV		Digits_LastState.5,C
		
		MOV		C,ACC.4
		MOV		Digits_LastState.4,C
		RET
		
		
;swap bits 3,2 of Digits_LastState and g_DigitState
SWAP2:
		MOV		A,g_DigitState				
		
		MOV		C,Digits_LastState.3
		MOV		g_DigitState.3,C
		
		MOV		C,Digits_LastState.2
		MOV		g_DigitState.2,C
		
		MOV		C,ACC.3
		MOV		Digits_LastState.3,C
		
		MOV		C,ACC.2
		MOV		Digits_LastState.2,C
		RET
		
		
		
		
;swap bits 1,0 of Digits_LastState and g_DigitState
SWAP1:
		MOV		A,g_DigitState				
		
		MOV		C,Digits_LastState.1
		MOV		g_DigitState.1,C
		
		MOV		C,Digits_LastState.0
		MOV		g_DigitState.0,C
		
		MOV		C,ACC.1
		MOV		Digits_LastState.1,C
		
		MOV		C,ACC.0
		MOV		Digits_LastState.0,C
		RET
		
		
		
;0.5s
Timer_3:
BLINK4:
		JNB		Digits_State.3,BLINK3
		ACALL	SWAP4
		
BLINK3:
		JNB		Digits_State.2,BLINK2
		ACALL	SWAP3
		
BLINK2:
		JNB		Digits_State.1,BLINK1
		ACALL	SWAP2
		
BLINK1:
		JNB		Digits_State.0,BLINKFINISH
		ACALL	SWAP1
		
BLINKFINISH:

		RET
		
		
		
		
		
		
		END