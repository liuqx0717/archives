$include (GlobalVars.inc)
$include (C8051F310.inc)
$include (beep.inc)
	
	
PUBLIC	CAL_MAIN
PUBLIC	Cal_KEYEVENT
	
	
CAL3	SEGMENT	CODE
		RSEG	CAL3

CAL_MAIN:	
		MOV		g_DigitState,#11111100B
		MOV		g_Digit1,#00H
		MOV		g_Digit2,#00H
		MOV		CALCULATE_NUM,#00H
		MOV		CALCULATE_1,#00H
		MOV		CALCULATE_2,#00H
		CLR		CAL_STATE1
		CLR		CAL_STATE2
		CLR		CAL_STATE3
		RET
		
		
Cal_KEYEVENT:	PUSH	00H
		PUSH	01H
		PUSH	02H	
		PUSH	03H
		MOV		R0,#00H
		MOV		R1,#00H
		MOV		R2,#00H
		MOV		R3,#00H
		MOV		A,08H
		JNB		CAL_STATE3,Calcu
		MOV		g_DigitState,#11111100B
		MOV		g_Digit1,#00H
		MOV		g_Digit2,#00H
		MOV		CALCULATE_NUM,#00H
		MOV		CALCULATE_1,#00H
		MOV		CALCULATE_2,#00H
		CLR		CAL_STATE3
Calcu:		
		CJNE	A,#0AH,NEXT
		LJMP	NEXT2
NEXT:	
		JNC		NEXT2
		MOV		A,CALCULATE_NUM
		CLR		C
		SUBB	A,#03H
		JNC		JUMPONE
		MOV		A,CALCULATE_NUM
		INC		A
		MOV		CALCULATE_NUM,A
		MOV		R2,A
DIGIT1:	
		CJNE	R2,#01H,DIGIT2
		MOV		g_DigitState,#11111100B
		MOV		A,08H
		MOV		g_Digit1,A
		LCALL	Beep_1Async
		LJMP	END2
DIGIT2:	
		CJNE	R2,#02H,DIGIT3
		MOV		g_DigitState,#11110000B
		MOV		A,g_Digit1
		SWAP	A
		ADD		A,08H
		MOV		g_Digit1,A
		LCALL	Beep_1Async
		LJMP	END2
DIGIT3:	
		MOV		g_DigitState,#11000000B
		MOV		A,g_Digit1
		ANL		A,#11110000B
		SWAP	A
		MOV		g_Digit2,A
		MOV		A,g_Digit1
		SWAP	A
		ANL		A,#11110000B
		ADD		A,08H
		MOV		g_Digit1,A
		LCALL	Beep_1Async
		LJMP	JUDGE

JUMPONE:LJMP	WRONG
		
NEXT2:	
		CJNE	A,#0AH,SUBBSTATE
		SETB	CAL_STATE1	
		CLR		A
		SETB	CAL_STATE2
		MOV		CALCULATE_NUM,A
		MOV		CALCULATE_1,g_Digit1
		MOV		CALCULATE_2,g_Digit2
		MOV		g_Digit1,#00H
		MOV		g_Digit2,#00H		
		MOV		A,#00
		MOV		CALCULATE_NUM,A
		LCALL	Beep_1Async
		LJMP	END2
SUBBSTATE:		
		CJNE	A,#0BH,DENGYU
		CLR		CAL_STATE1
		CLR		A
		SETB	CAL_STATE2
		MOV		CALCULATE_NUM,A
		MOV		CALCULATE_1,g_Digit1
		MOV		CALCULATE_2,g_Digit2
		MOV		g_Digit1,#00H
		MOV		g_Digit2,#00H	
		MOV		A,#00
		MOV		CALCULATE_NUM,A
		LCALL	Beep_1Async
		LJMP	END2
DENGYU:
		MOV		A,#00
		MOV		CALCULATE_NUM,A
		MOV		A,08H
		CJNE	A,#0CH,WRONG
		LJMP	JUDGE

JUDGE:
		JNB		CAL_STATE2,WRONG
		
		
ADDD:	
		MOV		g_DigitState,#00000000B
		JNB		CAL_STATE1,SUBBB
		MOV		A,CALCULATE_1
		CLR		C
		ADD		A,g_Digit1
		DA		A
		MOV		g_Digit1,A
		MOV		A,CALCULATE_2
		ADDC	A,g_Digit2
		DA		A
		MOV		g_Digit2,A
		CLR		CAL_STATE1
		CLR		CAL_STATE2
		SETB	CAL_STATE3
		LCALL	Beep_1Async
		LJMP	END2
		
		
SUBBB:
		LJMP	WRONG
		
		
		;MOV		g_DigitState,#00000000B
		;MOV		A,CALCULATE_1
		;CLR		C
		;MOV		R0,g_Digit1
		;MOV		R1,CALCULATE_1
		;MOV		A,#9AH
		;SUBB	A,R0
		;ADD		A,R1
		;DA		A		
		;MOV		R2,A
		;MOV		A,CALCULATE_2
		;MOV		R0,g_Digit2
		;ADDC	A,#99H
		;MOV		R1,A
		;MOV		A,#9AH
		;CLR		C
		;SUBB	A,R0
		;ADD		A,R1
		;ANL		A,#00001111B
		;DA		A
		;MOV		R3,A
		;CLR		CAL_STATE1
		;CLR		CAL_STATE2
		;SETB	CAL_STATE3
		;JNC		OUTLED
		;MOV		A,g_Digit1
		;MOV		R0,A
		;MOV		A,#9AH
		;SUBB	A,R0
		;MOV		R2,A
		;MOV		A,g_Digit2
		;MOV		R0,A
		;MOV		A,#9AH
		;SUBB	A,R0
		;ADD		A,#10100000B
		;MOV		R3,A
		;LJMP	OUTLED
		
OUTLED:
		MOV		A,#9AH
		CLR		C
		SUBB	A,R2
		MOV		R2,A		
		MOV		A,#9AH
		CLR		C
		SUBB	A,R3
		MOV		R3,A
		MOV		g_Digit1,R2
		MOV		g_Digit2,R3
		LJMP	END2
		
		
		
		
WRONG:		
		LCALL	Beep_3Async
		
END2:	
		POP		03H
		POP		02H
		POP		01H
		POP		00H
		RET
		
		
			END