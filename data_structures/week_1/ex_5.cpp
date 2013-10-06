#include <iostream>
using namespace std;

int compute(int val, int total = 0){
	if (val % 2 == 1){
		total++;
	}
	val /= 2;
	if (val!= 1){
		return compute(val, total);
	}
	return total+1;
}

void test(int val){
	cout << val << " has " << compute(val) << " 1s" <<endl;
}
int main(){
	test(4);
	test(5);
	test(6);
	test(10);
	test(31);
	test(32);
	test(33);
}