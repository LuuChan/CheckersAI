#include "stdafx.h"
#include "Board.h"

Board::Board()
{
	w = 0;
	b = 0;
	for (int i = 0; i < BOARDSZ; i++) {
		for (int j = 0; j < BOARDSZ; j++) {
			if (i < 3 && (i + j) % 2) {
				boardState[i][j] = WHITE;
				pieces[WHITE][w][0] = i;
				pieces[WHITE][w][1] = j;
				w++;
			}
			else if (i >= 5 && (i + j) % 2) {
				boardState[i][j] = BLACK;
				pieces[BLACK][b][0] = i;
				pieces[BLACK][b][1] = j;
				b++;
			}
			else boardState[i][j] = NONE;
		}
	}
}

// EX .Move(BLACK, 3, L, D);
int Board::Move(int player, int piece, int dirX, int dirY)
{
	if (piece < 0 || piece >= 12) return -1;
	int i, j;
	if (pieces[player][piece][0] >= 0) {
		i = pieces[player][piece][0];
		j = pieces[player][piece][1];
	}
	if (i + dirY < 0 || i + dirY >= BOARDSZ || j + dirX < 0 || j + dirX >= BOARDSZ) return -1;
	if (boardState[i + dirY][j + dirX] == player) return -1;
	if (boardState[i + dirY][j + dirX] == NONE) {
		boardState[i][j] = NONE;
		boardState[i + dirY][j + dirX] = player;
		pieces[player][piece][0] += dirY;
		pieces[player][piece][1] += dirX;
		return 0;
	}
	return -1;
}

void Board::PrintBoard(HDC hdc)
{
	HBRUSH blueBrush, blackBrush, whiteBrush;
	RECT square = { 0,0,0,0 };
	int left, top, right, bot;
	int squareSZ = 30, margin = 20, eMargin = 5;

	blueBrush = CreateSolidBrush(RGB(150, 100, 250));
	blackBrush = CreateSolidBrush(RGB(50, 50, 100));
	whiteBrush = CreateSolidBrush(RGB(200, 200, 250));

	for (int i = 0; i < BOARDSZ; i ++){
		for (int j = 0; j < BOARDSZ; j ++){
			top = i * squareSZ + margin;
			left = j * squareSZ + margin;
			bot = top + squareSZ;
			right = left + squareSZ;
			square = { left, top, right, bot };
			if ((i + j) % 2) {
				FillRect(hdc, &square, blueBrush);
				if (boardState[i][j] != NONE) {
					if (boardState[i][j] == WHITE) SelectObject(hdc, whiteBrush);
					else SelectObject(hdc, blackBrush);
					Ellipse(hdc, left + eMargin, top + eMargin, right - eMargin, bot - eMargin);
				}
			}
			else FillRect(hdc, &square, blackBrush);
		}
	}
}
