#include "tree.h"

// Function which returns lca node of given nodes 'a' and 'b'
TreeNode* TREE::findlca(TreeNode* a, TreeNode* b) 
{
  if (a == this->root) { return a ;}
  if (b == this->root) { return b ;}

  TreeNode* x = a ;
  TreeNode* y = b ; // Lets use x and y and preserve a and b.
  
  // The idea is that we first check whether a is an ancestor of b , b is an ancestor of a.
  // In case any of the above is true we return it.
  // Else we update both x and y to their parents and do the check.
  
  while(true)
  {
    // a as ancestor of b.
    while(y!=a && y!=NULL)
    {
      y = y->parent ;
    }
    if (y == a) { return a ;}
    y = b ;
    
    // b as ancestor of a .
    while( x!= b && x!=NULL)
    {
      x = x->parent ;
    }
    if (x == b) { return b ;}
    x = a ;

    a = a->parent ;
    b = b->parent ;
  }
  return NULL ;
}