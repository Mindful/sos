//a. Write some code:

#include <iostream>
#include <list>
#include <unordered_map> //C++ 11's hashtable, basically
using namespace std;

class polyNode
{
public:
    int coefficient;
    int exponent;


    polyNode( int c = 0, int e = 0 )
      : coefficient(c),exponent(e) { }

     bool operator< (const polyNode &rhs) const{
     	return this->exponent < rhs.exponent;
     }
};

list<polyNode> multiply(list<polyNode> p1, list<polyNode> p2){
	unordered_map<int, polyNode> hashtable;
	for (list<polyNode>::const_iterator i=p1.begin(); i != p1.end(); ++i){
		for (list<polyNode>::const_iterator j=p2.begin(); j != p2.end(); ++j){
			polyNode result = polyNode(i->coefficient * j->coefficient, i->exponent + j->exponent);
			if (!hashtable.count(result.exponent)){ 
				//There is no entry for this exponent, so we start with what we have
				hashtable[result.exponent] = result;
			} else {
				//There is already an entry for this exponent, so we add the coefficients
				hashtable[result.exponent].coefficient += result.coefficient;
			}
		}
	}
	list<polyNode> result;
	for (unordered_map<int, polyNode>::const_iterator i = hashtable.begin(); i != hashtable.end(); ++i){
		result.push_front(i->second);
	}
	result.sort();
	return result;

}

int main(){
	return 0;
}


//B.

// Okay, so the version that I wrote has some extra overhead in copying the unordered_map into a list so I can sort it. 
// If this were production level code we could use an array-based hash table and have it sort itself as an array once
// we were done using keys to reference it. If we did that, then this "alternative" method has a running time of
// multiplication + hashing on each element (2MN) plus the sort runtime which I assume to be Nlog(N) for a total of
// 2MN + (M+N)log(M+N) since the final polynomial has "about M+N terms"

// The non alternative method, where we multiply and then sort MN records is 2MN + MN*Log(MN), which is much worse.

