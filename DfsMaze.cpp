#include "DfsMaze.h"
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

vector<array<int, 2>> DfsMaze::drc = { {0, 1}, { 0,-1 }, { 1,0 }, { -1,0 } };

//格子
//enum { WALL = 0, SPACE = 1, PLAYER = 2, PATH = 3, WALK = 4 };
const vector<DfsMaze::Cell> DfsMaze::cells = { 
	{"■",win::whiteLight},
	{"■",win::back} ,
	{"me",win::green} ,
	{"■",win::red} ,
#if dfs_decrypt_debug
	{"■",win::grey},
#else
	{"■",win::back} ,
#endif
	{"■",win::red},
};

DfsMaze::DfsMaze(int height, int width){
	if (height < 11) height = 11;
	else if (!(height % 2)) height += 1;
	if (width < 11) width = 11;
	else if (!(width % 2)) width += 1;
	plat = vector<vector<int>>(height, vector<int>(width, WALL));
	srand(time(nullptr));
	//flush生成迷宫
	flush();
}

void DfsMaze::init() {
	for (int i = 0; i < plat.size(); ++i) {
		std::fill(plat[i].begin(), plat[i].end(), WALL);
	}
}

void DfsMaze::flush() {
	cout << "生成中...."<<std::flush;
#if dfs_flush_debug
	system("cls");
#endif
	init();
	vector<Pos> con;
	Pos pos = {
		(rand() % ((int)plat.size() - 3) + 1),
		(rand() % ((int)plat.back().size() - 3) + 1)
	};
	if (!(pos.i % 2)) pos.i += 1;
	if (!(pos.j % 2)) pos.j += 1;

	con.push_back(pos);
	plat[con.back().i][con.back().j]=SPACE;
	while (!con.empty()) {
		random_shuffle(drc.begin(), drc.end(), [](int i) {return rand() % i; });
		int i;
		for (i = 0; i < drc.size(); ++i) {
			Pos& pos = con.back();
			Pos np = { pos.i + 2 * drc[i][0],pos.j + 2 * drc[i][1] };
			if (np.i >= 0 && np.i < plat.size() && np.j >= 0 && np.j < plat.back().size()) {
				if (plat[np.i][np.j] == WALL) {
					plat[pos.i + drc[i][0]][pos.j + drc[i][1]] = SPACE;
					plat[np.i][np.j] = SPACE;
					con.push_back(np);
					break;
				}
			}
		}
		if (i == drc.size()) con.pop_back();
#if dfs_flush_debug
		win::gotoxy(0, 0);
		win::setCursor();
		if(!con.empty()) setPlat(con.back(), CUR);
		show();
		if(!con.empty()) setPlat(con.back(), SPACE);
		if (!con.empty()) cout << "back:" << con.back().i << "," << con.back().j ;
#endif
	}
	plat[1][0] = SPACE;
	plat[plat.size() - 2][plat.back().size() - 1] = SPACE;
	cout << "\ndone!" << endl;
}

void DfsMaze::show() const{
	for (int i = 0; i < plat.size(); ++i) {
		for (int j = 0; j < plat.back().size(); ++j) {
			cout << cells[plat[i][j]];
		}
		cout << endl;
	}
	win::setColor();
}

void DfsMaze::decrypt() {
#if dfs_decrypt_debug
	system("cls");
#endif
	vector<Pos> con;
	const Pos end = { plat.size() - 2,plat.back().size() - 2 };
	Pos pos = { 1,1 };
	setPlat(pos.left(), PATH);
	setPlat(end.right(), PATH);
	while (pos != end) {
		con.push_back(pos);
		setPlat(pos, WALK);
		if (getPlat(pos.right()) == SPACE) pos = pos.right();
		else if (getPlat(pos.down()) == SPACE) pos = pos.down();
		else if (getPlat(pos.left()) == SPACE) pos = pos.left();
		else if(getPlat(pos.up()) == SPACE) pos = pos.up();
		else {
			con.pop_back();
			con.pop_back();
			pos = con.back();
		}
#if dfs_decrypt_debug
		gotoxy(0, 0);
		setPlat(pos, CUR);
		show();
		setPlat(pos, WALK);
		cout << "cur:" << pos.i << ',' << pos.j << endl;
		//Sleep(100);
#endif
	}
	con.push_back(end);
	for (int i = 0; i < con.size(); ++i) {
		setPlat(con[i], PATH);
	}
	show();
	for (int i = 0; i < con.size(); ++i) {
		setPlat(con[i], SPACE);
	}
	plat[1][0] = SPACE;
	setPlat(end.right(), SPACE);
}

void DfsMaze::play() {
	system("cls");
	win::setCursor();
	Pos player = { 1,1 };
	const Pos end = { plat.size() - 2,plat.back().size() - 2 };
	setPlat(player.left(), PATH);
	setPlat(end.right(), PATH);
	while (player != end) {
		setPlat(player, PLAYER);
		gotoxy(0, 0);
		show();
		setPlat(player, SPACE);
		char input = _getch();
		while (_kbhit()) _getch();
		switch (input) {
		case 'a':
		case 'A':
			if (getPlat(player.left()) == SPACE) player = player.left();
			break;
		case 's':
		case 'S':
			if (getPlat(player.down()) == SPACE) player = player.down();
			break;
		case 'd':
		case 'D':
			if (getPlat(player.right()) == SPACE) player = player.right();
			break;
		case 'w':
		case 'W':
			if (getPlat(player.up()) == SPACE) player = player.up();
			break;
		case 27://ESC
			player = end;
			break;
		}
	}
	setPlat(player, PLAYER);
	gotoxy(0, 0);
	show();
	setPlat(player, SPACE);
	plat[1][0] = SPACE;
	setPlat(end.right(), SPACE);
	win::setCursor(true);
}