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
 * File Description: This file contains my EmptyNode class, which is used in my BST class. This class was developed solely by me - Jesse Chisholm.
 *
 */

#ifndef EMPTYNODE_H
#define EMPTYNODE_H

#include "TreeNode.h"

using namespace std;

class EmptyNode : public TreeNode
{
public:	
	//Default Constructor
	EmptyNode()
	{
	}

	////Other Methods

	//returns whether the node is an EmptyNode
	virtual bool isEmpty() const
	{
		return true;
	}
};

#endif