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
 * File Description: This file contains a helper function used in the program called isValidInput.
 *
 */

#ifndef HELPERS_H
#define HELPERS_H

#include <string>

#include "StringSplitter.h"

using namespace std;

bool isValidInput(string line)
{
	////Check Colons

	//whether there are the right amount of colons
	bool valid_colons;

	//number of colons in string
	int num_colons = 0;

	//loop through line
	for (int i = 0; i < line.size(); i++)
	{
		//if the current character is a colon
		if (line[i] == ':')
		{
			//increment number of colons
			num_colons++;
		}
	}

	//if there's one colon
	if (num_colons == 1)
	{
		valid_colons = true;
	}
	else
	{
		valid_colons = false;
	}

	////Check Fields Between Colons

	//whether the fields are valid
	bool valid_fields = false;

	//split line by ':'
	vector<string> fields = StringSplitter::split(line, ":");

	if (fields.size() == 2)
	{
		try
		{
			//try to convert first field to an int
			stoi(fields[0]);

			//successful => first field is an int => valid fields so far

			try
			{
				//try to convert second field to an int
				stoi(fields[1]);

				//successful => second field is an int => valid fields
				valid_fields = true;
			}
			catch (...)
			{
				//unsuccessful => second field isn't an int

				//if the second field is the string "EMPTY"
				if (fields[1] == "EMPTY")
				{
					//valid fields
					valid_fields = true;
				}
			}
		}
		catch (...)
		{
		}
	}

	return valid_colons && valid_fields;
}

#endif