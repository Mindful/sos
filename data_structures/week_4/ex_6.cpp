//ANSWERS
//b. The running time of the program is M*N. Insofar as I can see, this Model runs for (N-1)(M+1) iterations, making the 
// big O(MN)
//c. If M=1, the running time of the program is 2*N, which is O(N). I admit that I didn't honestly notice a substantial
//difference in speed using delete, although I didn't run actual benchmarking because I'd already spent a lot of time
//on this problem.





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
	int players = 5, m = 2, counter = 0; //players is "N"
	int total_iterations = 0;
	//No input validation here, but that's not what this is about
	cout << "Enter a desired number of players (N)" << endl;
	cin >> players;
	cout << "Enter a desired value for M (number of hops before a player loses)" << endl;
	cin >> m;
	Node *first, *last, *prev, *current;
	//Set up the players with i+1 so we're analogous to the book
	for (int i =0; i < players; i++){
		if (i==0){
			 prev = first = new Node(i+1);
		}
		else {
			current = new Node(i+1);
			prev->next = current;
			prev = last = current;
		}
	}
	//Make the list circular
	last->next = first;

	current = first;
	prev = last;
	while(players > 1){
		if(counter==m){
			counter = 0;
			prev->next = current->next;
			cout << "Player " << current->data << " has \"lost the game\"" << endl;
			delete current;
			current = prev->next;
			--players;
		}
		else {
			cout << "Player " << current->data << " has the \"hot potato\"" << endl;
			++counter;
			prev = current;
			current = current->next;
		}
		++total_iterations;
	} 
	cout << "Player " << current->data << " has won!" << endl;
	cout << total_iterations << " total iterations" << endl;





}