#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

template <typename Data>
class BSTNode {
   public:
    /** Constructor.  Initialize a BSTNode with the given Data item,
     *  no parent, and no children.
     */
    BSTNode(const Data &d) : data(d) { left = right = parent = 0; }

    BSTNode<Data> *left;
    BSTNode<Data> *right;
    BSTNode<Data> *parent;
    Data const data;  // the const Data in this node.

    /** Return the successor of this BSTNode in a BST, or 0 if none.
     ** PRECONDITION: this BSTNode is a node in a BST.
     ** POSTCONDITION:  the BST is unchanged.
     ** RETURNS: the BSTNode that is the successor of this BSTNode,
     ** or 0 if there is none.
     */
    // TODO ok
    BSTNode<Data> *successor() {

      if(this->right != NULL) {
        BSTNode<Data> *succ = this->right;
        // If right of child is not NULL, go to the very left of the right
        while(succ->left != NULL) {
          succ = succ->left;
        }
        return succ;
      }

      // This means that it does not have right of child, go up
      else {
        BSTNode<Data> *succ = this;
        while(succ->parent != NULL) {
          if(succ->parent->left == succ)
            return succ->parent;
          else
            succ = succ->parent;
        }
      }

	// just simply return 0 if there is no successor
      return 0;
    }
};

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
ostream &operator<<(ostream &stm, const BSTNode<Data> &n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
