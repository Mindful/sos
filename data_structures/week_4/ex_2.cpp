#include <iostream>  
using namespace std;

    struct singleNode
    {
        int  data;
        singleNode   *next;

        singleNode( int d = 0, singleNode *n = NULL )
          : data( d ), next( n ) { }
    };


    struct Node
    {
        int data;
        Node   *prev;
        Node   *next;

        Node( int d = 0, Node *p = NULL, Node *n = NULL )
          : data( d ), prev( p ), next( n ) { }
    };

//I used the book's source code from Figure 3->13 for node implementations, just changed slightly
//Because the problem is just asking us to write something to handle swapping


void swapSingle(singleNode *lhs, singleNode *rhs, singleNode *head){

	//Since there are no pointers going back in a singly linked list, we have to perform
	//a traversal to find the nodes before "rhs" and "lhs".
	singleNode *lhsPrev, *rhsPrev, *temp;;
	for (singleNode * counter = head; counter!=NULL; counter = counter->next){
		if (counter->next==lhs) lhsPrev = counter;
		if (counter->next==rhs) rhsPrev = counter;
	}

	lhsPrev->next = rhs;
	rhsPrev->next = lhs;

	temp = rhs->next;
	rhs->next = lhs->next;
	lhs->next = temp;

}

void swap(Node *lhs, Node *rhs){
	Node * temp;

	//There is kind of an edge case if the two nodes are next to each other in that things
	//look a little different, but this order of assignment still handles that fine

	//Update the nodes in front of both swapped nodes, so they point backward properly
	if(rhs->next!=NULL) rhs->next->prev = lhs;
	if(lhs->next!=NULL) lhs->next->prev = rhs;

	//Update the nodes behind both swapped nodes, so they point forward properly
	if(rhs->prev!=NULL) rhs->prev->next = lhs;
	if(lhs->prev!=NULL) lhs->prev->next = rhs;


	//Swap the values of "next" for the nodes
	temp = rhs->next;
	rhs->next = lhs->next;
	lhs->next = temp;

	//Swap the values of "prev" for the nodes
	temp = rhs->prev;
	rhs->prev = lhs->prev;
	lhs->prev = temp;

}

int main(){
	singleNode e(4, NULL);
	singleNode d(3, &e);
	singleNode c(2, &d);
	singleNode b(1, &c);
	singleNode a(0, &b);

	for (singleNode * counter = &a; counter!=NULL; counter = counter->next){
		cout << counter->data << endl;
	}

	cout << "Swapping b(1) and d(3)" <<endl;
	swapSingle(&b,&d,&a);
	for (singleNode * counter = &a; counter!=NULL; counter = counter->next){
		cout << counter->data << endl;
	}
	cout << "Swapping b(1) and e(4)" <<endl;
	swapSingle(&b,&e,&a);
	for (singleNode * counter = &a; counter!=NULL; counter = counter->next){
		cout << counter->data << endl;
	}


	//There isn't a written test here for the doubly-linked list swap because I did it on paper
	//to convince myself it worked for cases where nodes are next to each other



}
