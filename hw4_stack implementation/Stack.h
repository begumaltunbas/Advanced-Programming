

#include <string> 
using namespace std ;

struct StackNode
{
	int row;
	int col ;
	StackNode *next;
};

class DynIntStack
{
private:
	StackNode *top;

public:
	DynIntStack();
	void push(int row ,int col);
	void pop(int &row , int &col);
	bool isEmpty();
    ~DynIntStack();
};
