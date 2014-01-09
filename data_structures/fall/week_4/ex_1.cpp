#include <iostream>
#include <list>
using namespace std;

//This has a runtime of O(N), dependent on the length of the list "l"
//It would be very different if we weren't gauranteed that integers in "p"
//were in ascending order, though


void printLots(list<int> l, list<int> p){
	int counter = 0; //the first element is postion 0
	list<int>::iterator num = p.begin();
	for(list<int>::iterator it=l.begin(); it != l.end(); ++it){
		if (counter==*num){
			num++;
			cout << *it << endl;
		}
		++counter;
	}
	
}

int main(){
	list<int> l,p;
	//This just gives us a list counting by 2 from 0 to 30
	for (int i = 0; i <= 30; i+=2){
		l.push_back(i);
	}
	p.push_back(1);
	p.push_back(3);
	p.push_back(4);
	p.push_back(7);
	p.push_back(13);
	printLots(l,p);
}
