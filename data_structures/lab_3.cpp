#include <sstream>
#include <iostream>
using namespace std;

//This doesn't include the first problem (#31) because I did it as part of the homework
//and have already turned that in

template <typename Comparable>
class BinaryNode
{
public:
   Comparable element;
   BinaryNode *left;
   BinaryNode *right;

	virtual bool isOperator() =0;

   BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
     : element( theElement ), left( lt ), right( rt ) { }
};



template <typename Comparable>
class BinaryTree
{
};

class ExpressionTree : private BinaryTree<char>
{
private:
	class opNode : public BinaryNode<char>
	{
	public:
		// bool isOperator(){
		// 	return element < '0';
		// }
		opNode(opNode *l, opNode* r, char c) : BinaryNode<char>(c,l,r){}
	};

	class operatorNode : public opNode
	{
	public:
		bool isOperator(){
			return true;
		}
		operatorNode(opNode* l, opNode* r, char c) : opNode(l,r,c){
		}
	};

	class operandNode : public opNode
	{
	public:
		bool isOperator(){
			return false;
		}
		operandNode(char c) : opNode(NULL,NULL,c){
		}
	};

	opNode* root;

public:
	int evaluate(){
		return evaluate(root);
	}

	void test(){
		this->root = new operatorNode(NULL, NULL, '*');
		root->left = new operandNode('9');
		root->right = new operatorNode(new operandNode('3'), new operandNode('4'), '+');
	}

private:
	int evaluate(BinaryNode<char>* n){
		if (!n->isOperator()){
			return n->element - '0';
		}
		else{
			switch(n->element){
				case '+':
					return evaluate(n->left)+evaluate(n->right);
				case '-':
					return evaluate(n->left)-evaluate(n->right);
				case '*':
					return evaluate(n->left)*evaluate(n->right);
				case '/':
					return evaluate(n->left)/evaluate(n->right);
				}
			}
		}


};



int main(){
	ExpressionTree t;
	t.test();
	cout << t.evaluate() << endl;
	return 0;
}

