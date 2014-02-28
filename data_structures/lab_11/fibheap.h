#ifndef FIBHEAP_H
#define FIBHEAP_H

// fibheap.h - declaration file for Fibonacci heap structure

using namespace std ;

#define NIL 0

typedef int KeyType ; 

typedef class FibHeapNode * NodePtr ;

class FibHeapNode {
public:
   KeyType key ;
   int degree ;
   bool mark ;
   NodePtr p ;
   NodePtr left ;
   NodePtr right ;
   NodePtr child ;

// Constructor
   FibHeapNode( KeyType k ) : key(k) { }
} ;

class FibHeap {
public:
   NodePtr min ;
   int n ;

// Constructor
   FibHeap( ) : min(NIL), n(0) { }

   void FHinsert( NodePtr x ) ;
   NodePtr FHminimum( void ) ;
   NodePtr FHextractMin( void ) ;
   void FHdecreaseKey( NodePtr x, KeyType k ) ;
   void FHdelete( NodePtr x ) ;

// Utility routines
   void consolidate( void ) ;
   NodePtr search( NodePtr x, KeyType k ) ;
   void ShowHeap( void ) ;
} ;

   FibHeap FHunion( FibHeap H1, FibHeap H2 ) ;

#endif