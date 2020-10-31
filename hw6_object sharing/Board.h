
#include<string>
using namespace std;

#ifndef BOARD
#define BOARD

class Board
{
private:
	char theboard[2][6] ;

public:
	Board();
	void displayBoard() ;
	bool isFull();
	char getowner(int row, int col);
	void setowner(int row ,int col, char owner);
	int countownedcell(char player);


};

#endif