// fibheap.cpp implementation file for Fibonacci heaps

#include "fibheap.h"
#include <iostream>
#include <iomanip>

#define MAX_DEG 10

NodePtr A[MAX_DEG+1] ;
// Used as global to consolidate()


// Constructor - done in fibheap.h


// Utility routines to show structure and search 
void showChildren ( NodePtr x, int depth )
{
  if ( x != NIL ) {
    NodePtr y = x ;
    cout << setw( 6 ) << y->key << (y->mark ? "M" : " ") ;
    showChildren ( y->child, depth + 1 ) ;
    y = y->left ;
    while ( y != x ) {
      cout << "\n\n" ;
      cout << setw( depth*7 - 1 ) << y->key << (y->mark ? "M" : " ") ;
      showChildren ( y->child, depth + 1 ) ;
      y = y->left ;
    }
//    cout << "\n\n" ;
  }
}

void showTree ( NodePtr x )
{
  if ( x != NIL ) {
    cout << setw( 6 ) << x->key << (x->mark ? "M" : " ") ;
    showChildren ( x->child, 2 ) ;
    cout << "\n\n" ;
  }
}

void FibHeap :: ShowHeap ( )
{
  if ( min != NIL ) {
     NodePtr x = min ;
     do {
        showTree ( x ) ;
        x = x-> left ;
     } while ( x != min ) ;
//     cout << "\n\n" ;
  } else {
     cout << "Heap is empty.\n\n" ;
  }
}

// This shows the non-NILs in array A[] - may be useful for debugging
void showA ( )
{
   cout << "Array A:\n" ;
   for ( int i = 0 ; i <= MAX_DEG ; i++ ) {
      if ( A[i] != NIL ) {
         cout << "A[" << i << "] =\n" ;
         showTree ( A[i] ) ;
 //        cout << "\n\n" ;
      }
   }
}


// Utility routine to search heap starting at x for node with key k
// Used to test decrease-key() and delete()
NodePtr FibHeap :: search( NodePtr x, KeyType k )
{

// You write this for extra credit

   return NIL ;
}


void FibHeap :: FHinsert( NodePtr x )
{
   x->degree = 0 ;
   x->p = NIL ;
   x->child = NIL ;
   x->mark = false ;
   if ( min == NIL ) {
      x->left = x->right = x ;
      min = x ;
   } else {
      x->left = min->left ;
      x->right = min ;
      min->left->right = x ;
      min->left = x ;
      if ( x->key < min->key ) min = x ;
   }
   n++ ;
}

NodePtr FibHeap :: FHminimum( void )
{
   return min ;
}


// Utility routine to splice two linked lists together
NodePtr spliceIn(NodePtr x, NodePtr y)
{
    if (x == NIL)
        return y;
    else if (y == NIL)
        return x;
    else {
        NodePtr xPred = x->left;
        NodePtr yTail = y->left;

        x->left = yTail;
        yTail->right = x;
        y->left = xPred;
        xPred->right = y;
        return x;
    }
}

void link ( NodePtr y, NodePtr x )
{
   // Link out y - root list should not be empty since x is in it
   y->left->right = y->right ;
   y->right->left = y->left ;

   // Make y a child of x, incrementing degree x.

   y->p = x ;
   if ( x->child == NIL ) {
      y->left = y->right = y ;
      x->child = y ;
   } else {
      NodePtr z = x->child ;
      y->left = z->left ;
      y->right = z ;
      z->left->right = y ;
      z->left = y ;
   }
   x->degree = x->degree + 1 ;

   x->mark = false ;
}


// Consolidates the root list of this Fibonacci heap.  
// Implements the Consolidate procedure on page 516
void FibHeap :: consolidate ( )
{
   int i ;
   for ( i = 0 ; i <= MAX_DEG ; i++ ) {
      A[i] = NIL ;
   }
   // Count the number of roots in the root list to iterate through them
   int numRoots = 1 ;
   NodePtr z = min ;
   while ( z->left != min ) {
       numRoots++ ;
       z = z->left ;
   }

   // Iterate through the root list, keeping a pointer to next w
   NodePtr w = min;
   for ( i = 1 ; i <= numRoots ; i++ ) {
       NodePtr x = w;
       NodePtr nextW = w->right; // because we might move w,
				  // save its right sibling
       int d = x->degree;

	    while (A[d] != NIL) {
          //lines 8 - 13 of pseudocode
        NodePtr y = A[d];
        if (x->key > y->key){
          std::cout << "lines 8-13" << endl;
          //exchange X with Y
          NodePtr temp = y;
          y = x;
          x = temp;
        }
        link(y,x);
        A[d] = NIL;
        ++d;
	    }

       A[d] = x ;
       w = nextW ;
   } // End of outer for-loop

   min = NIL ;

   for ( i = 0 ; i <= MAX_DEG ; i++ ) {
    //lines 17-23 of the pseudocode
    if(A[i]!=NIL){
      std::cout << "lines 17-23" << endl;
      if(min==NIL){
        std::cout << "new root list" << endl;
        //create a root list containing just A[i]
        //I think this is done like so
        A[i]->p = NIL;
        // A[i]->right = NIL;
        // A[i]->left = NIL; //Should we null the left and right?
        min = A[i];
        //----
      } else{
        std:: cout << "splice" << endl;
        spliceIn(min, A[i]);
        A[i]->p = NIL;
        if(A[i]->key < min->key){
          min=A[i];
        }
      }
    }

   }

} // End of consolidate()


NodePtr FibHeap :: FHextractMin( void )
    {
        NodePtr z = min;

        if (z == NIL )
            return NIL ;        // empty Fibonacci heap
        else {
            // Add each child of z to the root list.  We can just
            // splice in z's children, but first we have to set their
            // parent pointers to NIL .
            if (z->child != NIL ) {
                z->child->p = NIL ;

                for (NodePtr x = z->child->right; x != z->child; x = x->right)
                    x->p = NIL ;

                min = spliceIn(min, z->child);
            }

            // Remove z from the root list.
            z->left->right = z->right;
            z->right->left = z->left;

            // Update min appropriately.
            if (z == z->right)
                min = NIL ;
            else {
                min = z->right;
                consolidate();
            }

            n--;

            return z ;
        }
    }


void FibHeap :: FHdecreaseKey( NodePtr x, KeyType k )
{

// You can write this for extra credit

}

void FibHeap :: FHdelete( NodePtr x )
{

// You can write this for extra credit

}

// non-class member function
FibHeap FHunion ( FibHeap H1, FibHeap H2 )
{

// You can write this for extra credit

}