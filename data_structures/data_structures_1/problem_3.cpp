#include "IntCell.h"
#include "IntCell.cpp"
using namespace std;

int main(){
	const int ARR_LENGTH = 5;
	//The question only mentions pointers to arrays, so the arrays are on the heap
	//but they hold actual IntCells and not IntCell ptrs
	IntCell *arr = new IntCell[ARR_LENGTH];
	IntCell *arr2 = new IntCell[ARR_LENGTH];
	//Populate array
	for (int i = 0; i < ARR_LENGTH; i++){
		 arr[i] = IntCell(i); 
	}
	//Copy array into second array
	for (int = 0; i < ARR_LENGTH; i++){
		arr2[i] = arr[i];
	}

}