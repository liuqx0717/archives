$include (C8051F310.INC)
$include (GlobalVars.inc)
	

PUBLIC	KeKeys_Init
PUBLIC	KeKeys_Scan

	
	
KEKEYS	SEGMENT	CODE
		RSEG	KEKEYS
	
	
	
KeKeys_Init:
		JB		INIT_KeKeys,FinishInit
		SETB	INIT_KeKeys
		
		
FinishInit:
		RET
	
	
	
	
	
	
;summary
;    detects which key is pressed down
;return value
;    the key code (00~09 means num0~9, 10~15 means F1~6, 0FFH means no key)
KeKeys_Scan:	
			MOV		P2,#11101111B
			ACALL	KeKeys_Delay
			MOV		A,P2
			CJNE	A,#0EEH,Keyboard01
			MOV		A,#00
			AJMP	BACK
Keyboard01:	
			CJNE	A,#0EDH,Keyboard02
			MOV		A,#01
			AJMP	BACK
Keyboard02:	
			CJNE	A,#0EBH,Keyboard03
			MOV		A,#02
			AJMP	BACK
Keyboard03:	
			CJNE	A,#0E7H,Keyboard04
			MOV		A,#03
			AJMP	BACK
Keyboard04:
			MOV		P2,#11011111B
			ACALL	KeKeys_Delay
			MOV		A,P2
			CJNE	A,#0DEH,Keyboard05
			MOV		A,#04
			AJMP	BACK
Keyboard05:	
			CJNE	A,#0DDH,Keyboard06
			MOV		A,#05
			LJMP	BACK
Keyboard06:	
			CJNE	A,#0DBH,Keyboard07
			MOV		A,#06
			AJMP	BACK
Keyboard07:	
			CJNE	A,#0D7H,Keyboard08
			MOV		A,#07
			AJMP	BACK
Keyboard08:	
			MOV		P2,#10111111B
			ACALL	KeKeys_Delay
			MOV		A,P2
			CJNE	A,#0BEH,Keyboard09
			MOV		A,#08
			AJMP	BACK
Keyboard09:	CJNE	A,#0BDH,Keyboard10
			MOV		A,#09
			AJMP	BACK
Keyboard10:	
			CJNE	A,#0BBH,Keyboard11
			MOV		A,#10
			AJMP	BACK
Keyboard11:	
			CJNE	A,#0B7H,Keyboard12
			MOV		A,#11
			AJMP	BACK
Keyboard12:	
			MOV		P2,#01111111B
			ACALL	KeKeys_Delay
			MOV		A,P2
			CJNE	A,#7EH,Keyboard13
			MOV		A,#12
			AJMP	BACK
Keyboard13:	
			CJNE	A,#7DH,Keyboard14
			MOV		A,#13
			AJMP	BACK
Keyboard14:	
			CJNE	A,#7BH,Keyboard15
			MOV		A,#14
			AJMP	BACK
Keyboard15:	
			CJNE	A,#77H,NOKEY
			MOV		A,#15
			AJMP	BACK
NOKEY:
			MOV		A,#0FFH
BACK:		
			RET
	
	
	
KeKeys_Delay:


			RET
	
	
	
		END