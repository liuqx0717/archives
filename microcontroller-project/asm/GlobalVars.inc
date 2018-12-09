; 08H~1FH:  local variables(arguments) & global variables
; 20H~2FH:  bits (00H~3FH)
; 30H~7FH:  stack & global variables

; A,B,C:      volatile


Timer_CNT1			EQU		18H
Timer_CNT8			EQU		1FH
	

Timer_CTRL			EQU		17H      ;H |1|2|3|4|5|6|7|8| L
	
LEDs_Pattern		EQU		16H
	
Keys_LastCode		EQU		15H
	
Beep_Count			EQU		14H
Beep_Total			EQU		13H
Beep_State			EQU		12H
	
g_Digit1			EQU		11H       ;Digit1~2
g_Digit2			EQU		10H       ;Digit3~4

TEST3_MainState		EQU		7FH

PASSWORD_State		EQU		7EH
PASSWORD_PSW1		EQU		7DH
PASSWORD_PSW2		EQU		7CH
HOMEWORK_Count		EQU		7BH
HOMEWORK_Second1	EQU		7AH
HOMEWORK_Second2	EQU		79H
HOMEWORK_Second3	EQU		78H
HOMEWORK_Second		EQU		77H
CALCULATE_NUM		EQU		76H
CALCULATE_1			EQU		75H
CALCULATE_2			EQU		74H



g_LEDs				EQU		20H
g_LED1				BIT		00H
g_LED2				BIT		01H
g_LED3				BIT		02H
g_LED4				BIT		03H
g_LED5				BIT		04H
g_LED6				BIT		05H
g_LED7				BIT		06H
g_LED8				BIT		07H
	
INT_C_old			BIT		08H
	
INIT_KeLED			BIT		09H
INIT_KeBeep			BIT		10H
INIT_KeKeys			BIT		11H
INIT_LED			BIT		12H
INIT_Beep			BIT		13H
INIT_Timer			BIT		14H
INIT_KeTimer2		BIT		15H
INIT_KeLEDs			BIT		16H
INIT_LEDs			BIT		17H
INIT_Keys			BIT		18H
INIT_KeDigits		BIT		19H
INIT_Digits			BIT		1AH
;INIT_
;INIT_
;INIT_
;INIT_

Digits_State		EQU		24H    
Digits_State7		BIT		20H
Digits_State0		BIT		27H
	
g_DigitState		EQU		25H       ;H |S41|S40|S31|S30|S21|S20|S11|S10|
g_DigitState7		BIT		28H	      ;Sn1 Sn0:
g_DigitState0		BIT		2FH		  ;    00normal  01dp  10 light  11 close
	
Digits_LastState	EQU		26H
Digits_LastState0	BIT		30H
Digits_LastState7	BIT		37H
	
HOMEWORK_State		EQU		27H
HOMEWORK_State7		BIT		38H
HOMEWORK_State0		BIT		3FH
CAL_STATE1			BIT		40H
CAL_STATE2			BIT		41H
CAL_STATE3			BIT		42H

