#include <iostream>

using namespace std;

//I worked with Colin Robinson on this problem

template <typename Object>
class Vector
{

  public:
/////////
// ITERATORS
/////////
    class const_iterator
    { 
      private:
            Object ** objects;
           int current;
            Vector<Object> * owner;

      public:
        const_iterator():current( 0 ), owner( 0 ), objects( 0 )
                  { }
        const_iterator( Vector<Object> * V, Object ** iterable, int location = 0)
          { objects = iterable;
                        owner = V;
                        current = location; }
    
        const Object & operator* ( ) const
          { return retrieve( ); }
            
        const_iterator & operator++ ( )
        {
                  if ( owner->size() > current ){ 
                        current++;
            return *this;
                  } else {
                        return *this;
                  }
        }
    
        const_iterator operator++ ( int )
        {
                  if ( owner->size() > current ) {
            const_iterator old = *this;
            current++;
            return old;
                  } else {
                    return *this;
                  }
        }
    
        bool operator== ( const const_iterator & rhs ) const
          { return (current == rhs.current) && (owner == rhs.owner); }
        bool operator!= ( const const_iterator & rhs ) const
          { return ! operator==(rhs); }
    
      protected: 
        Object & retrieve( ) const
          { return *(*objects + current); }
            
        friend class Vector<Object>;
    };

    class iterator : public const_iterator
    {
      private:
        Vector<Object> * owner;
        Object ** objects;
                int current;

      public:
        iterator( ) : current(0), owner(0), objects(0)
          { }
            iterator( Vector<Object> * V, Object ** iterable, int location = 0 ) :
                         current( location ), owner( V ), objects(iterable) { }

        Object & operator* ( )
          { return retrieve( ); }
        const Object & operator* ( ) const
          { return const_iterator::operator*( ); }
        
                bool operator==( Vector<Object>::iterator rhs )
                  { return current == rhs.current && owner == rhs.owner; }
                bool operator!=( Vector<Object>::iterator rhs )
                  { return ! operator==(rhs); }
    
        iterator & operator++ ( )
        {
                  if (owner->size() > current) {
            current++;
            return *this;
                  } else {
                        return *this;
                  }
        }
    
        iterator operator++ ( int )
        {
                  if (owner->size() > current) {
            iterator old = *this;
            current++;
            return old;
                  } else {
                        return *this;
                  }
        }
    
      protected:    
        Object & retrieve( )
          { return *(*objects + current); }

        friend class Vector<Object>;
    };

////////////
// END ITERATORS
////////////

  public:
    explicit Vector( int initSize = 0 )
      : theSize( initSize ), theCapacity( initSize + SPARE_CAPACITY )
      { objects = new Object[ theCapacity ]; }
    Vector( const Vector & rhs ) : objects( 0 )
      { operator=( rhs ); }
    ~Vector( )
      { delete [ ] objects; }

    const Vector & operator= ( const Vector & rhs )
    {
        if( this != &rhs )
        {
            delete [ ] objects;
            theSize = rhs.size( );
            theCapacity = rhs.theCapacity;

            objects = new Object[ capacity( ) ];
            for( int k = 0; k < size( ); k++ )
                objects[ k ] = rhs.objects[ k ];
        }
        return *this;
    }

    void resize( int newSize )
    {
        if( newSize > theCapacity )
            reserve( newSize * 2 + 1 );
        theSize = newSize;
    }

    void reserve( int newCapacity )
    {
        if( newCapacity < theSize )
            return;

        Object *oldArray = objects;

        objects = new Object[ newCapacity ];
        for( int k = 0; k < theSize; k++ )
            objects[ k ] = oldArray[ k ];

        theCapacity = newCapacity;

        delete [ ] oldArray;
    }
    Object & operator[]( int index )
      { return objects[ index ]; }
    const Object & operator[]( int index ) const
      { return objects[ index ]; }

    bool empty( ) const
      { return size( ) == 0; }
    int size( ) const
      { return theSize; }
    int capacity( ) const
      { return theCapacity; }

    void push_back( const Object & x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = x;
    }

    void pop_back( )
      { theSize--; }

    const Object & back ( ) const
      { return objects[ theSize - 1 ]; }

    iterator begin( )
      { return iterator(this, &objects, SPARE_CAPACITY); }
    const_iterator begin( ) const
      { return const_iterator(this, &objects, SPARE_CAPACITY); }
    iterator end( )
      { return iterator(this, &objects, theSize); }
    const_iterator end( ) const
      { return const_iterator(this, &objects, theSize); }

    enum { SPARE_CAPACITY = 16 };

  private:
    int theSize;
    int theCapacity;
    Object * objects;
};

int main(){
 Vector<int> a (10);
 Vector<int>::iterator b = a.begin();
 for (int i = 0; i < 100; i++, b++){
  a.push_back(i);
  if (!(i % 5)){
   cout << *b << endl;
  }
 }
 return 0;
}