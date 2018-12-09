#include "stdafx.h"

#ifndef AES_H_ 
#define AES_H_ 

namespace lqx {

	class AES
	{
	public:
		typedef enum ENUM_KeySize_
		{
			BIT128 = 0,
			BIT192,
			BIT256
		}ENUM_KEYSIZE;
	public:
		AES(ENUM_KEYSIZE keysize, unsigned char *key);        //128位key：16字节  192位key：24字节    256位key：32字节   超过的部分将被忽略
		~AES(void);
		void Cipher(unsigned char *input, unsigned char *output);   // input、output均为16字节
		void InvCipher(unsigned char *input, unsigned char *output);// input、output均为16字节
	protected:
		unsigned char *RotWord(unsigned char *word);
		unsigned char *SubWord(unsigned char *word);
		void AddRoundKey(int round);
		void SubBytes();
		void InvSubBytes();
		void ShiftRows();
		void InvShiftRows();
		void MixColumns();
		void InvMixColumns();
		static unsigned char gfmultby01(unsigned char b)
		{
			return b;
		}

		static unsigned char gfmultby02(unsigned char b)
		{
			if (b < 0x80)
				return (unsigned char)(int)(b << 1);
			else
				return (unsigned char)((int)(b << 1) ^ (int)(0x1b));
		}

		static unsigned char gfmultby03(unsigned char b)
		{
			return (unsigned char)((int)gfmultby02(b) ^ (int)b);
		}

		static unsigned char gfmultby09(unsigned char b)
		{
			return (unsigned char)((int)gfmultby02(gfmultby02(gfmultby02(b))) ^
				(int)b);
		}

		static unsigned char gfmultby0b(unsigned char b)
		{
			return (unsigned char)((int)gfmultby02(gfmultby02(gfmultby02(b))) ^
				(int)gfmultby02(b) ^
				(int)b);
		}

		static unsigned char gfmultby0d(unsigned char b)
		{
			return (unsigned char)((int)gfmultby02(gfmultby02(gfmultby02(b))) ^
				(int)gfmultby02(gfmultby02(b)) ^
				(int)(b));
		}

		static unsigned char gfmultby0e(unsigned char b)
		{
			return (unsigned char)((int)gfmultby02(gfmultby02(gfmultby02(b))) ^
				(int)gfmultby02(gfmultby02(b)) ^
				(int)gfmultby02(b));
		}
		int Nb;
		int Nk;
		int Nr;
		unsigned char *key;// the seed key. size will be 4 * keySize from ctor.
		typedef struct BYTE4_
		{
			unsigned char w[4];
		}BYTE4;
		BYTE4 *w;
		unsigned char * State[4];
		/*
		private byte[,] iSbox;  // inverse Substitution box
		private byte[,] w;      // key schedule array.
		private byte[,] Rcon;   // Round constants.
		private byte[,] State;  // State matrix*/

	};

}

#endif /* AES_H_ */ 