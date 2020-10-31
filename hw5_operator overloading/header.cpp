//
//  header.cpp
//  hw5
//
//  Created by Begum Altunbas on 10.04.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
//

//
//  header.cpp
//  hw5
//
//  Created by Begum Altunbas on 10.04.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
//

#include "Header.h"
#include <iostream>
#include <sstream>

IntegerSet :: IntegerSet() //default constructor
{
    myarray = NULL ;
    sizeofarray=0 ;
    
}


IntegerSet :: IntegerSet(int size) // constructor with size
{
    myarray= new int [size];
    sizeofarray=size ;
	for (int i=0 ; i< sizeofarray ; i++) //for Intset5
	{
		myarray[i]= i ;

	}
    
}


IntegerSet :: ~IntegerSet() //destructer deletes elements of class from heap
{
    sizeofarray=0 ;
    delete [] myarray ;
}


IntegerSet :: IntegerSet(const IntegerSet &copy) //deep copy
{
    sizeofarray=copy.sizeofarray ;
    myarray=new int [sizeofarray] ;
    
    
    for (int i=0; i<sizeofarray ;i++)
    {
        myarray[i] =copy.myarray[i] ;
    }
}


int IntegerSet:: getsize()const
{
    int a=0 ;
    a+= this->sizeofarray ;
    return a ;
    
}

int*  IntegerSet:: getarray()const
{
    return this->myarray ;
}


const IntegerSet& IntegerSet::operator=(const IntegerSet & rhs)
{
    if (this != &rhs) // if they are not already equal
    {
        // first delete left hand side
        sizeofarray = 0;
        delete[] myarray;

        // create new vector for left hand side
        sizeofarray = rhs.sizeofarray;
        myarray = new int[sizeofarray];

        for(int i = 0; i < sizeofarray; i++)
        {
            myarray[i] = rhs.myarray[i]; // assign content
        }
    }

    return *this;
}


IntegerSet operator +(const IntegerSet &lhs, const IntegerSet &rhs) //union operator sums the sets
{
    int a= lhs.getsize() ;
    int* b= lhs.getarray() ;
    
    int c=rhs.getsize() ;
    int* d= rhs.getarray() ;
    
    IntegerSet temp = IntegerSet(lhs) ;
    for(int i=0 ; i< c ;i++)
    {
        temp= temp+d[i] ;
        
    }
    return temp ;
}


const IntegerSet& IntegerSet :: operator += ( const IntegerSet &rhs)
{

	IntegerSet temp= IntegerSet() ;
	temp=rhs +*this ;
	*this=temp ;

 
    return *this ;
}

IntegerSet operator + (IntegerSet &lhs, int rhs) // adding element to array/set 
{
    bool flag=true ;
    for (int i=0 ; i< lhs.getsize() ; i++) // existence of elemnt in array check
    {
        if(lhs.getarray()[i]==rhs)
            flag=false ;
        
    }
    if (flag==true) // if unique then create size up set and add element to it
    {
        IntegerSet set= IntegerSet(lhs.getsize()+1);
        int *newone= set.getarray() ;
        int size =set.getsize();
        
        for (int i=0 ; i<size; i++)
        {
            if (i<lhs.getsize())
            {
                newone[i]=lhs.getarray()[i] ;
                }
            else
            {
                newone[i]=rhs ;
            }
            
        }
        return set;  
    }
    return lhs ;
    
}




ostream & operator << (ostream &osint, const IntegerSet &set) //printing elements of the set
{
  
    int a= set.getsize();
    int *b= set.getarray() ;
    osint <<"{" ;
    for (int i=0 ; i< a ; i++)
    {
        if (i!=a-1)
        {
            osint << b[i] << ",";
        }
        else {
            osint<< b[i] ;
        }
            }
    osint << "}" ;

    return osint ;
}


bool IntegerSet :: operator != (const IntegerSet & rhs) //checking if sets are equal
{
    if (this->sizeofarray!= rhs.sizeofarray)
    {
        return true ;
        
    }
    int i=0;
	for (int k=0 ; k<this->sizeofarray ; k++)
	{
		if (this->myarray[i] != rhs.myarray[k] )
		{
			return true ;
		}
		i++ ;   
    }
    return false;
   
}

IntegerSet  operator * (const IntegerSet &lhs, const IntegerSet & rhs) //intersection of both sets
{

    int a= lhs.getsize() ;
    int *b= lhs.getarray() ;
    
	int c=rhs.getsize();
	int *d= rhs.getarray();

    IntegerSet newone = IntegerSet() ;
    int *e = newone.getarray() ;

    for (int i=0 ; i<a ; i++)
    {
        for (int k=0; k< c ; k++)
        {
            if(b[i] == d[k])
            {
               newone= newone + d[k] ;
            }
                       
            
        }
    }
  return newone;
   
}



bool operator <= (int lhs,const IntegerSet & rhs ) 
{
    int a= rhs.getsize() ;
    int* b= rhs.getarray();
    for (int i=0; i< a ; i++)
    {
        if (lhs == b[i])
        {
            return true ;
        }
    }
    return false;
}


bool IntegerSet:: operator <= (const IntegerSet &rhs) //subset operator
{
    int x ;
    for (int i=0 ; i<this->sizeofarray; i++)
    {
        for ( x=0; x< rhs.sizeofarray ; x++)
        {
            if (this->myarray[i]==rhs.myarray[x])
            {
                break ;
                
            }
            
        }
        if (x==rhs.sizeofarray)
        {
            return false;
        }
    }
        
    
    return true;
}




