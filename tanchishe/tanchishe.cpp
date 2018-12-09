// sy2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <Windows.h>
#include <iostream>
#include <process.h>

#include <conio.h>

//#include <Iphlpapi.h>

//#include <TlHelp32.h>
//#include <vector>

//#include <lqxstd/procOp.h>
//#include <lqxstd/memshare.h>
//#include <lqxstd/others.h>
//#include <lqxstd/md5.h>
#pragma comment(lib,LL)

//#include <detours.h>
#pragma comment(lib,DL)


using std::cout;
using std::cin;


//void proc(int n, size_t w, size_t l)
//{
//	cout << n << '\n';
//}

#define SNAKESIZE 5U

enum _pointtype {
	PT_BACKGROUND,
	PT_SNAKEHEAD,
	PT_SNAKEBODY,
	PT_SNAKETAIL,
	PT_FOOD,
	PT_WALL
};

enum _snakestate {
	SS_MOVE,
	SS_CRASH,
	SS_EAT
};

enum _command {
	CMD_LEFT,
	CMD_RIGHT,
	CMD_UP,
	CMD_DOWN,
	CMD_STOP,
	CMD_PAUSE,
	CMD_CONTINUE
};

const _command counterdirect[] = {
	CMD_RIGHT,
	CMD_LEFT,
	CMD_DOWN,
	CMD_UP
};

struct _coord {
	int x;
	int y;
};

class _snake;

_pointtype scr[64 * 64];
int width, height, scrsize;
void(__stdcall*procaddr)(_pointtype *buff, _coord *snake, int snakesize, _snakestate state);
DWORD interval;
_command *cmd;
HANDLE mutex;

inline int getindex(int x, int y) {
	return y*width + x;
}

void genfood()
{
	int r;
	do {
		r = rand() % scrsize;
	} while (scr[r] != PT_BACKGROUND);
	scr[r] = PT_FOOD;
}

class _snake {
private:
	bool cleared = true;
	_coord *coord;
	_coord *coord_old;
	int size;
	int size_old;
	_command currentdir = CMD_UP;

public:

	void init(int maxsize, _coord firstcoord)
	{
		coord = new _coord[maxsize];
		coord_old = new _coord[maxsize];
		size = SNAKESIZE;
		size_old = 0;
		coord[0] = firstcoord;
		for (int i = 1; i < SNAKESIZE; ++i)
			coord[i] = { firstcoord.x,coord[i - 1].y + 1 };
		update_to_screen();
		cleared = false;
	}

	_coord *getfirstcoord() const { return coord; }
	int getsize() const { return size; }
	_snakestate move(_command direct);
	void update_to_screen();
	void clear()
	{
		if (cleared) return;
		int i;
		for (i = 0; i < size; ++i)
			scr[getindex(coord[i].x, coord[i].y)] = PT_BACKGROUND;
		update_to_screen();
		delete[] coord;
		delete[] coord_old;
		cleared = true;
	}
	~_snake() { clear(); }
};

_snakestate _snake::move(_command direct)
{
	int i;
	if (direct == counterdirect[currentdir]) direct = currentdir;

	_coord tail_old = coord[size - 1];

	for (i = size - 1; i >= 1; --i)
		coord[i] = coord[i - 1];
	switch (direct)
	{
	case CMD_LEFT:
		coord[0].x -= 1;
		break;
	case CMD_RIGHT:
		coord[0].x += 1;
		break;
	case CMD_UP:
		coord[0].y -= 1;
		break;
	case CMD_DOWN:
		coord[0].y += 1;
		break;
	default:
		break;
	}
	currentdir = direct;
	if (scr[getindex(coord[0].x, coord[0].y)] == PT_SNAKEBODY) {
		update_to_screen();
		return SS_CRASH;
	}
	if (scr[getindex(coord[0].x, coord[0].y)] == PT_WALL) {
		update_to_screen();
		return SS_CRASH;
	}
	if (scr[getindex(coord[0].x, coord[0].y)] == PT_FOOD) {
		coord[size] = tail_old;
		++size;
		genfood();

		update_to_screen();
		return SS_EAT;
	}
	update_to_screen();
	return SS_MOVE;

}

void _snake::update_to_screen()
{
	int i;
	for (i = 0; i < size_old; ++i)
		scr[getindex(coord_old[i].x, coord_old[i].y)] = PT_BACKGROUND;
	size_old = size;
	coord_old[0] = coord[0];
	scr[getindex(coord[0].x, coord[0].y)] = PT_SNAKEHEAD;
	for (i = 1; i < size - 1; ++i) {
		coord_old[i] = coord[i];
		scr[getindex(coord[i].x, coord[i].y)] = PT_SNAKEBODY;
	}
	coord_old[i] = coord[i];
	scr[getindex(coord[i].x, coord[i].y)] = PT_SNAKETAIL;

}

//FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED 

_snake snake;

HANDLE init(int _width, int _height, int _snakeX, int _snakeY, DWORD _interval, void(__stdcall*_procaddr)(_pointtype *buff, _coord *snake, int snakesize, _snakestate state), _command *_cmd)
{
	int i;

	if (_snakeX < 0 || _snakeX >= _width || _snakeY<0 || _snakeY>_height) return 0;
	width = _width;	height = _height; procaddr = _procaddr; cmd = _cmd; interval = _interval; scrsize = width*height;
	srand(GetTickCount());

	//scr = new _pointtype[width*height];
	*cmd = CMD_UP;
	snake.init(scrsize, { _snakeX, _snakeY });
	//for (int j = 0; j < snake.getsize(); ++j) cout << snake.getfirstcoord()[j].x << snake.getfirstcoord()[j].y << '\n'; ////////////////////////////////////
	for (i = 0; i < scrsize; ++i)
		scr[i] = PT_BACKGROUND;
	for (i = 0; i < width; ++i)
		scr[getindex(i, 0)] = scr[getindex(i, height - 1)] = PT_WALL;
	for (i = 0; i < height; ++i)
		scr[getindex(0, i)] = scr[getindex(width - 1, i)] = PT_WALL;
	genfood();
	//for (int j = 0; j < width*height; ++j) cout << scr[j] << '\n'; ////////////////////////////////////

	return mutex = CreateMutex(NULL, false, NULL);
}

unsigned __stdcall gamemain(void *)
{
	_command t = *cmd;
	_snakestate r;
	_coord *head = snake.getfirstcoord();
	bool stop = false;
	bool pause = false;
	int size = snake.getsize();
	while (t != CMD_STOP&&!stop) {
		switch (t)
		{
		case CMD_LEFT:
		case CMD_RIGHT:
		case CMD_UP:
		case CMD_DOWN:
			if (!pause) {
				r = snake.move(t);
				switch (r)
				{
				case SS_MOVE:
					break;
				case SS_CRASH:
					stop = true;
					break;
				case SS_EAT:
					break;
				default:
					break;
				}
				(*procaddr)(scr, head, size, r);
			}
			break;
		case CMD_STOP:
			break;
		case CMD_PAUSE:
			pause = true;
			break;
		case CMD_CONTINUE:
			pause = false;
			break;
		default:
			break;
		}
		Sleep(interval);
		t = *cmd;
	}

	snake.clear();

	return 0;
}

//每次都要先init再start!
HANDLE start()
{
	return (HANDLE)_beginthreadex(NULL, 0, &gamemain, NULL, 0, NULL);
}

//
//_command gendirect(_coord *head)
//{
//
//}











#define WIDTH 40U
#define HEIGHT 40U
#define SNAKEX (WIDTH/2)
#define SNAKEY (HEIGHT/2)
#define INTERVAL 100U


struct _point {
	char s[4];
	WORD a;
};

const _point point[] = {
	{ "  ",FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED },
	{ "◆",FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY },
	{ "■",FOREGROUND_GREEN | FOREGROUND_INTENSITY },
	{ "■",FOREGROUND_GREEN | FOREGROUND_INTENSITY },
	{ "●",FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY },
	{ "■",FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED }
};

HANDLE hcmd;
bool gameexit = false;
_pointtype scr_old[64 * 64];

void __stdcall output(_pointtype *buff, _coord *snake, int snakesize, _snakestate state)
{
	int x, y, i = 0;
	DWORD n;
	if (state == SS_CRASH) {
		gameexit = true;
		return;
	}

	for (y = 0; y < height; ++y) {
		for (x = 0; x < width; ++x) {
			if (scr_old[i] != buff[i]) {
				SetConsoleCursorPosition(hcmd, { (SHORT)x * 2,(SHORT)y });
				SetConsoleTextAttribute(hcmd, point[buff[i]].a);
				WriteConsole(hcmd, point[buff[i]].s, 2, &n, 0);
				scr_old[i] = buff[i];
			}

			++i;
		}
	}
	//for (int j = 0; j < width*height; ++j) cout << buff[j] << ' '; ////////////////////////////////////
	//for (int j = 0; j < snakesize; ++j) cout << snake[j].x << ',' <<snake[j].y << ' '; ////////////////////////////////////
	//cout << "out\n";
}

//lqx::memshare ms;

void proc(int n, int w, size_t l)
{

}


int _tmain(int argc, _TCHAR* argv[])
{
	//ms.init("asdf", 128, &proc);
	_command cmd;
	int key;

	hcmd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hcmd, &cci);
	cci.bVisible = false;
	SetConsoleCursorInfo(hcmd, &cci);
	if (!init(WIDTH, HEIGHT, SNAKEX, SNAKEY, INTERVAL, &output, &cmd)) return 1;
	for (int i = 0; i < scrsize; ++i) scr_old[i] = PT_BACKGROUND;
	SMALL_RECT sr = { 0,0,width * 2 - 1,height };
	SetConsoleWindowInfo(hcmd, true, &sr);
	start();
	while (!gameexit) {
		key = _getch();

		switch (key)
		{
		case 72:
			cmd = CMD_UP;
			break;
		case 80:
			cmd = CMD_DOWN;
			break;
		case 75:
			cmd = CMD_LEFT;
			break;
		case 77:
			cmd = CMD_RIGHT;
			break;
		default:
			break;
		}

	}


	return 0;
}


//HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS, false, lqx::getPID("inkball.exe"));
//if (!hp) {
//	cout << "hp!\n";
//	return 1;
//}
//DWORD o;
//if (!VirtualProtectEx(hp, (void *)0x011fed72, 20, PAGE_READWRITE, &o)) {
//	cout << "vp! " << lqx::formatmsg(GetLastError()) << '\n';
//	return 1;
//}
















