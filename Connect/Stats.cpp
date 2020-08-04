#include "Stats.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include "Accounts.h"

/*
	Liam Blais
	April 1st 2019
	This file handles everything for Statistic data storage, calculation and display.
	All functions have been pre-defined in the Stats.h header file.
	All functions written here were written by Liam Blais.
	Xu debugged and fixed stats update section
*/

using namespace std;
extern int winB;
extern int lossB;
extern int tieB;
extern int NumMB;
extern int NumGB;
Accounts a;

double Stats::averageMoves(int total, int numGames) {
	return (total + .0) / numGames; // Xu
}

double Stats::Percentage(int condition, int Games) {
	return  (condition + .0) / Games * 100;
}

Stats::Stats() {}

void Stats::GetCurrentStats(string Uname) {
	ifstream readfile;
	string user;
	readfile.open(Uname + "Stats.txt", ios::app);
	readfile >> user;
	readfile >> numGames;
	readfile >> highScore;
	readfile >> win;
	readfile >> loss;
	readfile >> tie;
	readfile >> numMoves;
	readfile >> lastMoves;
	readfile >> highScore;
	readfile.close();
}

void Stats::updateStatVars() {
	numGames = numGames + NumGB;
	loss = loss + lossB;
	win = win + winB;
	tie = tie + tieB;
	numMoves = numMoves + NumMB;
	lastMoves = NumMB;
	if (NumMB < highScore) {
		highScore = NumMB;
	}
}


void Stats::updateStats(string Uname) {
	GetCurrentStats(Uname);
	updateStatVars();
	ofstream tempfile;
	tempfile.open(Uname + "Stats.txt", ios::trunc);
	tempfile.close();
	ofstream file;
	file.open(Uname + "Stats.txt", ios::app);
	file << Uname << endl;
	file << numGames << endl;
	file << highScore << endl;
	file << win << endl;
	file << loss << endl;
	file << tie << endl;
	file << numMoves << endl;
	file << lastMoves << endl;
	file << highScore << endl;
	if (file.fail()) {
		cout << "File not found" << endl;
		exit(0);
	}
	file.close();
}

void Stats::NewUserStats(string Uname) {
	ofstream file;
	file.open(Uname + "Stats.txt", ios::app);
	file << Uname << endl;
	file << 0 << endl;
	file << 0 << endl;
	file << 0 << endl;
	file << 0 << endl;
	file << 0 << endl;
	file << 0 << endl;
	file << 0 << endl;
	file << 21 << endl; // Max num of moves (42/2)
	file.close();
}


void Stats::printStats(string Uname) {
	system("cls");
	cout << "                Connect Four" << endl;
	ifstream readfile;
	string user;
	readfile.open(Uname + "Stats.txt", ios::app);
	readfile >> user;
	readfile >> numGames;
	readfile.close();
	while (numGames == 0) {
		cout << "No games played." << endl << "You must play a game before viewing stats" << endl;
		system("pause");
		a.PlayerMenu(Uname);

	}
	if (numGames > 0) {
		GetCurrentStats(Uname);
		cout << "Username: " << Uname << endl;
		cout << "Total Number of Games: " << numGames << endl;
		cout << "Total Number of Wins: " << win << endl;
		cout << "Total Number of Losses: " << loss << endl;
		cout << "Total Number of Draws: " << tie << endl;
		cout << endl << "Win Percentage: " << Percentage(win, numGames) << "%" << endl;
		cout << "Loss Percentage: " << Percentage(loss, numGames) << "%" << endl;
		cout << "Draw Percentage: " << Percentage(tie, numGames) << "%" << endl;
		cout << endl << "Lowest Amount of Moves: " << highScore << endl;
		cout << "Total Number of Moves: " << numMoves << endl;
		cout << "Average Number of Moves: " << averageMoves(numMoves, numGames) << endl;
		cout << endl << "Back to Menu" << endl;
		system("pause");
		system("cls");
		a.PlayerMenu(Uname);
	}
}