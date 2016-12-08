/*************************************************************

Topic A Project CS M20

TopicA.cpp
Client file

Fall 2016

****************************************************************/

#pragma warning( disable: 4290 )  // disable warnings about the use of throw in function headers

#include <iostream>
#include <fstream>
#include <string>
#include <new>
using namespace std;

#include "LinkedListValue.h"
#include "soundtrack.h"

template<class T>
bool readInput(LinkedListValue<T> &obj, const string & filename);

void endProgram(const int returnValue);

#if 0
template<class ItemType>
bool swap(LinkedList<ItemType> &l, const int p1, const int p2);
#endif

#if 0
template<class ItemType>
bool swap(std::shared_ptr<LinkedList<ItemType>> aList, int i, int j);
#endif


int main()
{
	cout << "\nCreate int LinkedListValue llv1 using default constructor" << endl;
	LinkedListValue<int> llv1;

	cout << "\n\nInsert items into llv1" << endl;
	int val{ -34 };
	llv1.insert(val); //why does val have to be used here and not a value such as -34?
	llv1.insert(val = 2);
	llv1.insert(val = 17);
	llv1.insert(val = 63);
	llv1.insert(val = 225);
	llv1.insert(val = -2345);


	cout << "\n\nDisplay llv1:" << endl;
	cout << llv1 << endl << endl;



#if 0
	// replace test
	llv1.LinkedList::replace(1, 1117);
#endif




	cout << "\n\nCreate Linked List ll1 which is a copy of llv1" << endl;
	LinkedList<int> ll1 = llv1;
	cout << "\n\nDisplay ll1:" << endl;
	cout << ll1 << endl << endl;

	try {
		cout << "\n\nChange the fifth value of ll1 to 2015" << endl;
		ll1.replace(5, 2015);
		cout << "\n\nChange the tenth value of ll1 to 2016" << endl;
		ll1.replace(10, 2016);
	}
	catch (const PrecondViolatedExcept &e)
	{
		cout << e.what() << endl;
	}

	cout << "\n\nDisplay ll1:" << endl;
	cout << ll1 << endl << endl;
	
	cout << "\n\nCreate LinkedListValue llv2 which is a copy of llv1" << endl;
	LinkedListValue<int> llv2 = llv1;
	cout << "\n\nDisplay llv2:" << endl;
	cout << llv2 << endl << endl;

	cout << "\n\nRemove 63 from llv2" << endl;
	if (llv2.remove(val = 63))
		cout << "\n" << val << " was removed from llv2" << endl;
	else
		cout << "\n" << val << " was NOT removed from llv2" << endl;

	cout << "\n\nAttempt to remove 63 from llv2 again" << endl;
	if (llv2.remove(val))
		cout << "\n" << val << " was removed from llv2" << endl;
	else
		cout << "\n" << val << " was NOT removed from llv2" << endl;

	cout << "\n\nDisplay llv2:" << endl;
	cout << llv2 << endl << endl;

	cout << "\n\nCreate LinkedListValue llv3 from llv2" << endl;
	LinkedListValue<int> llv3(llv2);
	cout << "\n\nDisplay llv3:" << endl;
	cout << llv3 << endl << endl;

	cout << "\n\nAssign llv3 the values from llv1" << endl;
	llv3 = llv1;

	cout << "\n\nDisplay llv3:" << endl;
	cout << llv3 << endl << endl;

	cout << "\n\nAssign ll1 the values from llv3" << endl;
	ll1 = llv3;

	cout << "\n\nDisplay ll1:" << endl;
	cout << ll1 << endl << endl;

#if 0
	ll1.swap(2, 5);
	cout << "\n\nDisplay ll1 after swapping 2 and 5" << endl << ll1 << endl << endl;
#endif

#if 0
	bool res = swap(ll1, 2, 5);
	if (res)
		cout << "\n\nswap sucessful.  Display ll1" << endl << ll1 << endl << endl;
#endif

	/*****************************************************************************/

	cout << "\nCreate string LinkedListValue llv4 using default constructor" << endl;
	LinkedListValue<string> llv4;


	cout << "\n\nInsert items into llv4" << endl;
	string  strval = "CS";
	llv4.insert(strval); 
	llv4.insert(strval = "M");
	llv4.insert(strval = "20");
	llv4.insert(strval = "Data Structures");
	llv4.insert(strval = "Using");
	llv4.insert(strval = "C++");

	cout << "\n\nDisplay llv4:" << endl;
	cout << llv4 << endl << endl;

	cout << "\n\nCreate llv5 from llv4" <<endl;
	LinkedListValue<string> llv5(llv4);
	cout << "\n\nDisplay llv5:" << endl;
	cout << llv5 << endl << endl;

	cout << "\n\nDelete \"Data\" from llv5" << endl;
	if (llv5.remove(strval = "Data"))
		cout << "\"" << strval << "\" deleted from llv5" << endl;
	else
		cout << "\"" << strval << "\" NOT deleted from llv5" << endl;

	cout << "\n\nDelete \"Data Structures\" from llv5" << endl;
	if (llv5.remove(strval = "Data Structures"))
		cout << "\"" << strval << "\" deleted from llv5" << endl;
	else
		cout << "\"" << strval << "\" NOT deleted from llv5" << endl;

	cout << "\n\nDisplay llv5:" << endl;
	cout << llv5 << endl << endl;

	cout << "\n\nAssign llv5 to llv4" << endl;
	llv4 = llv5;
	cout << "\n\nDisplay llv4:" << endl;
	cout << llv4 << endl << endl;

	/**********************************************************************************/
	try {
		cout << "\n\nCreate soundtrack LinkedListValue llv6" << endl;
		LinkedListValue<soundtrack> llv6;

		cout << "\n\nInsert values from file" << endl;
		if (!readInput(llv6, "Topic A Soundtrack List.txt"))
			return 1; // something wrong with input file
		cout << "\n\nDisplay llv6:" << endl;
		cout << llv6 << endl;

		cout << "\n\nCreate a new POINTER to a LinkedListValue pllv7, a copy of llv6";
	
		unique_ptr<LinkedListValue<soundtrack>> pllv7 = make_unique<LinkedListValue<soundtrack>>(llv6);
		cout << "\n\nDisplay llv7" << endl;
		cout << *pllv7 << endl;

		cout << "\n\nDelete \"Henry V\" from pllv7" << endl;
		soundtrack buf;
		buf.setTitle("Henry V");
		if (pllv7->remove(buf))
			cout << "\"" << buf.getTitle() << "\" removed from pllv7" << endl;
		else
			cout << "\"" << buf.getTitle() << "\" NOT removed from pllv7" << endl;

		cout << "\n\nDisplay pllv7" << endl;
		cout << *pllv7 << endl;

		cout << "\n\nDelete \"Henry V\" AGAIN from pllv7" << endl;

		if (pllv7->remove(buf))
			cout << "\"" << buf.getTitle() << "\" removed from pllv7" << endl;
		else
			cout << "\"" << buf.getTitle() << "\" NOT removed from pllv7" << endl;

		cout << "\n\nDisplay pllv7" << endl;
		cout << *pllv7 << endl;

		cout << "\n\nAssign pllv7 to llv6" << endl;
		llv6 = *pllv7;

		cout << "\n\nDisplay llv6:" << endl;
		cout << llv6 << endl;

		int pos;
		cout << "\n\nFind the soundtrack recorded in 1947 in pllv7" << endl;
		buf.clear();
		buf.setRecorded("1947");
		if (pllv7->find(buf, pos))
			cout << "The soundtrack recorded in 1947 is in position " << pos << " and is the following:" << endl
			<< buf << endl;
		else
			cout << "No soundtrack recorded in 1947 found" << endl;

		pllv7.reset();

	}
	catch (bad_alloc &e)
	{
		cout << "\n\n" << e.what() << "\n\nMemory allocation failed.  Program ending";
		endProgram( 1 );
	}


	endProgram(0);
	return 0;
}

// How many exit points does the function have?
// What are the advantages/drawbacks of having multiple exit points?
template<class T>
bool readInput(LinkedListValue<T> &obj, const string & filename)
{
	ifstream in(filename);
	if (!in)
	{
		cout << "\nInput file" << filename << " cannot be found" << endl;
		return false;
	}

	soundtrack sound;

	while (!in.eof())
	{
		in >> sound;
		obj.insert(sound);
	}

	return true;
}

void endProgram(const int returnValue)
{
	cout << "\n\n\nProgram Ending ";
	cout << ((returnValue == 0) ? "Successfully" : "With a Problem") << endl;
	cout << "\nPress Enter to end";
	cin.ignore();
	exit(returnValue);
}

#if 1
template<class ItemType>
bool swap(LinkedList<ItemType> &l, const int p1, const int p2)
{
	bool result{ false };

	// If this test were not done, how could an invalid position be handled?
	if (p1 >= 1 && p1 <= l.getLength() && p2 >= 1 && p2 <= l.getLength())
	{
		auto v1 = l.getEntry(p1);
		l.replace(p1, l.getEntry(p2));
		l.replace(p2, v1);
		result = true;
	}

	return result;
};
#endif

