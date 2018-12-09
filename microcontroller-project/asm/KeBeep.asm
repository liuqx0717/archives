$include (C8051F310.INC)
$include (GlobalVars.inc)
	

PUBLIC	KeBeep_Init
PUBLIC	KeBeep_On
PUBLIC	KeBeep_Off
PUBLIC	KeBeep_Switch


BEEP	BIT		P3.1
	
	
KEBEEP 	SEGMENT	CODE
		RSEG	KEBEEP
			
KeBeep_Init:
		JB		INIT_KeBeep,FinishInit
		SETB	INIT_KeBeep
		
		CLR		BEEP
		
FinishInit:
		RET
		
		
		
KeBeep_On:
		SETB	BEEP
		RET
		
KeBeep_Off:
		CLR		BEEP
		RET
		
KeBeep_Switch:
		CPL		BEEP
		RET
		
		
		
		
		END