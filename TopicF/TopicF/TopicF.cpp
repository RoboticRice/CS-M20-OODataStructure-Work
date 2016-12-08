// TopicE.cpp : Defines the entry point for the console application.
// #include "stdafx.h"

/*
* Project: TopicF
* Class:   CS M20
* Student: Rice, Sammuel D.
* Edited:  20161114
* Due on:  20161116
* Version: 1.0 (History: 0.1)
* VCS:     Not hosted atm
* Status:
Complete:		Yes
Compiles:		Yes
Errors:			No
Created via:	VisualStudio 2015
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "AVL.h"
#include "Soundtrack.h"
using namespace std;

bool readFile(vector<soundtrack> &);
void trailingBlanks(string & val);
template<class TYPE>
void printer(TYPE& i);
void print1950s(soundtrack& i);
void programWait();
void endProgram(const int reason);

int main()
{
	//This was taken from the Topic D Source Code, and modified for this project
	vector<soundtrack> trackVec;
	cout << "\n\nReading values from input file..." << endl;
	if (!readFile(trackVec))
	{
		cout << "\n\n\nNo values in input file.";
		cin.ignore();
		endProgram(1);  // some non-zero value
	}

	//I personally like this so I know what was actually accepted, but I removed it since it's not in the sample exe
	//cout << "\nDisplaying content read from file:" << endl;
	//for (size_t i{ 0 }; i < trackVec.size(); ++i)
	//	cout << trackVec.at(i);
	//cout << endl << endl;

	//Start of my code
	cout << endl << "Creating an AVL, and populating it with input content..." << endl;
	AvlTree<soundtrack> myAvlTree;
	for (size_t i{ 0 }; i < trackVec.size(); ++i)
		myAvlTree.AVL_Insert(trackVec.at(i));
	
	//myAvlTree.AVL_Print(); //Do you not like their print code? I noticed you didn't use it in the sample exe
	programWait();

	soundtrack key;
	key.setLabel("FSM");
	key.setCat_Num("Box 03 Disc 8");
	cout << "Get item with key \"" << key.getLabel() << " " << key.getCat_Num() << "\":" << endl;
	if (myAvlTree.AVL_Retrieve(key, key))
		cout << "Found item with key in AVL." << endl;
	else 
		cout << "Did NOT find any items with key in AVL." << endl;
	cout << endl << endl;

	key.setCat_Num("Box 07 Disc 8");
	cout << "Get item with key \"" << key.getLabel() << " " << key.getCat_Num() << "\":" << endl;
	if (myAvlTree.AVL_Retrieve(key, key))
		cout << "Found item with key in AVL." << endl;
	else
		cout << "Did NOT find any items with key in AVL." << endl;
	cout << endl;

	programWait();

	cout << "Listing of all items in the tree: (There are " << myAvlTree.AVL_Count() << " items in the table)" << endl << endl;
	//myAvlTree.AVL_Print();
	myAvlTree.AVL_Traverse(printer);

	programWait();

	cout << "Listing of all recordings from the 1950s:" << endl << endl;
	//myAvlTree.AVL_Print();
	myAvlTree.AVL_Traverse(print1950s);

	programWait();

	//key.setLabel("FSM"); //already set
	key.setCat_Num("V8N11");
	cout << "Get item with key \"" << key.getLabel() << " " << key.getCat_Num() << "\":" << endl;
	if (myAvlTree.AVL_Retrieve(key, key) && myAvlTree.AVL_Delete(key))
		cout << "Found following item with key in AVL, and deleting:" << endl << key << endl;
	else
		cout << "Did NOT find any items with key in AVL." << endl;
	//This is done in two steps: 1) Find the item, 2) Delete the item. The steps are seperate b/c delete does not return the soundtrack item being deleted, but find does.
	cout << endl << endl;

	//key.setLabel("FSM"); //already set
	//key.setCat_Num("V8N11"); //already set
	cout << "Get item with key \"" << key.getLabel() << " " << key.getCat_Num() << "\":" << endl;
	if (myAvlTree.AVL_Retrieve(key, key) && myAvlTree.AVL_Delete(key))
		cout << "Found following item with key in AVL, and deleting:" << endl << key << endl;
	else
		cout << "Did NOT find any items with key in AVL." << endl;
	//This is done in two steps: 1) Find the item, 2) Delete the item. The steps are seperate b/c delete does not return the soundtrack item being deleted, but find does.
	cout << endl;

	programWait();

	cout << "Listing of all items in the tree: (There are " << myAvlTree.AVL_Count() << " items in the table)" << endl << endl;
	//myAvlTree.AVL_Print();
	myAvlTree.AVL_Traverse(printer);

	endProgram(0);
    return 0;
} // end main

bool readFile(vector<soundtrack> & trackVec)
{
	bool rc = true;

	string filename("Topic F Soundtrack.txt");
	ifstream inFile(filename);

	while (!inFile)
	{
		cout << filename << " cannot be opened.  Enter another file name -->  ";
		cin >> filename;
		cin.ignore();  // get rid of newline after filename entry
		inFile.clear();
		inFile.open(filename);
	}

	soundtrack st;
	string buf, sub;
	char *endPtr;  // for strtol

	bool duplicate = false;
	while (!inFile.eof())
	{
		st.clear();

		getline(inFile, buf);

		sub = buf.substr(0, 24);
		trailingBlanks(sub);
		st.setComposer(sub);

		sub = buf.substr(24, 40);
		trailingBlanks(sub);
		st.setTitle(sub);

		sub = buf.substr(64, 16);
		trailingBlanks(sub);
		st.setLabel(sub);

		sub = buf.substr(80, 24);
		trailingBlanks(sub);
		st.setCat_Num(sub);

		sub = buf.substr(104, 8);
		trailingBlanks(sub);
		st.setRecorded(sub);

		sub = buf.substr(112, 4);
		st.setReleased(static_cast<int>(strtol(sub.c_str(), &endPtr, 10)));

		if (st.getReleased() == 0)
			cout << "Error: \"" << sub << "\" is not a valid number for Released Year. The following input is being ignored:" << endl << st << endl;
		else
		{
			duplicate = false;
			size_t i{ 0 };
			while (!duplicate && i < trackVec.size())
			{
				if (trackVec.at(i) == st)
					duplicate = true;
				i++;
			}
			//for (size_t i{ 0 }; i < trackVec.size(); ++i)
				//duplicate = duplicate || ((trackVec.at(i)==st) ? true : false); //This does seem inefficient...
			if (!duplicate)
				trackVec.push_back(st);
			else
				cout << "Error: The following input is a duplicate and will be ignored:" << endl << st << endl;
		}
	}

	if (trackVec.empty())
		rc = false;

	inFile.close();

	return rc;
}

void trailingBlanks(string & val)
{
	int i;

	for (i = static_cast<int>(val.length()) - 1; isspace(val[i]); --i)  // What assumption is being made here?
		;

	val.erase(i + 1);
}

template<class TYPE>
void printer(TYPE& i)
{
	cout << i << endl;
}

void print1950s(soundtrack& i) //specific for 1950s
{
	string item = i.getRecorded();
	if (item.empty() || item.length() < 4)
		;
	else if (item.at(0) == '1' &&  item.at(1) == '9' && item.at(2) == '5')
		cout << i << endl;
}

void programWait()
{
	cout << endl
		<< endl
		<< "***************************************************************";
	cout << endl
		<< "Press Enter to continue --> ";
	cin.ignore();
	cout << endl
		<< endl;
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
} // end endProgram