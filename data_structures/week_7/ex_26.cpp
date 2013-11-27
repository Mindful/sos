//Can't really test these without an AVL tree, so this isn't written to compile
//mostly just very C++-like pseudocode

// rotate n with left child, right
void rotateRight (Node* & n) { 
 Node* child = n->left; 
 n->left = child->right; 
 child->right = n; 
 n->height = max(height(n->left), height(n->right))+1;
 child->height = max(height(child->left), n->height)+1;
 n = child; 
} 
 
 
// rotate n with right child, left
void rotateLeft (Node* & n) { 
 Node* child = n->right; 
 n->right = child->left; 
 child->left = n; 
 n->height = max(height(n->left), height(n->right))+1;
 child->height = max(height(child->right), n->height)+1;
 n = child;
} 



void doubleRotateLeftRight( Node* & n) 
{ 
 Node* child, subChild; 
 child=n->Left; 
 subChild=child->Right; 
 child->Right=subChild->Left; 
 n->Left=subChild->Right; 
 subChild->Left=child; 
 subChild->Right=n; 
 child->Height=Max( Height(child->Left), Height(child->Right) ) + 1; 
 n->Height=Max( Height(n->Left), Height(n->Right) ) + 1; 
 subChild->Height=Max( child->Height, n->Height ) + 1;
 n = subChild;
}

void DoubleRotateWithRight( Node* & n ) 
{ 
 Node* child, subChild; 
 child=n->Right; 
 subChild=child->Left; 
 child->Left=subChild->Right; 
 n->Right=subChild->Left; 
 subChild->Right=child; 
 subChild->Left=n; 
 child->Height=Max( Height(child->Left), Height(child->Right) ) + 1; 
 n->Height=Max( Height(n->Left), Height(n->Right) ) + 1; 
 subChild->Height=Max( n->Height, child->Height ) + 1; 
 n = subChild;
}



int main(){

}