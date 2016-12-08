/*************************************************************

Topic A Project CS M20

LinkedListValue.h
Derived LinkedList class to handle data by value

Fall 2016

****************************************************************/


#ifndef _LINKED_LIST_VALUE
#define _LINKED_LIST_VALUE

#include "LinkedList.h"

template<class ItemType>
class LinkedListValue : public LinkedList<ItemType>
{
public:

    LinkedListValue() { }
	LinkedListValue(const LinkedListValue<ItemType> &list) { *this = list; }
	virtual ~LinkedListValue() { this->clear(); }  // The C++ standard states that on the first pass a class template does exist 
							// therefore references to it should not be resolved unless the code explicitly states it.  By using this, for example

	bool insert(ItemType &val);
	bool remove(ItemType &val);

	bool find(ItemType &val, int &pos) const throw(PrecondViolatedExcept);

	LinkedListValue<ItemType> & operator = (const LinkedListValue<ItemType> & val);

	void replace() = delete; 

private:

};

// #include "LinkedListValue.cpp"

/*************************************************************

Topic A Project CS M20

LinkedListValue.cpp
Derived LinkedList class to handle data by value

Fall 2016

****************************************************************/

#include <iostream>
using namespace std;

// insert will always insert at the end of the list
template<class ItemType>
bool LinkedListValue<ItemType>::insert(ItemType &val)
{
	return LinkedList<ItemType>::insert(this->getLength() + 1, val);
}


template<class ItemType>
bool LinkedListValue<ItemType>::remove(ItemType &val)
{
	int pos;
	bool found = find(val, pos);

	if (found)
	{
		val = this->getEntry(pos);
		LinkedList<ItemType>::remove(pos);
	}

	return found;
}

template<class ItemType>
bool LinkedListValue<ItemType>::find(ItemType &val, int &pos) const throw(PrecondViolatedExcept)
{
	if (this->isEmpty())
	{
		pos = 0;
		return false;
	}

	bool end = false, found = false;

	pos = 1;

	for (auto i{ 1 }; !end && i <= this->getLength(); ++i)
	{
		if (val == this->getEntry(i))
		{
			found = true;
			end = true;
			pos = i;
			val = this->getEntry(i);
		}
	}

	return found;
}

template <class ItemType>
LinkedListValue<ItemType> & LinkedListValue<ItemType>::operator = (const LinkedListValue<ItemType> & val)
{
	LinkedList<ItemType>::operator = (val);
	return *this;
}

template <class ItemType>
ostream &operator << (ostream & out, const LinkedListValue<ItemType> & val)
{
	out << "\nThere are " << val.getLength() << " values in the list:" << endl;
	for (auto i{ 1 }; i <= val.getLength(); ++i)
	{
		out << val.getEntry(i) << endl;
	}

	return out;
}


#endif
