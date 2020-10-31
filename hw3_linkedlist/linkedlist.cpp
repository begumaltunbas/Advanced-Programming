//
//  linkedlist.cpp
//  hw 3 yeni
//
//  Created by Begum Altunbas on 9.03.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
//

#include "linkedlist.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

cardlist::cardlist ()
{
    head = NULL ;
    tail = NULL ;
}


void cardlist :: LittleAddInOrder( expirationnode *mininode, string cardno)// this func is taken from lecture materials and its for the single linked list which only carries card numbers we put them in ascending order

{
    creditcardnode *  ptr = mininode->chead;   // loop variable
    
    // if new node should be first, handle this case and return
    // in this case, we return the address of new node since it is new head
    if ((mininode->chead == NULL) || (cardno< mininode->chead->creditcardno))
    {
        creditcardnode * temp = new creditcardnode;  //node to be inserted
        temp->creditcardno=cardno ;
        temp->next = mininode->chead; //connect the rest
        mininode->chead =temp ;
        return ;
        //return new node(newkey, head);    //alternative to prev. 4 lines
    }
    
    // check node one ahead so we don't pass!
    while ( (ptr->next != NULL) && (ptr->next->creditcardno < cardno))
    {
        ptr = ptr->next;
    } // postcondition: new node to be inserted just after the node that ptr points
    
 
    //now insert node with newkey after where ptr points to
    creditcardnode * temp = new creditcardnode;  //node to be inserted
    temp->creditcardno=cardno ;
    temp->next = ptr->next; //connect the rest
    ptr->next = temp;
    //ptr->next = new node(newkey,ptr->next);   //alternative to prev. 4 lines
}



void cardlist::AddInOrder( int year, int month, string cardnumber) // this func is taken from lecture materials puts the linked list in a ascending order acc to dates and its a dobuled one modifies version of single which i implemented prev node as well

{
    expirationnode *bikbik = SearchList(month, year) ;
    if (bikbik==NULL )
    {
        expirationnode * ptr = head;   // loop variable
        
        // if new node should be first, handle this case and return
        // in this case, we return the address of new node since it is new head
        if ((head == NULL) || (year < head->year) || (head->year == year && head->month> month ))
        {
            expirationnode * temp = new expirationnode;  //node to be inserted
            temp->chead = NULL ;
            temp->year = year;
            temp ->month =month ;
            //        temp ->cards.push_back(cardnumber) ;
            LittleAddInOrder(temp, cardnumber) ;
            temp->next = head;
            if (head ==NULL){
                tail =temp ;
            }
            head = temp ;
            temp ->prev =NULL ;
            
            if (head->next != NULL ){
                temp->next->prev = temp ;
            }
//           cout<< cardnumber << " "<< month<<" "<<year<< ":"<< " added to a new expiration date node" << endl ;
            
            return;
            //return new node(newkey, head);    //alternative to prev. 4 lines
        }
        
        // check node one ahead so we don't pass!
        while ( (ptr->next != NULL) && ((ptr->next->year < year) || ( (ptr->next->year == year) && ptr->next->month< month )))
        {
            ptr = ptr->next;
        } // postcondition: new node to be inserted just after the node that ptr points
        
        //now insert node with newkey after where ptr points to
        expirationnode * temp = new expirationnode;  //node to be inserted
        
        temp->chead = NULL ;
        temp->month = month;
        temp->year =year ;
        //    temp ->cards.push_back(cardnumber) ;
        LittleAddInOrder(temp, cardnumber);
        temp->next = ptr->next; //connect the rest
        ptr->next = temp;
        temp->prev =ptr ;
        if (temp ->next != NULL ){
            temp->next->prev =temp ;
        }
        else {
            tail= tail->next ;
//            cout<< cardnumber << " "<< month<<" "<<year<< ":"<< " added to a new expiration date node" << endl ;
        }
    }
    else {
                    LittleAddInOrder(bikbik, cardnumber);
    }
}


void cardlist::displaylistchronological(){ // prints the list in chronological orders
    
    expirationnode * ptr = head;
    if (head ==NULL ){
           cout<< "List is empty!"<< endl ;
        return ;
       }
    creditcardnode *vikvik = ptr->chead ;
   
    while (ptr != NULL)
    {
        cout<< "Expiration Date: "<< ptr->month<< " " << ptr->year << endl ;
        vikvik = ptr->chead ;
        int count =1 ;
        while (vikvik != NULL){
            cout <<count << ")"<< vikvik->creditcardno<<endl ;
            vikvik= vikvik->next ;
            count ++ ;
        }
        
        cout<< "-------------------" << endl ;
        ptr = ptr->next;
    }
    cout << endl<<endl;
}

void cardlist::displaylistreversechronological() // prints the list reverse by starting from tail to head
{
    
    expirationnode * ptr = tail ;
    if (tail ==NULL ){
          cout<< "List is empty!"<< endl ;
        return ;
      }
    creditcardnode *vikvik = ptr->chead ;
  
    while (ptr != NULL)
    {
        vikvik = ptr->chead ;
        cout<< "Expiration Date: "<< ptr->month<< " " << ptr->year << endl ;
        int count=1 ;
        while (vikvik != NULL){
            cout<< count << ")" ;
            cout << vikvik->creditcardno<<endl ;
            vikvik= vikvik->next ;
            count ++ ;
        }
        
        cout<< "-------------------" << endl ;
        ptr = ptr->prev;
    }
    cout << endl<<endl;
    
    
}

expirationnode* cardlist::SearchList( int searchmonth, int searchyear) // this function is taken from recitation mat and checks if a value is found in list
{
    expirationnode *temp =head  ;
    while (temp != NULL)
    {
        if((temp->month == searchmonth) && (temp ->year == searchyear)) //If the node with the given expiration date  is found
            return temp;
        temp = temp->next;
    }
    //If the code proceeds from here, it means that the whole list is traversed
    //and a node with ID == searchValue could not be found.
    return NULL;
}


expirationnode* cardlist::cardloop(string cardnum) // checks if a cardnumber input exists in any of the nodes
{
   
    expirationnode *temp =head  ;
    while (temp != NULL)
    {
        creditcardnode * ptr = temp->chead ;
        while (ptr != NULL){
            if (ptr->creditcardno==cardnum)
            {
                return temp ;
            }
            ptr=ptr->next ;
        }
        temp = temp->next;
    }
    return NULL  ;
}



void  cardlist::DeleteOneNode (expirationnode * toBeDeleted) // this func is taken from lecture materials and deletes a specific node from a list and reconnects the remaining nodes
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
    expirationnode * ptr;
        
    if (toBeDeleted == head)  //if the node to be deleted is the first node
    {
        head = head->next;
        delete toBeDeleted;
        if (head!=NULL){
            head->prev = NULL ;
        }
        
    }
    else  //if the node to be deleted is in the middle or at the end
    {
        ptr = head;
        while (ptr->next != toBeDeleted){
             ptr = ptr->next;
        }

        if (toBeDeleted==tail ){
            tail =tail->prev ;
        }

        //after while ptr point to the node just before toBeDeleted

        //connect the previous node to the next node and delete
        ptr->next = toBeDeleted->next;
        delete toBeDeleted;
    }
}
void cardlist::bulkDelete(int month, int year) //this func deletes all nodes bigger then the input date by using deleteonenode
{
    expirationnode * temp=head  ;
    while ((temp != NULL) && (year > temp->year || (temp->year == year && temp->month< month )))
    {
        creditcardnode *pıt=temp->chead  ;
        int count=1 ;
        cout<< "Node with expiration date "<<  temp->month<< " " << temp->year<<  " and the following credit cards have been deleted!" << endl ;
        while (pıt != NULL ){
            
            cout<< count<<")"<<  pıt->creditcardno<< endl  ;
			if (pıt!=NULL){
				creditcardnode *temp2 =pıt ;
				pıt=pıt->next ;
				delete temp2 ;

			}
			
            count ++ ;
        }
       DeleteOneNode(temp);
        temp=head ;
    }
    
}


void cardlist::deleteall(){ //this funct is traversing each element of both linkedlists and deletes one by one by using deletonenode func
    
    expirationnode * pointer1 ;
    pointer1=head ;
    creditcardnode *pointer2 ;
    
    pointer2 = NULL ;
    while(pointer1!=NULL ){//finally clean whole linked list delete all nodes
        pointer2 =pointer1->chead;
        while (pointer2!=NULL){
			creditcardnode *temp =pointer2 ;
            pointer2 =pointer2->next ;
            delete temp ;
        }
        pointer1= head->next ;
        delete head  ;
        head=pointer1 ;
    }
    head=NULL ;
    pointer2= NULL ;
    
    
}


void cardlist::cardloop2(string cardnum){
     
    expirationnode *temp =head  ;
       while (temp != NULL)
       {
           creditcardnode * ptr = temp->chead ;
           while (ptr != NULL){
               if (ptr->creditcardno==cardnum)
               {
//                   return temp ;
                    cout<< "There exists a credit card given number "<< cardnum << " with expiration date: "<< temp->month<<" "<< temp->year<<endl ;
               }
               ptr=ptr->next ;
           }
           temp = temp->next;
       }
      
    
}
