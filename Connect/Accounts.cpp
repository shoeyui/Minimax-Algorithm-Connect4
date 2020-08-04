#include "Accounts.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
#include <cstdlib> 
#include "Board.h"
#include "Stats.h"

/*
	Liam Blais
	April 1st 2019
	This file handles everything for Account data storage, Login and Registration.
	There is also a class funtion which handles the PlayerMenu.
	All functions have been pre-defined in the Accounts.h header file
	All functions written here were written by Liam Blais with exception of code
	which runs the Board.
*/

using namespace std;

extern string player1; // Xu
static Board b; // Xu
static Stats s;

Accounts::Accounts() {}


/*
	Xu made the following changes to LoginCheck
	1. Changed from Bool to int to get more return values
	2. Check for blank file is made, previously the program would exit otherwise
	3. file.close for each return clause
*/
int Accounts::LoginCheck(string user, string pass)
{
	string test;
	ifstream file;
	string username;
	string password;
	file.open("accounts.txt");
	getline(file, test);
	if (file.fail() || test == "")
	{
		file.close();
		return 2;
	}
	file.close();
	file.open("accounts.txt");
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> username >> password;
			if ((username == user) && (password == pass)) {
				file.close();
				return 1;
			}
		}
	}
	file.close();
	return 0;
}

void Accounts::Register()
{
	ifstream file;
	ofstream newuser;
	file.open("accounts.txt", ios::app);
	newuser.open("accounts.txt", ios::app);
	bool uservalid = false;
	if (file.fail()) {
		cout << "File Not Found" << endl;
		exit(1);
	}

	while (!uservalid)
	{
		system("cls");
		cout << "Registration Mode" << endl;
		cout << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;
		cout << "Confirm password: ";
		cin >> ConfirmPassword;
		int m = 0;
		int k = 0;
		while (file >> UN >> PW)
		{
			m++;
			if (username != UN)
				k++;
		}

		if (m == k && password == ConfirmPassword) {
			uservalid = true;
			s.NewUserStats(username);
		}
		else if (m != k) { // Xu
			cout << "Scanning..." << endl;
			Sleep(1500);
			cout << "There is already a user with this username." << endl;
			system("pause");
		}
		else {
			cout << "The passwords do not match." << endl;
		}
	}
	newuser << username << " " << password << endl;
	file.close();
	newuser.close();
}

void Accounts::PlayerMenu(string Uname) {
	int choice2 = 0;
	system("cls");
	cout << "                Connect Four" << endl;
	cout << "Welcome " << Uname << "!" << endl << endl;
	cout << "1- Play a Game!" << endl << "2- View Statistics" << endl << "3- Log Out" << endl << endl << "Make a choice" << endl;
	cin >> choice2;
	while (choice2 < 1 || choice2>3) {
		cout << "Please enter between 1-4" << endl;
		cin >> choice2;
	}
	char replay2 = 'y';
	switch (choice2) {
	case 1:
		cout << "                Connect Four" << endl;
		player1 = Uname;
		while (replay2 == 'y') {
			system("cls");
			b.outputBoard();
			cout << endl << endl;
			b.play(b);
			cout << "Play again?" << endl;
			cin >> replay2;
			b.reset(b);
		}

		while (replay2 != 'y') {
			system("cls");
			s.updateStats(Uname);
			PlayerMenu(player1);
		}

		break;

	case 2:
		s.printStats(Uname);
		break;

	case 3:
		cout << "You have been logged out..." << endl;
		Sleep(1000);
		exit(0);
		break;
	}

}
