#include <iostream>
#include <string>
#include <stack>
#include <sstream>
using namespace std;

// Vrite a program to convert an infix expression that includes (, ), +, -, *, and /
// to postfix.

bool isInteger(char c){
	if (c >= 48 && c <= 57) return true; //It's an integer
	else return false;
}

bool isOperator(char c){
	if (c==42 || c==43 || c==45 || c==47) return true; //It's a binary operator we recognize
	else return false;
}

int precedence(char c){
	switch(c){
		case '(':
			return 100;
		case '*':
			return 10;
		case '/':
			return 9;
		case '+':
			return 8;
		case '-':
			return 7;
		default: //It's an integer
			return -1;
	}
}

void clean(stack<char>& s, string& result){
	while (s.size()>0 && s.top()!=')'){
		result+=s.top();
		s.pop();
	}
}

int main(){
	string result = "", expression;
	getline(cin, expression);
	stack<char> s;
	for (int i = 0; i < expression.size(); i++){
		if (isOperator(expression[i])){
			cout << "operator" << endl;
			if (s.size()==0 || precedence(s.top()) < precedence(expression[i])){
				cout << "case1" << endl;
				s.push(expression[i]);
			}
			else{
				while (precedence(s.top()) >= expression[i]){
					char temp = s.top();
					s.pop();
					result+= temp;
				}
				s.push(expression[i]);
			}
		}
		else if (expression[i]=='('){
			//it's a parenthesis, make stack related decisions
		}
		else if(isInteger(expression[i])){ //This case should read characters until it hits a space
			int space = expression.find(' ', i);
			if (space==string::npos) space=expression.size();
			string buffer = expression.substr(i, space-i);
			i = space;
			int val;
			stringstream stream(buffer);
			stream >> val;
			cout << val << endl;
			result+=val;
		}
		else {
			//invalid input
			//ignore it
		}
	}
	clean(s, result);
	cout << result << endl;

}
