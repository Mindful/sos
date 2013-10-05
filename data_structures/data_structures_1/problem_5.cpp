#include <iostream>
using namespace std;
class IntCell
{
  public:
    explicit IntCell( int initialValue = 0 );

    IntCell( const IntCell & rhs );
    ~IntCell( );
    const IntCell & operator=( const IntCell & rhs );

    int read( ) const;
    void write( int x );
  private:
    int *storedValue;
};

IntCell::IntCell( int initialValue )
{
    storedValue = new int( initialValue );
}

IntCell::IntCell( const IntCell & rhs )
{
    storedValue = new int( *rhs.storedValue );
}

IntCell::~IntCell( )
{
    delete storedValue;
}

const IntCell & IntCell::operator=( const IntCell & rhs )
{
    if( this != &rhs )
        *storedValue = *rhs.storedValue;
    return *this;
}

int IntCell::read( ) const
{
    return *storedValue;
}

void IntCell::write( int x )
{
    *storedValue = x;
}

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
        //It works fine here (as in, the values stay separate) because this implementation
        //of IntCell includes implements a deep copy, so the value is copied instead of the
        //pointer
        cout << "First Array [" << i << "]: " << arr[i].read();
        cout << " Second Array [" << i << "]: " << arr2[i].read() << endl;
        cout << "Adding 1 to slot " << i << " in First Array ONLY." << endl;
        arr[i].write(arr[i].read()+1);
        cout << "First Array [" << i << "]: " << arr[i].read();
        cout << " Second Array [" << i << "]: " << arr2[i].read() << endl;
        cout << "--------------------------------------" << endl;

    }

}