#include "LinkedList.h"

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
} //end default constructor

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList)
{
	//TBA
} //end copy constructor

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcept)
{
	//Enforce precondition
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		Node<ItemType>* nodePtr = getNodeAt(position);
		return nodePtr->getItem();
	}
	else
	{
		std::stringbuf message = "getEntry() called with an empty list or ";
		message = message + "invalid position.";
		throw(PrecondViolatedExcept(message));
	} //end if
} //end getEntry

template<class ItemType>
ItemType LinkedList<ItemType>::replace(int position, const ItemType& newEntry) throw(PrecondViolatedExcept)
{
	//Enforce precondition
	bool ableToReplace = (position >= 1) && (position <= itemCount);
	if (ableToReplace)
	{
		//Node<ItemType>* nodePtr = getNodeAt(position);
		//return nodePtr->getItem();
	}
	else
	{
		std::stringbuf message = "replace() called with an empty list or ";
		message = message + "invalid position.";
		throw(PrecondViolatedExcept(message));
	} //end if
} //end replace

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
	//Debugging check of precondition
	//assert( (position >= 1) && (position <= itemCount) );

	//Count from the beginning of the chain
	Node<ItemType>* curPtr = headPtr;
	for (int skip = 1; skip < position; skip++)
		curPtr = curPtr->getNext();

	return curPtr ;
} // end getNodeAt

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
	bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
	if (ableToInsert)
	{
		//Create a new node containing the new entry
		//Node<ItemType*> newNodePtr = new Node<ItemTYpe>(newEntry);//old
		auto newNodePtr = std::make_shared<Node<ItemType>>(newEntry);

		//Attach new node to chain
		if (newPosition == 1)
		{
			//Insert new node at beginning of chain
			newNodePtr->setNext(headPtr);
			headPtr = newNodePtr;
		}
		else
		{
			//Finde node that will be before new node
			//Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);//old
			auto prevPtr = getNodeAt(newPosition - 1);

			//Insert new node after node to which prevPtr points
			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
		} //end if

		itemCount++; //Increase count of entries
	} //end if

	return ableToInsert;
} //end insert

template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		//Node<ItemType>* curPtr = nullptr;//old
		if (position == 1)
		{
			//Remove the firsdt node in the chain
			//curPtr = headPtr; //Save pointer to node //old
			headPtr = headPtr->getNext();
		}
		else
		{
			//Find node that is before the one to remove
			//Node<ItemType>* prevPtr = getNodeAt(position - 1);//old
			auto prevPtr = getNodeAt(position - 1);

			//Point to node to remove
			//curPtr = prevPtr->getNext();//old
			auto curPtr = prevPtr->getNext();

			//Disconnect indicated node from chain by connecting the prior node with the one after
			prevPtr->setNext(curPtr->getNext());
		} //end if
		/*
		//return node to system
		curPtr->setNext(nullptr);
		delete curPtr;
		curPtr = nullptr;
		*/ //old
		itemCount--; //decrease count of entries
	} //end if

	return ableToRemove;
} //end remove

template<class ItemType>
void LinkedList<ItemType>::clear()
{
	//while (!isEmpty())
	//	remove(1); //old
	headPtr = nullptr;
	itemCount = 0;
} //end clear

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
} //end destructor