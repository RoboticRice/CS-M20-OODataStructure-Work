#include <iostream>
using namespace std;
/*
* Project: Template
* Class:   CS M10B
* Student: Rice, Sammuel D.
* Edited:  20160###
* Due on:  20160###
* Version: 0.1 (History: 0.1)
* gitHub:  https://github.com/RoboticRice/CS-M10B-Projects.git
*/

/*
* Instructions:
*
*//*
* Notes:
* This program does NOT impliment any error handling.
* This program is designed to work with TemplateClass.cpp (Version 0.1)
& TemplateClass.h (Version 0.1)
*/

bool swap(aList, const int &i, const int &j);

int main() {
	//Main class
	int list[5] = (1, 2, 3, 4, 5);
	cout << swap(list, 2, 3);
	return 0;
}

bool swap(aList, const int &i, const int &j) {
	//Assume i and j do NOT always exist in the list (?)
	//aList = list of items
	//i = positions of item 1
	//j = positions of item 2
	//Purpose: Take the item in position i and move it to position j, 
	//while taking the item in position j and move it to position i.
	if (aList[i] != null && aList[j] != null) {
		//if there is something at position i and if there is something at position j
		int *tempPtr = &aList[i];
		*aList[i] = &aList[j];
		*aList[j] = *tempPtr;
		//destroy tempPtr;
		return true;
	}
	else {
		return false;
	}
	//tempPtr point to the address of i
	//list pointer at i point to the address of j
	//list pointer at j point to the address of tempPtr
	//destroy tempPtr
}