//We could conceptualize two ways to do this:
// first, destructively, by reversing the list. this is O(N) and uses constant extra space, but has the side effect of
// reversing the list

// secondly, you can do this in O(N^2) by traversing the list N times in order to find the previous element each time,
// starting with the last element.


#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node   *next;

    Node( int d = 0, Node *n = NULL )
      : data( d ), next( n ) { }
};


void printReverse(Node* head){
	//temp is one out, tempNext is two out
	Node *current = head, *temp = head->next, *tempNext;
	while(true){
		tempNext = temp->next;
		if(tempNext!=NULL){
			temp->next = current;
			current = temp;
			temp = tempNext;
		}
		else{
			temp->next = current;
			current = temp;
			head->next=NULL; //This won't happen any other way
			while(current!=NULL){
				cout << current->data << endl;
				current = current->next;
			}
			break;
		}
	}
}

void safePrint(Node* head){
	Node *current = head, *lastPrinted = NULL;
	while(lastPrinted!=head){
		while(current->next!=lastPrinted){
			if(current->next==NULL){
				current = head;
			}
			else{
				current = current->next;
			}
		}
		cout << current->data << endl;
		lastPrinted=current;
	}
}


int main(){
	Node *head, *current;
	head = new Node(0);
	current = head;
	for (int i = 0; i < 15; i++){
		current->next = new Node(i+1);
		current = current->next;
	}
	current = head;
	cout << "list forward" << endl;
	while(current!=NULL){
		cout << current->data << endl;
		current = current->next;
	}
	cout << "list backward, O(N^2), but leaves list intact" << endl;
	safePrint(head);
	cout << "list backward, O(N) but reverses list" << endl;
	printReverse(head);
}