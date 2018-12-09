#include "AngleCalc.h"

#include "Ke_MPU6050.h"

#include <math.h>

//float filter(float m, float n);
//void AngleCalc_Init(void);


#define INIT_DELAY


//陀螺仪零点漂移
#define AngleCalc_GyroscopeZero -0.0021


//加速度计零点漂移
#define AngleCalc_AccelerometerZero 0.0


//小车倾角机械零点
#define AngleCalc_MechanicZero 0.024



static float dt = 0.05; //滤波器采样时间

static int Initialized = 0;














static float k1=0.000;  //加速度计的权重值
//static float angle; //得到的倾角
//static float r_ax=0;
//static float r_ay=0;
//static float r_az=0;//参考加速度计向量值

static float result;

static float GetAngleFromAccelerometer();






//static float K1 = 0.02;
static float angle_dot;
static float Q_angle = 0.001;// 过程噪声的协方差
static float Q_gyro = 0.003;//0.003 过程噪声的协方差 过程噪声的协方差为一个一行两列矩阵
static float R_angle = 0.5;// 测量噪声的协方差 既测量偏差
//static float dt = 0.005;//                 
static char  C_0 = 1;
static float Q_bias, angle_err;
static float PCt_0, PCt_1, E;
static float K_0, K_1, t_0, t_1;
static float Pdot[4] = { 0,0,0,0 };
static float PP[2][2] = { { 1, 0 },{ 0, 1 } };

float Kalman_Filter(float Accel, float Gyro)
{
	result += Gyro - Q_bias * dt; //先验估计
	Pdot[0] = Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分

	Pdot[1] = -PP[1][1];
	Pdot[2] = -PP[1][1];
	Pdot[3] = Q_gyro;
	PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
	PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;

	angle_err = Accel - result;	//zk-先验估计

	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];

	E = R_angle + C_0 * PCt_0;

	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;

	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 //后验估计误差协方差
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;

	result += K_0 * angle_err;	 //后验估计
	Q_bias += K_1 * angle_err;	 //后验估计
	angle_dot = Gyro / dt - Q_bias;	 //输出值(后验估计)的微分=角速度

	return result;
}


















#define AngleCalc_MyFilter_COEEFICIENT 100.0

//a为加速度计的倾角，g为陀螺仪测得的一个周期的倾角变化量
float AngleCalc_MyFilter(float a, float g)
{
	static float a_former;
	static float angle;

	float a_delta = a - a_former;
	float a_g_delta = fabsf(a_delta - g);

	float a_weight = 1.0 / (1.0 + AngleCalc_MyFilter_COEEFICIENT*a_g_delta);

	angle = a_weight*a + (1.0 - a_weight)*(angle + g);

	return angle;

}























//单位：秒
void AngleCalc_Init(float interval)
{
	if (!Initialized)
	{
		Initialized = 1;
		dt = interval;

		MPU_Init();


#ifdef INIT_DELAY
		for (uint32_t i = 0; i < 100000; i++);
#endif // INIT_DELAY

		

		short ax, ay, az;//加速度计xyz值

		float tmp = GetAngleFromAccelerometer();  //防止返回3个0

	}
}


float GetAngleFromAccelerometer()    //弧度
{
	short ax, ay, az;//加速度计xyz值

	do {
		MPU_Get_Accelerometer(&ax, &ay, &az);
	} 
	while (ay == 0 && az == 0);


	float ret = atanf((float)ay / (float)az) - AngleCalc_AccelerometerZero;

	return ret;//atanf((float)ay / (float)az);
}

float AngleCalc_GetDeltaAngleFromGyroscope()   //弧度
{

	short gx, gy, gz;//陀螺仪xyz值

	MPU_Get_Gyroscope(&gx, &gy, &gz);

	float ret = gx / (float)16.4 / (float)180 * (float)3.1415926535*dt - AngleCalc_GyroscopeZero;

	return ret; //gy / (float)16.4 / (float)180 * (float)3.1415926535*dt;

}


float AngleCalc_GetAngle(void)
{
	//short gx, gy, gz;//陀螺仪xyz值
	//short ax, ay, az;//加速度计xyz值
	////float axf, ayf, azf;

	//static float G_angle;
	//float A_angle;

	//MPU_Get_Gyroscope(&gx, &gy, &gz);
	//MPU_Get_Accelerometer(&ax, &ay, &az);

	//axf = (float)ax / (float)32767;
	//ayf = (float)ay / (float)32767;
	//azf = (float)az / (float)32767;


	//float fenzi = (axf*r_ax + ayf*r_ay + azf*r_az);
	//float fenmu = sqrtf(
	//	(axf*axf + ayf*ayf + azf*azf)*
	//	(r_ax*r_ax + r_ay*r_ay + r_az*r_az)
	//);
	//float A_angle = acosf(fenzi / fenmu);

	//gy = -(float)gy / 16.4; //方向处理，计算角速度值
	//G_angle += (gy / (float)180 * (float)3.1415926535)*0.05;//角速度积分
	//return filter(A_angle, G_angle);

	//A_angle = atanf(ay / az);

	//result = k1*GetAngleFromAccelerometer() +
	//	(((float)1 - k1)*AngleCalc_GetDeltaAngleFromGyroscope() + result);

	

	//result += 
	//	k1*GetAngleFromAccelerometer() +
	//	((float)1 - k1)*AngleCalc_GetDeltaAngleFromGyroscope();

	//result = GetAngleFromAccelerometer();

	float ret;

	//static float ret;
	//ret += AngleCalc_GetDeltaAngleFromGyroscope();

	ret= Kalman_Filter(GetAngleFromAccelerometer(), AngleCalc_GetDeltaAngleFromGyroscope()) - AngleCalc_MechanicZero;
	//ret = AngleCalc_MyFilter(GetAngleFromAccelerometer(), AngleCalc_GetDeltaAngleFromGyroscope()) - AngleCalc_MechanicZero;

	return ret;
}

//float filter(float m,float n)
//{
//	float angle1;
//	angle1 = k1*m + (1-k1)*n;
//	return angle1;
//	
//}
