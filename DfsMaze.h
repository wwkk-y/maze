#pragma once
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include "win.h"
#include "allheader.h"
using namespace win;
class DfsMaze//深度优先生成迷宫
{
	//格子
	struct Cell {
		std::string img;
		Color color;
		//Cell(const char* img, const Color& color) :img(img), color(color) {};
		friend std::ostream& operator<<(std::ostream& os, const Cell& cell) {
			win::setColor(cell.color);
			os << cell.img;
			return os;
		}
	};
	//移动方向
	static std::vector<std::array<int, 2>> drc;
	//地图
	std::vector<std::vector<int>> plat;
	//格子类型
	enum { WALL = 0, SPACE = 1, PLAYER = 2, PATH = 3, WALK = 4, CUR = 5 };
	//对应格子
	const static std::vector<Cell> cells;

public:
	struct Pos {
		int i;
		int j;
		bool operator!=(const Pos& pos) const{ return i != pos.i || j != pos.j; }
		bool operator==(const Pos& pos) const{ return !operator!=(pos); }
		Pos left() const{ return { i,j - 1 }; }
		Pos right() const{ return { i,j + 1 }; }
		Pos up() const{ return { i - 1,j }; }
		Pos down() const { return { i + 1,j }; }
	};
private:
	int& getPlat(const Pos& pos) { return plat[pos.i][pos.j]; }
	void setPlat(const Pos& pos, int val) { plat[pos.i][pos.j] = val; }
public:
	DfsMaze(int height = 21, int width = 21);
	//初始化
	void init();
	//生成迷宫
	void flush();
	//控制台展示
	void show() const;
	//解迷宫
	void decrypt();
	//玩
	void play();
};

