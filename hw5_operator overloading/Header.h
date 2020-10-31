//
//  Header.h
//  hw5
//
//  Created by Begum Altunbas on 10.04.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
//
#include <iostream>


using namespace std ;

class IntegerSet
{
private:
    int sizeofarray ;
    int *myarray; //= new int [size] ;
    
public :
    IntegerSet() ;
    IntegerSet(int size) ;
    ~IntegerSet() ; // destructor
    IntegerSet (const IntegerSet &copy) ; //deep copy constructor
    const IntegerSet &  operator = (const IntegerSet &rhs) ;
    bool operator != ( const IntegerSet & rhs);
    bool operator <= (const IntegerSet & rhs );
    const IntegerSet & operator += ( const IntegerSet &rhs); 
    int getsize ()const;
    int*  getarray ()const ;

    
   
    
};

ostream & operator << (ostream &os, const  IntegerSet & myarray) ; 
IntegerSet operator + (const IntegerSet & lhs , const IntegerSet & rhs); 
bool operator <= (int lhs,const IntegerSet & rhs );
IntegerSet operator * (const IntegerSet &lhs, const IntegerSet & rhs);
IntegerSet operator + ( IntegerSet &lhs, int rhs);


