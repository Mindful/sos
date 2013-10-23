#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

//this uses c++11 libraries, so it must be compiled like:
//g++ ex_7.cpp -std=c++11


int i,j,k,n;
long sum=0;
chrono::time_point<std::chrono::system_clock> start, end;
std::chrono::duration<double> elapsed_seconds;

void reset(){
	i=j=k=0;
	sum=0;
	start = std::chrono::system_clock::now();

}

int main(){
	cin >> n;
	//#1
	reset();
	for(i = 0; i < n; i++){
		sum++;
	}
	elapsed_seconds = std::chrono::system_clock::now() - start;
	cout << elapsed_seconds.count() << endl;

	//#2
	reset();
	for (i = 0; i < n; i++){
		for(j = 0; j< n; j++){
			sum++;
		}
	}
	elapsed_seconds = std::chrono::system_clock::now() - start;
	cout << elapsed_seconds.count() << endl;

	//#3
	reset();
	for (i = 0; i < n; i++){
		for(j = 0; j < n*n; j++){
			sum++;
		}
	}
	elapsed_seconds = std::chrono::system_clock::now() - start;
	cout << elapsed_seconds.count() << endl;

	//#4
	reset();
	for ( i = 0; i < n; i++){
		for(j = 0; j < i; j++){
			sum++;
		}
	}
	elapsed_seconds = std::chrono::system_clock::now() - start;
	cout << elapsed_seconds.count() << endl;

	//#5
	reset();
	for (i = 0; i < n; i++){
		for (j = 0; j < i * i; j++){
			for (k = 0; k < j; k++){
				sum++;
				//cout << "5: " << sum << endl;
			}
		}
	}
	elapsed_seconds = std::chrono::system_clock::now() - start;
	cout << elapsed_seconds.count() << endl;

	//#6
	reset();
	for (i = 1; i < n; i++){
		for (j = 1; j < i* i; j++){
			if (j%i==0){
				for (k = 0; k < j; k++){
					sum++;
					//cout << "6: " << sum << endl;
				}
			}
		}
	}
	elapsed_seconds = std::chrono::system_clock::now() - start;
	cout << elapsed_seconds.count() << endl;
	return 0;

}