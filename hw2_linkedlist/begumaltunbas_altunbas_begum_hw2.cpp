//
//  main.cpp
//  hw2
//
//  Created by Begum Altunbas on 21.02.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>


using namespace std ;

struct node { //creating node with month year and vector of card numbers
          int month, year;
          vector<string> cards;
          node* next;
};

node * SearchList(node *head, int searchmonth, int searchyear) // this function is taken from recitation mat and checks if a value is found in list
{
    node *temp =head  ;
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
        int yearint =atoi(year.c_str()) ;
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

bool cardloop(string cardnum, node *head, int &a,int &b) // checks if a cardnumber input exists in any of the nodes
{
    node *temp =head  ;
    while (temp != NULL)
    {
        for (int i=0; i< temp->cards.size();i++){
            if (temp->cards[i] == cardnum){
                 a=temp->month ;
                 b=temp->year ;
                return true ;
            }
               
        }
        temp = temp->next;
    }
    return false ;
}


void DisplayList (node * head) // this func is taken from lecture materials displays the linked list
{
    
    node * ptr = head;
    while (ptr != NULL)
    {
        cout<< "Expiration Date: "<< ptr->month<< " " << ptr->year << endl ;
        for (int i=0 ; i<ptr-> cards.size(); i++)
        {
            cout<< i+1 << ")" << ptr->cards[i] << endl ;
        }
        cout<< "-------------------" << endl ;
        ptr = ptr->next;
    }
    cout << endl<<endl;
}


node * AddInOrder(node * head, int year, int month, string cardnumber) // this func is taken from lecture materials puts the linked list in a sorted way though i did some modifications and applied differenr if statements and changed values according to hw case
// pre: list is sorted
// post: add newkey to list, keep list sorted, return head of new list with newkey in it
{
    node *  ptr = head;   // loop variable

    // if new node should be first, handle this case and return
    // in this case, we return the address of new node since it is new head
    if ((head == NULL) || (year < head->year) || (head->year == year && head->month> month ))
    {
        node * temp = new node;  //node to be inserted
        temp->year = year;
        temp ->month =month ;
        temp ->cards.push_back(cardnumber) ;
        temp->next = head; //connect the rest
        return temp;
        //return new node(newkey, head);    //alternative to prev. 4 lines
    }

    // check node one ahead so we don't pass!
    while ( (ptr->next != NULL) && ((ptr->next->year < year) || ( (ptr->next->year == year) && ptr->next->month< month )))
    {
        ptr = ptr->next;
    } // postcondition: new node to be inserted just after the node that ptr points

    //now insert node with newkey after where ptr points to
    node * temp = new node;  //node to be inserted
    temp->month = month;
    temp->year =year ;
    temp ->cards.push_back(cardnumber) ;
    temp->next = ptr->next; //connect the rest
    ptr->next = temp;
    //ptr->next = new node(newkey,ptr->next);   //alternative to prev. 4 lines

    return head;
}

void DeleteOneNode (node * toBeDeleted, node * & head) // this func is taken from lecture materials and deletes a specific node from a list and reconnects the remaining nodes
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
    node * ptr;
        
    if (toBeDeleted == head)  //if the node to be deleted is the first node
    {
        head = head->next;
        delete toBeDeleted;
    }
    else  //if the node to be deleted is in the middle or at the end
    {
        ptr = head;
        while (ptr->next != toBeDeleted)
            ptr = ptr->next;
        //after while ptr point to the node just before toBeDeleted

        //connect the previous node to the next node and delete
        ptr->next = toBeDeleted->next;
        delete toBeDeleted;
    }
}



int main() {
  
    node *mylist ;
    node *head ;
    
    ifstream inputfile ;
    string input ;

    cout<< "Please enter filename: " ;
    cin>> input ;
    
    inputfile.open(input) ;
    
    while (inputfile.fail()) //check if file opens correctly
    {
        cout<< "Can not find a file named " << input << endl ;
        cout<< "Please enter filename: " ;
        cin>>input ;
        inputfile.open(input) ;
    }
    string creditcardnum ;
    int month ;
    int year ;
  
    head=  NULL ;
    while (getline(inputfile, input)){
        istringstream iss (input) ;
        iss>>creditcardnum>>month>>year ;

        if (head == NULL ) // creating the first node of linked list
        {
            mylist = new node ;
            mylist->cards.push_back(creditcardnum) ;
            mylist-> month=month ;
            mylist ->year=year;
            mylist->next =NULL ;
            cout<< "New node is created with expiration date: " << month << " "<<year << endl ;
            
            cout<<"Credit card " << creditcardnum<< " added to node "<< month<< " "<<  year << endl ;
            cout<< "***************" << endl ;
            head=mylist ;
        }
        else if (SearchList(head, month, year) == NULL ) // if node is unique add it
        {
            head= AddInOrder(head, year, month,creditcardnum) ;
            cout<< "New node is created with expiration date: " << month << " "<<year << endl ;
            cout<<"Credit card " << creditcardnum<< " added to node "<< month<< " "<<  year << endl ;
            cout<< "***************" << endl ;
            
            }
        else { //if a node with same exp date exists only add creditcardnum to vector
            cout<< "Node with expiration date "<<  month<< " "  << year <<  " already exists" << endl ;
            cout<<  "Credit card " << creditcardnum<<  " added to node "<<  month<<" " << year<< endl ;
            cout<< "***************" << endl ;
            node *ptr = SearchList(head, month, year) ;
            ptr->cards.push_back(creditcardnum) ;
            
        }
        
    }
  
    int input1 ;
    string inputcard ;
    string month1;
    string year1 ;

    input1 =0 ;
    while (input1 !=4 )
    {
        
        cout << "1)Display List" << endl ;
        cout<< "2)Card Search via Credit Number" << endl ;
        cout<< "3)Delete Card with respect to Expiration Date" << endl ;
        cout<< "4)Exit" << endl ;
        
        cout<< "Please choose option from the menu: " ;
        cin>> input1 ;
        
        if (input1 ==1 ){ //if input is 1 display the list
            if (head==NULL ){
                cout<< "List is empty!"<< endl ;
            }
            DisplayList(head ) ;
        }
        else if (input1== 2){ // if input is 2 ask for a cred card num and display its exp date
            cout<< "Please enter the credit card number: " ;
            cin>> inputcard ;
            while (creditcardnumcheck(inputcard) ==false )
            {
                cout<< "Invalid format!"<< endl ;
                cout<< "Please enter the credit card number: " ;
                cin>>inputcard ;
                }
            if  (creditcardnumcheck(inputcard)==true)
            {
                int a;
                int b ;
                if (cardloop(inputcard, head, a , b)==true )
                {
                   
                    cout<< "There exists a credit card given number "<< inputcard<< " with expiration date: "<< a<<" "<< b<<endl ;
                    
                }
                else {
                    cout<< " There is no credit card with given credit card number: "<< inputcard << endl ;
                }
            }
        }
        else  if (input1==4){ //if input is 4 terminate
                   cout<< "Terminating..."<< endl ;
//                   return 1;
               }
        
        else if  (input1==3) //if input is 3 ask for month and year and check validity and then delete the cards with that date
        {

            cout<< "Please enter month and year: " ;
            cin >>month1;
            cin>>year1 ;
            while (monthinputchecker(month1, year1) == false)
            {
                cout<< "Invalid Date!"<< endl ;
                cout<< "Please enter month and year: " ;
                cin>> month1 ;
                cin>>year1 ;
            }
           if (  monthinputchecker(month1, year1)==true )
            {
               int  monthint=atoi(month1.c_str()) ;
               int  yearint= atoi(year1.c_str()) ;
                
                if (SearchList(head, monthint, yearint) == NULL )
                {
                    cout<< "There is no node with expiration date "<< month1 << " "<< year1<<"," << "nothing deleted!" << endl ;
                                
                }
                else {
                                node *ptr1 = SearchList(head, monthint, yearint) ;
                                cout<< "Node with expiration date " << month1<< " "<< year1<< " and the following credit cards have been deleted!"<< endl ;
                                for (int i=0; i<ptr1->cards.size() ;i++)
                                {
                                    cout<< i+1 <<")" ;
                                    cout<< ptr1->cards[i] << endl ;
                                    cout<< endl ;
                                }
                                DeleteOneNode(ptr1, head) ;
                            }
            }
        }

        else   { //if user enters input other than the menu give error 
            cout<< "Invalid option enter again!" << endl;
            cout<< "Please enter again! " ;
        }
        
    }
   
    node * pointer1 ;
    pointer1=head ;
    
    while(pointer1->next !=NULL ){ //finally clean whole linked list delete all nodes
        pointer1= head->next ;
        delete head  ;
        head=pointer1 ;
    }
    head=NULL ;
    
    return 0;
}
