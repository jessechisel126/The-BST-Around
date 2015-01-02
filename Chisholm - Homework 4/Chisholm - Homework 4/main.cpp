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
 * File Description: This file contains main, the driver of the program.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "BST.h"
#include "StringSplitter.h"
#include "helpers.h"

using namespace std;

int main(int argc, char *argv[])
{
	//vector of filenames, passed in through command line
	vector<string> filenames;

	//loop through arguments passed into main
	for (int i = 1; i < argc; i++)
	{
		//push the argument onto the filenames vector
		filenames.push_back(argv[i]);
	}

	//loop through input files
	for (int file_count = 0; file_count < filenames.size(); file_count++)
	{
		//the name of the current file
		string filename = filenames[file_count];

		//vector of pairs of strings - links between nodes
		vector<pair<string, string>> links;

		////Reading from File

		//open input file
		ifstream infile(filename);

		if (infile.is_open())
		{
			while (infile.good())
			{
				//line from file
				string line;

				//get line from file
				getline(infile, line);

				//if line is valid
				if (isValidInput(line))
				{
					//split line by ':'
					vector<string> fields = StringSplitter::split(line, ":");

					//a single link, formed from split line (as a vector)
					pair<string, string> link = { fields[0], fields[1] };

					//push link onto links vector
					links.push_back(link);
				}
				else
				{
					cout << "Error: the line \"" << line << "\" in \"" << filename << "\" is an invalid input string. Skipping." << endl;
				}
			}

			infile.close();
		}
		else
		{
			cout << "Error: file \"" << filename << "\" not opened correctly. Skipping." << endl;

			continue;
		}

		////Constructing Tree(s)

		//a vector of pointers to BST's
		vector<BST *> trees;

		//the single EmptyNode object used by all BST's
		EmptyNode *empty = new EmptyNode;

		for (int i = 0; i < links.size(); i++)
		{
			////Prep & Setup

			//whether the second element of link is "EMPTY"
			bool link_to_empty = false;

			//if this is a link ending in empty
			if (links[i].second == "EMPTY")
			{
				link_to_empty = true;
			}

			//first value in link (parent value)
			int parent_val = stoi(links[i].first);

			//second value in link (child value)
			int child_val;

			if (!link_to_empty)
			{
				//get child value
				child_val = stoi(links[i].second);
			}

			////Check if parent_val and/or child_val already exist in a tree

			//whether the parent_val was found
			bool parent_found = false;

			//whether the child_val was found
			bool child_found = false;

			//which tree parent_val was found in
			int j = 0;

			//which tree child_val was found in
			int k = 0;

			//while we haven't found the parent_val
			//and there are more trees to check
			while (!parent_found && j < trees.size())
			{
				//try to find parent_val
				parent_found = trees[j]->find(parent_val);

				if (!parent_found)
				{
					//move to next
					j++;
				}
			}


			//while we haven't found the child_val
			//and there are more trees to check
			while (!child_found && k < trees.size() && !link_to_empty)
			{
				//try to find child_val
				child_found = trees[k]->find(child_val);

				if (!child_found)
				{
					//adjust for off-by-one
					k++;
				}
			}

			////Central Logic

			/*
			case 1: parent_val found and child_val found
			j = index of tree where parent_val was found
			k = index of tree where child_val was found

			case 2: parent_val found and child_val not found
			j = index of tree where parent_val was found
			k = trees.size()

			case 3: parent_val not found and child_val found
			j = trees.size()
			k = index of tree where child_val was found

			case 4: parent_val not found and child_val not found
			j = trees.size()
			k = trees.size()

			note: if the child_val was found, it must be a root, otherwise
			there would need to be two nodes in the set of trees
			with the same value, which is against the assignments rules,
			or a node would have two parents, which violates BST rules.

			________________________________________________
			|example:
			|
			|    25         35
			|   /  \     ,    \      new connection: 35:30
			| 20    30         40
			|
			|   |option 1:
			|   |
			|   |    25    35
			|   |   /  \  /  \     invalid state: 30 has two parents
			|   | 20    30    40
			|
			|   |option 2:
			|   |
			|   |    25           35
			|   |   /  \    ,    /  \      invalid state: two instances of 30
			|   | 20    30     30    40
			|
			__________________________________________________

			*/

			if (parent_found)
			{
				if (!link_to_empty)
				{
					if (child_found)
					{
						//the new parent, which is the node of the tree
						//where the parent_val was found
						TreeNode *parent = trees[j]->traverseTo(parent_val);

						//the new child, which is the root of the tree
						//where the child_val was found
						TreeNode *child = trees[k]->getRoot();

						//link the parent to the child
						parent->add(child);

						//copy the pointer to last tree into 
						//newly cleared spot in trees vector
						trees[k] = trees[trees.size() - 1];

						//delete last element of trees array
						trees.pop_back();
					}
					else
					{
						//add the child_val at the parent_val
						trees[j]->addAt(parent_val, child_val);
					}
				}
			}
			else
			{
				//create new tree
				BST *new_tree = new BST(empty);

				//add parent_val as root to tree
				new_tree->addNewRoot(parent_val);

				if (!link_to_empty)
				{
					if (child_found)
					{
						//the new child, which is the root of the tree 
						//where the child_val was found
						TreeNode *child = trees[k]->getRoot();

						//the new parent, which is the root of the new_tree
						TreeNode *parent = new_tree->getRoot();

						//link the parent to the child
						parent->add(child);

						//overwrite old tree with new tree
						trees[k] = new_tree;
					}
					else
					{
						//add the child_val value at the parent_val
						new_tree->addAt(parent_val, child_val);

						//add new tree to trees vector
						trees.push_back(new_tree);
					}
				}
			}
		}

		cout << "The file \"" << filename << "\" contains " << trees.size() << " trees." << endl;
	}

	return 0;
}