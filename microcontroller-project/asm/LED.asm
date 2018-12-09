$include (KeLED.inc)
$include (GlobalVars.inc)
	
PUBLIC	LED_init
PUBLIC	LED_on
PUBLIC	LED_off
PUBLIC	LED_switch
	
LED  	SEGMENT	CODE
		RSEG	LED
			
			
LED_init:
		JB		INIT_LED,FinishInit
		SETB	INIT_LED
		
		LCALL	KeLED_init
		
FinishInit:
		RET
	
	
	
	
LED_on:
		LCALL	KeLED_on
		RET
		
LED_off:
		LCALL	KeLED_off
		RET
		
LED_switch:
		LCALL	KeLED_switch
		RET
		
		
		
		END