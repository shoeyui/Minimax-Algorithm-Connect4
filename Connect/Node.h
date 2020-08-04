#ifndef NODE_H_
#define NODE_H_
#include "Board.h"

/*
	Xu Han
	April 1st 2019
	This file is the node class header file
	All functions written here were written by Xu Han
*/

class node
{
private:
	int player;
	int column;
public:
	node();
	void changeC(int);
	void changeP(int);
	int showC();
	int showP();
	void play(Board&);
	bool check(Board&);
	void undo(Board&);
	bool terminal(Board&);
	int val(Board&);
};

#endif // !NODE_H_#pragma once
