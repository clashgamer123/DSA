#include "rb.h"
using ptr = RedBlackTree::ptr; 
// as the typedef was only inside the class we need classname:: to access it outside
// Hence use 'using' to create an alias.

RedBlackTree::RedBlackTree(){}

const ptr RedBlackTree::getRoot() const
{ 
	return root; 
}

ptr RedBlackTree::getSibling( ptr node ) const
{
	if (node->parent == nullptr)
	{
		return nullptr;
	}
	if (node->parent->right == node)
	{
		return node->parent->left;
	}
	else
	{
		return node->parent->right;
	}
}

ptr RedBlackTree::insert(int data)
{
	ptr newnodePtr = new node(data);
	if (!root) {
		root = newnodePtr;
		root->color = 0; // set root color as black
		return newnodePtr;
	}
	insert(root, newnodePtr);
	return newnodePtr;
}

// auxiliary function to perform RBT insertion of a node
// you may assume start is not nullptr
void RedBlackTree::insert(ptr start, ptr newnode)
{
	ptr x = start ;
	ptr y = nullptr;
	while(x!=nullptr)
	{
		y = x;
		if(newnode->data < x->data)
		{
			x = x->left ;
		}
		else
		{
			x = x->right ;
		}
	}
	if (y->data > newnode->data)
	{
		y->left = newnode ;
		newnode->parent = y;
	}
	else
	{
		y->right = newnode ;
		newnode->parent = y ;
	}

	// Now insertion is complete. We need to deal with red red violation if any. Pass the loc of the new node to fixup.
	fixup(newnode) ;

	return;
}

// Credits to Adrian Schneider
void RedBlackTree::printRBT(ptr start, const std::string& prefix, bool isLeftChild) const
{
	if (!start) return;

	std::cout << prefix;
	std::cout << (isLeftChild ? "|--" : "|__" );
	// print the value of the node
	std::cout << start->data << "(" << start->color << ")" << std::endl;
	// enter the next tree level - left and right branch
	printRBT(start->left, prefix + (isLeftChild ? "│   " : "    "), true);
	printRBT(start->right, prefix + (isLeftChild ? "│   " : "    "), false);
}

// Function performing right rotation
// of the passed node
void RedBlackTree::rightrotate(ptr loc)
{
	ptr par = loc->parent ;

	// *************IMPORTANT*****************
	// If par turns out to be root we need to update root .
	// or else we will get seg faults in next insertions.

	// par->left = loc->right ;
	// par->left->parent = par ;  ****** Potential seg fault as loc->right can be nullptr.
	
	par->left = loc->right ;
	if(par->left != nullptr)
	{
		par->left->parent = par;
	}

	if(par->parent == nullptr)
	{
		loc->parent = nullptr ;
		par->parent = loc ;
		loc->right = par ;
		this->root = loc ;
		return ;
	}

	if (par->parent->right == par)
	{
		par->parent->right = loc ;
	}
	else
	{
		par->parent->left = loc ;
	}

	loc->parent = par->parent ;
	par->parent = loc ;
	loc->right = par ;
	return ;
}

// Function performing left rotation
// of the passed node
void RedBlackTree::leftrotate(ptr loc)
{
	ptr par = loc->parent ;

	par->right = loc->left ;
	if(par->right != nullptr)
	{
		par->right->parent = par ;
	}

	if(par->parent == nullptr)
	{
		loc->parent = nullptr ;
		par->parent = loc;
		loc->left = par;
		this->root = loc ;
		return ;
	}

	if(par->parent->right == par)
	{
		par->parent->right = loc;
	}
	else
	{
		par->parent->left = loc;
	}

	loc->parent = par->parent ;
	par->parent = loc ;
	loc->left = par ;
	return ;
}

// This function fixes violations
// caused by RBT insertion
void RedBlackTree::fixup(ptr loc)
{
	// If loc is root ie red red violation has propogated to root.
	if (loc == this->root)
	{
		root->color = 0;
		return ;
	}

	// if not root and no violation.
	if (loc->parent->color == 0) { return ;}

	// red red violation and red uncle.
	ptr uncle = getSibling(loc->parent) ;
	if (uncle!=nullptr && uncle->color == 1)  // uncle!=nullptr important to prevent segfault.
	{
		uncle->color = 0;
		loc->parent->color = 0;
		uncle->parent->color = 1;
		
		// Now the red error may have propogated hence another fixup.
		fixup(uncle->parent) ;
		return ;
	}
	
	ptr par = loc->parent ;   
	// ptr gpar = uncle->parent ;  ****** Potential segfault as uncle can be nullptr.
	ptr gpar = loc->parent->parent ;


	// Now when uncle is nullptr or black we can end the red-red violation through rotations.
	// Let us divide this into 2 cases one where red_red violation is in left branch and other in right branch.

	// right branch
	if(gpar->right == par)
	{
		// not straight.
		if(par->left == loc)
		{
			rightrotate(loc) ;
			// This will exchange the par and loc positions.
			leftrotate(loc) ;
			gpar->color = 1;
			loc->color = 0;
			return ;
		}

		//  It is straight initially.
		leftrotate(par) ; 
		gpar->color = 1;
		par->color = 0;
		return ;
	}

	// left branch
	else
	{
		if(par->right == loc)
		{
			leftrotate(loc) ;
			rightrotate(loc) ;
			gpar->color = 1;
			loc->color = 0;
			return ;
		}

		rightrotate(par) ;
		gpar->color = 1;
		par->color = 0;
		return ;
	}

	// We are done.
}

// Function to print inorder traversal
// of the fixated tree
void RedBlackTree::inorder(ptr start) const
{
	if (!start)
		return;
	
	inorder(start->left);
	std::cout << start->data << " ";
	inorder(start->right);
}

// driver code
int main()
{
	int n; std :: cin >> n;
	assert (n < 10000 && n >= 0);
	int a[10000];
	RedBlackTree tree;

	for (int i = 0; i < n; i++) {
		std::cin >> a[i];

		// allocating memory to the node and initializing:
		// 1. color as red
		// 2. parent, left and right pointers as NULL
		// 3. data as i-th value in the array

		// calling function that performs rbt insertion of
		// this newly created node
		auto newnodePtr = tree.insert(a[i]);

		// calling function to preserve properties of rb
		// tree
	}

	tree.printRBT(tree.getRoot());

	return 0;
}


////  SUCCESSFUL IMPLEMENTATION.