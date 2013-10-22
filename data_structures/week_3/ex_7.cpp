#include <iostream>
using namespace std;

int i,j,k,n,sum;

void reset(){
	i=j=k=sum=0;
	n=1000;
}

int main(){
	//#1
	int reset();
	for(i = 0; i < n; i++){
		sum++;
	}

	//#2
	reset();
	for (i = 0; i < n; i++){
		for(j = 0; j< n; j++){
			sum++;
		}
	}

	//#3
	reset();
	for (i = 0; i < n; i++){
		for(j = 0; j < n*n; j++){
			sum++;
		}
	}

	//#4
	reset();
	for ( i = 0; i < n; i++){
		for(j = 0; j < i; j++){
			sum++;
		}
	}

	//#5
	reset();
	for (i = 0; i < n; i++){
		for (j = 0; j < i * i; j++){
			for (k = 0; k < j; k++){
				sum++;
			}
		}
	}

	//#6
	reset();
	for (i = 1; i < n; i ++){
		for (j = 1; i < i* i; j++){
			if (j%i==0){
				for (k = 0; k < j; k++){
					sum++;
				}
			}
		}
	}

}