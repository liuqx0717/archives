$include (C8051F310.INC)
$include (GlobalVars.inc)
	

PUBLIC	KeLED_init
PUBLIC	KeLED_on
PUBLIC	KeLED_off
PUBLIC	KeLED_switch


LED		BIT 	P0.0
	
	
	
KELED  	SEGMENT	CODE
		RSEG	KELED
			
			
KeLED_init:
		JB		INIT_KeLED,FinishInit
		SETB	INIT_KeLED
		
		SETB	LED
		
FinishInit:
		RET
	
	
KeLED_on:
		CLR		LED
		RET
		
KeLED_off:
		SETB	LED
		RET
		
KeLED_switch:
		CPL		LED
		RET
		
		
		
		END