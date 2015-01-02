/*
 * Programmer: Jesse Chisholm
 * Program: BST Program (HW4)
 * Date Started: 3/15/14
 * Date Completed: 3/17/14
 * Hours Worked: 12+
 * Collaboration: Breifly bounced some ideas off of Ben Windishar-Tatham
 *
 * Program Description: This program reads from an input text file - read in from the command line - with lines of the format of
 *						ParentNode:ChildNode, and constructs Binary Search Trees (BST's) based on this info. After constructing
 *						these trees, the program outputs to the screen how many trees were constructed.
 *						This program makes use of the BST class I developed - as well as the related TreeNode
 *						and EmptyNode classes which I also developed - and used them to construct the trees.
 *
 * File Description: This file contains my BST class, which which makes use of my TreeNode and EmptyNode classes.
 *					 This class was developed solely by me - Jesse Chisholm.
 *
 */

#ifndef BST_H
#define BST_H

#include "TreeNode.h"
#include "EmptyNode.h"

class BST
{
private:
	//this tree's root node
	TreeNode *_root;

	//the single EmptyNode used by this tree
	EmptyNode *_empty;

	//creates a node containing the value 
	//and sets right and left to the EmptyNode
	TreeNode *createNode(int value)
	{
		//create new node containing value
		TreeNode *node = new TreeNode(value);

		//this tree's EmptyNode disguised as a TreeNode for setting purposes
		TreeNode *empty = getEmpty();

		//set right and left to this tree's EmptyNode
		node->setLeft(empty);
		node->setRight(empty);

		return node;
	}
	
public:
	////Default Constructor

	BST(EmptyNode *empty)
	{
		//set this tree's empty node
		setEmpty(empty);

		//set the root to the empty node
		setRoot(empty);
	}

	////Getters and Setters

	EmptyNode *getEmpty()
	{
		return _empty;
	}

	void setEmpty(EmptyNode *empty)
	{
		_empty = empty;
	}

	TreeNode *getRoot()
	{
		return _root;
	}

	void setRoot(TreeNode *root)
	{
		_root = root;
	}

	////Other Methods

	//"smart" setter - makes sure new root points to EmptyNodes
	//!! throws exception if a root already exists !!
	void addNewRoot(int value)
	{
		//if root is non-empty
		if (!getRoot()->isEmpty())
		{
			throw exception("Root already exists - use setRoot.");
		}

		//set root to newly created node containing the value
		setRoot(createNode(value));
	} 

	//search the tree for the value
	bool find(int value)
	{
		//whether the value was found
		bool found = false;

		//the current node in traversal
		TreeNode *curr = getRoot();

		//while we haven't found the node and we can still traverse
		while (!found && !curr->isEmpty())
		{
			//if target value > current's value
			if (value > curr->getValue())
			{
				//set current to right subtree
				curr = curr->getRight();
			}
			//if target value < current's value
			else if (value < curr->getValue())
			{
				//set current to left subtree
				curr = curr->getLeft();
			}
			//if we've found the target value
			else
			{
				found = true;
			}
		}

		return found;
	}

	//add a child to the parent, preserving BST rules
	//!! throws an exception if the parent_val doesn't exist in this tree !!
	void addAt(int parent_val, int child_val)
	{
		//if the parent_val doesn't exist in this tree
		if (!this->find(parent_val))
		{
			cout << "Node containing \"" << parent_val << "\" not found." << endl;
			throw exception("Node not found.");
		}

		//create a new node containing the child_val
		TreeNode *child = createNode(child_val);

		//get the parent node
		TreeNode *parent = traverseTo(parent_val);

		//add the child to the parent
		parent->add(child);
	}
	
	//traverses to the node containing the value, assuming BST rules are intact
	//!! throws an exception if the value doesn't exist in this tree !!
	TreeNode *traverseTo(int value)
	{
		//if the value doesn't exist in this tree
		if (!this->find(value))
		{
			cout << "Node containing \"" << value << "\" not found." << endl;
			throw exception("Node not found.");
		}

		//whether the node has been found
		bool found = false;

		//the current node in traversal (start at root)
		TreeNode *current = getRoot();

		//while we haven't found the node
		while (!found)
		{
			//if search value < current value
			if (value < current->getValue())
			{
				//traverse left subtree
				current = current->getLeft();
			}
			//if search value > current value
			else if ((value > current->getValue()))
			{
				//traverse right subtree
				current = current->getRight();
			}
			//if search value == current value
			else
			{
				//we've traversed to the right node
				found = true;
			}
		}

		//return the current node
		return current;
	}
};

#endif