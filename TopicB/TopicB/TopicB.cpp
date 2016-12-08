// TopicA.cpp : Defines the entry point for the console application.
//#include "stdafx.h"

#pragma warning( disable: 4290 )  // disable warnings about the use of throw in function headers

#include <string>
#include <iostream>
#include <fstream>
#include "LinkedQueue.h"
#include "LinkedStack.h"
using namespace std;

/*
* Project: TopicB
* Class:   CS M20
* Student: Rice, Sammuel D.
* Edited:  20160914
* Due on:  20160914
* Version: 1.0 (History: 0.1)
* VCS:     Not hosted atm
* Status:
	ExtraCredit:	Yes
	Complete:		Yes
	Compiles:		Yes
	Errors:			No
	Created via:	VisualStudio 2015
*/

/**
1>------ Build started: Project: TopicB, Configuration: Debug Win32 ------
1>  TopicB.cpp
1>  TopicB.vcxproj -> C:\Users\Samous\Source\Repos\CS-M20-OODataStructure-Work\TopicB\Debug\TopicB.exe
1>  TopicB.vcxproj -> C:\Users\Samous\Source\Repos\CS-M20-OODataStructure-Work\TopicB\Debug\TopicB.pdb (Full PDB)
========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========
**/

string displayQueue(LinkedQueue<string> &aQueue);
bool addToStack(LinkedStack<char> &aStack, const string line);
string displayStack(LinkedStack<char> &aStack);
bool isValid(const string &aString);
void endProgram(const int reason);

int main()
{
	/*const*/ string fileName{ "TopicB.txt" };
	/*Added this section after looking at Prof.'s example .exe*/
	cout << "Enter input file name: ";
	cin >> fileName;
	/*The instructions state: The input file is TopicB.txt - which implies
	  there is only one input file, and it will always be called TopicB.txt,
	  but after looking at the .exe I changed the program to allow user input*/
	cout << "Searching for input file: " << fileName << endl;
	ifstream inFile;
	inFile.open(fileName, ios::in);
	if (!inFile)
	{
		cout << "ERROR_1 :: Unable to open file" << endl;
		endProgram(1); // terminate with error
	}

	cout << "File opened successfully." << endl
		 << endl
		 << "Reading contents into LinkedQueue lq." << endl;

	string line{ "" };
	LinkedQueue<string> lq;
	while (!inFile.eof())
	{
		getline(inFile, line);
		lq.enqueue(line);
	}
	if (lq.isEmpty())
	{
		cout << "ERROR_2 :: Queue is empty. Either the file was empty or could not be read!" << endl;
		endProgram(2); // terminate with error
	}
	
	cout << "Contents read into lq." << endl
		 << endl
		 << "Creating lq1 as a copy of lq." << endl;
	LinkedQueue<string> lq1(lq);

	cout << "Displaying contents of lq1 (the copy):" << endl
		 << endl;
	cout << displayQueue(lq1) << endl
		 << endl;

	cout << "Attempting to Peek at lq1 (now empty)..." << endl;
	try 
	{
		lq1.peekFront();
	}
	catch (PrecondViolatedExcept& e)
	{
		cerr << e.what();
		cout << endl;
		//endProgram(3); // terminate with error
	}
	cout << endl; //extra spacer
	
	cout << "Assigning lq to lq1." << endl;
	lq1 = lq;
	cout << "Displaying contents of lq1 (the copy):" << endl
		 << endl;
	cout << displayQueue(lq1) << endl
		 << endl;

	cout << "Placing the first line (string) into a stack (of chars) called ls1." << endl;
	LinkedStack<char> ls1;
	if (!addToStack(ls1, lq.peekFront()))
	{
		//Failed!
		cout << "ERROR_3 :: AddToStack() Failed!" << endl;
		endProgram(3); // terminate with error
	}

	cout << "Creating copy of ls1 called ls2." << endl;
	LinkedStack<char> ls2(ls1);
	cout << "Displaying contents of ls2 (the copy):" << endl
		 << endl;
	cout << displayStack(ls2) << endl
		 << endl;

	cout << "Assigning ls1 to ls2 (ls2=ls1;)." << endl;
	ls2=ls1;
	cout << "Displaying contents of ls2 (the copy):" << endl
		 << endl;
	cout << displayStack(ls2) << endl
		 << endl;

	/****Begin Condition Checking****/
	cout << endl
		 << endl
		 << "Begin expression checking:" << endl
		 << endl
		 << endl;
	while (!lq.isEmpty())
	{
		cout << "The string:   " << lq.peekFront() << "   is " << ((isValid(lq.peekFront())) ? "Valid" : "Invalid.") << endl;
		lq.dequeue();
	}

	endProgram(0);
    return 0;
}// end main

string displayQueue(LinkedQueue<string> &aQueue)
{
	string output { "" };
	while (!aQueue.isEmpty())
	{
		output = output + aQueue.peekFront() + "\n";
		aQueue.dequeue();
	}
	return output;
}//end displayQueue

bool addToStack(LinkedStack<char> &aStack, const string line)
{
	//cout << line.length() << endl;
	for (int i = line.length()-1; i >= 0; i--)
	{
	//cout << i << "::" << line.at(i) << endl;
		if (!aStack.push(line.at(i)))
			return false; //Failed
	}
	return true;
}//end addToStack

string displayStack(LinkedStack<char> &aStack)
{
	string output{ "" };
	while (!aStack.isEmpty())
	{
		//cout << "::" << aStack.peek() << endl;
		output.append(1, aStack.peek());
		aStack.pop();
	}
	return output;
}//end displayStack

bool isValid(const string &aString)
{
	LinkedStack<char> aStack;
	//cout << "aStack created." << endl;
	for (size_t i = 0; i < aString.length(); i++) //size_t is an unsigned int datatype, and is used (b/c it should always be >=0) to prevent warning C4018: '<': signed/unsigned mismatch
	{
		//cout << "for loop: " << i << endl;
		/* char list:
		( = 40
		{ = 123
		[ = 91
		" = 34
		' = 39
		) = 41
		} = 125
		] = 93
		\ = 92
		*/
		if (aString.at(i) == 92) //Extra Credit portion
			i++; //Ignore that char, and the next one
		else if (aString.at(i) == 40 || aString.at(i) == 123 || aString.at(i) == 91)
		{
			//( { or [
			//cout << "( found" << endl;
			aStack.push(aString.at(i));
		}
		else if (aString.at(i) == 34 || aString.at(i) == 39)
		{
			//" , '
			//cout << "\" found" << endl; 
			if (aStack.isEmpty()) //<--- Is there a better way to do this? I don't want to write a seperate section for the case where it's empty, but I don't want to check EVERY for loop to see if its empty either... is Try/Catch more efficient?
				aStack.push(aString.at(i));
			else if (aStack.peek() == aString.at(i))
			{
				//last item was a " or '
				//cout << "After previous \"" << endl;
				aStack.pop();
			}
			else
			{
				//Last item was anything else
				//cout << "New \"" << endl;
				aStack.push(aString.at(i));
			}
		}
		else if (aString.at(i) == 41)
		{
			//)
			//cout << ") found" << endl;
			if (aStack.isEmpty())
				aStack.push(aString.at(i));
			else if (aStack.peek() == 40)
			{
				//Last item was (
				//cout << "After (" << endl;
				aStack.pop();
			}
			else
			{
				//Last item was not (
				//cout << "Close ) prior to (" << endl;
				//Test Failed!
				return false;
			}//end if
		}
		else if (aString.at(i) == 125)
		{
			//}
			//cout << "} found" << endl;
			if (aStack.isEmpty())
				aStack.push(aString.at(i));
			else if (aStack.peek() == 123)
			{
				//Last item was {
				//cout << "After {" << endl;
				aStack.pop();
			}
			else
			{
				//Last item was not {
				//cout << "Close } prior to {" << endl;
				//Test Failed!
				return false;
			}//end if
		}
		else if (aString.at(i) == 93)
		{
			//]
			//cout << "] found" << endl;
			if (aStack.isEmpty())
				aStack.push(aString.at(i));
			else if (aStack.peek() == 91)
			{
				//Last item was [
				//cout << "After [" << endl;
				aStack.pop();
			}
			else
			{
				//Last item was not [
				//cout << "Close ] prior to [" << endl;
				//Test Failed!
				return false;
			}//end if
		}//end if
	}//end for
	//cout << "End for" << endl;
	if (!aStack.isEmpty())
		return false;
	return true;
}

void endProgram(const int reason)
{
	//Inspired by the same named function written by Prof.
	//It's functionally the exact same function
	cout << endl
		 << endl
		 << "Program ending ";
	cout << ((reason == 0) ? "successfully." : "unexpectantly due to error(s)!") << endl;
	cout << endl
		 << "Press Enter to end";
	cin.ignore();
	exit(reason);
}//end endProgram