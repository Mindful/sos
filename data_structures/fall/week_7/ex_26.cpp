//Can't really test these without an AVL tree, so this isn't written to compile

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



void doubleRotateLeftRight( Node* & n) //DoubleRotateWithLeft
{ 
 Node* child, subChild; 
 child=n->Left; 
 subChild=child->Right; 
 child->Right=subChild->Left; 
 n->Left=subChild->Right; 
 subChild->Left=child; 
 subChild->Right=n; 
 child->height=max( height(child->Left), height(child->Right) ) + 1; 
 n->height=max( height(n->Left), height(n->Right) ) + 1; 
 subChild->height=max( child->height, n->height ) + 1;
 n = subChild;
}

void doubleRotateRightLeft( Node* & n ) //DoubleRotateWithRight
{ 
 Node* child, subChild; 
 child=n->Right; 
 subChild=child->Left; 
 child->Left=subChild->Right; 
 n->Right=subChild->Left; 
 subChild->Right=child; 
 subChild->Left=n; 
 child->height=max( height(child->Left), height(child->Right) ) + 1; 
 n->height=max( height(n->Left), height(n->Right) ) + 1; 
 subChild->height=max( n->height, child->height ) + 1; 
 n = subChild;
}



int main(){

}