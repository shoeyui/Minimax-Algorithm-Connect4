#ifndef STATS_H_
#define STATS_H_
#include <string>
/*
	Liam Blais
	April 1st 2019
	This file is the Stats class header
	All functions written here were written by Liam Blais
*/

using namespace std;
class Stats {
protected:
	int highScore;
	int lastMoves; //stores the last game's number of moves
	int numMoves;
	int win;
	int loss;
	int tie;
	int numGames;
public:
	Stats();
	void printStats(string); // Outputs Statistics for user
	void updateStats(string); //Updates Text File Values from Local Variables
	double averageMoves(int, int); //Calculates Average number of moves.
	double Percentage(int, int); //Calculates percentage win/loss/tie
	void updateStatVars(); // Updates Local Variables after game play
	void GetCurrentStats(string); //Gets the Current Stats from Text File and stores values in local variables.
	void NewUserStats(string); //Makes a new Stats text file for user.
};

#endif // !STATS_H_