;CallBack:
;    Keys_CB
;        arguments:
;            08H  key code


$include (GlobalVars.inc)
$include (KeKeys.inc)

$include (Timer.inc)
	
	
PUBLIC	Timer_0
PUBLIC	Keys_Init

	
	
EXTRN	CODE	(Keys_CB)
	
	
KEYS	SEGMENT	CODE
		RSEG	KEYS
		
		

Keys_Init:
		JB		INIT_Keys,FinishInit
		SETB	INIT_Keys
		
		LCALL	KeKeys_Init
		LCALL	Timer_Init
		
		MOV		Keys_LastCode,#0FFH
		
		
FinishInit:
		RET
		
		
		
		
		
		
		
		
; 20ms
Timer_0:
		PUSH	08H
		LCALL	KeKeys_Scan
		MOV		08H,A
		CLR		C
		SUBB	A,#0FFH
		JZ		FINISH							;If current code is 0FFH(no key), goto FINISH
		MOV		A,08H
		CJNE	A,Keys_LastCode,GENERATE		; If current code is different from last code, goto GENERATE
		SJMP	FINISH
GENERATE:
		LCALL	Keys_CB
FINISH:
		MOV		Keys_LastCode,08H
		POP		08H
		RET









		END