//
//  main.cpp
//  hw 3 yeni
//
//  Created by Begum Altunbas on 9.03.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
//

#include "linkedlist.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>


using namespace std ;

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

bool monthinputchecker (string month, string year) //this func checks if expiration date input is valid  or not for option 3
{
    if ((if_number(month)==true) && (if_number(year)==true))
    {
        int  monthint = atoi(month.c_str()) ;
//        int yearint =atoi(year.c_str()) ;
        if ( 12 <monthint ||  monthint<0 )
        {
            return false ;
        }
        else {
            return true ;
        }
        
    }
    else {
        return false ;
    }
}

bool creditcardnumcheck (string cardnumber ){ //checks if a valid credit card num is taken as input
    
    if (cardnumber.length()!= 16)
        return false ;
    
    if (if_number(cardnumber) ==false)
        return false ;
    
    return true ;
}

void option1 (cardlist& doublelinkedlist){ //if user inputs 1  open the file and cout the nodes
    ifstream inputfile ;
    string input1 ;
    
    cout<< "Please enter filename: " ;
    cin>> input1 ;
    
    inputfile.open(input1) ;
    
    if (inputfile.fail()) //check if file opens correctly
    {
        cout<< "Could not find a file named " << input1 << endl ;
        cout << " "<<endl ;
    }
    string creditcardnum ;
    int month=-1 ;
    int year=-1 ;
    while (getline(inputfile, input1)){
        istringstream iss (input1) ;
        iss>>creditcardnum>>month>>year ;
		if (month!=-1 && year !=-1){
		if (doublelinkedlist.SearchList(month, year)== NULL ){
            doublelinkedlist.AddInOrder(year, month, creditcardnum) ;
            cout<< creditcardnum << " "<< month<<" "<<year<< ":"<< "added to a new expiration date node" << endl ;
                        
        }
        else if (doublelinkedlist.SearchList(month, year)!= NULL && doublelinkedlist.cardloop(creditcardnum)==NULL ){
            
            cout<< creditcardnum << " "<< month<<" "<<year<< ":"<< " inserted to an existing expiration date node"<< endl ;
            doublelinkedlist.AddInOrder(year, month, creditcardnum) ;
            
        }
        else if (doublelinkedlist.cardloop(creditcardnum)!=NULL ){
            cout<< creditcardnum << " "<< month<<" "<<year<< ":"<<" this card was already inserted" << endl ;
        }
		
		
		}

        
    }
}

int main() {
    cardlist doublelinkedlist ;
    string  input;
    string inputcard ;
    string month1, year1 ;
    int smt=0 ;
   
    while (smt!=6){ //option menu created
        cout<< "1) Upload Card(s) from a File" << endl ;
        cout<< "2) Display List Chronological" <<endl ;
        cout<< "3) Display List Reverse Chronological" << endl ;
        cout<< "4) Card Search"<< endl ;
        cout<< "5) Bulk Delete" << endl ;
        cout<< "6) Exit " << endl ;
        cout<< " Please choose option from the menu: " ;
        cin>> input ;
        
        if (if_number(input)==true ){
            int  inputinteger = atoi(input.c_str()) ;
            
            if (inputinteger ==1) {
               option1(doublelinkedlist) ;
            }
            else if (inputinteger==2) {
                
                doublelinkedlist.displaylistchronological() ;
            }
            else if (inputinteger==3){
                doublelinkedlist.displaylistreversechronological() ;
            }
            else if (inputinteger==4){
                cout<< "Please enter the credit card number: " ;
                cin>> inputcard ;
                while (creditcardnumcheck(inputcard) ==false )
                {
                    cout<< "Invalid format!"<< endl ;
                    break ;
                }
                if  (creditcardnumcheck(inputcard)==true)
                {
                    
                    if (doublelinkedlist.cardloop(inputcard)!=NULL )
                    {
                        doublelinkedlist.cardloop2(inputcard) ;
                        
                    }
                    else {
                        cout<< "There is no credit card with given credit card number: "<< inputcard << endl ;
                    }
                }
            }
            else if (inputinteger==5){
                cout<< "Please enter month and year: " ;
                cin >>month1;
                cin>>year1 ;
                while (monthinputchecker(month1, year1) == false)
                {
                    cout<< "Invalid format!"<< endl ;
                    break ;
                }
                if (  monthinputchecker(month1, year1)==true )
                {
                    int  monthint=atoi(month1.c_str()) ;
                    int  yearint= atoi(year1.c_str()) ;
                    doublelinkedlist.bulkDelete(monthint, yearint) ;
                    
                }
                
            }
            else if (inputinteger ==6){ //clean the nodes in each linkedlist
                cout<< "All the nodes have been deleted!"<< endl ;
                cout<< "Terminating!!!" ;
                doublelinkedlist.deleteall() ;
                return 1 ;
            }
        }
        else {
            cout<< "Invalid Operation!"<< endl ;
        }
        
    }
    return 0;
}
