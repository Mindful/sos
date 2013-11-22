#ifndef set
#define set
#include "bst.cpp"
#include <utility>  

//So I made the decision to change some of the binary search tree's private states to protected
//This breaks encapsulation to some degree, but only with inherited classes, and it lets me write
//much cleaner methods

template <typename T>
class Set : private BinarySearchTree<T>{
typedef typename BinarySearchTree<T>::BinaryNode SetNode;


public:
	class const_iterator{
	public:
        const_iterator( ) : current( NULL )
          { }

        const T& operator* ( ) const
          { return this->retrieve( ); }


        const_iterator & operator++ ( )
        {
            increment();
            return *this;
        }
    
        const_iterator operator++ ( int )
        {
            const_iterator old = *this;
            increment();
            return old;
        }

        void increment(){
        	SetNode *prev, *smallest;
        	//Smallest is definitely not current, that's all wrong
        	SetNode *temp = current;
        	bool left = false; //The direction we are trying to go
        	while(!left)
        	{
        		//Try to go right until we've made one right
        		//if we can't go right, go up and try again
        		if (temp->right!=NULL && temp->right!=prev){
        			if ((temp->right->element < smallest->element || smallest==NULL) &&
        				temp->right->element > current->element) smallest = temp->right;
        			temp = temp->right;
        			left = true;
        		}
        		else{
        			if ((temp->parent->element < smallest->element || smallest==NULL) &&
        				temp->parent->element > current->element) smallest = temp->parent;
        			prev = temp;
        			temp = temp->parent;
        		}
        	}
        	//We've now made that right, time to go left as much as we can
        	while(temp->left!=NULL)
        	{
        		if ((temp->left->element < smallest->element || smallest==NULL) &&
        			temp->left->element > current->element) smallest = temp->left;
        		temp = temp->left;
        	}
        	current = smallest;
        	//The end result sould be the smallest value we have iterated over that is also
        	//larger than our current value
        }

        bool operator== ( const const_iterator & rhs ) const
          { return current->element == rhs.current->element ; }
        bool operator!= ( const const_iterator & rhs ) const
          { return !( *this == rhs ); }
    
      protected:
        SetNode *current;
    
        T& retrieve( ) const
          { return current->element; }
    
        const_iterator( SetNode *p ) : current( p )
          { }
            
        friend class Set<T>;


	};


	//TODO: normal iterators need some love
	class iterator : public const_iterator{

    public:
        iterator( )
          { }
    
        T& operator* ( )
          { return this->retrieve( ); }

        const T& operator* ( ) const
          { return const_iterator::operator*( ); }

	protected:
        iterator( SetNode *p ) : const_iterator( p )
          {}
    
        friend class Set<T>;

	};


	const_iterator begin() const {
		return const_iterator(this->findMin(this->root));
	}

	pair<iterator,bool> insert( const T& item ){
		//Start looking at the root
		return insertFind(item, this->root, NULL);
	}
	pair<iterator,bool> insert( iterator hint, const T& item ){
		//Check if the hint is a valid insert location:
		//the only way I can interpret this is that the hint is going to point to a node
		//that we can insert under
		SetNode &h = hint.retrieve();
		if (h.element == item) 
			return pair<iterator,bool>(hint, false); //They pointed us to a duplicate node
		else if(h.left==NULL && item < h.element){
			h.left == new SetNode(item, NULL, NULL, h );
			return pair<iterator, bool>(iterator(&h.left), true);
		}
		else if(h.right==NULL && item > h.element){
			h.right == new SetNode(item, NULL, NULL, h );
			return pair<iterator, bool>(iterator(&h.right), true);
		}
		else return insert(item);
	}
	//Attempt to insert an item, returning an iterator to the location of a successful insert and true
	//or an iterator pointing to the duplicate item and false
	//if a hint is provided, see if that's a good location to insert, otherwise look normally

private:
	pair<iterator, bool> insertFind( const T& x, SetNode* & t, SetNode* parent)
    {

        if( t == NULL ) {
            t = new SetNode( x, NULL, NULL, parent );
        	return pair<iterator, bool>(iterator(t), true);
        }
        else if( x < t->element )
            insertFind( x, t->left, t );
        else if( t->element < x )
            insertFind( x, t->right, t );
        else
            return pair<iterator, bool>(iterator(t), false); //duplicate case
    }


public:
	int erase( const T& x ){

	} //if X is found, remove it and return 1, otherwise return 0
	iterator erase( iterator itr ); //delete item at itr, return itr item after deleted item
	iterator erase( iterator start, iterator end ); //delete all items between start and end, return end
	//END IS NOT ERASED

	iterator find( const T& x ) const;
	//returns the item if found, otherwise returns the... "endmarker"?



};
#endif

//TODO:

//Try to go down and to the right; if we can, we make that right and then lefts, keeping track of the min
//if we can't (if we're a leaf), we go up until we can make a right and then stop - the first node we CAN
//make a right at is the node we're looking for
