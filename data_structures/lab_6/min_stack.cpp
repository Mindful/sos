#include <stack>
#include <iostream>

using namespace std;

class MinStack{
	private:
		stack<int> s;
		stack<int> mins;
		int min;
		int curSize;

	public:
		MinStack() : curSize(0){}

		bool isEmpty(){
			return curSize==0;
		}

		void push(int i){
			if(isEmpty() || i <= min){
				min = i;
				mins.push(i);
			}
			s.push(i);
			++curSize;

		}

		int top(){
			if(isEmpty()) return 0; //Really this is an error
			return s.top();
		}

		void pop(){
			if(isEmpty()) return;
			int r = top();
			if (r==min){
				mins.pop();
				min = mins.top();
			}
			s.pop();
		}

		int getMin(){
			if(isEmpty()) return 0; //Really this is an error
			return min;
		}		

};

void printPush(MinStack &ms, int i){
	cout << "Push: " << i << endl;
	ms.push(i);

}

void printMin(MinStack &ms){
	cout << "Current Min: " << ms.getMin() << endl;
}

void printPop(MinStack &ms){
	cout << "Pop: " << ms.top() << endl;
	ms.pop();
}

int main(){
	MinStack ms;
	printPush(ms, 5);
	printMin(ms);
	printPush(ms, 4);
	printMin(ms);
	printPush(ms, 7);
	printPush(ms, 8);
	printPush(ms, 3);
	printPush(ms, 2);
	printPush(ms, 2);
	printMin(ms);
	printPop(ms);
	printMin(ms);
	printPop(ms);
	printPop(ms);
	printPop(ms);
	printMin(ms);
	return 0;
}