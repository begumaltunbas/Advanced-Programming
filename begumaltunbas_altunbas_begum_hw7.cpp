#include <iostream>
#include <string>

using namespace std;


unsigned char Permutation (unsigned char &a)
{
	unsigned char result=NULL ;
	
	unsigned char zero= a & 1;
	result=result | (zero<<2) ;
	unsigned char one= a&2;
	result=result | (one>>1) ;
	unsigned char two= a &4;
	result=result | (two<<1) ;
	unsigned char three= a&8;
	result=result| (three>>2) ;
	unsigned char four= a&16;
	result=result| (four<<2) ;
	unsigned char five= a&32;
	result=result | (five>>1) ;
	unsigned char six= a& 64;
	result=result | (six<<1) ;
	unsigned char seven = a&128;
	result=result| (seven>>2) ;

	return result;
}



int main()
{
	string key,text;
	cout<<" *** Welcome to the Simple Data Encryption Application ***"<< endl ;
	cout<<"Please enter the encryption key: " ;
	getline (cin,key) ;
	cout <<"Please enter the plaintext to be encrypted:" ;
	
	
	
	while (getline(cin,text))
	{
		string longkey ;
		int count=0 ;
		int times = text.length()/key.length() ;
		int mod= text.length() % key.length() ;
	
		unsigned char a;
		for (int i=0 ; i< text.length();i++)
		{
			a=text[i] ;
			text[i]=Permutation(a) ;
		
		}

		if (key.length() < text.length())
		{
			
			while (count!= times)
			{
				longkey += key ;
				count++;
			}
			if (mod!=0)
			{
				for (int k=0; k<key.substr(0,mod).length() ;k++)
				{
					longkey+=key[k]; 
				}
			}
			else 
			{
				longkey=longkey;
			}
		
		}
		else 
		{
			for (int y=0 ;y <text.length();y++)
			{
					longkey+=key[y] ;
			}
		}
		cout<< "Ciphertext: ";
		for (int i=0; i< text.length();i++)
		{
			
			unsigned char x= text[i]^longkey[i];
			
			cout<< hex << (int) x ;
		}
		cout<< endl ;
		cout <<"Please enter the plaintext to be encrypted:" ;
	}

	
return 0;
}