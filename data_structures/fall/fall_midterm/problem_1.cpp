#include "list.h"

	//Problem 1, as member function
	//O(5N+4), or strictly O(N), with just constant extra space
	//for the buffer variables. No new or malloc
	//Commented out becuase it's actually in the list.h file


// 	void reverse(){
// 		Node* current = head;
// 		Node* temp;
// 		while (current!=NULL){
// 			temp = current->next;
// 			current->next = current->prev;
// 			current->prev=temp;
// 			current=temp;
// 		}
// 		temp = head;
// 		head = tail;
// 		tail = temp;
// 	}



// //Problem 1, as non-member function (using a member function)
// //Using a member function for this, it functions very similarly
// //to the way it does if we'd written the whole thing as a member function
// //roughly O((N-1)*4 + 7), or strictly O(N)
// //with just constant extra space for the buffer variables. No new or malloc


// //This is the member functionec
// commented out because it's actually in list.h
//     void swapNext( iterator itr )
//     {
//     	if(itr==end()){
//     		Node* p = itr.current;
//     		Node* temp = p->next;
//     		p->next = p->prev;
//     		p->prev = temp;
//     		temp = head;
//     		head = tail;
//     		tail = temp;
//     	}
//     	else{
// 	        Node *p = itr.current;
// 	        Node *temp = p->next;
// 	   		p->next = p->prev;
// 	 		p->prev=temp;
//     	}
//     }

//This is the non-member function
void reverseList(List<int>& l){
	for( List<int>::iterator itr = l.begin( ); itr != l.end( );){
		List<int>::iterator tempItr = itr;
		++itr;
		l.swapNext(tempItr);
	}
	l.swapNext(l.end());
}


int main(){
	List<int> l;
	for (int i = 0; i < 15; i++){
		l.insert(l.begin(), 15-i);
	}
    for( List<int>::const_iterator itr = l.begin( ); itr != l.end( ); ++itr )
    	cout << *itr << endl;
    l.reverse();
    for( List<int>::const_iterator itr = l.begin( ); itr != l.end( ); ++itr )
    	cout << *itr << endl;
    reverseList(l);
    for( List<int>::const_iterator itr = l.begin( ); itr != l.end( ); ++itr )
    	cout << *itr << endl;

}

