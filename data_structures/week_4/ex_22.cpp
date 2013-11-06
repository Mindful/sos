//The problem didn't specify and this is a pretty substantial thing to do in any case, so this only supports binary operators

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
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


//TODO: this only works for single digit integers; update it to use spaces as a separator
int main(){
	string expression;
	getline(cin, expression);
	stack<char> s;
	for (int i = 0; i < expression.size(); i++){
		if (isOperator(expression[i])){
			int j = evaluate(s,expression[i]);
			cout << j << " evaluated" << endl;
			s.push(j);
		} 
		else if(isInteger(expression[i])){ //This case should read characters until it hits a space
			int space = expression.find(' ', i);
			if (space==string::npos) space=expression.size()-1;
			string buffer = expression.substr(i, space-i);
			i = space;
			int val;
			stringstream stream(buffer);
			stream >> val;
			cout << val << endl;
			s.push(val);
		}
	}


}
