#pragma once
#ifndef BOARD_H_
#define BOARD_H_

/*
	Xu Han
	April 1st 2019
	This file is the Board class header
	All functions written here were written by Xu Han
*/

class Board
{
public:
	Board();
	void play(Board&);
	void reset(Board&);
	int fill(int n);
	bool check(int n);
	void add(int n, int p);
	void del(int n);
	void outputBoard();
	int minimax(int person);
	int row2();
	void result(int n);
	int win();
	int board[8][7];
	int isFull[7];
};

#endif // !BOARD_H_