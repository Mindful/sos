//These all run in O(N). We're very proud.

//Addition and multiplication function identically for these purposes, 
//and can be handled in one function

//It's just the max by definition, there's nothing bigger than the largest int plus or multiplied by itself
#include <iostream>

int multiplicationMax(int arr[], int size){
	int max = arr[0];
	for (int i = 0; i < size; i++){
		if (arr[i] > max){
			max = arr[i];
		}
	}
	return max*max;
}

int additionMax(int arr[], int size){
	int max = arr[0];
	for (int i = 0; i < size; i++){
		if (arr[i] > max){
			max = arr[i];
		}
	}
	return max+max;
}



//Addition and multiplication function identitally for these purposes,
//and can be handled in one function

//We keep running maxes and mins to find the largest value minus the smallest value before it
int decreasingMax(int arr[], int size){
	int min, best, temp;
	best = 0; //Because the worst value we can never be less than a number minus itself
	min = arr[0];
	for (int i = 0; i < size; i++){
		if (arr[i] < min){ 
			min = arr[i];
		} 
		temp = arr[i] - min;
		if (temp > best){
			best = temp;
		}
	}
	return best;
}

int dividingMax(int arr[], int size){
	int min, best, temp;
	best = 0; //Because the worst value we can never be less than a number minus itself
	min = arr[0];
	for (int i = 0; i < size; i++){
		if (arr[i] < min){ 
			min = arr[i];
		} 
		temp = arr[i] / min;
		if (temp > best){
			best = temp;
		}
	}
	return best;
}

using namespace std;

int main(){
    int a[] = {100,70,60,2};
    cout << a << " subtracting max, " << decreasingMax(a, 4) << endl;
    return 0;
}