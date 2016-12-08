// TopicD.cpp : Defines the entry point for the console application.
//#include "stdafx.h"

#pragma warning( disable : 4290 ) //Added to remove warnings about exception handling

#include <iostream>
#include "BinarySearchTree.h"
#include "Soundtrack.h"
using namespace std;

template<class ItemType>
void printer(ItemType& i);
template<class ItemType>
void printAll(BinarySearchTree<ItemType>& bst);
template<class ItemType>
void printPre(BinarySearchTree<ItemType>& bst);
void getInput(BinarySearchTree<int> &bst);
void getInput(BinarySearchTree<soundtrack> &bst);
void programWait();
void endProgram(const int reason);

int main()
{
	cout << "Create default int tree bst1" << endl;
	BinarySearchTree<int> bst1;

	cout << "Display bst1" << endl;
	printAll(bst1);

	cout << "Read values from input file" << endl;
	cout << "Put release year values into bst1" << endl
		<< endl
		<< endl;
	getInput(bst1);

	cout << "Next, insert following values into bst1 in this order: 1 2 -10 15 -20 0 10" << endl;
	bst1.add(1);
	bst1.add(2);
	bst1.add(-10);
	bst1.add(15);
	bst1.add(-20);
	bst1.add(0);
	bst1.add(10);

	cout << "Display bst1" << endl;
	printAll(bst1);

	cout << "Height of bst1 is " << bst1.getHeight() << endl
		<< endl
		<< "The number of nodes in bst1 is " << bst1.getNumberOfNodes() << endl
		<< endl;

	cout << "Retrieve value using getEntry -10 from the tree:" << endl
		<< endl;
	try
	{
		bst1.getEntry(-10);
		cout << "Found";
	}
	catch (NotFoundException &)
	{
		cout << "Did not find";
	}
	cout << " -10 in tree bst1" << endl
		<< endl;

	cout << "Use contains to see if value 11 is in the tree:" << endl
		<< endl;
	if (bst1.contains(11))
		cout << "Found";
	else
		cout << "Did not find";
	cout << " 11 in bst1" << endl
		<< endl;

	cout << "Create bst2, a pointer to BinarySearchTree, from bst1" << endl;
	BinarySearchTree<int>* bst2 = new BinarySearchTree<int>;
	bst2 = &bst1; //Is this what you meant by "from bst1" ?

	cout << "Display bst2" << endl;
	printAll(*bst2);

	cout << "Height of bst2 is " << bst2->getHeight() << endl
		<< endl
		<< "The number of nodes in bst2 is " << bst2->getNumberOfNodes() << endl
		<< endl;

	cout << "Delete 2014 from bst2" << endl
		<< endl;
	if (bst2->remove(2014))
		cout << "Removed";
	else
		cout << "Did not remove";
	cout << " 2014 from bst2" << endl
		<< endl;

	cout << "Delete 2014 from bst2" << endl
		<< endl;
	if (bst2->remove(2014))
		cout << "Removed";
	else
		cout << "Did not remove";
	cout << " 2014 from bst2" << endl
		<< endl;

	cout << "Display bst2" << endl;
	printAll(*bst2);

	cout << "Height of bst2 is " << bst2->getHeight() << endl
		<< endl
		<< "The number of nodes in bst2 is " << bst2->getNumberOfNodes() << endl
		<< endl;

	cout << "Create bst3 then assign bst2 to bst3" << endl;
	BinarySearchTree<int> bst3 = *bst2;

	cout << "Display bst3" << endl;
	printAll(bst3);

	cout << "Height of bst3 is " << bst3.getHeight() << endl
		<< endl
		<< "The number of nodes in bst3 is " << bst3.getNumberOfNodes() << endl
		<< endl;

	programWait();

	cout << "Create bstST1 which is a binary search tree of soundtrack objects" << endl
		<< endl;
	BinarySearchTree<soundtrack> bstST1; //Assuming this was a typo in your output, and you meant bstST1 not bstT1

	cout << "Put soundtrack records into bstST1" << endl
		<< endl;
	getInput(bstST1);

	cout << "Display bstST1" << endl;
	printAll(bstST1);

	cout << "Height of bstST1 is " << bstST1.getHeight() << endl
		<< endl
		<< "The number of nodes in bstST1 is " << bstST1.getNumberOfNodes() << endl
		<< endl;

	cout << "Create bstST2 from bstST1" << endl
		<< endl;
	BinarySearchTree<soundtrack> bstST2(bstST1);

	cout << "Display bstST2" << endl;
	printAll(bstST2);

	cout << "Height of bstST2 is " << bstST2.getHeight() << endl
		<< endl
		<< "The number of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl
		<< endl;

	programWait();

	soundtrack searchForThis;
	searchForThis.setTitle("Godzilla");
	cout << "Search bstST2 using getEntry for the object that has " << searchForThis.getTitle() << " as a title" << endl
		<< endl;
	try
	{
		bstST2.getEntry(searchForThis);
		cout << "Found";
	}
	catch (NotFoundException &)
	{
		cout << "Did not find";
	}
	cout << " " << searchForThis.getTitle() << " in tree bstST2" << endl
		<< endl
		<< endl;

	searchForThis.setTitle("godzilla");
	cout << "Search bstST2 using getEntry for the object that has " << searchForThis.getTitle() << " as a title" << endl
		<< endl;
	try
	{
		bstST2.getEntry(searchForThis);
		cout << "Found";
	}
	catch (NotFoundException &)
	{
		cout << "Did not find";
	}
	cout << " " << searchForThis.getTitle() << " in tree bstST2" << endl
		<< endl
		<< endl;

	searchForThis.setTitle("");
	searchForThis.setComposer("Elmer Bernstein");
	cout << "Search bstST2 using getEntry for the object that has " << searchForThis.getComposer() << " as a composer" << endl
		<< endl;
	try
	{
		bstST2.getEntry(searchForThis);
		cout << "Found";
	}
	catch (NotFoundException &)
	{
		cout << "Did not find";
	}
	cout << " " << searchForThis.getComposer() << " in tree bstST2" << endl
		<< endl
		<< endl;

	searchForThis.setComposer("");
	searchForThis.setTitle("Much Ado About Nothing");
	cout << "Delete the object from bstST2 with the title \"" << searchForThis.getTitle() << "\", a leaf" << endl
		<< endl;
	if (bstST2.remove(searchForThis))
		cout << "Deleted";
	else
		cout << "Unable to delete";
	cout << " \"" << searchForThis.getTitle() << "\" in tree bstST2" << endl
		<< endl
		<< endl;

	cout << "Display bstST2" << endl;
	printPre(bstST2);

	cout << "Height of bstST2 is " << bstST2.getHeight() << endl
		<< endl
		<< "The number of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl
		<< endl;

	searchForThis.setTitle("Moonfleet");
	cout << "Delete the object from bstST2 with the title \"" << searchForThis.getTitle() << "\", a tree with only a right subtree" << endl
		<< endl;
	if (bstST2.remove(searchForThis))
		cout << "Deleted";
	else
		cout << "Unable to delete";
	cout << " \"" << searchForThis.getTitle() << "\" in tree bstST2" << endl
		<< endl
		<< endl;

	cout << "Display bstST2" << endl;
	printPre(bstST2);

	cout << "Height of bstST2 is " << bstST2.getHeight() << endl
		<< endl
		<< "The number of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl
		<< endl;

	searchForThis.setTitle("Godzilla");
	cout << "Delete the object from bstST2 with the title \"" << searchForThis.getTitle() << "\", a tree with two subtrees whose right child is the inorder successor" << endl
		<< endl;
	if (bstST2.remove(searchForThis))
		cout << "Deleted";
	else
		cout << "Unable to delete";
	cout << " \"" << searchForThis.getTitle() << "\" in tree bstST2" << endl
		<< endl
		<< endl;

	cout << "Display bstST2" << endl;
	printPre(bstST2);

	cout << "Height of bstST2 is " << bstST2.getHeight() << endl
		<< endl
		<< "The number of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl
		<< endl;

	searchForThis.setTitle("King of Hearts");
	cout << "Delete the object from bstST2 with the title \"" << searchForThis.getTitle() << "\", a tree with two children whose right child is NOT the inorder successor" << endl //what?
		<< endl;
	if (bstST2.remove(searchForThis))
		cout << "Deleted";
	else
		cout << "Unable to delete";
	cout << " \"" << searchForThis.getTitle() << "\" in tree bstST2" << endl
		<< endl
		<< endl;

	cout << "Display bstST2" << endl;
	printPre(bstST2);

	cout << "Height of bstST2 is " << bstST2.getHeight() << endl
		<< endl
		<< "The number of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl
		<< endl;

	searchForThis.setTitle("Psycho");
	cout << "Retrieve the object from bstST2 with the title \"" << searchForThis.getTitle() << "\" using contains" << endl //what?
		<< endl;
	if (bstST2.contains(searchForThis))
		cout << "Found";
	else
		cout << "Unable to find";
	cout << " \"" << searchForThis.getTitle() << "\" in tree bstST2" << endl
		<< endl
		<< endl;

	cout << "Display bstST2" << endl;
	printAll(bstST2);

	cout << "Height of bstST2 is " << bstST2.getHeight() << endl
		<< endl
		<< "The number of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl
		<< endl;

	programWait();

	cout << "Create bstST3, a pointer to BinarySearchTree, and then assign bstST2 to it" << endl
		<< endl;
	BinarySearchTree<soundtrack>* bstST3 = new BinarySearchTree<soundtrack>;
	bstST3 = &bstST2;

	cout << "Display bstST3" << endl;
	printAll(*bstST3);

	cout << "Height of bstST3 is " << bstST3->getHeight() << endl
		<< endl
		<< "The number of nodes in bstST3 is " << bstST3->getNumberOfNodes() << endl
		<< endl;

	endProgram(0);
    return 0;
}

template<class ItemType>
void printer(ItemType& i)
{
	cout << i << endl;
}

template<class ItemType>
void printAll(BinarySearchTree<ItemType>& bst)
{
	cout << "PREORDER" << endl;
	bst.preorderTraverse(printer);
	cout << endl
		<< "INORDER" << endl;
	bst.inorderTraverse(printer);
	cout << endl
		<< "POSTORDER" << endl;
	bst.postorderTraverse(printer);
	cout << endl
		<< endl;
}

template<class ItemType>
void printPre(BinarySearchTree<ItemType>& bst)
{
	cout << "PREORDER" << endl;
	bst.preorderTraverse(printer);
	cout << endl
		<< endl;
}

//overloaded this for when using just the release year, and the whole soundtrack
void getInput(BinarySearchTree<int> &bst)
{
	ifstream inFile;
	string name { "Topic D Soundtrack.txt" };
	inFile.clear();
	inFile.open(name);
	if (!inFile)
	{
		cout << "Error opening " << name << endl
			<< "Please select another file." << endl
			<< endl;
		do
		{
			cout << "Enter input file name:  ";
			cin >> name;
			inFile.clear();
			inFile.open(name.c_str());

			if (!inFile)
			{
				cout << name << " cannot be opened.\n";
			}
		} while (!inFile);
		cin.ignore();
	}
	
	while (getline(inFile, name))//!empty
	{
		//add the last 4 char in the getline string to bst
		name = name; //broke this up for easier to read code
		bst.add(std::stoi(name.substr(112, 4))); //24+40+16+24+8=112
	}

	inFile.close();
}

void getInput(BinarySearchTree<soundtrack> &bst)
{
	ifstream inFile;
	string name{ "Topic D Soundtrack.txt" };
	inFile.clear();
	inFile.open(name);
	if (!inFile)
	{
		cout << "Error opening " << name << endl
			<< "Please select another file." << endl
			<< endl;
		do
		{
			cout << "Enter input file name:  ";
			cin >> name;
			inFile.clear();
			inFile.open(name.c_str());

			if (!inFile)
			{
				cout << name << " cannot be opened.\n";
			}
		} while (!inFile);
		cin.ignore();
	}

	soundtrack record;
	while (!inFile.eof())
	{
		inFile >> record;
		bst.add(record);
	}

	inFile.close();
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
}//end endProgram