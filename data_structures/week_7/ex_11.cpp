#include "set.cpp"
#include <iostream>
using namespace std;

//TODO: clone needs to be updated to handle the presence of parent nodes




int main(){
	 Set<int> s;
	 s.insert(1);
	 s.insert(5);
	 s.insert(10);
	 s.insert(4);
	 s.insert(6);
	 for (Set<int>::const_iterator i = s.begin(); i != s.end(); i++){
	 	cout << *i << endl;
	 }
	 Set<int>::const_iterator i = s.find(6);
	 cout << "6: " << *i << endl;
	return 0;
}