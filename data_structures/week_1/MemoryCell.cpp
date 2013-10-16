//perator<< using a member print function - what?
/**
 * A class for simulating a memory cell.
 */

#include <iostream>
using namespace std;
template <typename T>
class MemoryCell
{
  public:
    explicit MemoryCell( const T & initialValue = T( ) )
      : storedValue( initialValue ) { }
    const T & read( ) const
      { return storedValue; }
    void write( const T & x )
      { storedValue = x; }
    bool operator==(const MemoryCell<T>& rhs){
     	return storedValue == rhs.storedValue;
     }
    bool operator<=(const MemoryCell<T>& rhs){
      return storedValue <= rhs.storedValue;
     }
    bool operator<(const MemoryCell<T>& rhs){
      return storedValue <rhs.storedValue;
     }
    bool operator!=(const MemoryCell<T>& rhs){
      return storedValue != rhs.storedValue;
     }
    //This is my << operator as a friend function. It works, it's just commented out so I can have it in
    //the same file as the other << operator definition.
    // friend std::ostream& operator<< (std::ostream& stream, const MemoryCell<T>& rhs){
    //   stream << rhs.storedValue;
    // }
  private:
    T storedValue;
};

    //This is my "operator using a member print function". I could have written a specific member function
    //to print, but it would just have done the same thing that read() does.
    template <typename T>
    std::ostream& operator<< (std::ostream& stream, const MemoryCell<T>& rhs){
      stream << rhs.read();
    }

int main(){
  MemoryCell<int> arr[5];
  cout << "Runing tests on an array like: ";
  for (int i = 0; i < 5; i++){
    MemoryCell<int> temp = MemoryCell<int>(i);
    cout << "[" << temp.read() << "] ";
    arr[i] = temp;
  }
  cout << endl;
  bool tests[4];
  tests[0] = arr[1] < arr[2];
  tests[1] = arr[1] <= arr[2] && arr[2] <= MemoryCell<int>(2);
  tests[2] = arr[4] == MemoryCell<int>(4);
  tests[3] = arr[0] != arr[1];
  bool failed = false;
  for (int i = 0; i < 4; i++){
    if (tests[i] == false){
      failed = true;
      cout << "Test " << i << "failed!" << endl;
    }
  }
  if (!failed){
    cout << "All tests passed." << endl;
  }
}