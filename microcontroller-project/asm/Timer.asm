; CALLBACK:
;     Timer_1

$include (C8051F310.INC)
$include (KeTimer2.inc)
$include (GlobalVars.inc)

PUBLIC	KeTimer2_CB
PUBLIC	Timer_Init
PUBLIC	Timer_CheckCTRL
PUBLIC	Timer_Start
PUBLIC	Timer_Stop


EXTRN	CODE	(Timer_0)				;T = 20ms   in Keys.asm
	
EXTRN	CODE	(Timer_1)				;T = 100ms  in Beep.asm
EXTRN	CODE	(Timer_2)				;T = 100ms  in LEDs.asm
EXTRN	CODE	(Timer_3)				;T = 0.5s   in Digits.asm
EXTRN	CODE	(Timer_4)				;T = 0.1s   in homework.asm
EXTRN	CODE	(Timer_5)				;T = 0.5s   in homework.asm
EXTRN	CODE	(Timer_6)				;T = 1s     in homework.asm
	
	
	
TIMER	SEGMENT	CODE
		RSEG	TIMER


;20 ms
SUM		EQU		6
	
CNTVAL:	
		DB		5						;Timer_1   T = 20ms * 5 = 0.1s
		DB		5						;Timer_2   T = 20ms * 5 = 0.1s
		DB		25						;Timer_3   T = 20ms * 25 = 0.5s
		DB		5						;Timer_4   T = 20ms * 5 = 0.1s
		DB		25						;Timer_5   T = 20ms * 25 = 0.5s
		DB		50						;Timer_6   T = 20ms * 50 = 1s


JMPTAB:
		LCALL	Timer_1
		LJMP	FINISH
		LCALL	Timer_2
		LJMP	FINISH
		LCALL	Timer_3
		LJMP	FINISH
		LCALL	Timer_4
		LJMP	FINISH
		LCALL	Timer_5
		LJMP	FINISH
		LCALL	Timer_6
		LJMP	FINISH
		
		




;Timer_0 will start immediately
;Timer_n(1~8) will start only after you call the Timer_Start function
;Timer_0 cannot be stopped by Timer_Stop function
Timer_Init:
		JB		INIT_Timer,FinishInit
		SETB	INIT_Timer
		
		PUSH	DPH
		PUSH	DPL
		PUSH	00H						;R0
		PUSH	02H						;R2  Loop counter
		PUSH	03H						;R3  Store the value of A temporarily

		LCALL	KeTimer2_Init
		
		MOV		DPTR,#CNTVAL
		MOV		R2,#SUM
		MOV		R0,#Timer_CNT1
		CLR		A
INIT:
		MOV		R3,A
		MOVC	A,@A+DPTR
		MOV		@R0,A
		MOV		A,R3
		INC		A
		INC		R0
		DJNZ	R2,INIT
		
		LCALL	KeTimer2_Start
		
		POP		03H
		POP		02H
		POP		00H
		POP		DPL
		POP		DPH

FinishInit:
		RET







;arguments:
;    08H  n
;return:
;    returns 0 if Timer_n is not running
Timer_CheckCTRL:
		PUSH	08H
		
		SETB	C
		CLR		A
RR_LOOP1:
		RRC		A
		DJNZ	08H,RR_LOOP1
		
		ANL		A,Timer_CTRL
		
		POP		08H
		
		RET




;arguments:
;    08H  n
Timer_Start:
		PUSH	08H
		
		SETB	C
		CLR		A
RR_LOOP2:
		RRC		A
		DJNZ	08H,RR_LOOP2
		
		ORL		Timer_CTRL,A
		
		POP		08H
		
		RET
		
		
		
;arguments:
;    08H  n
Timer_Stop:
		PUSH	08H
		
		SETB	C
		CLR		A
RR_LOOP3:
		RRC		A
		DJNZ	08H,RR_LOOP3
		
		CPL		A
		ANL		Timer_CTRL,A
		
		POP		08H
		
		RET









KeTimer2_CB:
		PUSH	DPH
		PUSH	DPL
		PUSH	00H						;R0
		PUSH	02H						;R2  Loop counter
		PUSH	03H						;R3  0,1,2,...
		PUSH	08H						;for argument passing
		
		MOV		R2,#SUM
		MOV		R0,#Timer_CNT1
		MOV		R3,#00H
		MOV		08H,#01H
		
		LCALL	Timer_0
		
TICK:
		MOV		A,R3
		
		ACALL	Timer_CheckCTRL
		JZ		FINISH					;if Timer_CheckCTRL returns 0, goto FINISH
		
		MOV		A,R3
		DEC		@R0
		MOV		A,@R0
		JNZ		FINISH					;if (R0) != 0, goto FINISH
										
		MOV		A,R3					;trigger Timer_n
		MOV		DPTR,#CNTVAL
		MOVC	A,@A+DPTR
		MOV		@R0,A
		MOV		A,R3
		MOV		DPTR,#JMPTAB
		ADD		A,R3
		ADD		A,R3
		ADD		A,R3
		ADD		A,R3
		ADD		A,R3					;A = A*6
		JMP		@A+DPTR
FINISH:
		INC		R3
		INC		R0
		INC		08H
		DJNZ	R2,TICK
		
		POP		08H
		POP		03H
		POP		02H
		POP		00H
		POP		DPL
		POP		DPH
		
		RET
		
		
			
			
		END