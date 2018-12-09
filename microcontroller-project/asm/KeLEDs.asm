;LED data input/output: 
;    LED1 ~ LED8

$include (C8051F310.INC)
$include (GlobalVars.inc)
	
	
PUBLIC	KeLEDs_Init
PUBLIC	KeLEDs_Output
	
	
	
DAT		BIT		P3.3
CLK		BIT		P3.4
	

KeLEDs 	SEGMENT	CODE
		RSEG	KeLEDs


KeLEDs_Init:
		JB		INIT_KeLEDs,FnishInit
		SETB	INIT_KeLEDs
		MOV		g_LEDs,#0FFH
		ACALL	KeLEDs_Output
FnishInit:
		RET

 

KeLEDs_Output:
		CLR		CLK
		ACALL	KeLEDs_Delay
		MOV		C,g_LED1
		MOV		DAT,C
		SETB	CLK
		ACALL	KeLEDs_Delay
		
		CLR		CLK
		ACALL	KeLEDs_Delay
		MOV		C,g_LED2
		MOV		DAT,C
		SETB	CLK
		ACALL	KeLEDs_Delay
		
		CLR		CLK
		ACALL	KeLEDs_Delay
		MOV		C,g_LED3
		MOV		DAT,C
		SETB	CLK
		ACALL	KeLEDs_Delay
		
		CLR		CLK
		ACALL	KeLEDs_Delay
		MOV		C,g_LED4
		MOV		DAT,C
		SETB	CLK
		ACALL	KeLEDs_Delay
		
		CLR		CLK
		ACALL	KeLEDs_Delay
		MOV		C,g_LED5
		MOV		DAT,C
		SETB	CLK
		ACALL	KeLEDs_Delay
		
		CLR		CLK
		ACALL	KeLEDs_Delay
		MOV		C,g_LED6
		MOV		DAT,C
		SETB	CLK
		ACALL	KeLEDs_Delay
		
		CLR		CLK
		ACALL	KeLEDs_Delay
		MOV		C,g_LED7
		MOV		DAT,C
		SETB	CLK
		ACALL	KeLEDs_Delay
		
		CLR		CLK
		ACALL	KeLEDs_Delay
		MOV		C,g_LED8
		MOV		DAT,C
		SETB	CLK
		ACALL	KeLEDs_Delay

		
		RET


KeLEDs_Delay:
		NOP
		NOP
		
		RET

		END