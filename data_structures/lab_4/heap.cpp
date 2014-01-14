#include <vector>
#include <iostream>
#include <exception>

using namespace std;


struct UnderflowException : public exception {
        const char *what() const throw () {
                return "Empty Heap";
        }
};

template <typename Comparable>
class BinaryHeap
{
  public:
    explicit BinaryHeap( int capacity = 100 ) : array(capacity), currentSize(capacity){
    }
    explicit BinaryHeap( const vector<Comparable> & items )
      : array( items.size( ) + 10 ), currentSize( items.size( ) )
    {
        for( int i = 0; i < items.size( ); i++ )
            array[ i + 1 ] = items[ i ];
        buildHeap( );
    }

    bool isEmpty( ) const{
    	return array.empty();
    }
    const Comparable & findMin( ) const{
    	if (isEmpty()) return NULL;
    	return array[1];

    }

     /**
     * Insert item x, allowing duplicates.
     */
    void insert( const Comparable & x )
    {
        if( currentSize == array.size( ) - 1 )
            array.resize( array.size( ) * 2 );
    
            // Percolate up
        int hole = ++currentSize;
        for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 )
            array[ hole ] = array[ hole / 2 ];
        array[ hole ] = x;
    };

    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {
        if( isEmpty( ) )
            throw UnderflowException( );
    
        array[ 1 ] = array[ currentSize-- ];
        percolateDown( 1 );
    }
    
    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
    void deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
            throw UnderflowException( );
    
        minItem = array[ 1 ];
        array[ 1 ] = array[ currentSize-- ];
        percolateDown( 1 );
    }
    
    void makeEmpty( ){
    	//This method isn't mentioned in the book, so I'm taking it
    	//to mean "make this heap empty" and not "make an empty heap"
    	array.resize(0);

    }

    void printHeap(){
    	for (int i = 0; i < array.size(); ++i){
    		cout << array[i] << endl;
    	}
    }

  private:
    int                currentSize;  // Number of elements in heap
    vector<Comparable> array;        // The heap array

    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    void buildHeap( )
    {
        for( int i = currentSize / 2; i > 0; i-- )
            percolateDown( i );
    }


    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */
    void percolateDown( int hole )
    {
        int child;
        Comparable tmp = array[ hole ];
    
        for( ; hole * 2 <= currentSize; hole = child )
        {
            child = hole * 2;
            if( child != currentSize && array[ child + 1 ] < array[ child ] )
                child++;
            if( array[ child ] < tmp )
                array[ hole ] = array[ child ];
            else
                break;
        }
        array[ hole ] = tmp;
    }
};

int main(){
	int randifier[] = {3, 8, 1, 2, 5};
	vector<int> v1(10);
	for (int i = 0; i < v1.size(); ++i){
		v1[i] = randifier[i%5] + (v1.size()-i);
		cout << v1[i] << endl;
	}
	BinaryHeap<int> b2(v1);
	cout << "print heap" << endl;
	b2.printHeap();
	return 0;
}

