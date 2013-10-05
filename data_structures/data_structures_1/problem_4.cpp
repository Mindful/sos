#include <iostream>
using namespace std;
class IntCell
{
  public:
    explicit IntCell( int initialValue = 0 )
      { storedValue = new int( initialValue ); }

    int read( ) const
      { return *storedValue; }
    void write( int x )
      { *storedValue = x; }
  private:
    int *storedValue;
};

int main(){
	const int ARR_LENGTH = 5;
	//The question only mentions pointers to arrays, so the arrays are on the heap
	//but they hold actual IntCells and not IntCell pointers
	IntCell *arr = new IntCell[ARR_LENGTH];
	IntCell *arr2 = new IntCell[ARR_LENGTH];
	//Populate array
	for (int i = 0; i < ARR_LENGTH; i++){
		 arr[i] = IntCell(i); 
	}
	//Copy array into second array
	for (int i = 0; i < ARR_LENGTH; i++){
		arr2[i] = arr[i];
	}
	for (int i = 0; i < ARR_LENGTH; i++){
		//Here's the shallow copy problem: there may be different IntCells in each array,
		//but the copied IntCells point to the same int as their original, so when we change
		//one we change the value that both of them read.
		cout << "First Array [" << i << "]: " << arr[i].read();
		cout << " Second Array [" << i << "]: " << arr2[i].read() << endl;
		cout << "Adding 1 to slot " << i << " in First Array ONLY." << endl;
		arr[i].write(arr[i].read()+1);
		cout << "First Array [" << i << "]: " << arr[i].read();
		cout << " Second Array [" << i << "]: " << arr2[i].read() << endl;
		cout << "--------------------------------------" << endl;

	}

}