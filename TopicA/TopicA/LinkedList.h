/** ADT list: Link-based implementation.
    Listing 9-2.
    @file LinkedList.h */

#ifndef _LINKED_LIST
#define _LINKED_LIST

// #define EXER

#include "ListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcept.h"


template<class ItemType>
class LinkedList : public ListInterface<ItemType>
{
private:
	shared_ptr<Node<ItemType>> headPtr; // Pointer to first node in the chain;
                            // (contains the first entry in the list)
   int itemCount;           // Current count of list items 
   
   // Locates a specified node in this linked list.
   // @pre  position is the number of the desired node;
   //       position >= 1 and position <= itemCount.
   // @post  The node is found and a pointer to it is returned.
   // @param position  The number of the node to locate.
   // @return  A pointer to the node at the given position.
   shared_ptr<Node<ItemType>> getNodeAt(int position) const; // Node<ItemType>*

public:
   LinkedList() : itemCount{ 0 } {}
   LinkedList(const LinkedList<ItemType>& aList);
   virtual ~LinkedList();

#ifdef EXER
   // added for Topic A Exercises
   bool swap(const int, const int);
#endif

   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType& newEntry);
   bool remove(int position);
   void clear();
   
   /** @throw PrecondViolatedExcep if position < 1 or 
                                      position > getLength(). */
   ItemType getEntry(int position) const throw(PrecondViolatedExcept);

   /** @throw PrecondViolatedExcep if position < 1 or 
                                      position > getLength(). */
   void replace(int position, const ItemType& newEntry)
                               throw(PrecondViolatedExcept);

   LinkedList<ItemType> & operator = ( const LinkedList<ItemType> & aList );
}; // end LinkedList

// #include "LinkedList.cpp"

// The copy constructor and the method replace were left as exercises.
// ===================================================================


/***********************************************************
CS M20 Topic A Project

In addition to the above functions, overloaded the assignment operator.  Why?

*************************************************************/

/** Implementation file for the class LinkedList.
@file LinkedList.cpp */


   //added
template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList) : itemCount(0) 
{
	headPtr = nullptr;
	*this = aList;
}  // end copy constructor


template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
}  // end destructor

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
	return itemCount;
}  // end getLength

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
	bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
	if (ableToInsert)
	{
		// Create a new node containing the new entry 
		auto newNodePtr = make_shared<Node<ItemType>>( newEntry );  // why auto?

		// Attach new node to chain
		if (newPosition == 1)
		{
			// Insert new node at beginning of chain
			newNodePtr->setNext(headPtr);
			headPtr = newNodePtr;
		}
		else
		{
			// Find node that will be before new node
			auto prevPtr = this->getNodeAt(newPosition - 1);

			// Insert new node after node to which prevPtr points
			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
		}  // end if

		itemCount++;  // Increase count of entries
	}  // end if

	return ableToInsert;
}  // end insert

template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		if (position == 1)
		{
			// Remove the first node in the chain
			headPtr = headPtr->getNext();
		}
		else
		{
			// Find node that is before the one to delete
			auto prevPtr = getNodeAt(position - 1);

			// Point to node to delete
			auto curPtr = prevPtr->getNext();

			// Disconnect indicated node from chain by connecting the
			// prior node with the one after
			prevPtr->setNext(curPtr->getNext());
		}  // end if

		   // deleted node should be automatically deleted as no entity is pointing to it anymore

		itemCount--;  // Decrease count of entries
	}  // end if

	return ableToRemove;
}  // end remove

template<class ItemType>
void LinkedList<ItemType>::clear()
{
	headPtr.reset(); // See text page 300
	itemCount = 0;
}  // end clear

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcept)
{
	// Enforce precondition
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		auto nodePtr = getNodeAt(position);
		return nodePtr->getItem();
	}
	else
	{
		string message = "getEntry() called with an empty list or ";
		message = message + "invalid position.";
		throw(PrecondViolatedExcept(message));
	}  // end if
}  // end getEntry

   // added
template<class ItemType>
void LinkedList<ItemType>::replace(int position, const ItemType& newEntry)
throw(PrecondViolatedExcept)
{
	// Enforce precondition
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		auto nodePtr = getNodeAt(position);
		nodePtr->setItem(newEntry);
	}
	else
	{
		auto message = "replace() called with an empty list or invalid position"; // auto gives const string literal 
		throw(PrecondViolatedExcept(message));
	}  // end if
}  // end replace


template<class ItemType>
shared_ptr<Node<ItemType>> LinkedList<ItemType>::getNodeAt(int position) const
{
	// Debugging check of precondition
	if (!((position >= 1) && (position <= itemCount)))
	{
		throw PrecondViolatedExcept("getNodeAt() called with invalid position");
	}

	// Count from the beginning of the chain
	auto curPtr = headPtr;
	for (auto skip{ 1 }; skip < position; skip++)
		curPtr = curPtr->getNext();

	return curPtr;
}  // end getNodeAt

   // Operator overload

template<class ItemType>
LinkedList<ItemType> & LinkedList<ItemType>::operator = (const LinkedList<ItemType> & aList)
{
	if (this == &aList)
		return *this;

	clear();

	if (aList.itemCount == 0)
	{
		headPtr.reset();
		itemCount = 0;
	}
	else
		for (auto i{ 1 }; i <= aList.itemCount; ++i)
			insert(i, aList.getEntry(i));

	return *this;
} // end assignment overload


template <class ItemType>
ostream &operator << (ostream & out, const LinkedList<ItemType> & val)
{
	cout << "\nThere are " << val.getLength() << " values in the list:" << endl;
	for (auto i{ 1 }; i <= val.getLength(); ++i)
	{
		out << val.getEntry(i) << endl;
	}

	return out;
}

//  End of implementation file.

#ifdef EXER
/**********************************
	Added for Topic A Exercises

	Exercise 2 Page 263 (7th Edition)

	Parameters represent the positions to have their values swapped
**************************************/
template<class ItemType>
bool LinkedList<ItemType>::swap(const int p1, const int p2)
{
	if (p1 >= 1 && p1 <= itemCount && p2 >= 1 && p2 <= itemCount)
	{
		auto v1 = getNodeAt(p1);
		auto v2 = getNodeAt(p2);
		ItemType val{ v1->getItem() };
		v1->setItem(v2->getItem());
		v2->setItem(val);
		return true;
	}
	else
		return false;
}


#endif



#endif 
