$include (C8051F310.INC)
$include (GlobalVars.inc)
$include (LED.inc)
$include (Beep.inc)
$include (Timer.inc)
$include (LEDs.inc)
$include (Keys.inc)
$include (Digits.inc)
$include (test3.inc)
	
	


PUBLIC	Homework_Main
PUBLIC	Homework_KeyEvent
	
PUBLIC	Timer_4
PUBLIC	Timer_5
PUBLIC	Timer_6


HOMEWORK	SEGMENT		CODE
			RSEG		HOMEWORK


HOMEWORK_Count1		EQU		10			; 5Hz    reload value
HOMEWORK_Count2		EQU		2			; 1Hz    reload value
HOMEWORK_Count3		EQU		1			; 0.5Hz  reload value
	


;NUM1~3  Select
;F1      Start/Stop
;F2      Set

;HOMEWORK_State
;    3~0 state
;        0000 stop
;        0001 play
;        0010 pause
;        0011 setting
;    5~4 num

;HOMEWORK_Count
;HOMEWORK_Second1~3


Homework_Main:
		PUSH	08H
		
		MOV		HOMEWORK_Second1,#20H
		MOV		HOMEWORK_Second2,#20H
		MOV		HOMEWORK_Second3,#20H

		ACALL	Select1

		POP		08H
		RET
		
		
		
		
		
Select1:
		ACALL	StopTimer1
		ACALL	StopTimer2
		ACALL	StopTimer3
		MOV		HOMEWORK_State,#00H
		CLR		HOMEWORK_State.5
		CLR		HOMEWORK_State.4
		MOV		HOMEWORK_Count,#HOMEWORK_Count1
		MOV		HOMEWORK_Second,HOMEWORK_Second1
		MOV		g_Digit1,#05H
		MOV		g_Digit2,#1AH
		MOV		g_DigitState,#00H
		LCALL	Digits_StopBlink1
		LCALL	Digits_StopBlink2
		LCALL	Digits_StopBlink3
		LCALL	Digits_StopBlink4
		LCALL	LED_off
		LCALL	LEDs_Clear

		RET
		
Select2:
		ACALL	StopTimer1
		ACALL	StopTimer2
		ACALL	StopTimer3
		MOV		HOMEWORK_State,#00H
		CLR		HOMEWORK_State.5
		SETB	HOMEWORK_State.4
		MOV		HOMEWORK_Count,#HOMEWORK_Count2
		MOV		HOMEWORK_Second,HOMEWORK_Second2
		MOV		g_Digit1,#01H
		MOV		g_Digit2,#2AH
		MOV		g_DigitState,#00H
		LCALL	Digits_StopBlink1
		LCALL	Digits_StopBlink2
		LCALL	Digits_StopBlink3
		LCALL	Digits_StopBlink4
		LCALL	LED_off
		LCALL	LEDs_Clear

		RET
		
Select3:
		ACALL	StopTimer1
		ACALL	StopTimer2
		ACALL	StopTimer3
		MOV		HOMEWORK_State,#00H
		SETB	HOMEWORK_State.5
		CLR		HOMEWORK_State.4
		MOV		HOMEWORK_Count,#HOMEWORK_Count3
		MOV		HOMEWORK_Second,HOMEWORK_Second3
		MOV		g_Digit1,#05H
		MOV		g_Digit2,#3AH
		MOV		g_DigitState,#00000100B
		LCALL	Digits_StopBlink1
		LCALL	Digits_StopBlink2
		LCALL	Digits_StopBlink3
		LCALL	Digits_StopBlink4
		LCALL	LED_off
		LCALL	LEDs_Clear

		RET





StartTimer1:
		PUSH	08H

		MOV		08H,#4
		LCALL	Timer_Start
		LCALL	LEDs_Start
		
		
		POP		08H
		RET


StopTimer1:
		PUSH	08H

		MOV		08H,#4
		LCALL	Timer_Stop
		LCALL	LEDs_Stop
		
		POP		08H
		RET
		
StartTimer2:
		PUSH	08H

		MOV		08H,#5
		LCALL	Timer_Start
		LCALL	LEDs_Start
		
		POP		08H
		RET


StopTimer2:
		PUSH	08H

		MOV		08H,#5
		LCALL	Timer_Stop
		LCALL	LEDs_Stop
		
		POP		08H
		RET
		
StartTimer3:
		PUSH	08H

		MOV		08H,#6
		LCALL	Timer_Start
		LCALL	LEDs_Start
		
		POP		08H
		RET


StopTimer3:
		PUSH	08H

		MOV		08H,#6
		LCALL	Timer_Stop
		LCALL	LEDs_Stop
		
		POP		08H
		RET
		





;start or pause
StartPlay:
		PUSH	07H
		
		MOV		A,HOMEWORK_State
		ANL		A,#0FH
		MOV		R7,A
		
		CJNE	R7,#0,CONTINUE1
		LCALL	Beep_2Async
		LCALL	Digits_StartBlink3
		CLR		HOMEWORK_State.1
		SETB	HOMEWORK_State.0
		MOV		g_DigitState,#00000000B
		MOV		g_Digit1,HOMEWORK_Second
		SJMP	StartPlay_Start
		
		CONTINUE1:
		CJNE	R7,#2,CONTINUE2
		LCALL	Beep_1Async
		CLR		HOMEWORK_State.1
		SETB	HOMEWORK_State.0
		SJMP	StartPlay_Start
		
		CONTINUE2:
		CJNE	R7,#1,_StartPlay
		LCALL	Beep_1Async
		SETB	HOMEWORK_State.1
		CLR		HOMEWORK_State.0
		SJMP	StartPlay_Pause
		
StartPlay_Start:
		MOV		A,HOMEWORK_State
		ANL		A,#00110000B
		MOV		R7,A
		LCALL	Digits_StartBlink3

		StartNUM1:
		CJNE	R7,#00000000B,StartNUM2
		ACALL	StartTimer1
		SJMP	_StartPlay
		
		StartNUM2:
		CJNE	R7,#00010000B,StartNUM3
		ACALL	StartTimer2
		SJMP	_StartPlay
		
		StartNUM3:
		CJNE	R7,#00100000B,StartNUM4
		ACALL	StartTimer3
		SJMP	_StartPlay
		
		StartNUM4:
		SJMP	_StartPlay
		
StartPlay_Pause:
		MOV		A,HOMEWORK_State
		ANL		A,#00110000B
		MOV		R7,A
		LCALL	Digits_StopBlink3

		PauseNUM1:
		CJNE	R7,#00000000B,PauseNUM2
		ACALL	StopTimer1
		SJMP	_StartPlay
		
		PauseNUM2:
		CJNE	R7,#00010000B,PauseNUM3
		ACALL	StopTimer2
		SJMP	_StartPlay
		
		PauseNUM3:
		CJNE	R7,#00100000B,PauseNUM4
		ACALL	StopTimer3
		SJMP	_StartPlay
		
		PauseNUM4:
		SJMP	_StartPlay
		


_StartPlay:
		POP		07H
		RET



EnterSetting:
		PUSH	07H
		
		SETB	HOMEWORK_State.0
		SETB	HOMEWORK_State.1
		
		LCALL	Digits_StartBlink1
		LCALL	Digits_StartBlink2
		
		MOV		A,HOMEWORK_State
		ANL		A,#00110000B
		MOV		R7,A

		EnterSettingNUM1:
		CJNE	R7,#00000000B,EnterSettingNUM2
		MOV		g_Digit1,HOMEWORK_Second1
		SJMP	_EnterSetting
		
		EnterSettingNUM2:
		CJNE	R7,#00010000B,EnterSettingNUM3
		MOV		g_Digit1,HOMEWORK_Second2
		SJMP	_EnterSetting
		
		EnterSettingNUM3:
		CJNE	R7,#00100000B,EnterSettingNUM4
		MOV		g_DigitState,#00000000B
		MOV		g_Digit1,HOMEWORK_Second3
		SJMP	_EnterSetting
		
		EnterSettingNUM4:
		SJMP	_EnterSetting

_EnterSetting:
		POP		07H
		RET



ExitSetting:
		PUSH	07H
		
		CLR		HOMEWORK_State.0
		CLR		HOMEWORK_State.1
		
		
		MOV		A,HOMEWORK_State
		ANL		A,#00110000B
		MOV		R7,A

		ExitSettingNUM1:
		CJNE	R7,#00000000B,ExitSettingNUM2
		MOV		HOMEWORK_Second1,g_Digit1
		ACALL	Select1
		SJMP	_ExitSetting
		
		ExitSettingNUM2:
		CJNE	R7,#00010000B,ExitSettingNUM3
		MOV		HOMEWORK_Second2,g_Digit1
		ACALL	Select2
		SJMP	_ExitSetting
		
		ExitSettingNUM3:
		CJNE	R7,#00100000B,ExitSettingNUM4
		MOV		HOMEWORK_Second3,g_Digit1
		ACALL	Select3
		SJMP	_ExitSetting
		
		ExitSettingNUM4:
		SJMP	_ExitSetting

_ExitSetting:
		POP		07H
		RET




		
Homework_KeyEvent:
		PUSH	07H
		PUSH	06H
		MOV		A,HOMEWORK_State
		ANL		A,#0FH
		MOV		R7,A					;R7: state 
		MOV		R6,08H					;R6: key code
		
		CJNE	R7,#3,NORMALMODE
		SJMP	SETTINGMODE
NORMALMODE:
		
		KEY1:
		CJNE	R6,#1,KEY2
		LCALL	Beep_1Async
		ACALL	Select1
		AJMP	_Homework_KeyEvent
		
		KEY2:
		CJNE	R6,#2,KEY3
		LCALL	Beep_1Async
		ACALL	Select2
		AJMP	_Homework_KeyEvent

		KEY3:
		CJNE	R6,#3,KEY10
		LCALL	Beep_1Async
		ACALL	Select3
		AJMP	_Homework_KeyEvent
		
		KEY10:
		CJNE	R6,#10,KEY11
		ACALL	StartPlay
		AJMP	_Homework_KeyEvent
		
		KEY11:
		CJNE	R6,#11,INVALID1
		CJNE	R7,#0,INVALID1
		LCALL	Beep_1Async
		ACALL	EnterSetting
		AJMP	_Homework_KeyEvent
		
SETTINGMODE:
		CLR		C
		MOV		A,#9
		SUBB	A,R6
		JC		OTHERKEYS
		
		LCALL	Beep_1Async
		
		MOV		A,g_Digit1
		SWAP	A
		ANL		A,#0F0H
		ANL		06H,#0FH
		ORL		A,R6
		MOV		g_Digit1,A
		AJMP	_Homework_KeyEvent
		
		
OTHERKEYS:
		CJNE	R6,#11,INVALID1
		LCALL	Beep_1Async
		ACALL	ExitSetting
		AJMP	_Homework_KeyEvent
		

		
INVALID1:
		LCALL	Beep_3Async
		SJMP	_Homework_KeyEvent
		


_Homework_KeyEvent:
		POP		06H
		POP		07H
		RET
		
		
		
		

;100ms
Timer_4:
		DEC		HOMEWORK_Count
		MOV		A,HOMEWORK_Count
		JNZ		FINISH1
		MOV		HOMEWORK_Count,#HOMEWORK_Count1
		
		MOV		A,HOMEWORK_Second
		ADD		A,#99H
		DA		A
		MOV		HOMEWORK_Second,A
		MOV		g_Digit1,HOMEWORK_Second
		MOV		A,HOMEWORK_Second
		JNZ		FINISH1
		LCALL	Beep_2Async
		ACALL	Select1
		RET
		
FINISH1:
		LCALL	LED_switch
		RET
		
		
		
;0.5ms
Timer_5:
		DEC		HOMEWORK_Count
		MOV		A,HOMEWORK_Count
		JNZ		FINISH2
		MOV		HOMEWORK_Count,#HOMEWORK_Count2
		
		MOV		A,HOMEWORK_Second
		ADD		A,#99H
		DA		A
		MOV		HOMEWORK_Second,A
		MOV		g_Digit1,HOMEWORK_Second
		MOV		A,HOMEWORK_Second
		JNZ		FINISH2
		LCALL	Beep_2Async
		ACALL	Select2
		RET
		
FINISH2:
		LCALL	LED_switch
		RET





;1s
Timer_6:
		DEC		HOMEWORK_Count
		MOV		A,HOMEWORK_Count
		JNZ		FINISH3
		MOV		HOMEWORK_Count,#HOMEWORK_Count3
		
		MOV		A,HOMEWORK_Second
		ADD		A,#99H
		DA		A
		MOV		HOMEWORK_Second,A
		MOV		g_Digit1,HOMEWORK_Second
		MOV		A,HOMEWORK_Second
		JNZ		FINISH3
		LCALL	Beep_2Async
		ACALL	Select3
		RET
		
FINISH3:
		LCALL	LED_switch
		RET
		
		
		
		
		
		END