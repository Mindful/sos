#include <iostream> 
using namespace std;

struct Node
{
    int data;
    Node   *next;

    Node( int d = 0, Node *n = NULL )
      : data( d ), next( n ) { }
};

class listParser{
public:
	static int size(Node* head){
		int size = 1;
		Node* current = head;
		while(current!=NULL){
			++size;
			current=current->next;
		}
		return size;
	}
	static void print(Node* head){
		Node* current = head;
		while(current!=NULL){
			cout << current->data << endl;
			current=current->next;
		}
	}
	static bool contains(Node* head, int val){
		Node* current = head;
		while(current!=NULL){
			if (current->data==val) return true;
			current=current->next;
		}
		return false;
	}
	static bool addIfMissing(Node* head, int val){
		if (!contains(head, val)){
			//Insert the value right after head, so we don't change the head of the list
			Node* temp = head->next;
			head->next = new Node(val);
			head->next->next = temp;
			return true;
		}
		return false;
	}
	static bool remove(Node*& head, int val){
		//This function can potetially update the head pointer
		//if the thing we delete is the head value
		Node *current = head, *prev = NULL;
		while(current!=NULL){
			if (current->data==val){
				if (prev==NULL){
					//We are deleting head, and it must be updated
					head = head->next;
					delete current;
					return true;
				}
				prev->next = current->next;
				delete current;
				return true;
			}
			prev = current;
			current=current->next;
		}
		return false;
	}
};


int main(){
	Node* head = new Node(0);
	Node* temp = head;
	for (int i =0; i < 15; i++){
		temp->next = new Node(i+1);
		temp = temp->next;
	}
	//Almost forgot static functions are called like ::
	listParser::print(head);
	cout << "Size: " << listParser::size(head) << endl;
	cout << "Contains 8? " << listParser::contains(head, 8) << endl;
	cout << "Contains 17? " << listParser::contains(head, 17) << endl;
	cout << "Add 16 if missing" << endl;
	listParser::addIfMissing(head, 16);
	listParser::print(head);
	cout << "Size: " << listParser::size(head) << endl;
	cout << "Remove 0 and 3" << endl;
	listParser::remove(head, 0);
	listParser::remove(head, 3);
	listParser::print(head);
}