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


        //Try to go down and to the right; if we can, we make that right and then lefts, keeping track of the min
        //if we can't (if we're a leaf), we go up until we can make a right and then stop - the first node we CAN
        //make a right at is is where we can stop looking.
        //the reason we can stop looking once we can go right is because we know all the items to the right are larger


        void increment(){
        	SetNode *prev = NULL, *smallest = current, *temp = current;
            if (temp->right!=NULL) 
            {
                //We are not at a leaf; make a right and as many lefts as possible
                temp = temp->right;
                while(temp->left!=NULL)
                {
                    temp = temp->left;
                }
                smallest = temp;
            }
            else {
                //We are at a leaf. Go up until we can go right and then stop, keeping the minimum
                //Read one ahead, since we start with current as min (if it's the tree's max)
                while((temp->right==NULL || temp->right==prev) && temp->parent){
                    if ((smallest==current || temp->parent->element < smallest->element) 
                        && temp->parent->element > current->element) smallest = temp->parent;
                    prev = temp;
                    temp = temp->parent;
                }
            }
            if (current!=smallest) current = smallest; 
            else current = NULL; //We didn't find anything larger, we were at max, so now we're at end
        }

        bool operator== ( const const_iterator & rhs ) const
          { return current == rhs.current; }
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


        iterator & operator++ ( )
        {
            this->increment();
            return *this;
        }
    
        iterator operator++ ( int )
        {
            iterator old = *this;
            this->increment();
            return old;
        }

	protected:
        iterator( SetNode *p ) : const_iterator( p )
          {}
    
        friend class Set<T>;

	};


	iterator begin() const {
		return iterator(this->findMin(this->root));
	}

    iterator end() const {
        return iterator(NULL);
    }




    iterator find( const T& x ) const{
        SetNode* current = this->root;
        while(true){
            if(x > current->element){
                current = current->right;
            }
            else if (x < current->element){
                current = current->left;
            }
            else return iterator(current);
            if(current==NULL) return iterator(NULL); //"Return the endmarker"
        }
    }

    int erase( const T& x ){
        iterator result = find(x);
        if (result==end()) return 0;
        else {
            deleteNode(result.current);
            return 1;  
        }
    } //if X is found, remove it and return 1, otherwise return 0

    iterator erase( iterator itr ){
        deleteNode(itr++.current);
        return itr;
    }//delete item at itr, return itr item after deleted item


    iterator erase( iterator start, iterator end ){
        while(start!=end){
            cout << "del " << *start << endl;
            deleteNode(start++.current);
        }
        return end;
    }//delete all items between start and end, return end
    //END IS NOT ERASED

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

    void deleteNode(SetNode* del){
        if( del->left != NULL && del->right != NULL ) // Two children
        {
            SetNode *min = this->findMin( del->right );
            del->element = min->element;
            deleteNode(min); //This is just min, but deleteNode() needs the proper pointer to clear
        }
        else
        {
            SetNode *oldNode = del;
            SetNode *parent = del->parent;
            if(parent){
                if (parent->right==del){
                    //We're the right child
                    parent->right = ( del->left != NULL ) ? del->left : del->right;
                    if (parent->right) parent->right->parent = parent;
                }
                else{
                    //We're the left child
                    parent->left = ( del->left != NULL ) ? del->left : del->right;
                    if (parent->left) parent->left->parent = parent;
                }
            }
            else{
                //We're the root, we have no parents :(
                this->root = ( del->left != NULL ) ? del->left : del->right;
                this->root->parent=NULL;
            }
            delete oldNode;
        }
    }
	pair<iterator, bool> insertFind( const T& x, SetNode* & t, SetNode* parent)
    {
        if( t == NULL ) {
            t = new SetNode( x, NULL, NULL, parent );
        	return pair<iterator, bool>(iterator(t), true);
        }
        else if( x < t->element ){
            insertFind( x, t->left, t );
        }
        else if( x > t->element ){
            insertFind( x, t->right, t );
        }
        else{
            return pair<iterator, bool>(iterator(t), false); //duplicate case
        }
    }

    static void printNode(SetNode* n){
        cout << "-------------" << endl;
        cout << "Node: " << n->element << endl;
        if (n->parent) cout << "Parent: " << n->parent->element << endl;
        if (n->left) cout << "Left: " << n->left->element << endl;
        if (n->right) cout << "Right: " << n->right->element << endl;
        cout << "-------------" << endl;
    }


};
#endif
