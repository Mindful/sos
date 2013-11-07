#include <iostream>

struct Node
{
    int  data;
    Node   *prev;
    Node   *next;

    Node( const int & d = int( ), Node *p = NULL, Node *n = NULL )
      : data( d ), prev( p ), next( n ) { }
};

class List{

  List( )
  { init( ); }
    
    ~List( )
    {
        clear( );
        delete head;
        delete tail;
    }
    
    List( const List & rhs )
    {
        init( );
        *this = rhs;
    }
    
    
    void init( )
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }

};