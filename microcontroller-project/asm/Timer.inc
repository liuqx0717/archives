;Timer_0 will start immediately
;Timer_n(1~8) will start only after you call the Timer_Start function
;Timer_0 cannot be stopped by Timer_Stop function
EXTRN	CODE	(Timer_Init)
	
	
	
;arguments:
;    08H  n
;return:
;    returns 0 if Timer_n is not running
EXTRN	CODE	(Timer_CheckCTRL)
	
	
	
;arguments:
;    08H  n
EXTRN	CODE	(Timer_Start)
	
	
	
;arguments:
;    08H  n
EXTRN	CODE	(Timer_Stop)