#ifndef _LDASM_

#define _LDASM_

#ifndef _WIN64

#ifdef __cplusplus

extern "C" {

	namespace lqx {

#endif



		unsigned long __fastcall SizeOfCode(void *Code, unsigned char **pOpcode);



		unsigned long __fastcall SizeOfProc(void *Proc);



		char __fastcall IsRelativeCmd(unsigned char *pOpcode);



#ifdef __cplusplus

	}

}

#endif

#endif

#endif