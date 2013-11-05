//The problem didn't specify and this is a pretty substantial thing to do in any case, so this only supports binary operators

#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main(){
	string expression;
	getline(cin, expression);
	for (int i = 0; i < expression.size(); i++){
		//if it's an operation we recognize or a number
		//put it on the stack.
		//otherise, skip it
	}
}