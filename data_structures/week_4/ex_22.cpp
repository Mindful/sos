//The problem didn't specify and this is a pretty substantial thing to do in any case, so this only supports binary operators

#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isInteger(char c){
	if (c >= 48 || c <= 57) return true; //It's an integer
	else return false;
}

bool isBinaryOperator(char c){
	if (c==42 || c==43 || c==45 || c==47) return true; //It's a binary operator we recognize
	else return false;
}

bool validOperation(char c){
	return isInteger(c) || isBinaryOperator(c);
}


//this is working backwards right now; It should run from the bottom of the stack
int evaluate(stack<char>& s){
	int operands[2];
	char c;
	for(int i = 0; i < 2; i++){
		c=s.top();
		s.pop();
		if (isInteger(c)) {
			cout << "found " << c-'0' << endl;
			operands[i]=c-'0'; //The value as an integer
		}
		else operands[i]=evaluate(s);
	}
	//The next thing we pop has to be a binary operator
	c=s.top();
	s.pop();
	switch (c){
		case '+':
			return operands[0]+operands[1];
		case '-':
			return operands[0]-operands[1];
		case '*':
			return operands[0]*operands[1];
		case '/':
			return operands[0]/operands[1];
		default:
			break;
	}


}


//interpretation has to be a recursive call, in case one of your operands is operator
int main(){
	string expression;
	getline(cin, expression);
	stack<char> s;
	for (int i = 0; i < expression.size(); i++){
		if (validOperation(expression[i])) s.push(expression[i]);
		//if it's an operation we recognize or a number
		//put it on the stack.
		//otherise, skip it
	}
	//we can't just print this, we have to put it back on the stack and keep running it until the stack is empty
	cout << evaluate(s) << endl;


}
