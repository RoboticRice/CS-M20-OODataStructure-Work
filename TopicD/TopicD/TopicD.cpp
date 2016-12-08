/***************************************************************************************
	Topic D Project - Binary Trees
	CS M20 
	Martin Chetlen
*************************************************************************************/

#pragma warning( disable: 4290 )  // disable Visual Studio warnings about the use of throw in function headers

#include <iostream>
#include <fstream>
#include <string>
#include <new>
#include <vector>
#include <cstdlib>  // for strtol
#include <memory>

using namespace std;

#include "BinarySearchTree.h"
#include "Soundtrack.h"

bool readFile( vector<soundtrack> & );
void trailingBlanks(string & val);

// Used by tree traversals
template<class ItemType>
void display( ItemType val );


int main()
{
	try
	{
		cout << "Create default int tree bst1" << endl;
		BinarySearchTree<int>  bst1;

		cout << "Display bst1\nPreorder:" << endl;
		bst1.preorderTraverse( display );
		cout << "\nInorder:" << endl;
		bst1.inorderTraverse( display );
		cout << "\nPostorder:" << endl;
		bst1.postorderTraverse( display );
		
		vector<soundtrack> trackVec;

		cout << "\n\nRead values from input file" << endl;
		if (!readFile(trackVec))
		{
			cout << "\n\n\nNo values in input file.  Program Ending\nPress Enter to end -->  ";
			cin.ignore();
			return 2;  // some non-zero value
		}

		cout << "Put release year values into bst1" << endl;
		for (size_t i{ 0 }; i < trackVec.size(); ++i)
			bst1.add(trackVec[i].getReleased());
		

		cout << "\n\n Next, insert following values into bst1 in this order: 1 2 -10 15 -20 0 10" << endl;
		bst1.add( 1 );
		bst1.add( 2 );
		bst1.add( -10 );
		bst1.add( 15 );
		bst1.add( -20 );
		bst1.add( 0 );
		bst1.add( 10 );

		cout << "Display bst1\nPreorder:" << endl;
		bst1.preorderTraverse( display );
		cout << "\nInorder:" << endl;
		bst1.inorderTraverse( display );
		cout << "\nPostorder:" << endl;
		bst1.postorderTraverse( display );

		cout << "\nHeight of bst1 is " << bst1.getHeight() << endl;
		cout << "\nNumber of nodes in bst1 is " << bst1.getNumberOfNodes() << endl;

		int val;
		try
		{
			val = -10;
			cout << "\nRetrieve value using getEntry " << val << " from the tree:" << endl;
			bst1.getEntry( val );
			cout << "\n Found " << val << " in tree bst1" << endl;
		}
		catch( NotFoundException & nfe1 )
		{
			cout << nfe1.what() << endl;;
		}

		val = 11;
		cout << "\nUse contains to see if value " <<  val << " is in the tree:" << endl;
		if ( bst1.contains( val ) )
			cout << endl << val << " IS found in bst1" << endl;
		else
			cout << endl << val << " NOT found in bst1" << endl;


		cout << "\nCreate bst2, a pointer to BinarySearchTree, from bst1\n";
		// BinarySearchTree<int> *bst2 = new BinarySearchTree<int>( bst1 );
		unique_ptr<BinarySearchTree<int>> bst2 = make_unique<BinarySearchTree<int>> (bst1);
		
		cout << "Display bst2\nPreorder:" << endl;
		bst2->preorderTraverse( display );
		cout << "\nInorder:" << endl;
		bst2->inorderTraverse( display );
		cout << "\nPostorder:" << endl;
		bst2->postorderTraverse( display );

		cout << "\nHeight of bst2 is " << bst2->getHeight() << endl;
		cout << "\nNumber of nodes in bst2 is " << bst2->getNumberOfNodes() << endl;

		val = 2014;
		cout << "\nDelete " << val << " from bst2 " << endl;
	
		if ( bst2->remove( val ) )
			cout << "\n" << val << " deleted from bst2" << endl;
		else
			cout << "\n" << val << " NOT deleted from bst2" << endl;

		cout << "\nDelete " << val << " from bst2 " << endl;
		
		val = 2014;
		if ( bst2->remove( val ) )
			cout << "\n" << val << " deleted from bst2" << endl;
		else
			cout << "\n" << val << " NOT deleted from bst2" << endl;

		cout << "Display bst2\nPreorder:" << endl;
		bst2->preorderTraverse( display );
		cout << "\nInorder:" << endl;
		bst2->inorderTraverse( display );
		cout << "\nPostorder:" << endl;
		bst2->postorderTraverse( display );

		cout << "\nHeight of bst2 is " << bst2->getHeight() << endl;
		cout << "\nNumber of nodes in bst2 is " << bst2->getNumberOfNodes() << endl;

		cout << "\nCreate bst3 then assign bst2 to bst3\n";
		BinarySearchTree<int> bst3;
		bst3 = *bst2;

		cout << "Display bst3\nPreorder:" << endl;
		bst3.preorderTraverse( display );
		cout << "\nInorder:" << endl;
		bst3.inorderTraverse( display );
		cout << "\nPostorder:" << endl;
		bst3.postorderTraverse( display );

		cout << "\nHeight of bst3 is " << bst3.getHeight() << endl;
		cout << "\nNumber of nodes in bst3 is " << bst3.getNumberOfNodes() << endl;

		bst2.reset();


		cout << "\n\n***************************************************************\nPress Enter to continue --> ";
		cin.get();

		cout << "\n\nCreate bstT1 which is a binary search tree of soundtrack objects\n" << endl;
		BinarySearchTree<soundtrack> bstST1;

		cout << "\n\nPut soundtrack records into bstST1" << endl;

		for (size_t i{ 0 }; i < trackVec.size(); ++i)
			bstST1.add(trackVec[i]);

		cout << "\n\nDisplay bstST1\nPreorder:" << endl;
		bstST1.preorderTraverse( display );
		cout << "\nInorder:" << endl;
		bstST1.inorderTraverse( display );
		cout << "\nPostorder:" << endl;
		bstST1.postorderTraverse( display );

		cout << "\nHeight of bstST1 is " << bstST1.getHeight() << endl;
		cout << "\nNumber of nodes in bstST1 is " << bstST1.getNumberOfNodes() << endl;


		cout << "\nCreate bstST2 from bstST1" << endl;
		BinarySearchTree<soundtrack> bstST2( bstST1 );

		cout << "\n\nDisplay bstST2\nPreorder:" << endl;
		bstST2.preorderTraverse( display );
		cout << "\nInorder:" << endl;
		bstST2.inorderTraverse( display );
		cout << "\nPostorder:" << endl;
		bstST2.postorderTraverse( display );

		cout << "\nHeight of bstST2 is " << bstST2.getHeight() << endl;
		cout << "\nNumber of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl;

		cout << "\n\n***************************************************************\nPress Enter to continue --> ";
		cin.get();

		soundtrack st1( "", "Godzilla" );


		cout << "\n\nSearch bstST2 using getEntry for the object that has Godzilla as a title\n" << endl;
		try
		{
			st1 = bstST2.getEntry( st1 );
			cout << "\n Found.  The object consists of " << st1 << endl;
		}
		catch( NotFoundException & nfe1 )
		{
			cout << nfe1.what() << endl;
		}
		
		st1.clear();
		st1.setTitle( "godzilla" );

		cout << "\nSearch bstST2 using getEntry for the object that has godzilla as a title\n" << endl;
		try
		{
			st1 = bstST2.getEntry( st1 );
			cout << "\n Found.  The object consists of " << st1 << endl;
		}
		catch( NotFoundException & nfe1 )
		{
			cout << nfe1.what() << endl;
		}

		st1.clear();
		st1.setComposer("Elmer Bernstein");

		cout << "\n\n\nSearch bstST2 using getEntry for the object that has Elmer Bernstein as the composer\n" << endl;
		try
		{
			st1 = bstST2.getEntry(st1);
			cout << "\n Found.  The object consists of " << st1 << endl;
		}
		catch (NotFoundException & nfe1)
		{
			cout << nfe1.what() << endl;
		}


		cout << "\n\n\nDelete the object from bstST2 with the title Much Ado About Nothing, a leaf\n" << endl;
		st1.clear();
		st1.setTitle("Much Ado About Nothing");
		
		if ( bstST2.remove( st1 ) )
			cout << "\n\"" << st1.getTitle() << "\" deleted from bstST2" << endl;
		else
			cout << "\n\"" << st1.getTitle() << "\" NOT deleted from bstST2" << endl;

		cout << "\n\n***************************************************************\nPress Enter to continue --> ";
		cin.get();
		
		cout << "\n\nDisplay bstST2\nPreorder:" << endl;
		bstST2.preorderTraverse( display );
		cout << "\nHeight of bstST2 is " << bstST2.getHeight() << endl;
		cout << "\nNumber of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl;

		cout << "\n\nDelete the object from bstST2 with the title Moonfleet, a tree with only a right subtree \n" << endl;
		st1.clear();
		st1.setTitle("Moonfleet");
		if (bstST2.remove(st1))
			cout << "\n\"" << st1.getTitle() << "\" deleted from bstST2" << endl;
		else
			cout << "\n\"" << st1.getTitle() << "\" NOT deleted from bstST2" << endl;

		cout << "\n\nDisplay bstST2\nPreorder:" << endl;
		bstST2.preorderTraverse(display);
		cout << "\nHeight of bstST2 is " << bstST2.getHeight() << endl;
		cout << "\nNumber of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl;

		cout << "\n\nDelete the object from bstST2 with title Godzilla, a tree with two subtrees whose right child is the inorder successor\n" << endl;
		st1.clear();
		st1.setTitle("Godzilla");
		if (bstST2.remove(st1))
			cout << "\n\"" << st1.getTitle() << "\" deleted from bstST2" << endl;
		else
			cout << "\n\"" << st1.getTitle() << "\" NOT deleted from bstST2" << endl;

		cout << "\n\nDisplay bstST2\nPreorder:" << endl;
		bstST2.preorderTraverse(display);
		cout << "\nHeight of bstST2 is " << bstST2.getHeight() << endl;
		cout << "\nNumber of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl;

		cout << "\n\nDelete the object from bstST2 with the title King of Hearts, a tree with two children whose right child is NOT the inorder successor\n" << endl;
		st1.clear();
		st1.setTitle("King of Hearts");
		if (bstST2.remove(st1))
			cout << "\n\"" << st1.getTitle() << "\" deleted from bstST2" << endl;
		else
			cout << "\n\"" << st1.getTitle() << "\" NOT deleted from bstST2" << endl;

		cout << "\n\nDisplay bstST2\nPreorder:" << endl;
		bstST2.preorderTraverse(display);
		cout << "\nHeight of bstST2 is " << bstST2.getHeight() << endl;
		cout << "\nNumber of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl;

		cout << "\n\nRetrieve the object with title Psycho using contains\n" << endl;
		st1.clear();
		st1.setTitle("Psycho");
		if ( bstST2.contains( st1 ) )
			cout << "\n\"" << st1.getTitle() << "\" found in bstST2" << endl;
		else
			cout << "\n\"" << st1.getTitle() << "\" NOT found in bstST2" << endl;

		cout << "\n\nDisplay bstST2\nPreorder:" << endl;
		bstST2.preorderTraverse( display );
		cout << "\nInorder:" << endl;
		bstST2.inorderTraverse( display );
		cout << "\nPostorder:" << endl;
		bstST2.postorderTraverse( display );

		cout << "\nHeight of bstST2 is " << bstST2.getHeight() << endl;
		cout << "\nNumber of nodes in bstST2 is " << bstST2.getNumberOfNodes() << endl;

		cout << "\n\n***************************************************************\nPress Enter to continue --> ";
		cin.get();

		cout << "\n\nCreate bstST3, a pointer to BinarySearchTree, and then assign bstST2 to it\n" << endl;
		shared_ptr<BinarySearchTree<soundtrack>> bstST3 = make_shared<BinarySearchTree<soundtrack>>();
		*bstST3 = bstST2;
		cout << "Display bstST3\nPreorder:" << endl;
		bstST3->preorderTraverse( display );
		cout << "\nInorder:" << endl;
		bstST3->inorderTraverse( display );
		cout << "\nPostorder:" << endl;
		bstST3->postorderTraverse( display );

		cout << "\nHeight of bstST3 is " << bstST3->getHeight() << endl;
		cout << "\nNumber of nodes in bstST3 is " << bstST3->getNumberOfNodes() << endl;

		bstST3.reset();
	}
	catch( bad_alloc &ba )
	{
		cout << "Error allocating memory. " << ba.what() << "\n  Program ending\n" << endl;
		return 5;
	}

	cout << "\n\nProgram Over\n" << endl;

	cout << "Press Enter to end -->  ";
	cin.ignore();

	return 0;
}

// Used by tree traversals
template<class ItemType>
void display( ItemType val )
{
	cout << val << endl;
} // end display

bool readFile(vector<soundtrack> & trackVec )
{
	bool rc = true;

	string filename( "Topic D Soundtrack.txt" );
	ifstream inFile( filename );

	while ( !inFile )
	{
		cout << filename << " cannot be opened.  Enter another file name -->  ";
		cin >> filename;
		cin.ignore();  // get rid of newline after filename entry
		inFile.clear();
		inFile.open( filename );
	}

	soundtrack st;
	string buf, sub;
	char *endPtr;  // for strtol

	while ( !inFile.eof() )
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
		st.setReleased(static_cast<int>(strtol(sub.c_str(), &endPtr, 10)));  // What assumption is being made here?

		trackVec.push_back( st );
	}

	if ( trackVec.empty() )
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
