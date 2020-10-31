
#include <iostream> 
#include "Board.h"
#include<string>

using namespace std;

class Player 
{
private:
	char playerchar ;
	int row,col ;
	int direction;
	Board& board ;

public :
	Player :: Player(Board& myboard, char id ,int dir) ;
	
	void move (int amount);
	void claimOwnership();
	bool wins ();
	int getRow();
	int getCol();


};