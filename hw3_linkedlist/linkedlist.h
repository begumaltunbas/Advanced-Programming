//
//  linkedlist.hpp
//  hw 3 yeni
//
//  Created by Begum Altunbas on 9.03.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
// 

#include <string>
using namespace std;

struct creditcardnode
{
    string creditcardno;
    creditcardnode * next ;
};


struct expirationnode {
    int month, year ;
    creditcardnode * chead ;
    expirationnode * next  ;
    expirationnode * prev;
    
} ;

class cardlist
{
private:
    expirationnode *head;        //Head node, start of LinkedList
    expirationnode *tail;        //Tail node, end of LinkedList

public:
    cardlist();            //Constructor
    
    void AddInOrder(int month, int year, string creditcardno);
    void LittleAddInOrder( expirationnode *mininode, string cardno) ;
    void displaylistchronological();
    void displaylistreversechronological();
    void cardsearch(string creditcardno);
    void bulkDelete (int month, int year);
    void deleteall() ;
    expirationnode* SearchList (int searchmonth, int searchyear) ;
    void  DeleteOneNode (expirationnode * toBeDeleted) ;
    expirationnode* cardloop(string cardnum) ;
    void cardloop2  (string cardnum) ;
};


