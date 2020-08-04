/*
	Xu Han
	April 1st 2019
	This file handles all of the board operations and state
	There are a few standalone functions that check for win/loss conditions
	All other functions have been pre-defined in the Board.h header file
	All functions written here were written by Xu Han
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
#include "Node.h"
#include "Stats.h"

using namespace std;
extern string player1;
// MAX/MIN determined by using 2^16
#define MIN -65536
#define MAX 65536
extern int DEPTH = 0;
Stats s;//Liam
int winB; //Liam
int lossB;//Liam
int tieB;//Liam
int NumGB;//Liam
int NumMB;//Liam

int checkLoss(int p, Board &b)
{
	node k;
	// Since p is either 1 or 2 depending on player or ai, 3-p alternates the turns
	// if its ai, p=2, so (3-p)=(3-2)=1, thus making it represent the player
	k.changeP(3 - p);
	for (int i = 0; i < 7; i++)
	{
		k.changeC(i);
		// Checks if full
		if (k.check(b))
		{
			// Tries every column, to see if there is win condition
			k.play(b);
			if (b.win() == k.showP())
			{
				// If win condition is seen for player, the ai "undos" their attempt
				k.undo(b);
				return i;
			}
			k.undo(b);
		}
	}
	return -2;
}

int checkWin(int p, Board &b)
{
	node k;
	k.changeP(p);
	for (int i = 0; i < 7; i++)
	{
		k.changeC(i);
		if (k.check(b))
		{
			k.play(b);
			if (b.win() == k.showP())
			{
				// Returns winning move
				k.undo(b);
				return i;
			}
			k.undo(b);
		}
	}
	return -1;
}
/*
	Recursively repeats till MAX is returned or search DEPTH is reached
	MAX is returned when every valid play is made by alternating players
	Once search DEPTH is exhausted, or when win condition is detected, the minimax
	algorithm will give a score value
*/
int ai(node x, int depth, int a, int b, Board &c)
{
	bool played = false;
	if (x.check(c))
	{
		x.play(c);
		played = true;
	}
	else {
		return MAX;
	}
	if (depth == 0 || x.terminal(c))
	{
		int scoreVal = x.val(c);
		x.undo(c);
		played = false;
		return scoreVal;
	}
	node n;
	n.changeP(3 - x.showP());
	for (int i = 0; i < 7; i++)
	{
		n.changeC(i);
		int maxMove;
		maxMove = a;
		a = max(a, -1 * ai(n, depth - 1, -b, -a, c));
		if (a == MAX or a == MIN) {
			a = maxMove;
		}
		if (b <= a) {
			break;
		}
	}
	if (played) {
		x.undo(c);
	}
	return a;
}

Board::Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			board[i][j] = 0;
		}
		isFull[i] = 0;
	}
}

void Board::reset(Board &b) {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			board[i][j] = 0;
		}
		isFull[i] = 0;
	}
}
// Checks which row to put, by checking how "full" the inputted col is
int Board::fill(int n)
{
	return isFull[n];
}
// Checks if input is isFull on board
bool Board::check(int n)
{
	return (isFull[n] < 6 ? true : false);
}
// Adds a piece
void Board::add(int n, int p)
{
	board[n][isFull[n]++] = p;
}
void Board::del(int n)
{
	board[n][--isFull[n]] = 0;
}
void Board::outputBoard()
{
	cout << "                Connect Four" << endl;
	for (int i = 5; i >= 0; i--)
	{
		cout << "          |";
		for (int j = 0; j < 7; j++)
		{
			switch (board[j][i])
			{
			case 0:
				cout << " _ ";
				break;
			case 1:
				cout << " X ";
				break;
			case 2:
				cout << " O ";
				break;
			}
		}
		cout << "|" << endl;
	}
	cout << "          | 1  2  3  4  5  6  7 |" << endl;
	cout << endl << endl;
}

/*
	Minimax algorithm assigns a point value to each possible move
	The goal is to make the move with least risk (Minimum loss)
	The following code judges many factors when giving points
	All values were tested and adjusted by using a macro to play 10 games per value set (Random input)
	The value set that took most number of moves to win was chosen
	Over 500 games were played
	The macro was done on Corsair iCUE software
*/
int Board::minimax(int person)
{
	int value = 0;
	// Central plays are worth some value
	for (int i = 0; i < 6; i++)
	{
		if (board[3][i] == 2)
			value += 3;
		if (board[3][i] == 1)
			value -= 3;
	}

	// Checks for one left and right
	for (int i = 0; i < 6; i++)
	{
		for (int j = 2; j < 5; j += 2)
		{
			if (board[j][i] == 2)
				value += 2;
			if (board[j][i] == 1)
				value += 300;
		}
	}

	// Checks one from edge connections
	for (int i = 0; i < 6; i++)
	{
		for (int j = 1; j < 6; j += 4)
		{
			if (board[j][i] == 2)
				value += 0;
			if (board[j][i] == 1) {
				value += 500;
			}
		}
	}

	// Checks sneaky edge play connections
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j += 6)
		{
			if (board[j][i] == 2)
				value += 3;
			if (board[j][i] == 1)
				value -= 3;

		}
	}

	// Checks for two in a row + separate function due to how common two in a rows are
	value += row2();
	// Checks for three in a row pieces
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int p = 1; p < 3; p++)
			{
				if (board[i][j] == 0)
				{
					board[i][j] = p;
					if (win() == 2)
					{
						if (win() % 2 == (j + 1) % 2)
							value += 50;
						else
							value += 10;
					}
					else if (win() == 1)
					{
						if (win() % 2 == (j + 1) % 2)
							value += 20;
						else
							value += 10;
					}
					board[i][j] = 0;
				}
			}
		}
	}
	return value;
}

// Outputs winner or tie
void Board::result(int n)
{

	switch (n) {
	case 1: cout << endl << endl << player1 << ", You win!" << endl;
		lossB = 0;
		tieB = 0;
		winB = 1;//Liam
		break;
	case 2: cout << endl << endl << "You lose!" << endl;
		winB = 0;
		tieB = 0;
		lossB = 1;//Liam
		break;
	case 3: cout << endl << endl << "Tie!" << endl;
		winB = 0;
		lossB = 0;
		tieB = 1;//Liam
		break;
	}
}

/*
	After testing, there needs to be a value assigned to pieces that are two in a row
	Value goes down when the player has 2 in a row
	Value goes up when ai has 2 in a row
	The reason for this is to put priority on applying pressure and being a proactive AI
	It feels faster paced when the AI is not playing defensively
*/
int Board::row2()
{
	int value = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (board[i][j] == 1 && board[i + 1][j] == 1)
				value -= 20;
			else if (board[i][j] == 1 && board[i][j + 1] == 1)
				value -= 16;
			else if ((board[i][j] == 1 && board[i + 1][j + 1] == 1) ||
				(board[i][j] == 1 && board[i + 1][j - 1] == 1))
				value -= 20;
			else if (board[i][j] == 2 && board[i + 1][j] == 2)
				value += 20;
			else if (board[i][j] == 2 && board[i][j + 1] == 2)
				value += 16;
			else if ((board[i][j] == 2 && board[i + 1][j + 1] == 2) ||
				(board[i][j] == 1 && board[i + 1][j - 1] == 1))
				value += 20;
		}
	}
	return value;
}
int Board::win()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			// Checks horizontal/vertical/diagonal four in a row
			if ((i + 3 < 7 && board[i][j] == 1 && board[i + 1][j] == 1 && board[i + 2][j] == 1 && board[i + 3][j] == 1) ||
				(j + 3 < 6 && board[i][j] == 1 && board[i][j + 1] == 1 && board[i][j + 2] == 1 && board[i][j + 3] == 1) ||
				(i + 3 < 7 && j + 3 < 6 && board[i][j] == 1 && board[i + 1][j + 1] == 1 && board[i + 2][j + 2] == 1 && board[i + 3][j + 3] == 1) ||
				(i - 3 >= 0 && j + 3 < 6 && board[i][j] == 1 && board[i - 1][j + 1] == 1 && board[i - 2][j + 2] == 1 && board[i - 3][j + 3] == 1))
				return 1;
			else if ((i + 3 < 7 && board[i][j] == 2 && board[i + 1][j] == 2 && board[i + 2][j] == 2 && board[i + 3][j] == 2) ||
				(j + 3 < 6 && board[i][j] == 2 && board[i][j + 1] == 2 && board[i][j + 2] == 2 && board[i][j + 3] == 2) ||
				(i + 3 < 7 && j + 3 < 6 && board[i][j] == 2 && board[i + 1][j + 1] == 2 && board[i + 2][j + 2] == 2 && board[i + 3][j + 3] == 2) ||
				(i - 3 >= 0 && j + 3 < 6 && board[i][j] == 2 && board[i - 1][j + 1] == 2 && board[i - 2][j + 2] == 2 && board[i - 3][j + 3] == 2))
				return 2;
		}
	}
	bool draw = true;
	for (int i = 0; i < 7; i++)
	{
		if (draw == true)
		{
			for (int j = 0; j < 6; j++)
			{
				// If there are any empty spaces, it does not draw yet
				if (board[i][j] == 0)
					draw = false;
			}
		}
	}
	if (draw == true) {
		return 3;
	}
	return 0;
}

void Board::play(Board &b)
{
	int c;
	int difficulty = 0;
	// Difficulty is based on how exhaustive the DEPTH is
	NumGB = 1;
	NumMB = 0;
	while (difficulty < 1 || difficulty > 3) {
		cout << "Select difficulty" << endl <<
			"1. Initiate" << endl <<
			"2. Intermediate" << endl <<
			"3. Impossible" << endl;
		cin >> difficulty;
	}
	if (difficulty == 1) {
		DEPTH = 0;
	}
	else if (difficulty == 2) {
		DEPTH = 3;
	}
	else {
		DEPTH = 4;
	}

	bool p = false;
	for (; b.win() == 0; p = !p)
	{
		system("cls");
		b.outputBoard();
		if (!p)
		{
			cout << player1 << ", your turn: [1-7]  ";
			cin >> c;
			--c;
			NumMB++;//Liam

			if (c < 0 || c > 6)
			{
				cout << "Out of bounds. Try Again." << endl;
				p = !p;
				Sleep(1000);
				continue;
			}
			else if (b.fill(c) < 6)
			{
				b.add(c, (p ? 2 : 1));
			}
			else
			{
				cout << "Column is full. Try again." << endl;
				p = !p;
				Sleep(1000);
				continue;
			}
		}
		else
		{
			int scores[7];
			node o;
			for (int i = 0; i < 7; i++)
			{
				o.changeC(i);
				if (p) {
					o.changeP(2);
				}
				else {
					o.changeP(1);
				}
				// scores are calculated here
				scores[i] = ai(o, DEPTH, MIN, MAX, b);
				// Outputs the scores for each column
				cout << "Minimax output for column " << i + 1 << ":    " << scores[i] << endl;
			}
			Sleep(1000);

			c = checkWin((p ? 2 : 1), b);
			if (c == -1)
			{
				c = checkLoss((p ? 2 : 1), b);
				if (c == -2)
				{
					for (int i = 0; i < 7; i++)
					{
						if (scores[i] >= MAX) {
							scores[i] = MIN;
						}
					}
					for (int i = 0; i < 7; i++)
					{
						// max_element returns the largest value in array scores
						if (scores[i] == *max_element(scores, scores + 7))
							// The column with largest move score is where the ai will go
							c = i;
					}
				}

			}
			// Checks scope of column with bounds of board
			if (c < 0 || c > 6)
			{
				p = !p;
				continue;
			}
			else if (b.fill(c) < 6)
			{
				// Add the piece to board
				b.add(c, (p ? 2 : 1));

			}
			else
			{
				p = !p;
				continue;
			}
		}
	}
	system("cls");
	b.outputBoard();
	result(b.win());
}