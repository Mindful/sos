#include <iostream>
#include <cstdlib>
using namespace std;

/*
 * Used the assembled code from Figures
 * 4.16, 4.17, 4.18, 4.20,, 4.21, 4.23
 * Removed the "remove" method, because it
 * isn't in the lab spec. "put" internally
 * calls a modified "insert" and "get" is written
 * from scratch.
 */



template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root(NULL) { 
    }

    BinarySearchTree( const BinarySearchTree & rhs ) : root(NULL) {
	makeEmpty();

	*this = rhs;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    const Comparable & findMin( ) const {
	return findMin(root)->element;
    }

    const Comparable & findMax( ) const {
	return findMax(root)->element;
    }

    bool contains( const Comparable & x ) const {
	return contains(x, root);
    }

    bool isEmpty( ) const {
	return root == NULL;
    }

    void printTree( ) const {
	printTree(root);
	cout << endl;
    } 

    void makeEmpty( ) {
	makeEmpty(root);
    }

    void put( const Comparable & x ) {
	insert(x, root);
    }

    const Comparable & get(int index) const {
        get(index, root)->element;
    }

    /**
     * Deep copy.
     */
    const BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }
        return *this;
    }
    

  private:
    struct BinaryNode
    {
       Comparable element;
       BinaryNode *left;
       BinaryNode *right;
       int leftsize;

       BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, int ls )
         : element( theElement ), left( lt ), right( rt ), leftsize(ls) { }
    };

    BinaryNode *root;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * (SJS) Note that this is not a const method
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {

        if( t == NULL ) 
            t = new BinaryNode( x, NULL, NULL, 0 ); //obviously shouldn't actually be 0
        else if( x < t->element ){
            t->leftsize+=1; //I believe this is basically only the necessary change
            insert( x, t->left );
        }
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }

    BinaryNode * get(int index, BinaryNode *t) const
    {
        if (t == NULL)
            return NULL;
        if (t->leftsize == index || (t->left == NULL && t->right == NULL))
            return t;
        else if (index < t->leftsize)
            return get(index, t->left);
        else
            return get(index-(t->leftsize+1), t->right);
    }



    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

    void printTree( BinaryNode *t ) const {
	// do an in-order traversal
	if (t == NULL)
		return;
	else {
		printTree(t->left);
		cout << t->element << ", ";
		printTree(t->right);
	}
    } 

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == NULL )
            return NULL;
 
        return new BinaryNode( t->element, clone( t->left ), clone( t->right ), t->leftsize );
    }
};

int main() {
	BinarySearchTree<int> t1;
	t1.put(11);
	t1.put(5);
	t1.put(3);
	t1.put(6);
    t1.put(4);
    t1.put(18);

	t1.printTree();

    cout << "3rd element (index 2): " << t1.get(2) << endl;
    cout << "1st element (index 0): " << t1.get(0) << endl;
    cout << "5th element (index 4): " << t1.get(4) << endl;

	cout << endl;
	
}