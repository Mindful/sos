// cmdint.cpp - command interpreter to test Fibonacci Heap module

#include "fibheap.h"
#include <iostream>
#include <string>

// using namespace std ;

int main()
{
  string comment ;
  char choice ;
  KeyType key, newKey ;
  FibHeap H ;
  NodePtr x ;

  bool interact = false ;
  bool xprint = true ;

  if ( interact )  cout << "Choose: (i)nsert, (m)inimum, (e)extract min, "
                        << "(u)nion, decrease (k)ey,\n (d)elete, (s)earch, "
                        << "(S)how, or +/- turns extract print on/off: " ;
  cin >> choice ;
  while ( !cin.eof() ) {
    switch ( choice ) {
      case 'c':
                // This is done above with the constructor
                break ;
      case 'i': 
                if ( interact ) cout << "Enter key value to insert: " ;
                cin >> newKey ;
                {
                  NodePtr x = new FibHeapNode( newKey ) ;
                  H.FHinsert( x ) ;
                }
                break ;
      case 'm': 
                x = H.FHminimum() ;
                cout << "Minimum = " << x->key << "\n" ;
                break ;
      case 'e': 
                x = H.FHextractMin( ) ;
                if ( x != NIL ) {
                   if ( xprint ) 
                      cout << "Minimum extracted = " << x->key << "\n" ;
                } else {
                   cout << "Heap empty, can't extract minimum.\n\n" ;
                }
                break ;
      case 'u': 
                if ( interact ) cout << "Enter key values to insert into"
                                     << " new heap (-1 to stop): " ;
                {
                  FibHeap H2 ;
                  cin >> newKey ;
                  while ( newKey >= 0 )
                  {
                    NodePtr x = new FibHeapNode ( newKey ) ;
                    H2.FHinsert( x ) ;
                    cin >> newKey ;
                  }
                  cout << "Original heap:\n" ;
                  H.ShowHeap ( ) ;
                  cout << "\n" ;
                  cout << "New heap:\n" ;
                  H2.ShowHeap ( ) ;
                  cout << "\n" ;
                  FibHeap H3 = FHunion( H, H2 ) ;
                  cout << "Union of heaps:\n" ;
                  H3.ShowHeap ( ) ;
                  cout << "\n" ;
                }
                break ;
      case 'k':
                if ( interact ) cout << "Enter key to decrease and new key: " ;
                cin >> key >> newKey ;
                x = H.search( H.min, key ) ;
                if ( x != NIL ) {
                   H.FHdecreaseKey( x, newKey ) ;
                } else {
                   cout << "Originaly key = " << key << "not in heap.\n\n" ;
                }
                break ;
      case 'd':
                if ( interact ) cout << "Enter key value to delete: " ;
                cin >> key ;
                x = H.search( H.min, key ) ;
                H.FHdelete( x ) ;
                break ;
      case 's':
                if ( interact ) cout << "Enter key value to search for: " ;
                cin >> key ;
                x = H.search( H.min, key ) ;
                if ( x != NIL ) {
                   cout << "key, " << key << ", found" << "\n\n" ;
                } else {
                   cout << "key, " << key << ", not found" << "\n\n" ;
                }
                break ;
      case 'S': cout << "Structure of Fibonacci Heap"
                     << " (rotated 90 degrees to the left):\n" ;
                if ( H.min == NIL ) {
                   cout << "\nEmpty heap\n\n" ;
                } else {
                   cout << "\n" ;
                   H.ShowHeap ( ) ;
                }
                break ;
      case '+': xprint = true ;
                break ;
      case '-': xprint = false ;
                break ;
      case '#': cout << '#' ; getline(cin, comment) ;
                cout << comment << "\n\n" ;
                break ;
      case '\n': cout << "end of line encountered\n" ;
                break ;
      default: cout << "Illegal choice: " << choice << endl ;
    }
    if ( interact )  cout << "Choose: (i)nsert, (m)inimum, (e)extract min, "
                          << "(u)nion, decrease (k)ey,\n (d)elete, (s)earch, "
                          << "(S)how, or +/- turns extract print on/off: " ;
    cin >> choice ;
  }
  cout << endl ;

  return 0;
}
