#include "Player.h"
#include "Board.h"
#include<iostream>
#include<string>

using namespace std;

Player :: Player(Board& myboard,char id ,int dir)
	: board(myboard) , playerchar(id),direction(dir) //constructor of player class with board initializer? cheated from tictactoe 
{
	row=0;
	col=0;
}

void Player :: move (int amount)  //move in matrix according to direction and col,row situtation
{
	int counter=0;
	while (counter!=amount)
	{
		if (this->direction==1)
		{
			if (this->col==5)
			{
				if (this->row!=1)
					this->row=1;
				else 
					this->col--;
			}
			else if (this->col==0)
			{
				if (this->row==0)
					this->col++;
				else
					this->row--;
			}
			else 
			{
				if (this->row==0)
					this->col++;
				else 
					this->col--;
			}
			counter++;
		}
		else if (this->direction==0)
		{
			if (this->col==5)
			{
				if (this->row!=0)
					this->row--;
				else
					this->col--;
			}
			else if (this->col==0)
			{
				if (this->row==0)
					this->row=1;
				else
					this->col++;

			}
			else 
			{
				if(this->row==0)
					this->col--;
				else
					this->col++;
			}
			counter++;
			
		}
	}
}


void Player :: claimOwnership() //claims that the cell belongs to player if its vacant
{

	if ( board.getowner(row,col)== '-')
	{
		board.setowner(this->row,this->col,this->playerchar) ;
	}
	
}

bool Player:: wins() //player wins if it has 7 cellcount in the end
{
	if (board.countownedcell(playerchar)==7)
	{
		return true;
	}
	else 
		return false;

}


int Player::getRow()
{
	return row;
}

int Player:: getCol ()
{
	return col ;

}