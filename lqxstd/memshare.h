#include "stdafx.h"


#ifndef _MEMSHARE_H_
#define _MEMSHARE_H_

#include <Windows.h>

#define _DEFAULTBUFFSIZE 1024U

namespace lqx {

	class memshare {
	private:
		const char *_global = "Global\\";
		unsigned int *_msgpos;
		unsigned int *_nread;
		struct param {
			int n;
			int wParam;
			int lParamH;
			int lParamL;
		}*_param;
		unsigned char *_dat;
		bool _terminate;
		int err = 0xF0;   //0xFFF:δ��ʼ��������
		unsigned int _buffersize;
		unsigned int _msgprocessed;
		size_t _size;
		HANDLE _hreceiveevent;
		HANDLE _he1; //receiveevent,manual
		HANDLE _he2; //read,auto
		HANDLE _hm1; //_publicmsgpos
		HANDLE _hm2; //_nread
		HANDLE _hm3; //write data
		HANDLE _hfm;
		HANDLE _phe1; //clear
		char _name[40];
		char _he1name[40];
		char _he2name[40];
		char _hm1name[40];
		char _hm2name[40];
		char _hm3name[40];
		void(*_eventproc)(int n, int wParam, int lParamH, int lParamL);

		void processevent();
		unsigned int decreasenread();

		static unsigned __stdcall receiveevent(void *p);

	public:

		bool init(char *name, size_t size, void(*eventproc)(int n, int wParam, int lParamH, int lParamL), bool global = false, unsigned int buffersize = _DEFAULTBUFFSIZE);
		void clear();  //����Ϣ������(eventproc)�е���ʱ��Ӧ����һ�����߳�������clear�����������
		memshare() {}
		memshare(char *name, size_t size, void(*eventproc)(int n, int wParam, int lParamH, int lParamL), bool global = false, unsigned int buffersize = _DEFAULTBUFFSIZE)
		{
			init(name, size, eventproc, global, buffersize);
		}
		~memshare() { clear(); }

		size_t read(size_t pos, size_t n, void *buff);//����ʵ�ʸ���
		size_t write(size_t pos, size_t n, void *buff);//����ʵ�ʸ���
		void sendevent(int n, int wParam, int lParamH, int lParamL);
		void wait()
		{
			if (err) return;
			if(!_phe1) _phe1 = CreateEvent(NULL, true, false, 0);
			if(_phe1) WaitForSingleObject(_phe1, INFINITE);
		}
	};

}

#endif





/*

#include "stdafx.h"

#ifndef _MEMSHARE_H
#define _MEMSHARE_H

#ifndef _NAMESPACETYPE
#define _NAMESPACETYPE "Global\\"
#endif

#include <Windows.h>
#include <random>

namespace lqx {


	class memshare {
	private:
		const char *errinfo[10] = {
			"�����ɹ���ɡ�",
			"δ��ʼ�����ʼ��ʱ������Ч��",
			"CreateFileMappingʧ�ܡ�",
			"MapViewOfFileʧ�ܡ�",
			"CreateMutexʧ�ܡ�",
			"CreateEventʧ�ܡ�",
			"����receiveevent�߳�ʧ�ܡ�"
			"�����¼������߳�ʧ�ܡ�"

		};
		struct eparam {
			size_t nmsg;
			unsigned short nreadp;
			unsigned short nreadd;
			int n;
			int wParam;
			size_t lParam;
		} *_pbase;
		size_t _nmsg;
		bool terminated;
		unsigned int ntask;
		unsigned int _sendeventinterval;
		char _name[40]= _NAMESPACETYPE;
		char _mname1[40] = _NAMESPACETYPE;
		char _mname2[40] = _NAMESPACETYPE;
		char _mname3[40] = _NAMESPACETYPE;
		char _mname4[40] = _NAMESPACETYPE;
		char _mname5[40] = _NAMESPACETYPE;
		char _ename1[40] = _NAMESPACETYPE;
		char _ename2[40] = _NAMESPACETYPE;
		char _ename3[40] = _NAMESPACETYPE;
		unsigned char *_dbase;
		size_t _size;
		size_t psize;
		int err = 1;
		HANDLE hfm;
		HANDLE hm1;//data
		HANDLE hm2;//nreadp
		HANDLE hm3;//nreadd
		HANDLE hm4;//write param
		HANDLE hm5;//write data
		HANDLE phm1;
		//HANDLE phm2;
		HANDLE he1;//event
		HANDLE he2;//write param
		HANDLE he3;//write data
		HANDLE hreceiveevent;

#ifndef _WIN64
		std::mt19937 mt;
#else
		std::mt19937_64 mt;
#endif
		

		void(*_eventproc)(int n, int wParam, size_t lParam);

		static unsigned __stdcall receiveevent(void *);
		static unsigned __stdcall waitreceiveevent(void *);

		void increasenreadp();
		unsigned short decreasenreadp();
		void increasenreadd();
		unsigned short decreasenreadd();
	public:

		void init(char *name, size_t size, void(*eventproc)(int n, int wParam, size_t lParam), unsigned int sendeventinterval = 1);
		void clear();
		memshare(char *name, size_t size, void(*eventproc)(int n, int wParam, size_t lParam), unsigned int sendeventinterval = 1) { init(name, size, eventproc, sendeventinterval); }
		memshare() { ; }
		~memshare() { clear(); }

		const char* geterrinfo() { return errinfo[err]; }
		unsigned int getntask() { return ntask; }
		HANDLE getreceiveevent() { return hreceiveevent; }

		size_t read(size_t pos, size_t n, void *buff);//����ʵ�ʸ���
		size_t write(size_t pos, size_t n, void *buff);//����ʵ�ʸ���
		void sendevent(int n, int wParam, size_t lParam);
	};


}





#endif




*/