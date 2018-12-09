// sydll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


class findway {

private:
	const char LEFT = 0x1;
	const char RIGHT = 0x2;
	const char UP = 0x4;
	const char DOWN = 0x8;
	int *b;
	unsigned int size;
	unsigned int w, h;
	int ex, ey, sx, sy;
	int getindex(int x, int y) { return y*w + x; }
	bool cleared = true;
	bool updatesource;
	void(*_proc)(int x, int y);
	bool _find();
	int dx, dy;

public:
	struct coord {
		int x;
		int y;
	} *path;
	int pathlen;

	void init(int *buff, unsigned int width, unsigned int height, bool updatesourcebuff, void(*proc)(int x, int y)) {
		w = width; h = height; _proc = proc;
		size = w*h;
		updatesource = updatesourcebuff;
		b = (updatesourcebuff ? buff : new int[size]);
		path = new coord[size];
		pathlen = 0;
		CopyMemory(b, buff, size*sizeof(int));
		cleared = false;
	}
	bool find(int startX, int startY, int endX, int endY) { ex = endX; ey = endY; sx = startX; sy = startY; return _find(); }
	void clear() {
		if (cleared) return;
		if (!updatesource) delete[] b;
		delete[] path;
		cleared = true;
	}
	~findway() { clear(); }


};

bool findway::_find()
{
	b[getindex(sx, sy)] = 1;
	path[pathlen] = { sx,sy };
	++pathlen;
	if (_proc) (*_proc)(sx, sy);

	if (sx == ex&&sy == ey) return true;

	char flags = 0;

	dx = ex - sx;
	dy = ey - sy;
	if (sx == 0) flags |= LEFT;
	if (sx == w - 1) flags |= RIGHT;
	if (sy == 0) flags |= UP;
	if (sy == h - 1) flags |= DOWN;

	//for (unsigned int j = 0, jj; j < h; ++j) {               /////////////////////////////////////////////////////
	//	for (jj = 0; jj < w; ++jj) cout << b[getindex(jj, j)] << ' ';
	//	cout << '\n';
	//}
	//system("cls");                                        /////////////////////////////////////////////////////////

	if (dx > 0 && !(flags & RIGHT)) {
		flags |= RIGHT;
		if (!b[getindex(sx + 1, sy)]) {
			++sx;
			if (_find()) return true;
			--sx;
		}
	}
	if (dx < 0 && !(flags & LEFT)) {
		flags |= LEFT;
		if (!b[getindex(sx - 1, sy)]) {
			--sx;
			if (_find()) return true;
			++sx;
		}
	}
	if (dy > 0 && !(flags & DOWN)) {
		flags |= DOWN;
		if (!b[getindex(sx, sy + 1)]) {
			++sy;
			if (_find()) return true;
			--sy;
		}
	}
	if (dy < 0 && !(flags & UP)) {
		flags |= UP;
		if (!b[getindex(sx, sy - 1)]) {
			--sy;
			if (_find()) return true;
			++sy;
		}
	}

	if (!(flags & LEFT)) {
		if (!b[getindex(sx - 1, sy)]) {
			--sx;
			if (_find()) return true;
			++sx;
		}
	}
	if (!(flags & RIGHT)) {
		if (!b[getindex(sx + 1, sy)]) {
			++sx;
			if (_find()) return true;
			--sx;
		}
	}
	if (!(flags & UP)) {
		if (!b[getindex(sx, sy - 1)]) {
			--sy;
			if (_find()) return true;
			++sy;
		}
	}
	if (!(flags & DOWN)) {
		if (!b[getindex(sx, sy + 1)]) {
			++sy;
			if (_find()) return true;
			--sy;
		}
	}
	--pathlen;
	return false;
}



int *scr;
findway f;
int _sx, _sy, _ex, _ey;
int _interv;
void(__stdcall *_cb)(int x, int y);

void proc(int x, int y)
{
	(*_cb)(x, y);
	Sleep(_interv);
}

extern "C" __declspec(dllexport) void __stdcall initmap(int *source, int width, int height, int sx, int sy, int ex, int ey, void(__stdcall *cb)(int x, int y), void(__stdcall *cb2)(bool found), int interv)
{
	scr = source; _interv = interv; _cb = cb;
	f.init(scr, width, height, true, &proc);
	_sx = sx; _sy = sy; _ex = ex; _ey = ey;
	//_beginthreadex(NULL, 0, &start, NULL, 0, NULL);

	(*cb2)(f.find(_sx, _sy, _ex, _ey));
}

extern "C" __declspec(dllexport) void __stdcall clear()
{
	f.clear();
}

extern "C" __declspec(dllexport) int __stdcall getpath(findway::coord *resultv)
{
	//for (int i = 0; i < f.pathlen; ++i)
	//	resultv[i] = f.path[i];
	//return f.pathlen;
	int i, j, n;
	for (i = 0, n = 0;; ) {

		resultv[n] = f.path[i];
		++n;

		if (i == f.pathlen - 1) break;

		for (j = f.pathlen - 1; j >= 0; --j) {

			if (f.path[j].x == f.path[i].x) {
				if (f.path[j].y == f.path[i].y - 1 || f.path[j].y == f.path[i].y + 1) {
					i = j;
					break;
				}
			}
			if (f.path[j].y == f.path[i].y) {
				if (f.path[j].x == f.path[i].x - 1 || f.path[j].x == f.path[i].x + 1) {
					i = j;
					break;
				}
			}
		}


	}

	return n;

}