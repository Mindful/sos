#include "bst.cpp"

//The actual methods to compute depth, leaves, nodes, etc. are in bst.cpp
//they just start from only the root

int main(){
	BinarySearchTree<int> t1;
	t1.insert(11);
	t1.insert(5);
	t1.insert(3);
	t1.insert(6);
	t1.insert(4);
	t1.insert(8); 
	t1.insert(16);
	cout << "Leaves: " << t1.countLeaves() << endl;
	cout << "Nodes: " << t1.countNodes() << endl;
	cout << "Full Nodes: " << t1.countFullNodes() << endl;
	t1.printTree();
	return 0;
}