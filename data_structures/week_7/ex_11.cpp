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
	 Set<int>::const_iterator itr = s.begin();
	 for (int i = 0; i < 5; i++){
	 	cout << *itr << endl;
	 	itr++;
	 }
	return 0;
}