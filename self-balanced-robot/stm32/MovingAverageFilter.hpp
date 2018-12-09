#ifndef __MOVINGAVERAGEFILTER_HPP
#define __MOVINGAVERAGEFILTER_HPP



template<class T> class MovingAverageFilter {
private:
	T _order = 0;
	int _order_int = 0;
	T *_buffer = 0;
	T _ret = 0;

public:
	void init(T order, T *buffer)
	{
		_order = order;
		_order_int = (int)order;
		_buffer = buffer;
		_ret = 0;
		for (int i = 0; i < _order_int; i++) {
			buffer[i] = 0;
		}

	}

	MovingAverageFilter() { ; }
	MovingAverageFilter(T order, T *buffer) { init(order, buffer); }

	T update(T data)
	{

		_ret -= _buffer[0] / _order;

		for (int i = 1; i < _order_int; i++) {
			_buffer[i - 1] = _buffer[i];
		}

		_buffer[_order_int - 1] = data;
		_ret += data / _order;

		return _ret;
	}


};



#endif // !__MOVINGAVERAGEFILTER_HPP
