#include <iostream>
using namespace std;

//I don't see a way to do this in constant extra space, because when we write merged elements to their proper location,
//if we're using the same array, we risk overwriting a yet unmerged element and effectively duplicating the element we
//just merged

//The space and time analysis for this, as I've written it, are exactly the same as the normal mergesort (barring
//the stack frame space we lose to recursion)

void nrc_merge(int array[], int size){
	int is = 2; //Iteration size
	int curloc = 0;
	while (is<size*2){ //It should be equal to or slightly greater than size on last iteration
		cout << "Iteration Size: " << is << endl;
		for(; curloc<size; curloc+=is){

			int ms = is/2; //Merge size
			int lSize = (curloc+ms>=size) ? size - (curloc) : ms;
			int rSize = (curloc+lSize+ms>=size) ? size - (curloc+lSize) : ms;
			cout << "lSize " << lSize << " rSize " << rSize << endl;
			int lArray[lSize], rArray[rSize];

			cout << "Start copy" << endl;
			//Iterate over 
			//TODO: The only remaining problem here is that this loop is retarded
			//and assumes we're going to go the entire iteration without checking size
			for (int i = 0; i < lSize+rSize; i++){
				if(i<lSize){
					cout << "Copy " << array[curloc+i] << " to lArray at " << i << endl;
					lArray[i]=array[curloc+i];
				} else if (i-lSize < rSize){
					cout << "Copy " << array[curloc+i] << " to rArray at " << i-ms << endl;
					rArray[i-ms]=array[curloc+i];
				}
				else {
					break;
				}
			}


			int lCounter = 0, rCounter = 0, location = curloc;

			cout << "Start Merge" << endl;
			//Try and copy from both lists until one is empty
			while (lCounter < lSize && rCounter < rSize){
				if (lArray[lCounter] < rArray[rCounter]) {
				    array[location++] = lArray[lCounter++];
				    cout << "Write " << lArray[lCounter-1] << " from slot " << lCounter-1 << " in left array to ";
				    cout << location << endl;
				} 
				else {
				    array[location++] = rArray[rCounter++];
				    cout << "Write " << rArray[rCounter-1] << " from slot " << rCounter-1 << " in right array to ";
				    cout << location << endl;
				}

			}
			//Finish left list
			while (lCounter < lSize){
				array[location++] = lArray[lCounter++];
				    cout << "Write " << lArray[lCounter-1] << " from slot " << lCounter-1 << " in left array to ";
				    cout << location << endl;
			}
			//Finish right list
			while (rCounter < rSize){
				array[location++] = rArray[rCounter++];
				    cout << "Write " << rArray[rCounter-1] << " from slot " << rCounter-1 << " in right array to ";
				    cout << location << endl;
			}

		}
		//------
		//--------
		is*=2;
		curloc = 0;
		for (int i = 0; i < size; i++){
			cout << array[i] << ", ";
		}
		cout << endl << endl;
	}
}



int main(){
	int arr1[] = {5,3,9,8,26,4,1,20,15,10};
	int size = 10;
	for (int i = 0; i < size; i++){
		cout << arr1[i] << ", ";
	}
	cout << endl <<  "Run sort" << endl << endl;
	nrc_merge(arr1, size);
	for (int i = 0; i < size; i++){
		cout << arr1[i] << ", ";
	}
	cout << endl;

}