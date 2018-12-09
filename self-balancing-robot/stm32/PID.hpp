#ifndef __PID_HPP
#define __PID_HPP

#include <cmath>
#include "MovingAverageFilter.hpp"

//微分时滑动平均滤波器的阶数
#define PID_D_ORDER 10U

template<class T> class PID {
private:

	T _LastDelta = 0;
	T _SumDelta = 0;

	T *_in = 0;
	T _target = 0;

	MovingAverageFilter<T> filter;
	T _filterbuffer[PID_D_ORDER];


public:

	T _Kp = 0;
	T _Ki = 0;
	T _Kd = 0;
	T _SumMax = 0;

	void init(T Kp, T Ki, T Kd, T *in, T target, T SumMax) {
		_Kp = Kp;
		_Ki = Ki;
		_Kd = Kd;
		_in = in;
		_target = target;
		_SumMax = SumMax;
		_LastDelta = _SumDelta = 0;
		filter.init(PID_D_ORDER, _filterbuffer);

	}

	PID(T Kp, T Ki, T Kd, T *in, T target, T SumMax) { init(Kp, Ki, Kd, in, target, SumMax); }
	PID() { ; }

	void SetTarget(T target) { _target = target; }
	void IncreaseTarget(T delta) { _target += delta; }
	void DecreaseTarget(T delta) { _target -= delta; }
	T GetTarget() { return _target; }


	//每隔相等的时间间隔调用一次这个函数
	T Update()
	{
		//防止空指针
		if (!_in) return 0;

		T delta = _target - *_in;
		if (fabsf(_SumDelta + delta) < _SumMax || !_SumMax) {
			_SumDelta += delta;
		}
		T ret = _Kp*delta + _Ki*_SumDelta + _Kd*filter.update(delta - _LastDelta);
		_LastDelta = delta;
		return ret;
	}


};





#endif // !__PID_HPP


