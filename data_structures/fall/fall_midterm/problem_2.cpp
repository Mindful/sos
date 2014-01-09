#include "list.h"
#include <string>
//Using the textbook's list

template <typename Object>
class Stack{
private:
	List<Object>* l;
public:
	Stack( )
      { l = new List<Object>(); }
    
    ~Stack( )
    {
    	delete l;
    }
    
    Stack( const Stack & rhs )
    {
        *this = rhs;
    }

    const Stack & operator= ( const Stack & rhs )
    {
        if( this == &rhs ) return *this;
        l = rhs.l; //Copy the internal list from the other Stack
        return *this;
    }

    Object top(){
    	return *(l->begin());
    }

    Object pop(){
    	Object temp = top();
    	l->erase(l->begin());
    	return temp;
    }

    void push(Object val){
    	l->insert(l->begin(), val);
    }

    bool isEmpty(){
    	return l->size()==0;
    }

};


//Here is the paren parser
int main(){
	string expression;
	getline(cin, expression);
	Stack<char> s;
	for (int i = 0; i < expression.length(); i++){
		if(expression[i]=='(') s.push(expression[i]);
		else if(expression[i]=')'){
			if(s.isEmpty()){
				cout << "Bad input: right paren without corresponding left paren" << endl;
			}
			else{
				s.pop();
			}
		}
	}
	//Now we've gone through the whole string, each paren should have found its partner
	if (!s.isEmpty()){
		cout << "Bad input: left paren without corresponding right paren" << endl;
	}
}