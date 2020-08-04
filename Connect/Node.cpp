/*
	Xu Han
	April 1st 2019
	This file handles the game logistics, and checks which player is playing
	All functions written here 1were written by Xu Han
*/

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

string player1;
node::node() {
}

// Adds a piece to the board for specified player
void node::play(Board &b)
{
	b.add(column, player);
}


// Checks if board is full
bool node::check(Board &b)
{
	return (b.isFull[column] < 6);
}


// Undo last move
void node::undo(Board &b)
{
	b.del(column);
}

// Checks win condition
bool node::terminal(Board &b)
{
	if (b.win() != 0)
	{
		return true;
	}
	return false;
}

// Evaluates the highest scoring move for the player
int node::val(Board &b)
{
	return b.minimax(player);
}

// Set of four functions to modify and read private members of node class
void node::changeC(int a) {
	column = a;
}

void node::changeP(int a) {
	player = a;
}

int node::showC() {
	return column;
}

int node::showP() {
	return player;
}