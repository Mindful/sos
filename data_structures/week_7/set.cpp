#ifndef set
#define set
#include "bst.cpp"
#include <utility>  

//So I made the decision to change some of the binary search tree's private states to protected
//This breaks encapsulation to some degree, but only with inherited classes, and it lets me write
//much cleaner methods

template <typename T>
class Set : private BinarySearchTree<T>{



public:
	class const_iterator{
        const_iterator( ) : current( NULL )
          { }

        const T& operator* ( ) const
          { return this->retrieve( ); }

        bool operator== ( const const_iterator & rhs ) const
          { return current->element == rhs.current->element ; }
        bool operator!= ( const const_iterator & rhs ) const
          { return !( *this == rhs ); }
    
      protected:
        typename BinarySearchTree<T>::BinaryNode *current;
    
        T& retrieve( ) const
          { return current->element; }
    
        const_iterator( typename BinarySearchTree<T>::BinaryNode *p ) : current( p )
          { }
            
        friend class Set<T>;


	};

	class iterator : public const_iterator{

      public:
        iterator( )
          { }
    
        T& operator* ( )
          { return this->retrieve( ); }

        const T& operator* ( ) const
          { return const_iterator::operator*( ); }

	protected:
        iterator( typename BinarySearchTree<T>::BinaryNode *p ) : const_iterator( p )
          {}
    
        friend class Set<T>;

	};

private:
	pair<iterator,bool> insert( const T& item ){
		//Start looking at the root
		return insertFind(item, this->root);
	}
	pair<iterator,bool> insert( iterator hint, const T& item ){
		//Check if the hint is a valid insert location:
		//the only way I can interpret this is that the hint is going to point to a node
		//that we can insert under
		typename BinarySearchTree<T>::BinaryNode &h = hint.retrieve();
		if (h.element == item) 
			return pair<iterator,bool>(hint, false); //They pointed us to a duplicate node
		else if(h.left==NULL && item < h.element){
			h.left == new typename BinarySearchTree<T>::BinaryNode(item, NULL, NULL );
			return pair<iterator, bool>(iterator(&h.left), true);
		}
		else if(h.right==NULL && item < h.element){
			h.right == new typename BinarySearchTree<T>::BinaryNode(item, NULL, NULL );
			return pair<iterator, bool>(iterator(&h.right), true);
		}
		else return insert(item);
	}
	//Attempt to insert an item, returning an iterator to the location of a successful insert and true
	//or an iterator pointing to the duplicate item and false
	//if a hint is provided, see if that's a good location to insert, otherwise look normally

	pair<iterator, bool> insertFind( const T& x, typename BinarySearchTree<T>::BinaryNode* & t )
    {

        if( t == NULL ) {
            t = new typename BinarySearchTree<T>::BinaryNode( x, NULL, NULL );
        	return pair<iterator, bool>(iterator(&t), true);
        }
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            return pair<iterator, bool>(iterator(&t), false); //duplicate case
    }


	int erase( const T& x ); //if X is found, remove it and return 1, otherwise return 0
	iterator erase( iterator itr ); //delete item at itr, return itr item after deleted item
	iterator erase( iterator start, iterator end ); //delete all items between start and end, return end
	//END IS NOT ERASED

	iterator find( const T& x ) const;
	//returns the item if found, otherwise returns the... "endmarker"?



};
#endif