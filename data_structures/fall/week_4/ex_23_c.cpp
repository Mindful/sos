//The problem didn't specify and this is a pretty substantial thing to do in any case, so this only supports binary operators
//Also, everything should be separated by _exactly one space_ for this to work properly

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

// Colin Robinson Helped :)

bool isInteger(char c){
	if (c >= 48 && c <= 57) return true; //It's an integer
	else return false;
}

bool isOperator(char c){
	if (c==42 || c==43 || c==45 || c==47 || c=='^') return true; //It's a binary operator we recognize
	else return false;
}

string grab(stack<string>&s){
	string i = s.top();
	s.pop();
	return i;
}

string evaluate(stack<string>& s, char c){
	string first = grab(s);
	string second = grab(s);
	switch (c){
		case '+':
			return " ( " + second + " + " + first + " ) ";
		case '-':
			return " ( " + second + " - " + first + " ) ";
		case '*':
			return " ( " + second + " * " + first + " ) ";
		case '/':
			return " ( " + second + " / " + first + " ) ";
		case '^':
		    return " ( " + second + " ^ " + first + " ) ";
		default:
			break;
	}



}


//TODO: this only works for single digit integers; update it to use spaces as a separator
int main(){
	string expression;
	cout << "Please enter one line of operands and operators, each separated by exactly one space" << endl;
	getline(cin, expression);
	stack<string> s;
	for (int i = 0; i < expression.size(); i++){
		if (isOperator(expression[i])){
			string j = evaluate(s,expression[i]);
			cout << j << " evaluated" << endl;
			s.push(j);
		} 
		else if(isInteger(expression[i])){ //This case should read characters until it hits a space
			int space = expression.find(' ', i);
			if (space==string::npos) space=expression.size();
			string buffer = expression.substr(i, space-i);
			i = space;
			cout << buffer << endl;
			s.push(buffer);
		}
	}


}