// There are people standing in a circle waiting to be executed. The counting out begins at some point in the circle 
// and proceeds around the circle in a fixed direction. In each step, a certain number of people are skipped and 
// the next person is executed. The elimination proceeds around the circle (which is 
// becoming smaller and smaller as the executed people are removed), until only the last person remains, who is given freedom.

// And the book made this about potatoes. 


// The people, in this case, are a circularly linked list

#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node   *next;

    Node( int d = 0, Node *n = NULL )
      : data( d ), next( n ) { }
};

int main(){
	int players = 5, m = 2, counter = 1; //players is "N"
	Node *first, *last, *prev, *current;
	//Set up the players
	for (int i =0; i < players; i++){
		if (i==0){
			 prev = first = new Node(i);
		}
		else {
			current = new Node(i);
			prev->next = current;
			prev = last = current;
		}
	}
	//Make the list circular
	last->next = first;

	current = first;
	prev = last;
	while(players > 1){
		if((counter % m) == 0){
			counter = 1;
			prev->next = current->next;
			cout << "Player " << current->data << " has \"lost the game\"" << endl;
			delete current;
			current = prev->next;
			--players;
		}
		else {
			prev = current;
			current = current->next;
			cout << "Player " << current->data << " has the \"hot potato\"" << endl;
			++counter;
		}
	} 
	cout << "Player " << current->data << " has won!" << endl;





}