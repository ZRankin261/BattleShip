// Cobb Battleship Project
//Written by: Zackary Rankin
//Assuming Single player game, Where the computer generates the ships, and the user
// is trying to guess the locations of the ship. 

#include <iostream>
#include <sstream>
#include "Gameboard.h"

void IntroMessage();
char InitialUserPrompt();
bool Instructions();
void GamePrompt(char &col, int &row);
void ExitMessage();

using namespace std;

int main()
{
	bool IsCheater = false;
	char input = 'N';
	char column = 'A';
	int row = 0, Hitcount = 0;
	Gameboard X;

	IntroMessage();
	input = InitialUserPrompt();
	while(input == 'Y')
	{	
	//Uncomment to see number of times GetPoint is called
	//X.GetCounter();
	X.ShipBuilder();
	//X.GetCounter();
	IsCheater = Instructions();
	if(IsCheater != false)
	{
		X.PrintShipGrid();
	}
		while(Hitcount != 17)
		{
			
		X.PrintShotGrid();
		GamePrompt(column,row);
		X.CheckifHit(column,row);
		Hitcount = X.GetHitCount();
		}
		cout << "Congrats you have won the Game!!" << endl;
	input = InitialUserPrompt();
	}
	ExitMessage();

	return 0;
}
// Welcome the user to the program
void IntroMessage()
{

	cout << "Welcome to my Battleship Program" << endl;

}
//Asks the user if they would like to play the game
// Will error if input is incorrect
char InitialUserPrompt()
{
	
	char Userinput;
	cout << "Would you like to play? Y/N" << endl;
	cin >> Userinput;
	Userinput = toupper(Userinput);
	

	while(Userinput != 'Y' && Userinput != 'N')
	{
		cout << "Error your input was incorrect" << endl;
		cout << "Would you like to play? Y/N" << endl;
		cin >> Userinput;
		Userinput = toupper(Userinput);
		
	}

	return Userinput;

}
//Asks the user if they would like to Cheat the game and look at the ships locations.
// The function will then return a boolean representing if the user wants to cheat or not
bool Instructions()
{
	char Cheat;
	bool result = false;
	cout << "The game has generated your ships" << endl;
	cout << "Would you like to see the Ship Grid? Y/N |WARNING THIS RUINS THE GAME!|" << endl;
	cin >> Cheat;
	Cheat = toupper(Cheat);
	while(Cheat != 'Y' && Cheat != 'N')
	{
		cout << "Error Incorrect input. Try Again" << endl;
		cout << "Would you like to see the Ship Grid? Y/N |WARNING THIS RUINS THE GAME!|" << endl;
		cin >> Cheat;
		Cheat = toupper(Cheat);
	}
	cout << "Your Shot Grid will help you keep track of what points you have already tried" << endl;
	cout << "Keep guessing points untill all the ships have been sunk" << endl;

	if(Cheat == 'Y')
	{
	result = true;
	}

	return result;
}
// This function 
void GamePrompt(char&col, int&row)
{
	char X ;
	char Y = 'A';
	
	cout << "Select a Point in the following format" <<endl;
	cout << "Input the Letter of the Column" << endl;
	cin >> Y;
	Y = toupper(Y);
	while(Y>'J' || Y <'A')
	{
		cout << "The Letter you selected is invalid. Try Again" << endl;
		cin >> Y;
		Y = toupper(Y);

	}
	cout << "Input the Number of the Row" << endl;
	cin >> X;
	X = X - 48;
	while(X>10 || X < 1)
	{
		cout << "The Number you selected is invalid. Try Again" << endl;
		cin >> X;		
		X = X -48;
	}
	
	col = Y;
	row = X;


}

void ExitMessage()
{
	cout << "Thank You for Playing!" << endl;

}