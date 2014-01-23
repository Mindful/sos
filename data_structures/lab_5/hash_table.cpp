#include <vector>
#include <list>
#include <string>
#include <iostream>
#include "employee.cpp"
using namespace std;


template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable( int size = 101 ) : currentSize(0), theLists(size){}

    void makeEmpty( )
    {
        for( int i = 0; i < theLists.size( ); i++ )
            theLists[ i ].clear( );
    }

    bool contains( const HashedObj & x ) const
    {
        const list<HashedObj> & whichList = theLists[ myhash( x ) ];
        return find( whichList.begin( ), whichList.end( ), x ) != whichList.end( );
    }
    
    bool remove( const HashedObj & x )
    {
        list<HashedObj> & whichList = theLists[ myhash( x ) ];
        typename list<HashedObj>::iterator itr = find( whichList.begin( ), whichList.end( ), x );
    
        if( itr == whichList.end( ) )
            return false;
    
        whichList.erase( itr );
        --currentSize;
        return true;
    }
    bool insert( const HashedObj & x )
    {
        list<HashedObj> & whichList = theLists[ myhash( x ) ];
        if( find( whichList.begin( ), whichList.end( ), x ) != whichList.end( ) )
            return false;
        whichList.push_back( x );
    
        if( ++currentSize > theLists.size( ) )
            rehash( );
    
        return true;
    }

  private:
    vector<list<HashedObj> > theLists;   // The array of Lists
    int  currentSize;

    typename list<HashedObj>::const_iterator find(typename list<HashedObj>::const_iterator start, 
    typename list<HashedObj>::const_iterator end, HashedObj x ) const
    {
        typename list<HashedObj>::const_iterator result = end;
        for(;start!=end;start++){
            if (*start==x) result = start;
        }
        return result;
    }

    typename list<HashedObj>::iterator find(typename list<HashedObj>::iterator start, 
    typename list<HashedObj>::iterator end, HashedObj x )
    {
        typename list<HashedObj>::iterator result = end;
        for(;start!=end;start++){
            if (*start==x) result = start;
        }
        return result;
    }

    /**
     * Rehashing for separate chaining hash table.
     */
    void rehash( )
    {
        vector<list<HashedObj> > oldLists = theLists;
    
            // Create new double-sized, empty table
        theLists.resize(( 2 * theLists.size( ) )+1 );
        for( int j = 0; j < theLists.size( ); j++ )
            theLists[ j ].clear( );
    
            // Copy table over
        currentSize = 0;
        for( int i = 0; i < oldLists.size( ); i++ )
        {
            typename list<HashedObj>::iterator itr = oldLists[ i ].begin( );
            while( itr != oldLists[ i ].end( ) )
                insert( *itr++ );
        }
    }
    int myhash( const HashedObj & x ) const
    {
        int hashVal = hash( x );
    
        hashVal %= theLists.size( );
        if( hashVal < 0 )
            hashVal += theLists.size( );
    
        return hashVal;
    }
};

int hash( const string & key)
{
      int hashVal = 0;

      for( int i = 0; i < key.length( ); i++ )
          hashVal += key[ i ];

      return hashVal;
}

int hash( const Employee & item )
{
    return hash( item.getName( ) );
}

int main(){
    HashTable<Employee> table;
    Employee e1("John", 200, 1);
    Employee e2("Bob", 300, 2);
    Employee e3("Jeff", 500, 4);
    table.insert(e1);
    table.insert(e2);
    cout << "Insert e1 and e2" << endl;
    if (!table.contains(e3)) cout << "Table does not contain e3" << endl;
    else cout << "Bad news!" << endl;
    cout << "Remove e2" << endl;
    table.remove(e2);
    if (!table.contains(e2)) cout << "Table does not contain e2" << endl;
    else cout << "Bad news!" << endl;
    if (table.contains(e1)) cout << "Table does contain e1" << endl;
    else cout << "Bad news!" << endl;
}