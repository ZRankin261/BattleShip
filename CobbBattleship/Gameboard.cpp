#include "Gameboard.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

//Initilized the game board with no ships, and No Hits
Gameboard::Gameboard(void)
{
	Hitcount = 0;
	Counter = 0;
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 10; j++)
		{
			Board[i][j].Ship = false;
			Board[i][j].Hit = '_';
		}
}
Gameboard::~Gameboard(void)
{
}
// This function will place the 5 ships randomly on the gameboard without them overlapping
// or running off the edge of the board.
void Gameboard::ShipBuilder()
{
	//Randomly Generates numbers from the time of the CPU
	srand(time(0));
	int row = 0, column = 0, Direction = 0;
	Direction = rand()%4;
	GetPoint(row,column);
	//Creates the Air Craft Carrier
	CreateBoat(row,column,Direction,5);
	//Creates the Battle Ship
	Direction = rand()%4;
	CreateBoat(row,column,Direction,4);
	//Creates the Sub/Destroyer
	Direction = rand()%4;
	CreateBoat(row,column,Direction,3);
	Direction = rand()%4;
	CreateBoat(row,column,Direction,3);
	// Creates the Patrol Boat
	Direction = rand()%4;
	CreateBoat(row,column,Direction,2);
		

	
}
// This function creates the boats on the gameboard, It must first check to see if the boat is
// within the bounds of the game board. Then it will also check to see if their is a conflict
// with an existing boat. Both conditions must be met before the boat can be built.
void Gameboard::CreateBoat(int row, int column, int Direction,int size)
{
	// Flag that is set if confict exists with an existing boat
	bool Conflict = true;
	Conflict = CheckOverlap(row,column,Direction,size);
	if(Direction == 0)
		{
			//checks to see if the boat fits, and if there is a conflict 
			while(row-size <0 || Conflict == true)
			{
				GetPoint(row,column);
				Conflict = CheckOverlap(row,column,Direction,size);
			}
			//Generates the boat
			for(int i = 0; i< size ;i++)
			{
				Board[(row-i)][column].Ship = true;
			}
		}
	else if(Direction == 1)
		{
			//checks to see if the boat fits, and if there is a conflict 
			while(column+size >9|| Conflict == true)
			{
				GetPoint(row,column);
				Conflict = CheckOverlap(row,column,Direction,size);
			}
			//Generates the boat
			for(int i = 0; i< size ;i++)
			{
				Board[row][(column+i)].Ship = true;
			}
		}
	else if(Direction == 2)
		{
			//checks to see if the boat fits, and if there is a conflict 
			while(row+size >9|| Conflict == true)
			{
				GetPoint(row,column);
				Conflict = CheckOverlap(row,column,Direction,size);
			}
			//Generates the boat
			for(int i = 0; i< size ;i++)
			{
				Board[row+i][column].Ship = true;
			}
		}
	else if(Direction == 3)
		{
			//checks to see if the boat fits, and if there is a conflict 
			while(column-size < 0|| Conflict == true)
			{
				GetPoint(row,column);
				Conflict = CheckOverlap(row,column,Direction,size);
			}
			//Generates the boat
			for(int i = 0; i< size ;i++)
			{
				Board[row][(column-i)].Ship = true;
			}
		}
	
}
//Generates new random starting points for the boats to be built from.
//seeded with time to get random results
void Gameboard::GetPoint(int &row, int &column)
{
	row = rand()%10;
	column = rand()%10;
	Counter++;
}
void Gameboard::GetCounter()
{
	cout << "Counter:" << Counter;

}
// This function checks to see if the boat that is being built will overlap with an existing boat.
//if the boats overlap it will set a flag that there is a conflict to be resolved.
//I created this as a seperate function so I would not have to back track if I had a conflict.
bool Gameboard::CheckOverlap(int row, int column, int Direction, int size)
{
	bool Flag = false;
	if(Direction ==0 )
	{
		for(int i = 0; i< size ;i++)
			{
				if(Board[(row-i)][column].Ship == true)
				{
				 Flag = true;
				}
			}
	}

	else if(Direction == 1)
	{
			for(int i = 0; i< size ;i++)
			{
				if(Board[row][(column+i)].Ship == true)
				{
					Flag = true;
				}
			}
	}
	else if(Direction == 2)
	{
		for(int i = 0; i< size ;i++)
			{
				if(Board[(row+i)][column].Ship == true)
				{
					Flag = true;
				}
			}
	}
	else if(Direction == 3)
	{
			for(int i = 0; i< size ;i++)
			{
				if(Board[row][(column-i)].Ship == true)
				{
					Flag = true;
				}
			}

	}
	return Flag;
}
void Gameboard::CheckifHit(char Column, int row)
{
	//Subtracting the proper integer to make it represent the index of my array
	int colindex = (Column-65);

	if(Board[row-1][colindex].Ship == true)
	{
		cout << "\tYou Hit " << Column << " , " << row << endl;
		Board[row-1][colindex].Hit = 'X';
		Hitcount++;
	}
	else
	{
		Board[row-1][colindex].Hit = 'O';
		cout << "\tYou Missed " << Column << " , " << row << endl;
	}

}
// This Function will print the Grid that shows what positions have been hit or missed
// if the Cell has the Hit flag set to true then it will print an X 
// if the Cell has the Hit flag set to false then it will print an M
void Gameboard::PrintShotGrid()
{
	
	cout << "\n\t SHOT GRID" << endl << endl;
	cout << setw(3) << "";
	//prints the column Letter indexes
	for(int k = 0; k < 10; k++)	{
		char temp = 'A';
		temp = static_cast<char>(temp+k);
		cout << left << setw(3) << temp;
	}
	cout << endl;
	for(int i=0; i < 10; i++)
	{
		
		for(int j=0; j < 10; j++)
		{
			// if first row then print the Indexs
			if(j == 0)
			{
				cout << left << setw(3) << i+1;
			}	
				cout << left << setw(3) << Board[i][j].Hit;			

		}
		cout << endl;

	}
}
// This function will print the grid that has just the information on the locations of the ships
// If the Cell has the Ship flag set to true it will print an S for that Cell.
// else the Cell has the Ship flag set to false it will print a W.
void Gameboard::PrintShipGrid()
{
	cout << "\n\t SHIP GRID" << endl << endl;
	cout << setw(3) << "";
	//prints the column indexes
	for(int k = 0; k < 10; k++)	{
		char temp = 'A';
		temp = static_cast<char>(temp+k);
		cout << left << setw(3) << temp;
	}
	cout << endl;
	for(int i=0; i < 10; i++)
	{
		
		for(int j=0; j < 10; j++)
		{
			// if first row then print the Indexs
			if(j == 0)
			{
				cout << left << setw(3) << i+1;
			}
		
			if(Board[i][j].Ship == true)
			{
				//Chose S for Ship
				cout << left << setw(3) << "S" ; 
			}
			else
				//Chose W for Water
				cout << left << setw(3) << "W" ;
		}
		cout << endl;

	}


}