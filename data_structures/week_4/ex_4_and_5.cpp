#include <iostream>  
#include <list>
using namespace std;



//I couldn't figure out a better way to do this than O(N*L) where N and L are the sizes of the lists
//The other option is combining the lists and then removing duplicates (or non-duplicates, for intersection),
//but that just ends up being (N+L)^2, which is equivalent as far as big O is concerned

//Basically, for each element in rhs, we check if it exists in lhs and if not we add it to the result list
//(which is intially a copy of lhs)
list<int> setUnion(const list<int> &lhs, const list<int> &rhs){
	list<int> result = lhs; //Copy lhs, then we're just adding anything new from rhs
	for(list<int>::const_iterator i=rhs.begin(); i != rhs.end(); ++i){
		bool isNew = true;
		for(list<int>::const_iterator k=lhs.begin(); k != lhs.end(); ++k){
			if (*i == *k) isNew = false;
		}
		if (isNew) result.push_back(*i);
	}
	return result;
}

//Basically, for each element in rhs, we check if it exists in lhs and if so we add it to the result list
list<int> setIntersection(const list<int> &lhs, const list<int> &rhs){
	list<int> result; //new empty list
	for(list<int>::const_iterator i=rhs.begin(); i != rhs.end(); ++i){
		bool duplicated = false;
		for(list<int>::const_iterator k=lhs.begin(); k != lhs.end(); ++k){
			if (*i == *k) duplicated = true;
		}
		if (duplicated) result.push_back(*i);
	}
	return result;
}

int main(){
	list<int> fours, threes;
	for (int i = 0; i <= 36; i++){
		if (i%4==0) fours.push_back(i);
		if (i%3==0) threes.push_back(i);
	}
	cout << "fours" << endl;
	for(list<int>::iterator i = fours.begin(); i != fours.end(); ++i){
		cout << *i << endl;
	}
	cout << "threes" << endl;
	for(list<int>::iterator i = threes.begin(); i != threes.end(); ++i){
		cout << *i << endl;
	}
	list<int> result = setIntersection(fours, threes);
	cout << "fours intersect threes" << endl;
	for(list<int>::iterator i = result.begin(); i != result.end(); ++i){
		cout << *i << endl;
	}

	result = setUnion(fours, threes);
	cout << "fours union threes" << endl;
	for(list<int>::iterator i = result.begin(); i != result.end(); ++i){
		cout << *i << endl;
	}
}