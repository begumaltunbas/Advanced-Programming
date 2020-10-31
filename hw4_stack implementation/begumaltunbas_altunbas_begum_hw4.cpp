//
//  main.cpp
//  hw4
//
//  Created by Begum Altunbas on 21.03.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
//


#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include "Stack.h"

using namespace std ;

void print_table(char** values,  int num_rows, int num_cols)
{
    int i, j;
    for (i = 0; i < num_rows; i++) {
        for (j= 0 ; j< num_cols ; j++)
            cout << values[i][j] << " ";
        cout << endl;
    }
}


bool  if_number (string s ) //this function checks if the user input coordinates contain  digits or not
{
    for (int i=0 ; i< s.length(); i++)
    {
        char c = s.at(i) ;
        if ((c>= 48 && c<= 57) )
        {
            return true ;
            
        }
    }
    return false;
}

void filecheck (){ 
    ifstream inputfile ;
    string input1 ;
    
    cout<< "Please enter file name: " ;
    cin>> input1 ;
    
    inputfile.open(input1) ;
    
    if (inputfile.fail()) //check if file opens correctly
    {
        cout<< "Can not open a file named " << input1 << endl ;
        cout << " "<<endl ;
        filecheck() ;
    }
    
}



void traverse(char** values,  int startrow, int startcol,DynIntStack stack, char fillingchar)
{
    bool flag=true ;
    const int actstartrow=startrow ;
    const int actstartcol=startcol ;

    bool a=true ;
    while (flag)
    {
        if (values[startrow][startcol+1] != 'X' && values[startrow][startcol+1] == ' '){ //right check
            
            values[startrow][startcol+1] = fillingchar ;
            stack.push(startrow, startcol+1);
            startrow =startrow;
            startcol =startcol+1 ;

            a=true ;
            
        }
        else if (values[startrow+1][startcol] != 'X' && values[startrow+1][startcol]== ' '){ //down check
            values[startrow+1][startcol] =fillingchar ;
            stack.push(startrow+1, startcol) ;
            startrow=startrow+1 ;
            startcol =startcol ;
            a=true;
        }
        
        else if (values[startrow][startcol-1] != 'X' && values[startrow][startcol-1]== ' '){ //left check
            values[startrow][startcol-1] =fillingchar ;
            stack.push(startrow, startcol-1) ;
            startcol=startcol-1 ;
            startrow =startrow;

            a=true ;
        }
        
        else if (values[startrow-1][startcol] != 'X' && values[startrow-1][startcol]== ' '){ //up check
            
            values[startrow-1][startcol] =fillingchar ;
            stack.push(startrow-1, startcol) ;
            startrow=startrow-1 ;
            startcol =startcol ;

            a=true ;
        }
        
        else {
			//no neighbour avaliable then pop the last coordinate
           
            stack.pop(startrow, startcol);
          
        }
        if (startcol==actstartcol && startrow==actstartrow && a)
        {
            a=false ;
        }
        else if (stack.isEmpty()==true)
        {
			//when the stack is finally empty then stop the loop
            flag=false ;
        }
        
    }
   
    
}


int main ()
{
    ifstream file ;
    string inputrow, inputcol,inputfile,startrow,startcol ;
    bool flag=true ;
    
    while (flag==true ) {
        cout<< "Enter the number of rows: " ;
        cin>> inputrow ;
        if (if_number (inputrow)== false)
        {
            cout<< inputrow << " is not valid!" << endl ;
            
            
        }
        
        else if (if_number (inputrow)== true)
        {
            int  inputrowint = atoi(inputrow.c_str()) ;
            if (inputrowint<=0 || inputrowint<3)
            {
                cout<< inputrowint << " is not valid!" << endl ;
            }
            else {
                break ;
            }
        }
    }
    
    bool flag2=true ;
    
    while (flag2==true)
    {
        
        cout<< "Enter the number of columns: " ;
        cin >> inputcol ;
        if (if_number(inputcol)==false)
        {
            cout<< inputcol << " is not valid!" << endl ;
            
        }
        else {
            int  inputcolint = atoi(inputcol.c_str()) ;
            if (inputcolint<=0 || inputcolint<3)
            {
                cout<< inputcolint << " is not valid!" << endl ;
                
            }
            else {
                break ;
            }
        }
    }
    
    cout<< "Please enter filename: " ;
    cin>> inputfile;
    
    file.open(inputfile) ;
    
    while (file.fail())
    {
        cout<< "Can not find a file named " << inputfile << endl ;
        cout<< "Please enter filename: " ;
        cin>>inputfile ;
        file.open(inputfile) ;
    }
    
    string line ;
    string rowst ;
    string colst ;
    
    
    int row ;
    int column;
    
    int a ;
    a= inputfile.find('x') ;
    
    rowst= inputfile.substr (0,a) ;
    row = atoi(rowst.c_str()) ;
    inputfile= inputfile.substr(a+1) ;
    
    
    int b;
    b=inputfile.find('.') ;
    colst = inputfile.substr(0,b) ;
    column =atoi(colst.c_str()) ;
    

	//create matrix without class and vector but using 2d dynamic arrays
    char ** nums  ;
    nums = new char* [row] ;
    
    for(int i=0 ; i<row ;i ++)
    {
        nums [i] = new char [column] ;
    }
    
    int i=0 ;
    while (getline(file, line))
    {
        for (int j= 0 ; j< column ; j++)
        {
            nums[i][j] =line[j];
            
        }
        i++ ;
        
    }
    
    int startrowint ;
    int startcolint ;
    
    cout<< "Please enter starting point: " ;
    cin>> startrow>>startcol;
    while (if_number(startrow)==false || if_number(startcol)==false )
    {
        cout<< "Invalid coordinate!" <<endl ;
        cout<< "Please enter starting point: " ;
        cin>> startrow>>startcol;
    }
    while (if_number(startrow)==true && if_number(startcol)==true )
    {
        startrowint = atoi(startrow.c_str()) ;
        startcolint = atoi(startcol.c_str()) ;
        
        if ((startrowint<0 || startrowint>=row) || (startcolint<0 ||startcolint>=column) ){
            cout<< "Invalid coordinate!" <<endl ;
            cout<< "Please enter starting point: " ;
            cin>> startrow>>startcol;
        }
        else {
            if (  nums[startrowint][startcolint] == 'X' ){
                cout<< "Starting point is already occupied."<<endl ;
                cout<< "Terminating..."<<endl ;
				
                return 1;
            }
            break ;
            
           
        }
        
    }
    char charinput ;
    cout<< "Enter the filling char: " ;
    cin>>charinput ;
    while (charinput=='X' || charinput== 'x')
    {
        cout<< "Filling char is not valid!" <<endl ;
        cout<< "Enter the filling char: " ;
        cin>>charinput ;
    }
  
    DynIntStack stack;
    stack.push(startrowint, startcolint);
    nums[startrowint][startcolint] = charinput ;
    traverse(nums, startrowint, startcolint, stack,  charinput) ;
    print_table(nums, row, column) ;
    
    return 0 ;
}


