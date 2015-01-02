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
 * File Description: This file contains my TreeNode class, which is used in my BST class. This class was developed solely by me - Jesse Chisholm.
 *
 */

#ifndef TREENODE_H
#define	TREENODE_H

class TreeNode
{
private:
	int _value;
	TreeNode *_left;
	TreeNode *_right;

public:
	////Constructors

	//Default Constructor
	TreeNode()
	{
		//set left and right to nullptr
		setLeft(nullptr);
		setRight(nullptr);
	}

	//Constructor - value passed in
	TreeNode(int value)
	{
		//set left and right to nullptr
		setLeft(nullptr);
		setRight(nullptr);

		//set the value
		setValue(value);
	}

	////Getters and Setters

	int getValue() const
	{
		return _value;
	}

	void setValue(int value)
	{
		_value = value;
	}

	TreeNode *getLeft() const
	{
		return _left;
	}

	void setLeft(TreeNode *left)
	{
		_left = left;
	}

	TreeNode *getRight() const
	{
		return _right;
	}

	void setRight(TreeNode *right)
	{
		_right = right;
	}

	////Other Methods

	//add a child to this node, preserving BST rules
	void add(TreeNode *child)
	{
		//value of the child
		int child_val = child->getValue();

		//value of this node
		int parent_val = this->getValue();

		//if child's value < parent's value
		if (child_val < parent_val)
		{
			//set the left of the parent to the child
			this->setLeft(child);
		}
		//if child's value >= parent's value
		else
		{
			//set the right of the parent to the child
			this->setRight(child);
		}
	}

	//returns whether the node is an EmptyNode
	virtual bool isEmpty() const
	{
		return false;
	}
};

#endif