
//  main.cpp
//  Homework1
//  Created by Begum Altunbas on 6.02.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
//this piece of code is smt gameish that finds a closed area on a matrix filled with x s and o s.

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

bool  if_number (string s ) //this function checks if the user input coordinates contain  alphabetical letters
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
struct cells
{
    int x ;
    int y ;
    
} ;

bool coordinateVisited ( vector <cells> storedcoordinates, int a , int b ) //func stores the visited coordinates in a vector built with a struct which contains x and y coordinates as integers
{
    for (int i=0 ; i< storedcoordinates.size(); i++ )
    {
        if ((storedcoordinates[i].x == a) && (storedcoordinates[i].y == b) ){
            return false ;
        }
    }
    
    return true ;
}


int enclosed_area (int c,int d, vector <vector<char> > &matrix,  vector <cells> &storedcoordinates ) //this func returns 3 diff int values accd to possible results of exec.
{
  
    char startingpoint =  matrix[c][d] ;
    cells cellstart ;
    cells cell ;
    cellstart.x=c ;
    cellstart.y =d ;
    storedcoordinates.push_back(cellstart) ; //first store initial coords as cellstart
    
    
    if(startingpoint== 'o')
    {
        cout<< "This cell is not occupied!"<< endl ;
        return 1;
        
    }
    bool flag= true ;
    while (flag)
    {
        if   (d < matrix[0].size()-1 && matrix[c][d+1]== 'x' &&
              (coordinateVisited(storedcoordinates, c, d+1))== true) //right check
        {
        cells cell  ;
        cell.x =c ;
        cell.y = d+1 ;
        if ( (cell.x != cellstart.x) || (cell.y != cellstart.y) )
        {
            storedcoordinates.push_back(cell) ;
            d ++ ;
        }
    }
    else if(c < matrix.size()-1 && matrix[c+1][d]=='x' && (coordinateVisited(storedcoordinates, c+1, d))== true ) //down check
    {
        cell.x =c+1 ;
        cell.y = d ;
        if ( (cell.x != cellstart.x) || (cell.y != cellstart.y))
        {
            storedcoordinates.push_back(cell) ;
            c ++ ;
        }
       
    }
    else if (0<d && d < matrix [0].size()+1 && matrix[c][d-1]=='x' && (coordinateVisited(storedcoordinates, c, d-1))== true) //left check
    {
        cell.x = c ;
        cell.y = d-1;
        if ( (cell.x != cellstart.x) || (cell.y != cellstart.y))
        {
            storedcoordinates.push_back(cell) ;
            d--  ;
        }
      
    }
    else if (0<c && c<matrix.size()+1 && matrix[c-1][d]== 'x' && (coordinateVisited(storedcoordinates, c-1, d))== true) // up check
    {
        cell.x =c-1 ;
        cell.y = d ;
        if ( (cell.x != cellstart.x) || (cell.y != cellstart.y))
        {
            storedcoordinates.push_back(cell) ;
            c--  ;
        }
    }
     else //
     {
         flag= false ;
         if (((c-1 == cellstart.x) && (d == cellstart.y))  || ((c == cellstart.x) && (d+1 == cellstart.y)) ||  ((c+1 == cellstart.x) && (d == cellstart.y)) ||  ((c == cellstart.x) && (d-1 == cellstart.y)) ) // if last stored coordinate's any neighbour  is equal to starting coordinate then it is a closed area
         {
             return 2;
             
         }
         else { // not closed area
                  return 3 ;
         }
     }
}
    return 0 ;
}

int main()
{
    ifstream inputfile ;
    string studentinput ;
    cout<< "Please enter filename: " ;
    cin>> studentinput ;
    
    inputfile.open(studentinput) ;
    
    while (inputfile.fail())
    {
        cout<< "Can not find a file named " << studentinput << endl ;
        cout<< "Please enter filename: " ;
        cin>>studentinput ;
        inputfile.open(studentinput) ;
    }
    // 146-159 tranfering txt into a matrix
    string line ;
    vector <vector<char> > matrix ;
    int counter =0 ;
    while(getline(inputfile,line))
    {
        istringstream iss (line) ;
        char y ;
        matrix.push_back(vector<char>()) ;
        while (iss>>y)
        {
            matrix [counter].push_back(y) ;
        }
        counter++ ;
    }
    
    bool flag=true ;
    
    for (int i = 1; i < matrix.size(); i++)
    {
        if (matrix[0].size()!= matrix[i].size()) //check if builds a proper matrix size
        {
            
           cout<< studentinput << " is invalid matrix, does not contain same amount of char each row! "<< endl ;
            flag=false ;
            return 1;
        }
        
    }
    if (flag ==true )
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[0].size(); j++) //check if contains element other than x and o
            {
                if (matrix[i][j] != 'o' && matrix [i][j] !='x')
                {
                        flag=false ;
                    }
                }
            }
        if (!flag)
        {
                cout<< studentinput << " includes invalid char(s)" << endl ;
        }
    }
    string  a,b ; //input coordinates by user created as string
    if (flag==true)
    {
        cout<< "Input matrix: "<< endl ;
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[0].size(); j++)
            {
                cout << matrix[i][j];
            }
            cout << endl;
        }
        int inta =0 ;
        int intb=0 ;
        while (inta != -1 && intb !=-1 )
        {
            cout<< "Please enter starting coordinates, first row X then column Y: " ;
            
            cin >> a>>b;
            while ( if_number(a)== false || if_number(b)==false)
                    {
                        cout<< "Invalid coordinates "<< endl ;
                        cout<< "Please enter starting coordinates, first row X then column Y: " ;
                        cin >> a ;
                        cin>> b ;
                   }
                    inta = atoi(a.c_str()) ; //turning string coord numbers  into integers
                    intb =atoi(b.c_str()) ;
                    
                    while ((inta >=matrix.size() || inta<0) || (intb>=matrix[0].size() || intb<0) )
                   {
                       if (inta==-1 && intb==-1)
                       {
                           cout<< "Terminating..."<< endl ;
                           return 0 ;
                       }
                       
                       cout<< "Invalid coordinates" << endl ;
                       cout<< "Please enter starting coordinates, first row X then column Y: " ;
                       
                       cin >> a >>b ;
                       
                       if (if_number(a)==true && if_number(b)==true ){
                           inta = atoi(a.c_str()) ;
                           intb =atoi(b.c_str()) ;
                       }
                       
                   }
                    vector <cells> storedcoordinates ;
                    int result =enclosed_area(inta, intb, matrix, storedcoordinates) ;
            
                      if ( result ==2 ){
                          if (storedcoordinates.size()>=4){
                              cout<< "Found an enclosed area. The coordinates of the followed path: " << endl ;
                              for (int i=0 ; i < storedcoordinates.size() ; i++ )
                              {
                                  cout<< storedcoordinates[i].x << " "<< storedcoordinates[i].y << endl ;
                                  
                              }
                              
                          }
                          else {
                              cout<< " Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path: " << endl ;
                              for (int i=0 ; i < storedcoordinates.size() ; i++ )
                              {
                                  cout<< storedcoordinates[i].x << " "<< storedcoordinates[i].y << endl ;
                                  
                              }
                          }
                    }
                    else if (result ==3 )
                    {
                        cout<< " Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path: " << endl ;
                        for (int i=0 ; i < storedcoordinates.size() ; i++ )
                        {
                            cout<< storedcoordinates[i].x << " "<< storedcoordinates[i].y << endl ;
                            
                        }
                    }
        }
  }
return 0;
}
