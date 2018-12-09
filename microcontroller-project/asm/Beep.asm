$include (GlobalVars.inc)
$include (KeBeep.inc)

$include (Timer.inc)
	
PUBLIC	Beep_Init
PUBLIC	Beep_On
PUBLIC	Beep_Off
PUBLIC	Beep_Switch
PUBLIC	Beep_1Async
PUBLIC	Beep_2Async
PUBLIC	Beep_3Async

PUBLIC	Timer_1

	
BEEP 	SEGMENT	CODE
		RSEG	BEEP
			
Beep_Init:
		JB		INIT_Beep,FinishInit
		SETB	INIT_Beep
		
		LCALL	KeBeep_Init
		LCALL	Timer_Init
		
		MOV		Beep_Count,#00H
		MOV		Beep_Total,#00H
		MOV		Beep_State,#0
		
FinishInit:
		RET
		
		

		
		
Beep_On:
		LCALL	KeBeep_On
		RET
		
Beep_Off:
		LCALL	KeBeep_Off
		RET
		
Beep_Switch:
		LCALL	KeBeep_Switch
		RET
		
		
		
		
; beep for 0.1s, asynchronous
Beep_1Async:
		MOV		A,Beep_State
		JNZ		FINISH1
		MOV		A,Beep_Count
		JNZ		FINISH1						;if there is a running beep, skip current beep
		
		MOV		Beep_Total,#1
		MOV		Beep_State,#0
		ACALL	Beep_On
		
		ACALL	StartTimer
		
FINISH1:
		RET
		
		
		
; beep for 0.8s, asynchronous
Beep_2Async:
		MOV		A,Beep_State
		JNZ		FINISH2
		MOV		A,Beep_Count
		JNZ		FINISH2						;if there is a running beep, skip current beep
		
		MOV		Beep_Total,#8
		MOV		Beep_State,#0
		ACALL	Beep_On
		
		ACALL	StartTimer
		
FINISH2:
		RET
		
		
		
		
		
		
; 2 beeps, each for 0.2s, with an interval of 0.1s, asynchronous
Beep_3Async:
		MOV		A,Beep_State
		JNZ		FINISH3	
		MOV		A,Beep_Count
		JNZ		FINISH3						;if there is a running beep, skip current beep
		
		MOV		Beep_State,#1
		MOV		Beep_Total,#3
		ACALL	Beep_On
		
		ACALL	StartTimer
		
FINISH3:
		RET		






Beep_3Async1:
		ACALL	Beep_Off

		MOV		Beep_State,#2
		MOV		Beep_Total,#1

		RET		




Beep_3Async2:
		ACALL	Beep_On
		
		MOV		Beep_State,#0
		MOV		Beep_Total,#3
		

		RET		





StartTimer:
		PUSH	08H
		MOV		08H,#1
		LCALL	Timer_Start
		POP		08H
		RET
		
StopTimer:
		PUSH	08H
		MOV		08H,#1
		LCALL	Timer_Stop
		POP		08H
		RET	





;0.1s
Timer_1:

		INC		Beep_Count
		MOV		A,Beep_Total
		CJNE	A,Beep_Count,FINISH			;if Beep_Total != Beep_Count, goto FINISH
		
		MOV		Beep_Count,#00H
		
CHKSTATE:
		MOV		A,Beep_State
		CJNE	A,#0,STATE1
STATE0:
		ACALL	Beep_Off
		ACALL	StopTimer
		MOV		Beep_State,#00H
		SJMP	FINISH
STATE1:
		CJNE	A,#1,STATE2
		ACALL	Beep_3Async1
		SJMP	FINISH
STATE2:
		CJNE	A,#2,FINISH
		ACALL	Beep_3Async2
		SJMP	FINISH

		
FINISH:
		RET
		
		END