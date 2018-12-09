$include (C8051F310.INC)
$include (GlobalVars.inc)
$include (LED.inc)
$include (Beep.inc)
$include (Timer.inc)
$include (LEDs.inc)
$include (Keys.inc)
$include (Digits.inc)
$include (CAL.INC)
	
$include (password.inc)
$include (homework.inc)
	


PUBLIC	TEST3_ChangeState
	
PUBLIC	MAIN
PUBLIC	Keys_CB



	


BEEP	BIT 	P3.1
KINT	BIT 	P0.1



TEST3  	SEGMENT	CODE
		RSEG	TEST3
		
MAIN:   
		PUSH	08H
		SETB	EA
		
		LCALL	Beep_Init
		LCALL	Timer_Init
		LCALL	LEDs_Init
		LCALL	Keys_Init
		LCALL	Digits_Init
		
		MOV		08H,#1
		LCALL	TEST3_ChangeState
		
		SWEEP:
		LCALL	Digits_Sweep
		LCALL	DELAY
		SJMP	SWEEP

		POP		08H
		RET


DELAY:
		PUSH	02H
		PUSH	03H

		MOV		R3,#17H
DELAY_LOOP1:
		MOV		R2,#0FFH
DELAY_LOOP2:
		DJNZ	R2,DELAY_LOOP2
		DJNZ	R3,DELAY_LOOP1
		
		
		POP		03H
		POP		02H
		RET



;arguments:
;    08H  state
TEST3_ChangeState:
		MOV		TEST3_MainState,08H
		
		MOV		A,TEST3_MainState
		
ChangeState_STATE0:
		CJNE	A,#0,ChangeState_STATE1
		
		SJMP	FINISHSTATE
		
ChangeState_STATE1:
		CJNE	A,#1,ChangeState_STATE2
		LCALL	Password_Main
		SJMP	FINISHSTATE
		
ChangeState_STATE2:
		CJNE	A,#2,ChangeState_STATE3
		LCALL	Homework_Main
		SJMP	FINISHSTATE
		
ChangeState_STATE3:
		CJNE	A,#3,ChangeState_STATE4
		LCALL	CAL_MAIN
		SJMP	FINISHSTATE
		
ChangeState_STATE4:
		
FINISHSTATE:

		RET




;arguments:
;    08H  key code
Keys_CB:
		PUSH	08H
		MOV		A,08H
		CJNE	A,#15,NORMAL
		
		MOV		A,TEST3_MainState
SWITCH1:
		CJNE	A,#2,SWITCH2
		MOV		08H,#3
		ACALL	TEST3_ChangeState
		SJMP	FINISHKEY
SWITCH2:
		CJNE	A,#3,FINISHKEY
		MOV		08H,#2
		ACALL	TEST3_ChangeState
		SJMP	FINISHKEY


NORMAL:
		MOV		A,TEST3_MainState
		
Keys_STATE0:
		CJNE	A,#0,Keys_STATE1
		
		SJMP	FINISHKEY
		
Keys_STATE1:
		CJNE	A,#1,Keys_STATE2
		LCALL	Password_KeyEvent
		SJMP	FINISHKEY
		
Keys_STATE2:
		CJNE	A,#2,Keys_STATE3
		LCALL	Homework_KeyEvent
		SJMP	FINISHKEY
		
Keys_STATE3:
		CJNE	A,#3,Keys_STATE4
		LCALL	Cal_KEYEVENT
		SJMP	FINISHKEY
		
Keys_STATE4:
		
FINISHKEY:
		POP		08H
		RET





		

		
		
		
		
		
		
		END