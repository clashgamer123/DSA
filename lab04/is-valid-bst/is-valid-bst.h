#include "tree.h"

/**
 * @brief Check if a binary tree is a valid binary search tree
 * 
 * @param root The root of the binary tree
 * @return true If the binary tree is a valid binary search tree
 * @return false If the binary tree is not a valid binary search tree
 *
 * Your task is to check if the tree indexing all the values of type T is a
 * valid binary search tree, which implies that for each node in the tree,
 * all the values in its left subtree are less than the value of that node, and
 * all the values in its right subtree are greater than the value of that node.
 *
 * You can add helper functions or data structures, but you should not modify
 * the existing function signature. Note that this requiress knowledge about
 * the concpet of smart pointers in C++.
 *
 * Lastly, do not add `using namespace std;` as it is a bad practice.
 * The full problem involves the above task AND the task in the file
 * "employee.h". You should complete both tasks.
 */

template <std::totally_ordered T>
bool is_valid_bst(std::shared_ptr<struct node_t<T>> root) 
{
    if (root == nullptr) { return true ;}
    bool b1 ; // checks if right key is greater.
    bool b2 ; // checks if left key is smaller.
    bool b3 ; // checks if right sub tree is ordered.
    bool b4 ; // checks if left sub tree is ordered .

    b3 = is_valid_bst(root->right_child) ;
    b4 = is_valid_bst(root->left_child) ;

    // for b1 and b2.
    if (root->right_child == nullptr) { b1 = true ;}
    else { b1 = (((root->right_child)->value)>=root->value) ? (true) : false ;}

    if (root->left_child == nullptr) { b2 = true ;}
    else { b2 = (((root->left_child)->value)<=root->value) ? (true) : false ;}

    return (b1 && b2 && b3 && b4) ;
}
