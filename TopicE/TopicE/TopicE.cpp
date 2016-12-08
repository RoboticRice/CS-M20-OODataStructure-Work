// TopicE.cpp : Defines the entry point for the console application.
// #include "stdafx.h"

/*
* Project: TopicB
* Class:   CS M20
* Student: Rice, Sammuel D.
* Edited:  20161029
* Due on:  20161102
* Version: 0.1 (History: 0.1)
* VCS:     Not hosted atm
* Status:
Complete:		No
Compiles:		Yes
Errors:			Yes, Abort is called during runtime*
Created via:	VisualStudio 2015
*/

//*Note on the error, it appears to happen at different times in the code, as the output is different each time I run this program...

/**
1>------ Build started: Project: TopicE, Configuration: Debug Win32 ------
1>  TopicE.cpp
1>  TopicE.vcxproj -> C:\Users\Samous\Source\Repos\CS-M20-OODataStructure-Work\TopicE\Debug\TopicE.exe
1>  TopicE.vcxproj -> C:\Users\Samous\Source\Repos\CS-M20-OODataStructure-Work\TopicE\Debug\TopicE.pdb (Full PDB)
========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========
**/

#pragma warning( disable: 4290 )  // disable warnings about the use of throw in function headers

#include <iostream>
#include <ctime>
#include <vector>
#include "HeapPriorityQueue.h"
#include "TopicEData.h"
using namespace std;

void getData(vector<topicEData>& list);
bool valid(topicEData testMe);
template<class ItemType>
void printVector(vector<ItemType>& list);
void endProgram(const int reason);

int main()
{
	//input data
	vector<topicEData> notProccessed;
	getData(notProccessed);

	//check to make sure there IS data
	if (notProccessed.empty())
		endProgram(1);

	cout << "Print all valid data" << endl;
	//printVector(notProccessed);
	cout << endl;

	//create the Queue, with the first item being the last box in our vector
	HeapPriorityQueue<topicEData> queue(notProccessed.size()); //with maxItems = size of notProccessed
	queue.enqueue(notProccessed.back());
	notProccessed.pop_back(); //remove the last box from the vector, as it is now in our queue

	vector<topicEData> placeHolder, fullBoxes;
	bool beenPlaced = false;
	while (!notProccessed.empty()) //while we still have stuff to proccess
	{
		//cout << "!notProccessed.empty()" << endl;
		if (queue.isEmpty())
		{
			//cout << "queue.isEmpty()" << endl;
			queue.enqueue(notProccessed.back());
			notProccessed.pop_back();
		}
		else
		{
			//cout << "NOT queue.isEmpty()" << endl;
			beenPlaced = false;
			while (!queue.isEmpty() && !beenPlaced)
			{
				//cout << "!queue.isEmpty() && !beenPlaced" << endl;
				if ((queue.peekFront().getTotal() + notProccessed.back().getTotal()) <= 1.0) //if you can add both and be lessthan or equal to 1, do it
				{
					//cout << "added <= 1.0" << endl;
					unique_ptr<topicEData> newBox = make_unique<topicEData>(queue.peekFront().getNumber());
					newBox->add(queue.peekFront().getTotal());
					newBox->add(notProccessed.back().getTotal());
					queue.dequeue();
					notProccessed.pop_back();
					queue.enqueue(*newBox);
					beenPlaced = true;
				}
				else //otherwise, try the next box in the queue
				{
					//cout << "try the next box in the queue" << endl;
					placeHolder.push_back(queue.peekFront());
					queue.dequeue();
				}
			}
			//cout << "done with that while loop" << endl;
			//rebuild our queue
			while (!placeHolder.empty())
			{
				//cout << "put back queue items" << endl;
				queue.enqueue(placeHolder.back());
				placeHolder.pop_back();
			}
			cout << "done putting back" << endl;
			//if the item didn't fit into anything...
			if (!beenPlaced)
			{
				cout << "!beenPlaced" << endl;
				cout << notProccessed.back() << endl;
				queue.enqueue(notProccessed.back());
				cout << "enqueue" << endl;
				notProccessed.pop_back();
				cout << "end if !been" << endl;
			}
			cout << "end else" << endl;
		}
		//cout << "end of else statement" << endl;
		if (queue.peekFront().getTotal() >= 0.99)
		{
			//cout << "if total >= 0.99" << endl;
			fullBoxes.push_back(queue.peekFront());
			queue.dequeue();
		}
		cout << "loooooooop" << endl;
	}

	cout << "Print all full boxes" << endl;
	printVector(fullBoxes);
	cout << endl;

	cout << "Print all boxes waiting to be filled" << endl;
	//printQueue
	cout << endl;

	endProgram(0);
    return 0;
}

void getData(vector<topicEData>& list)
{
	int curBoxNumber = (int)time(0);

	ifstream inFile;
	string name{ "TopicEin.txt" };
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

	while (!inFile.eof())//!empty
	{
		std::unique_ptr<topicEData> input = std::make_unique<topicEData>(++curBoxNumber);
		inFile >> *input;
		if (valid(*input))
			list.push_back(*input);
	}

	inFile.close();
	//validate
}

bool valid(topicEData testMe)
{
	topicEData zero(0), one(1);
	one.add(1);
	return (testMe > zero) && (testMe <= one);
}

template<class ItemType>
void printVector(vector<ItemType>& list)
{
	for (size_t i = 0; i < list.size(); i++)
		cout << list[i] << endl;
	cout << "Vector conatins " << list.size() << " items." << endl
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

