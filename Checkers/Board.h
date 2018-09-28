#pragma once
#include <windef.h>
#include <vector>
#define BLACK 1
#define WHITE 0
#define NONE -1
#define BOARDSZ 8
#define U -1
#define D 1
#define L -1
#define R 1

class Board
{
	int boardState[BOARDSZ][BOARDSZ];
	int pieces[2][12][2], w, b;
	bool turn;
public:
	Board();

	int Move(int player, int piece, int dirX, int dirY);
	void PrintBoard(HDC hdc);
};

