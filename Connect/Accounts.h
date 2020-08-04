#ifndef ACCOUNTS_H_
#define ACCOUNTS_H_
/*
	Liam Blais
	April 1st 2019
	This file is the Accounts class header
	All functions written here were written by Liam Blais
*/

#include <string>
using namespace std;

class Accounts {

protected:
	string UN;
	string PW;
	string username;
	string password;
	string ConfirmPassword;
public:
	Accounts();
	int LoginCheck(string, string);
	void Register();
	void PlayerMenu(string);
};



#endif // !ACCOUNTS_H_