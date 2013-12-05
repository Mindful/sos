#include "bst.cpp"

//The actual methods to compute depth, leaves, nodes, etc. are in bst.cpp
//they just start from only the root

//Running time: O(N), because we hit each node once. This is true for all of the counting algorithms
//implemented here

int main(){
	BinarySearchTree<int> t1;
	int a[7] = {11, 5, 3, 6, 4, 8, 16};
	for (int i = 0; i < 7; ++i){
		t1.insert(a[i]);
	}
	cout << "Leaves: " << t1.countLeaves() << endl;
	cout << "Nodes: " << t1.countNodes() << endl;
	cout << "Full Nodes: " << t1.countFullNodes() << endl;
	t1.printTree();

	BinarySearchTree<int> t2;
	for (int i = 0; i < 7; ++i){
		t2.insert(a[i]+1);
	}
	t2.printTree();
	if (t1.similar(t2)) cout << "Trees are similar" << endl;
	else cout << "Trees not similar" << endl;

	BinarySearchTree<int> t3;
	t3.insert(8);
	t3.insert(10);
	t3.insert(9);
	t3.insert(7);
	t3.insert(1);
	t3.insert(15);
	t3.insert(16);
	t3.printTree();
	t1.printTree();
	if (t1.similar(t3)) cout << "Trees are similar" << endl;
	else cout << "Trees not similar" << endl;
	return 0;
}