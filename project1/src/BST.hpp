#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
   protected:
    /** Pointer to the root of this BST, or 0 if the BST is empty */
    //BSTNode<Data> *root;

    /** Number of Data items stored in this BST. */
    unsigned int isize;

    /** Height of this BST. */
    unsigned int iheight;

   public:
BSTNode<Data> *root;
    /** define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
        Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(0) {}

    /** Default destructor.
        Delete every node in this BST.
     */
    // TODO double checked
    virtual ~BST() {
    	deleteAll(root);
    	isize=0;
    	iheight=0;
    }

    /** Given a reference to a Data item, insert a copy of it in this BST.
     *  Return  true if the item was added to this BST
     *  as a result of this call to insert,
     *  false if an item equal to this one was already in this BST.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=)  For the reasoning
     *  behind this, see the assignment writeup.
     */
    // TODO double checked
    virtual bool insert(const Data &item) {
	// The variable to hold the temp high of the tree
	int cur_height=0;

	// Create one cur pointer to point to root and also the parent
	BSTNode<Data> *cur=root;
	BSTNode<Data> *parent=nullptr;

	// If the cur is NULL, then it must be the root pointer, create a new
	// node for root
	if(cur == NULL) {
		cur = new BSTNode<Data> (item);
		cur->left = NULL;
		cur->right = NULL;
		root = cur;
		isize++;
		cur_height++;
		iheight = cur_height;
		return true;
	}

	// We Iterate the tree to find the right spot for the new node
	// also return false if the node is already exists
	while(cur){
		parent=cur;
		cur_height++;

		// check the postion of the new element
		if(cur->data < item){cur=cur->right;}
		else if(item < cur->data){cur=cur->left;}
		else return false;
	}

	// Once we find the correct of the new node, we create a new node
	cur=new BSTNode<Data> (item);
	cur->parent=parent;

	// Connect the left and right node between the parent and left right node
	if(cur->parent!=NULL){
		if(cur->parent->data < item){
			cur->parent->right=cur;
		}else{
			cur->parent->left=cur;
		}
	}
	cur->left = NULL;
	cur->right = NULL;
	isize++;
	iheight=(cur_height+1) < iheight ? iheight : cur_height+1;
	return true;

    }

   /** Find a Data item in the BST.
     *  Return an iterator pointing to the item, or pointing past
     *  the last node in the BST if not found.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=).  For the reasoning
     *  behind this, see the assignment writeup.
     */
    // TODO
    virtual iterator find(const Data &item) const {

      // First we use a pointer to point to the root
      BSTNode<Data> *cur = root;

	// Iterate the tree to see if we can find the element
      while(cur != NULL) {

        if(cur->data < item)
            cur = cur->right;

        else if(item < cur->data)
          cur = cur->left;
		
		// Found the element
	      else
	        return typename BST<Data>::iterator(cur);
      }

	// Return a empty Iterator if the element is not found in the tree
     
      return typename BST<Data>::iterator(0);

    }

    /** Return the number of items currently in the BST.
     */
    // TODO double checked
    unsigned int size() const {return isize;}

    /** Return the height of the BST.
     */
    // TODO double checked
    unsigned int height() const {return iheight;}

    /** Return true if the BST is empty, else false.
     */
    // TODO double checked
    bool empty() const {
	// We simply just check if the tree has root, if it has root
	// then it's not empty
	     if(root != NULL)
          return false;
	     else
          return true;
    }
    /** Return an iterator pointing to the first item in the BST (not the root).
     */
    // TODO
    iterator begin() const {
      return typename BST<Data>::iterator(first(root));
    }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** Perform an inorder traversal of this BST.
     */
    void inorder() const { inorder(root); }

   private:
    /** Recursive inorder traversal 'helper' function */

    /** Inorder traverse BST, print out the data of each node in ascending
       order. Implementing inorder and deleteAll base on the pseudo code is an
       easy way to get started.
     */
    // TODO double checked
    void inorder(BSTNode<Data> *n) const {
        /* Pseudo Code:
          if current node is null: return;
          recursively traverse left sub-tree
          print current node data
          recursively traverse right sub-tree
        */
    	if(n == NULL)
        return;

    	inorder(n->left);
    	cout << n->data << endl;
    	inorder(n->right);
    }

    /** Find the first element of the BST
     */
    static BSTNode<Data> *first(BSTNode<Data> *curr) {
        if (curr == 0) return 0;
        while (curr->left != 0) curr = curr->left;
        return curr;
    }

    /** do a postorder traversal, deleting nodes
     */
    // TODO double checked
    static void deleteAll(BSTNode<Data> *n) {
        /* Pseudo Code:
          if current node is null: return;
          recursively delete left sub-tree
          recursively delete right sub-tree
          delete current node
        */
      if(n == NULL)
         return;

      deleteAll(n->left);
      deleteAll(n->right);

      //Delete the node
      delete(n);
    }
};

#endif  // BST_HPP
