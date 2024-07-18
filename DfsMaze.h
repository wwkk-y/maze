#pragma once
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include "win.h"
#include "allheader.h"
using namespace win;
class DfsMaze//������������Թ�
{
	//����
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
	//�ƶ�����
	static std::vector<std::array<int, 2>> drc;
	//��ͼ
	std::vector<std::vector<int>> plat;
	//��������
	enum { WALL = 0, SPACE = 1, PLAYER = 2, PATH = 3, WALK = 4, CUR = 5 };
	//��Ӧ����
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
	//��ʼ��
	void init();
	//�����Թ�
	void flush();
	//����̨չʾ
	void show() const;
	//���Թ�
	void decrypt();
	//��
	void play();
};

