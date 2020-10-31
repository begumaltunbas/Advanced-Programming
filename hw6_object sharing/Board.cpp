
#include "Board.h"
#include "Player.h"
#include<iostream>
#include<string>


using namespace std;

Board ::Board() //initialize each cell to vacant "-"
{
	for (int i=0; i<2 ; i++)
	{
		for (int k=0; k<6 ;k++)
		{
			theboard[i][k]= '-';
		
		}
	}
}

void Board :: displayBoard ()  //displays matrix
{
	for (int i=0; i<2 ; i++)
	{
		for (int k=0; k<6 ;k++)
		{
			cout<< theboard[i][k]<<" ";
		
		}
		cout<< endl ;
	}
}

char Board:: getowner(int row, int col) //returns the owner of cell
{
	if (theboard[row][col]=='-')
	{
		return '-';
	}
	else if (theboard[row][col]=='A')
	{
		return 'A ';  
	}
	else {
		return 'B' ;
	}
	
}

void Board :: setowner(int row, int col, char player) //sets the owner to the relevant player
{
	
	theboard[row][col]=player ;
	 
}

bool Board::isFull()  //returns false if at least 1 cell is vacant
{
	for (int i=0 ;i<2; i++)
	{
		for (int k=0;k<6 ;k++)
		{
			if (theboard[i][k] == '-')
				return false;
			
		}
	}
	return true;
}

int Board :: countownedcell(char player) //returns the owned cell by player 
{
	int score= 0;
	for (int i=0; i<2 ; i++)
	{
		for (int k=0; k<6 ;k++)
		{
			if (theboard[i][k]==player)
				score++;
		}
	}
	return score;
}