//The problem didn't specify and this is a pretty substantial thing to do in any case, so this only supports binary operators

#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isInteger(char c){
	if (c >= 48 && c <= 57) return true; //It's an integer
	else return false;
}

bool isOperator(char c){
	if (c==42 || c==43 || c==45 || c==47) return true; //It's a binary operator we recognize
	else return false;
}

int grab(stack<char>&s){
	int i = s.top();
	s.pop();
	return i;
}

int evaluate(stack<char>& s, char c){
	switch (c){
		case '+':
			return grab(s)+grab(s);
		case '-':
			return grab(s)-grab(s);
		case '*':
			return grab(s)*grab(s);
		case '/':
			return grab(s)/grab(s);
		default:
			break;
	}



}


//interpretation has to be a recursive call, in case one of your grab(s) is operator
int main(){
	string expression;
	getline(cin, expression);
	stack<char> s;
	for (int i = 0; i < expression.size(); i++){
		if(isInteger(expression[i])){
			s.push(expression[i]-'0');
			cout << expression[i]-'0' << " found" << endl;
		}
		else if (isOperator(expression[i])){
			int j = evaluate(s,expression[i]);
			cout << j << " evaluated" << endl;
			s.push(j);
		}
	}


}
