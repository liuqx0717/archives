;g_DigitState:  
;    H |S41|S40|S31|S30|S21|S20|S11|S10|
;    Sn1 Sn0:
;        00normal  01dp  10 light  11 close

;g_Digit1:    Digit1~2
;g_Digit2:    Digit3~4

EXTRN	CODE	(Digits_Init)
EXTRN	CODE	(Digits_Sweep)
EXTRN	CODE	(Digits_StartBlink4)
EXTRN	CODE	(Digits_StartBlink3)
EXTRN	CODE	(Digits_StartBlink2)
EXTRN	CODE	(Digits_StartBlink1)
EXTRN	CODE	(Digits_StopBlink4)
EXTRN	CODE	(Digits_StopBlink3)
EXTRN	CODE	(Digits_StopBlink2)
EXTRN	CODE	(Digits_StopBlink1)