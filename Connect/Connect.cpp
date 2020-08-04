/*
	Xu Han + Liam Blais
	April 1st 2019
	This file contains the int main() function for the program
	This file has two functionalities
		1. Pre-edit the console window properties to be more aesthetically pleasing
		2. Create and employ the main menu for the game
	The console window editting + while loop contents were written by Xu Han
	The main menu was written by Liam Blais
*/
#include "Accounts.h"
#include "Node.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <cwchar>
#include <fstream>

using namespace std;
extern string player1;
static Board b;
static Accounts a;
bool firstRun = true;

void ConsoleChange() {
	// Change the font size and window size/position for console
	CONSOLE_FONT_INFOEX f;
	HWND console = GetConsoleWindow();
	RECT consoleRectangle;
	f.cbSize = sizeof(f);
	f.dwFontSize.Y = 30;
	GetWindowRect(console, &consoleRectangle);
	wcscpy_s(f.FaceName, L"KaiTi");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &f);
	MoveWindow(console, consoleRectangle.left, consoleRectangle.top, 700, 700, TRUE);
	SetWindowPos(console, 0, 500, 50, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

int main()
{
	if (firstRun) {
		ConsoleChange();
	}
	firstRun = false;
	string USR;
	string PSW;
	int loginattempts = 0;
	char replay = 'y';
	ifstream userfile;
	userfile.open("accounts.txt");
	cout << "                Connect Four" << endl;
	if (!userfile.is_open())
	{
		cout << "File not found" << endl << "Creating file..." << endl;
		Sleep(500);
		ofstream outfile("accounts.txt");
		cout << "File created" << endl;
		Sleep(2200);
		system("cls");
		outfile.close();
		main();
	}
	else
	{
		int choice = 0;
		cout << "1-Login" << endl << "2-Register" << endl << "3-Guest Mode" << endl << "4-Exit Game" << endl << endl << "Make a choice:" << endl;
		cin >> choice;
		while (choice > 4 || choice < 1) {
			cout << "Please enter between 1-4" << endl;
			cin >> choice;
		}
		

		switch (choice)
		{
		case 1:
			if (a.LoginCheck(USR, PSW) == 2) {
				system("cls");
				cout << "No accounts found." << endl;
				cout << "Please register an account." << endl;
				Sleep(3000);
				system("cls");
				userfile.close();
				main();
			}
			while (a.LoginCheck(USR, PSW) == 0)
			{
				system("cls");
				cout << "Login Mode" << endl;
				loginattempts++;
				cout << "Username: ";
				cin >> USR;
				cout << "Password: ";
				cin >> PSW;
				system("cls");
				if (a.LoginCheck(USR, PSW) == 1) {

					a.PlayerMenu(USR);

				}
				else if (loginattempts == 3)
				{
					cout << "Maximum login attempts exceeded." << endl;
					Sleep(2000);
					system("cls");
					userfile.close();
					main();
					break;
				}
				else
				{
					cout << "Invalid username/password combination" << endl;
					Sleep(2000);
				}
			}
			userfile.close();
			break;

		case 2:
			a.Register();
			system("cls");
			userfile.close();
			main();
			break;

		case 3:
			userfile.close();
			system("cls");
			cout << "Guest Mode" << endl;
			Sleep(2000);
			system("cls");
			cout << "                Connect Four" << endl;
			cout << "Enter player name: ";
			cin >> player1;
			while (replay == 'y') {
				system("cls");
				b.outputBoard();
				cout << endl << endl;
				b.play(b);
				cout << "Play again?" << endl;
				cin >> replay;
				b.reset(b);
			}
			break;
		case 4:
			userfile.close();
			system("cls");
			cout << "Goodbye!" << endl << endl;
			Sleep(2000);
			exit(0);
			break;
		}

	}
	return 0;
}