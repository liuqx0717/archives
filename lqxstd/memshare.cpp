#include "stdafx.h"



#define _RECEIVEEVENTINTERV 500
#define _READ_TIMEOUT 5000

#include "memshare.h"
#include "md5.h"
#include <process.h>

namespace lqx {

	bool memshare::init(char *name, size_t size, void(*eventproc)(int n, int wParam, int lParamH, int lParamL), bool global, unsigned int buffersize)
	{
		if (!(err & 0xF0)) clear();

		int lasterr;
		size_t totalsize;

		_terminate = false;
		_buffersize = buffersize;
		_size = size;
		_eventproc = eventproc;
		_msgpos = 0;
		_nread = 0;
		_dat = 0;
		_param = 0;
		_hreceiveevent = _he1 = _he2 = _hm1 = _hm2 = _hm3 = _hfm = _phe1 = 0;
		totalsize = sizeof(_msgpos) + sizeof(_nread) + sizeof(param)*_buffersize + _size;

		if (global) {
			strcpy(_name, _global);
			strcpy(_he1name, _global);
			strcpy(_he2name, _global);
			strcpy(_hm1name, _global);
			strcpy(_hm2name, _global);
			strcpy(_hm3name, _global);
		}
		else
			_name[0] = _he1name[0] = _he2name[0] = _hm1name[0] = _hm2name[0] = _hm3name[0] = 0;

		lqx::MD5 md5;
		md5.update((void*)name, strlen(name));
		strcat(_name, md5.toString().c_str());
		md5.update((void*)_name, 16);
		strcat(_he1name, md5.toString().c_str());
		md5.update((void*)_he1name, 16);
		strcat(_he2name, md5.toString().c_str());
		md5.update((void*)_he2name, 16);
		strcat(_hm1name, md5.toString().c_str());
		md5.update((void*)_hm1name, 16);
		strcat(_hm2name, md5.toString().c_str());
		md5.update((void*)_hm2name, 16);
		strcat(_hm3name, md5.toString().c_str());

#ifdef _WIN64
		_hfm = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, totalsize >> 32, totalsize, _name);
#else
		_hfm = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, totalsize, _name);
#endif

		if (!_hfm) goto e;
		lasterr = GetLastError();

		if (!(_msgpos = (unsigned int *)MapViewOfFile(_hfm, FILE_MAP_ALL_ACCESS, 0, 0, totalsize))) goto e;
		_nread = _msgpos + 1;
		_param = (param*)(_nread + 1);
		_dat = (unsigned char *)_param + sizeof(param)*_buffersize;
		if (lasterr == ERROR_ALREADY_EXISTS) {
			WaitForSingleObject(_hm1, INFINITE);
			_msgprocessed = *_msgpos;
			ReleaseMutex(_hm1);
		}
		else {
			*_msgpos = *_nread = _msgprocessed = 0;
		}

		if (!(_hm1 = CreateMutex(NULL, false, _hm1name))) goto e;
		if (!(_hm2 = CreateMutex(NULL, false, _hm2name))) goto e;
		if (!(_hm3 = CreateMutex(NULL, false, _hm3name))) goto e;
		if (!(_he1 = CreateEvent(NULL, true, false, _he1name))) goto e;
		if (!(_he2 = CreateEvent(NULL, false, false, _he2name))) goto e;

		if (!(_hreceiveevent = (HANDLE)_beginthreadex(NULL, 0, &receiveevent, this, 0, 0))) goto e;

		err = 0x00;
		return true;


	e:
		err = 0x0F;
		return false;

	}

	void memshare::clear()
	{
		if (err & 0xF0) return;

		_terminate = true;
		if (_hreceiveevent) {
			WaitForSingleObject(_hreceiveevent, INFINITE);
			CloseHandle(_hreceiveevent);
		}
		if (_msgpos)UnmapViewOfFile((void *)_msgpos);
		if (_hfm) CloseHandle(_hfm);
		if (_hm1) CloseHandle(_hm1);
		if (_hm2) CloseHandle(_hm2);
		if (_hm3) CloseHandle(_hm3);
		if (_he1) CloseHandle(_he1);
		if (_he2) CloseHandle(_he2);

		if (_phe1) {
			SetEvent(_phe1);
			ResetEvent(_phe1);
			CloseHandle(_phe1);
		}

		err = 0xF0;
	}


	unsigned int memshare::decreasenread()
	{
		unsigned int tmp;
		--*_nread;
		tmp = *_nread;
		if (!tmp) SetEvent(_he2);
		return tmp;
	}



	unsigned __stdcall memshare::receiveevent(void *p)
	{

		while (!((memshare*)p)->_terminate) {

			WaitForSingleObject(((memshare*)p)->_he1, _RECEIVEEVENTINTERV);

			((memshare*)p)->processevent();

		}
		return 0;
	}



	void memshare::processevent()
	{
		unsigned int n;

		WaitForSingleObject(_hm1, INFINITE);
		n = *_msgpos;
		ReleaseMutex(_hm1);

		while (_msgprocessed != n) {

			(_msgprocessed == _buffersize - 1) ? _msgprocessed = 0 : ++_msgprocessed;
			//cout << "msgpos:" << n << " msgprocessed:" << _msgprocessed << ' ';
			(*(_eventproc))(
				_param[_msgprocessed].n,
				_param[_msgprocessed].wParam,
				_param[_msgprocessed].lParamH,
				_param[_msgprocessed].lParamL
				);

		}
	}



	void memshare::sendevent(int n, int wParam, int lParamH, int lParamL)
	{
		if (err) return;

		WaitForSingleObject(_hm1, INFINITE);

		(*_msgpos == _buffersize - 1) ? *_msgpos = 0 : ++*_msgpos;
		_param[*_msgpos].n = n; _param[*_msgpos].wParam = wParam; _param[*_msgpos].lParamH = lParamH; _param[*_msgpos].lParamL = lParamL;

		SetEvent(_he1);
		ResetEvent(_he1);

		ReleaseMutex(_hm1);
	}


	size_t memshare::read(size_t pos, size_t n, void *buff)
	{
		if (err) return 0;

		if (!n) return 0;

		WaitForSingleObject(_hm2, INFINITE);
		++*_nread;
		ReleaseMutex(_hm2);

		size_t nread = (pos + n <= _size) ? n : (_size - pos);
		CopyMemory(buff, _dat, nread);
		//Sleep(50000);

		WaitForSingleObject(_hm2, INFINITE);
		decreasenread();
		ReleaseMutex(_hm2);

		return nread;
	}

	size_t memshare::write(size_t pos, size_t n, void *buff)
	{
		if (err) return 0;

		if (!n) return 0;

		WaitForSingleObject(_hm3, INFINITE);

		WaitForSingleObject(_hm2, INFINITE);
		if (*_nread) {
			ReleaseMutex(_hm2);
			if (WaitForSingleObject(_he2, _READ_TIMEOUT) == WAIT_TIMEOUT)
				while (decreasenread());
		}
		else
			ReleaseMutex(_hm2);

		size_t nwrite = (pos + n <= _size) ? n : (_size - pos);
		CopyMemory(_dat, buff, nwrite);

		ReleaseMutex(_hm3);

		return nwrite;
	}


}











/*
#include "stdafx.h"

#include "memshare.h"
#include "md5.h"
#include <process.h>


#define READP_TIMEOUT 5000
#define READD_TIMEOUT 20000
#define	RECEIVEEVENT_INTERVEL 2000


namespace lqx {
	void memshare::init(char *name, size_t size, void(*eventproc)(int n, int wParam, size_t lParam), unsigned int sendeventinterval)
	{
		byte *tmp;
		std::random_device rd;

		if (err != 1) return;
		if (!(name&&size&&eventproc)) return;

		terminated = false;
		ntask = 0;
		_nmsg = 0;
		_pbase = 0;
		hfm = hm1 = hm2 = hm3 = hm4 = hm5 = phm1 = he1 = he2 = he3 = hreceiveevent = 0;
		mt.seed(rd());

		size_t l = strlen(_NAMESPACETYPE) + 15;
		_size = size;
		_eventproc = eventproc;
		psize = sizeof(eparam);
		_sendeventinterval = sendeventinterval;

		lqx::MD5 md5;
		md5.update((void*)name, strlen(name));
		strcat(_name, md5.toString().c_str());
		md5.reset();
		md5.update((void*)_name, l);
		strcat(_mname1, md5.toString().c_str());
		md5.reset();
		md5.update((void*)_mname1, l);
		strcat(_mname2, md5.toString().c_str());
		md5.reset();
		md5.update((void*)_mname2, l);
		strcat(_mname3, md5.toString().c_str());
		md5.reset();
		md5.update((void*)_mname3, l);
		strcat(_mname4, md5.toString().c_str());
		md5.reset();
		md5.update((void*)_mname4, l);
		strcat(_mname5, md5.toString().c_str());
		md5.reset();
		md5.update((void*)_mname5, l);
		strcat(_ename1, md5.toString().c_str());
		md5.reset();
		md5.update((void*)_ename1, l);
		strcat(_ename2, md5.toString().c_str());
		md5.reset();
		md5.update((void*)_ename2, l);
		strcat(_ename3, md5.toString().c_str());

#ifdef _WIN64
		hfm = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, (psize + _size) >> 32, psize + _size, _name);
#else
		hfm = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, psize + _size, _name);
#endif

		if (!hfm) {
			err = 2;
			return;
		}

		if (!(tmp = (byte*)MapViewOfFile(hfm, FILE_MAP_ALL_ACCESS, 0, 0, psize + _size))) {
			err = 3;
			return;
		}
		_dbase = tmp + psize;
		//ZeroMemory(tmp, psize);
		_pbase = (eparam*)tmp;
		*_pbase = { 0,0,0,0,0,0 };

		if (!(hm1 = CreateMutex(NULL, false, _mname1))) {
			err = 4;
			return;
		}

		if (!(hm2 = CreateMutex(NULL, false, _mname2))) {
			err = 4;
			return;
		}

		if (!(hm3 = CreateMutex(NULL, false, _mname3))) {
			err = 4;
			return;
		}

		if (!(hm4 = CreateMutex(NULL, false, _mname4))) {
			err = 4;
			return;
		}

		if (!(hm5 = CreateMutex(NULL, false, _mname5))) {
			err = 4;
			return;
		}


		if (!(phm1 = CreateMutex(NULL, false, NULL))) {
			err = 4;
			return;
		}

		if (!(he1 = CreateEvent(NULL, true, false, _ename1))) {
			err = 5;
			return;
		}

		if (!(he2 = CreateEvent(NULL, false, false, _ename2))) {
			err = 5;
			return;
		}

		if (!(he3 = CreateEvent(NULL, false, false, _ename3))) {
			err = 5;
			return;
		}

		if (!(hreceiveevent = (HANDLE)_beginthreadex(NULL, 0, &receiveevent, this, 0, 0))) {
			err = 6;
			return;
		}


		err = 0;



	}

	void memshare::increasenreadp()
	{
		WaitForSingleObject(hm2, INFINITE);
		++(_pbase->nreadp);
		ReleaseMutex(hm2);
	}

	unsigned short memshare::decreasenreadp()
	{
		unsigned short tmp;
		WaitForSingleObject(hm2, INFINITE);
		--(_pbase->nreadp);
		tmp = _pbase->nreadp;
		if (!_pbase->nreadp) SetEvent(he2);
		ReleaseMutex(hm2);
		return tmp;
	}

	void memshare::increasenreadd()
	{
		WaitForSingleObject(hm3, INFINITE);
		++(_pbase->nreadd);
		ReleaseMutex(hm3);
	}

	unsigned short memshare::decreasenreadd()
	{
		unsigned short tmp;
		WaitForSingleObject(hm3, INFINITE);
		--(_pbase->nreadd);
		tmp = _pbase->nreadd;
		if (!_pbase->nreadd) SetEvent(he3);
		ReleaseMutex(hm3);
		return tmp;
	}

	unsigned __stdcall memshare::receiveevent(void *p)
	{
		memshare *t = (memshare*)p;
		if (t->err) return 0;

		while (!t->terminated) {

			if (WaitForSingleObject(t->he1, RECEIVEEVENT_INTERVEL) == WAIT_TIMEOUT) continue;

			t->increasenreadp();
			//if (!_beginthreadex(NULL, 0, &(t->waitreceiveevent), p, 0, NULL)) t->err = 7;
			_beginthreadex(NULL, 0, &(t->waitreceiveevent), p, 0, NULL);


		}
		return 0;
	}

	unsigned __stdcall memshare::waitreceiveevent(void *p)
	{
		eparam tmp;
		memshare *t = (memshare*)p;
		if (t->err) return 0;

		tmp = *(t->_pbase);
		//Sleep(400);////////////////////////////////////////////////

		if (tmp.nmsg == t->_nmsg) {
			t->decreasenreadp();
			return 0;
		}
		t->_nmsg = tmp.nmsg;

		t->decreasenreadp();

		WaitForSingleObject(t->phm1, INFINITE);
		++(t->ntask);
		(*(t->_eventproc))(tmp.n, tmp.wParam, tmp.lParam);
		--(t->ntask);
		ReleaseMutex(t->phm1);
		return 0;
	}



	void memshare::sendevent(int n, int wParam, size_t lParam)
	{
		if (err) return;

		WaitForSingleObject(hm4, INFINITE);

		size_t r = mt();

		eparam tmp;
		WaitForSingleObject(hm2, INFINITE);
		tmp = *_pbase;
		if (tmp.nreadp) {
			ReleaseMutex(hm2);
			if (WaitForSingleObject(he2, READP_TIMEOUT) == WAIT_TIMEOUT)
				while (decreasenreadp());
		}
		else
			ReleaseMutex(hm2);

		//tmp.n = n; tmp.wParam = wParam; tmp.lParam = lParam;
		_pbase->n = n; _pbase->wParam = wParam; _pbase->lParam = lParam; _pbase->nmsg = r;
		SetEvent(he1);
		ResetEvent(he1);
		if (_sendeventinterval) Sleep(_sendeventinterval);
		//Sleep(100);////////////////////////////////////////////////////////////////////////////////////
		ReleaseMutex(hm4);


	}

	size_t memshare::read(size_t pos, size_t n, void *buff)
	{
		if (err) return 0;

		if (!n) return 0;

		WaitForSingleObject(hm5, INFINITE);
		increasenreadd();
		ReleaseMutex(hm5);

		size_t nread = (pos + n <= _size) ? n : (_size - pos);
		CopyMemory(buff, _dbase, nread);
		decreasenreadd();
		return nread;
	}

	size_t memshare::write(size_t pos, size_t n, void *buff)
	{
		if (err) return 0;

		if (!n) return 0;

		WaitForSingleObject(hm5, INFINITE);

		eparam tmp;
		WaitForSingleObject(hm3, INFINITE);
		tmp = *_pbase;
		if (tmp.nreadd) {
			ReleaseMutex(hm3);
			if (WaitForSingleObject(he3, READD_TIMEOUT) == WAIT_TIMEOUT)
				while (decreasenreadd());
		}
		else
			ReleaseMutex(hm3);

		size_t nwrite = (pos + n <= _size) ? n : (_size - pos);
		CopyMemory(_dbase, buff, nwrite);

		ReleaseMutex(hm5);
		return nwrite;
	}

	void memshare::clear()
	{
		if (err == 1) return;
		terminated = true;
		if (hreceiveevent) WaitForSingleObject(hreceiveevent, INFINITE);
		if (_pbase)UnmapViewOfFile((void *)_pbase);
		if (hfm) CloseHandle(hfm);
		if (hm1) CloseHandle(hm1);
		if (hm2) CloseHandle(hm2);
		if (hm3) CloseHandle(hm3);
		if (hm4) CloseHandle(hm4);
		if (hm5) CloseHandle(hm5);
		if (phm1) CloseHandle(phm1);
		if (he1) CloseHandle(he1);
		if (he2) CloseHandle(he2);
		if (he3) CloseHandle(he3);
		if (hreceiveevent) CloseHandle(hreceiveevent);

		err = 1;
	}

}



*/