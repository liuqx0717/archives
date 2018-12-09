$include (C8051F310.INC)
$include (GlobalVars.inc)
$include (Beep.inc)
$include (Timer.inc)
$include (Keys.inc)
$include (Digits.inc)
$include (test3.inc)



PUBLIC	Password_Main
PUBLIC	Password_KeyEvent


PASSWORD	SEGMENT		CODE
			RSEG		PASSWORD


Password_Main:
		MOV		g_Digit1,#0AAH
		MOV		g_Digit2,#0AAH
		MOV		g_DigitState,#00111111B
		MOV		PASSWORD_State,#0
		
		LCALL	Digits_StartBlink4
		LCALL	Digits_StopBlink3
		LCALL	Digits_StopBlink2
		LCALL	Digits_StopBlink1

		RET




;judge if the key code is valid, and beep
;arguments:
;    08H  key code
;return value:
;    C    returns 0 if the key is valid 
IsValid:
		MOV		A,#9
		CLR		C
		SUBB	A,08H
		JC		INVALID
		LCALL	Beep_1Async
		RET
INVALID:
		LCALL	Beep_3Async
		SETB	C
		RET
		
IsValid2:
		MOV		A,#9
		CLR		C
		SUBB	A,08H
		JC		INVALID2

		RET
INVALID2:
		LCALL	Beep_3Async
		SETB	C
		RET
		
		


;arguments:
;    08H  key code
Password_KeyEvent:
		PUSH	08H
		
		MOV		A,PASSWORD_State
		
STATE0:
		CJNE	A,#0,STATE1
		LCALL	IsValid
		JC		FINISHKEY				;if the key code is invalid, goto FINISHKEY
		MOV		PASSWORD_PSW1,08H
		MOV		PASSWORD_State,#1
		LCALL	Digits_StopBlink4
		MOV		g_DigitState,#00001111B
		LCALL	Digits_StartBlink3
		SJMP	FINISHKEY
		
		STATE1:
		CJNE	A,#1,STATE2
		LCALL	IsValid
		JC		FINISHKEY				;if the key code is invalid, goto FINISHKEY
		MOV		A,08H
		SWAP	A
		ORL		PASSWORD_PSW1,A
		MOV		PASSWORD_State,#2
		LCALL	Digits_StopBlink3
		MOV		g_DigitState,#00000011B
		LCALL	Digits_StartBlink2
		SJMP	FINISHKEY
		
		STATE2:
		CJNE	A,#2,STATE3
		LCALL	IsValid
		JC		FINISHKEY				;if the key code is invalid, goto FINISHKEY
		MOV		PASSWORD_PSW2,08H
		MOV		PASSWORD_State,#3
		LCALL	Digits_StopBlink2
		MOV		g_DigitState,#00000000B
		LCALL	Digits_StartBlink1
		SJMP	FINISHKEY
		
		STATE3:
		CJNE	A,#3,STATE4
		LCALL	IsValid2
		JC		FINISHKEY				;if the key code is invalid, goto FINISHKEY
		MOV		A,08H
		SWAP	A
		ORL		PASSWORD_PSW2,A
		MOV		PASSWORD_State,#0
		LCALL	Digits_StopBlink1
		MOV		A,PASSWORD_PSW1
		CJNE	A,#70H,FAIL
		MOV		A,PASSWORD_PSW2
		CJNE	A,#71H,FAIL
		LCALL	Beep_2Async
		MOV		08H,#2
		LCALL	TEST3_ChangeState
		SJMP	FINISHKEY
		FAIL:
		LCALL	Beep_3Async
		MOV		g_DigitState,#00111111B
		LCALL	Digits_StartBlink4
		SJMP	FINISHKEY
		
		STATE4:
		
		FINISHKEY:
		POP		08H

		RET






		END