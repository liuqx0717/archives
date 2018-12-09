#ifndef __MOVEMENTCONTROL_H
#define __MOVEMENTCONTROL_H


//刷新间隔，每隔多少个timer的周期
#define MOVEMENTCONTROL_INTERVAL_COUNT 5


//刷新间隔，等于MOVEMENTCONTROL_INTERVAL_COUNT乘上timer的周期
#define MOVEMENTCONTROL_INTERVAL_IN_SECONDS 0.010




void MovementControl_Init();
































//void MovementControl_StartPIDErrect();
//void MovementControl_StopPIDErrect();
//
//
//void MovementControl_StartPIDSpeed();
//void MovementControl_StopPIDSpeed();
//
//void MovementControl_StartPIDInnerErrect();
//void MovementControl_StopPIDErrect();



#endif // !__MOVEMENTCONTROL_H
