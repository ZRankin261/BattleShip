#pragma once
class Gameboard
{
	struct Cell{
		bool Ship;
		char Hit;	
	};

private:
	int Hitcount;	
	Cell Board[10][10];
	int Counter;
public:	
	Gameboard(void);
	void ShipBuilder();
	void CreateBoat(int row, int column, int Direction, int size);
	bool CheckOverlap(int row, int column, int Direction, int size);
	void GetPoint(int &row, int &column);
	void CheckifHit(char row, int column);
	int GetHitCount() {return Hitcount;};
	void PrintShotGrid();
	void PrintShipGrid();
	void GetCounter();
	~Gameboard(void);
};

