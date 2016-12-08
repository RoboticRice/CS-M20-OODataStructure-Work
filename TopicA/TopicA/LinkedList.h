/** ADT list: Link-based implementation.
@file LinkedList.h */

#ifndef LINKED_LIST_
#define LINKED_LIST_

#include "ListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcept.h"
#pragma warning( disable: 4290 ) //added to remove a warning, as suggested by Prof.

template<class ItemType>
class LinkedList : public ListInterface<ItemType>
{
private:
	Node<ItemType>* headPtr; //Pointer to first node in the chain
							 //(contains the first entry in the list)
	int itemCount;			 //Current count of list items
	//Locates a specified node in a linked list.
	//@pre position is the number of the desired node position >= 1 and position <= itemCount.
	//@post The node is found and a pointer to it is returned.
	//@param position the number of the node to locate
	//@return a pointer to the node at the given position.
	Node<ItemType>* getNodeAt(int position) const;

public:
	LinkedList();
	LinkedList(const LinkedList<ItemType>& aList);
	virtual ~LinkedList();

	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const ItemType& newEntry);
	bool remove(int position);
	void clear();

	/** @throw   PrecondViolatedExcept if position < 1 or position > getLength(). */
	ItemType getEntry(int position) const throw(PrecondViolatedExcept);

	/** @throw   PrecondViolatedExcept if position < 1 or position > getLength(). */
	ItemType replace(int position, const ItemType& newEntry) throw(PrecondViolatedExcept);
}; //end LinkedList

//#include "LinkedList.cpp" //<- this was in the textbook, but it doesn't work here, why was it in the book?
#endif