//By Jason Yan
#ifndef __ANGLECALC_H
#define __ANGLECALC_H


//单位：秒
void AngleCalc_Init(float interval);

float AngleCalc_GetAngle(void);

float AngleCalc_GetAngleFromAccelerometer();

float AngleCalc_GetDeltaAngleFromGyroscope();


#endif