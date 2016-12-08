// TopicA.cpp : Defines the entry point for the console application.
//#include "stdafx.h"
#include "Soundtrack.h"
#include "LinkedListValue.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/*
* Project: TopicA
* Class:   CS M20
* Student: Rice, Sammuel D.
* Edited:  20160906
* Due on:  20160907
* Version: 0.2 (History: 0.1)
* gitHub:  Not hosted atm			//https://github.com/RoboticRice/CS-M20-OODataStructure-Work.git
* Status:
	Complete:	No
	Compiles:	No
	Errors:		Yes
*/

/**
1>------ Build started: Project: TopicA, Configuration: Debug Win32 ------
1>  TopicA.cpp
1>  LinkedListValue.cpp
1>  Generating Code...
1>TopicA.obj : error LNK2019: unresolved external symbol "public: __thiscall LinkedListValue<class Soundtrack>::LinkedListValue<class Soundtrack>(void)" (??0?$LinkedListValue@VSoundtrack@@@@QAE@XZ) referenced in function _main
1>TopicA.obj : error LNK2019: unresolved external symbol "public: virtual __thiscall LinkedListValue<class Soundtrack>::~LinkedListValue<class Soundtrack>(void)" (??1?$LinkedListValue@VSoundtrack@@@@UAE@XZ) referenced in function _main
1>TopicA.obj : error LNK2019: unresolved external symbol "public: virtual bool __thiscall LinkedListValue<class Soundtrack>::insert(int,class Soundtrack const &)" (?insert@?$LinkedListValue@VSoundtrack@@@@UAE_NHABVSoundtrack@@@Z) referenced in function _main
1>C:\Users\Samous\Source\Repos\CS-M20-OODataStructure-Work\TopicA\Debug\TopicA.exe : fatal error LNK1120: 3 unresolved externals
========== Build: 0 succeeded, 1 failed, 0 up-to-date, 0 skipped ==========
**/

/* Note:
* I was never able to progress any further in the project because I got stuck at this point with the above mentioned
* error, and spent over 2 hours trying to diagnose it with a friend.
*/

int main()
{
	const string fileName = "Topic A Soundtrack List.txt";

	cout << "Searching for input file: " << fileName << endl;
	ifstream inFile;
	inFile.open(fileName, ios::in);
	if (!inFile)
	{
		cout << "Unable to open file" << endl
			 << "Program Terminated!";
		exit(1); // terminate with error
	}
	cout << "File opened successfully." << endl
		 << endl
		 << "Reading contents and populating list..." << endl;
	string line{ "" };
	Soundtrack track;
	LinkedListValue<Soundtrack> discography;// = new LinkedListValue<Soundtrack>();
	while (getline(inFile, line))
	{
		track.setComposer(line);
		if (getline(inFile, line))
		{
			track.setTitle(line);
			if (getline(inFile, line))
			{
				track.setLabel(line);
				if (getline(inFile, line))
				{
					track.setCatalog(line);
					if (getline(inFile, line))
					{
						track.setRecorded(line);
						if (getline(inFile, line))
						{
							track.setReleased(line);
						}
					}
				}
			}
		}
		if (!discography.insert(1, track))
		{
			cout << "Failure to add item in list" << endl
				 << "Program Terminated!";
			exit(2); // terminate with error
		}
		cout << track.print() << endl;
		track.clear();
	} //end while loop
	inFile.close();
	cout << "List completely populated." << endl
		 << endl
		 << "Printing list:" << endl
		 << endl;
	//Print list here...
	cout << "Program Ending Successfully" << endl 
		 << endl 
		 << "Press Enter to end";
	cin.get();
    return 0;
}

