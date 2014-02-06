#include <iostream>
using namespace std;

//Disclaimer: I did not write this recursive mergesort code, some helpful person on stack overflow did
//I just wanted something I could look at to remind me how mergesort worked

int  merge  (int list1[ ] , int size1 , int list2[ ] , int size2 , int list3[ ], int size3)
{
    int i1, i2, i3;
    if (size1+size2 > size3) {
        return false;
    }
    i1 = 0; i2 = 0; i3 = 0;
    /* while both lists are non-empty */
    while (i1 < size1 && i2 < size2) {
        if (list1[i1] < list2[i2]) {
            list3[i3++] = list1[i1++];
        } 
        else {
            list3[i3++] = list2[i2++];
        }
    }
    while (i1 < size1) {   
        /* copy remainder of list1 */
        list3[i3++] = list1[i1++];
    }
    while (i2 < size2) { 
        /* copy remainder of list2 */
        list3[i3++] = list2[i2++];
    }
    return true;
}

void merge_sort (int array[], int size)
{
    int temp[size];
    int mid, i;
    if (size < 2) {
        return;
    } 
    else {
        mid = size / 2;
        merge_sort(array, mid);
        merge_sort(array + mid, size - mid);
        merge (array, mid, array + mid, size - mid, temp, size);
        for (i = 0; i < size; i++) {
            array[i] = temp[i];
        }
    }
}

//I don't see a way to do this in constant extra space, because when we write merged elements to their proper location,
//if we're using the same array, we risk overwriting a yet unmerged element and effectively duplicating the element we
//just merged

void nrc_merge(int array[], int size){
	int is = 2; //Iteration size
	int curloc = 0;
	while (is<size*2){ //It should be equal to or slightly greater than size on last iteration
		cout << "Iteration Size: " << is << endl;
		for(; curloc<size; curloc+=is){

			int ms = is/2; //Merge size
			int lSize = ms;
			int rSize = (curloc+ms>=size) ? size - curloc : ms;
			int lArray[lSize], rArray[rSize];

			//Iterate over 
			for (int i = 0; i < is; i++){
				if(i<ms){
					cout << "Copy " << array[curloc+i] << " to lArray at " << i << endl;
					lArray[i]=array[curloc+i];
				} else{
					cout << "Copy " << array[curloc+i] << " to rArray at " << i-ms << endl;
					rArray[i-ms]=array[curloc+i];
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