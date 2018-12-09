#ifndef __MOTOR_H
#define __MOTOR_H


//speed范围：-1 ~ +1，超出范围的话取 1 (或 -1)
void Motor_SetLeftSpeed(float speed);



//speed范围：-1 ~ +1，超出范围的话取 1 (或 -1)
void Motor_SetRightSpeed(float speed);



#endif // !__MOTOR_H
