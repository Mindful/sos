#include "set.cpp"
#include <iostream>
using namespace std;


int main(){
	 Set<int> s;
	 s.insert(1);
	 s.insert(5);
	 s.insert(10);
	 s.insert(4);
	 s.insert(6);
	 for (Set<int>::iterator i = s.begin(); i != s.end(); i++){
	 	cout << *i << endl;
	 }
	 Set<int>::iterator i = s.find(6);
	 cout << "find 6: " << *i << endl;
	 s.erase(4);
	 	 cout << "del 4" << endl;
	 for (Set<int>::iterator i = s.begin(); i != s.end(); i++){
	 	cout << *i << endl;
	 }
	 i = s.erase(i);
	 cout << "del 6 and now at " << *i << endl;
	 for (Set<int>::iterator i = s.begin(); i != s.end(); i++){
	 	cout << *i << endl;
	 }
	 for (int i = 0; i < 7; ++i){
	 	s.insert(i);
	 }
	 for (Set<int>::iterator i = s.begin(); i != s.end(); i++){
	 	cout << *i << endl;
	 }
	 cout << "delete from 2-4" << endl;
	 s.erase(s.find(2), s.find(5));
	 for (Set<int>::iterator i = s.begin(); i != s.end(); i++){
	 	cout << *i << endl;
	 }
	return 0;
}