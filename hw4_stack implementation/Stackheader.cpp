

#include "Stack.h"
#include <iostream>
#include <sstream>
#include <fstream>



DynIntStack::DynIntStack() //constructor 
{
	top = NULL; 
}


void DynIntStack::push(int row , int col ) //code taken from lecture material DynIntStack.cpp
{
	StackNode *newNode;
	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->row = row;
	newNode->col=col ;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

void DynIntStack::pop(int & row , int &col) //code taken from lecture material DynIntStack.cpp
{
	StackNode *temp;

	if (isEmpty())
	{
		return ;
		//cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		row = top->row;
		col = top->col ;
		temp = top->next;
		delete top;
		top = temp;
	}
}

bool DynIntStack::isEmpty() //code taken from lecture material DynIntStack.cpp
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

DynIntStack::~DynIntStack()  //Destructer finally deletes the class members
{
    StackNode *ptr=NULL ;
    StackNode *temp=this->top ;
    while (temp!=NULL )
    {
      
		ptr=temp ;
        temp=temp->next ;
        delete ptr;
    }
}
