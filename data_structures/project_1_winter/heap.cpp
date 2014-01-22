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
    explicit BinaryHeap(bool (*cmp_function)(const Comparable lhs, const Comparable rhs),
     int capacity = 0 ) : array(capacity+1), currentSize(0),
     lessthan(cmp_function){}
    explicit BinaryHeap(bool (*cmp_function)(const Comparable lhs, const Comparable rhs),
     const vector<Comparable> & items ) : array( items.size( ) + 1), currentSize( items.size( ) ),
     lessthan(cmp_function)
    {
        for( int i = 0; i < items.size( ); i++ )
            array[ i + 1 ] = items[ i ];
        buildHeap( );
    }


    bool isEmpty( ) const{
    	return currentSize==0 || array[1]==NULL;
    }


    const Comparable & findMin( ) const{
        if( isEmpty( ) )
            throw UnderflowException( );
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
        //cout << "hole " << hole << endl;
        for( ; hole > 1 && lessthan(x,array[ hole / 2 ]); hole /= 2 )
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
    	for (int i = 0; i < currentSize; ++i){
            if (array[i]!=NULL){
                cout << *array[i] << endl;
            }
    	}
    }

    vector<Comparable> array;        // The heap array

        //Used by heapsort. The heap's sort.
    void sort(){
    	for (int i = 0; i < array.size() - 1; ++i){
    		Comparable min;
    		deleteMin(min); //Min is now the smallest item that was in the heap before we deleted it
    		array[array.size()-(i+1)] = min;
    		cout << min << " to slot " << array.size()-(i+1) << endl;
    	}
    }

  private:
    bool (*lessthan)(const Comparable lhs, const Comparable rhs); //lhs < rhs
    int                currentSize;  // Number of elements in heap
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
            if( child != currentSize && lessthan(array[ child + 1 ],array[ child ]) )
                child++;
            if( lessthan(array[ child ], tmp) )
                array[ hole ] = array[ child ];
            else
                break;
        }
        array[ hole ] = tmp;
    }

};


// template <typename T>
// static vector<T> heapSort(vector<T> &arr){
// 	BinaryHeap<T> h1(arr);
// 	h1.sort(); // The sorted vector will have a leading zero, because the heap also has a leading zero

// 	return h1.array; //I'm aware this copies which kind of defeats the purpose of heapsort
// 	//and it not using extra space, but I'm just demonstrating method here
// }

// int main(){
// 	int randifier[] = {3, 8, 1, 2, 5};
// 	vector<int> v1(10);
// 	for (int i = 0; i < v1.size(); ++i){
// 		v1[i] = randifier[i%5] + (v1.size()-i);
// 		cout << v1[i] << endl;
// 	}
// 	cout << "heap sort" << endl;
// 	vector<int> v2 = heapSort<int>(v1);
// 	for (int i = 0; i < v2.size(); ++i){
// 		cout << v2[i] << endl;
// 	}
// 	return 0;
// }

