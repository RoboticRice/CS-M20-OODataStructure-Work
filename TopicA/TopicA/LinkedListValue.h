/** LinkedList Value based class for use with LinkedList
@file LinkedListValue.h */

#ifndef LINKED_LIST_VALUE_
#define LINKED_LIST_VALUE_

#include "LinkedList.h"

template<class ItemType>
class LinkedListValue : public LinkedList<ItemType>
{
private:
	LinkedList<ItemType> subList;
public:
	LinkedListValue();
	LinkedListValue(const LinkedListValue<ItemType>& aList);
	~LinkedListValue();

	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const ItemType& newEntry);
	bool remove(int position);
	void clear();

	/** @throw   PrecondViolatedExcept if position < 1 or position > getLength(). */
	ItemType getEntry(int position) const throw(PrecondViolatedExcept);
}; //end LinkedListValue

#endif