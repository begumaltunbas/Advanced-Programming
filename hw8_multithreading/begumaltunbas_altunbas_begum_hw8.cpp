
#include <iostream>
#include "HW8DynIntQueue.h"
#include <random>
#include <time.h>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

 
int random_range(const int & min, const int & max) 
{
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}


int total_customer_count ;
int cashier2_threshold;
int min_arrival, max_arrival ;
int min_checkout_time, max_checkout_time;
HW8DynIntQueue myQueue;
int size=0;
int counter=0;
mutex myMutex, coutMutex,mutex1;


void customer ()
{
	//this is a customer func creates customers according to size and certain random time interval puts them in a queue.Code similarly taken from rec12 producer consumer cpp but modified
	for(int i = 1; i <= total_customer_count; i++)
	{
		int random =random_range(min_arrival,max_arrival);
		myMutex.lock();
		if (size<total_customer_count) 
		{  
			myQueue.enqueue(i);
			//size++;
			myMutex.unlock();
			coutMutex.lock();
			
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			size++;
			cout <<"New customer with ID "<< i << " has arrived  ";
			cout<< "(queue size is "<<size  <<") :" ;
			cout<< put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
			this_thread::sleep_for(chrono::seconds(random)) ;
		}
		else
		{
			myMutex.unlock();
			i--;
		}
	}
}



void cashier (int id)
{
    //this function is for both cashier 1 and 2, 2 works only size reaches and exceeds threshold, cashiers dequeue customers according to random checkout time.Code similarly taken from rec12 producer cosnumer.cpp but modified according to cashier 
	int random =random_range(min_checkout_time,max_checkout_time);
	this_thread::sleep_for(chrono::seconds(random));
	
	
	//mutex1.lock();
	if (id==1)
	{
		int item;
		while(counter < total_customer_count)
		{	
		//	int random2 =random_range(min_checkout_time,max_checkout_time);
			myMutex.lock();
			if (!myQueue.isEmpty()) 
			{  
				myQueue.dequeue(item);
			//size--;
				counter++;
				myMutex.unlock();
			//mutex1.unlock();
				coutMutex.lock();
				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				size--;
				cout <<"Cashier "<< id <<" started transaction with customer "<< item <<" (queue size is "<<size<<")" << put_time(ptm,"%X") <<endl;
				coutMutex.unlock();
			
				this_thread::sleep_for(chrono::seconds(random)); // simulation for consume

				coutMutex.lock();
				tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				cout<< "Cashier "<<id <<" finished transaction with customer "<< item <<" at " << put_time(ptm,"%X") <<endl;
				coutMutex.unlock();
			}
		else
		{
			myMutex.unlock();
		//	mutex1.unlock();
		}
		//mutex1.unlock();
            
        }
		//mutex1.unlock();
	}
	else 
	{
		int item;
		while(counter < total_customer_count)
		{	
		
			myMutex.lock();
			if (!myQueue.isEmpty() && myQueue.getCurrentSize()>=cashier2_threshold) 
			{  
				myQueue.dequeue(item);
			//size--;
				counter++;
				myMutex.unlock();
			//mutex1.unlock();
				coutMutex.lock();
				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				size--;
				cout <<"Cashier "<< id <<" started transaction with customer "<< item <<" (queue size is "<<size<<")" << put_time(ptm,"%X") <<endl;
				coutMutex.unlock();
			
				this_thread::sleep_for(chrono::seconds(random)); // simulation for consume

				coutMutex.lock();
				tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				cout<< "Cashier "<<id <<" finished transaction with customer "<< item <<" at " << put_time(ptm,"%X") <<endl;
				coutMutex.unlock();
			}
			else
			{
				myMutex.unlock();
			}
		}
	}
}


int main ()
{
	//taking inputs
	cout<<"Please enter the total number of customers: " ;
	cin >> total_customer_count  ;
	cout<< "Please enter the number of customers waiting in the queue to open the second cashier: " ;
	cin>> cashier2_threshold;
	cout << "Please enter the inter-arrival time range between two customers: " << endl;
	cout<< "Min: ";
	cin >> min_arrival ;
	cout<< "Max: ";
	cin >> max_arrival ; 
	cout << "Please enter the checkout time range of cashiers: " << endl ;
	cout<< "Min: " ;
	cin>> min_checkout_time ;
	cout<< "Max: " ;
	cin >>max_checkout_time ;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	cout<< "Simulation starts " <<put_time(ptm,"%X") <<endl;


    //creating and then joining threads
	thread thr0(customer);
	thread thr1(cashier, 1);
	thread thr2(cashier,2);
	

	thr0.join() ;
	thr1.join();
	thr2.join();
	

	time_t t1 = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptr = new struct tm; 
	localtime_s(ptr, &t1); 

	cout<< "End of the simulation ends: "<< put_time(ptr,"%X") <<endl;
	

return 0 ;
}
