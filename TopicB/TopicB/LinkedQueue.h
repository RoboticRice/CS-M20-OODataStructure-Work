/** ADT queue: Link-based implimentationn.
@file LinkedQueue.h */

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

//#include "QueueInterface.h"
#include "Node.h"
#include "PrecondViolatedExcept.h"
#include <memory>

template<class ItemType>
class LinkedQueue //: public QueueInterface<ItemType>
{
private:
	// The queue is implimented as a chain of linked nodes that has
	// two external pointers, a head pointer for the front of the queue
	// and a tail pointer for the back of the queue.
	std::shared_ptr<Node<ItemType>> frontPtr;
	std::shared_ptr<Node<ItemType>> backPtr;

public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue& aQueue);
	~LinkedQueue();

	bool isEmpty() const;
	bool enqueue(const ItemType& newEntry);
	bool dequeue();

	/** @throw PrecondViolatedExcept if the queue is empty */
	ItemType peekFront() const throw (PrecondViolatedExcept);

	LinkedQueue<ItemType> & operator = (const LinkedQueue<ItemType> & aQueue);
}; // end LinkedQueue

//#include "LinkedQueue.cpp"
//********Start of .cpp file**********

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue() : frontPtr(nullptr), backPtr(nullptr)
{
} //end default constructor

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue<ItemType>& aQueue)
{
	//Point to nodes in original chain
	std::shared_ptr<Node<ItemType>> originalChainPtr = aQueue.frontPtr;
	if (originalChainPtr == nullptr)
	{
		backPtr = nullptr; //Original Stack is empty
		frontPtr = nullptr;
	}
	else
	{
		//Copy first node
		frontPtr = std::make_shared<Node<ItemType>>(originalChainPtr->getItem());
		//frontPtr = new Node<ItemType>();
		//frontPtr->setItem(originalChainPtr->getItem());

		//point to first node in new chain
		std::shared_ptr<Node<ItemType>> newChainPtr = frontPtr;

		//Update backPtr
		backPtr = newChainPtr;

		//Advance original-chain pointer
		originalChainPtr = originalChainPtr->getNext();

		//Copy remaining nodes
		while (originalChainPtr != nullptr)
		{
			//get next item from original chain
			ItemType nextItem = originalChainPtr->getItem();

			//Create a new node containing the next item
			auto newNodePtr = make_shared<Node<ItemType>>(nextItem);

			//Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);

			//Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();

			//Update backPtr
			backPtr = newChainPtr;

			//Advance original-chain pointer
			originalChainPtr = originalChainPtr->getNext();
		}//end while
		newChainPtr->setNext(nullptr); //Flag end of chain
	}//end if
}//end copy constructor

template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue()
{
	//Pop until stack is empty
	while (!isEmpty())
		dequeue();
}//end destructor

template<class ItemType>
bool LinkedQueue<ItemType>::isEmpty() const
{
	return frontPtr == nullptr;
} //end isEmpty

template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry)
{
	auto newNodePtr = std::make_shared<Node<ItemType>>(newEntry);

	//Insert the new node
	if(isEmpty())
		frontPtr = newNodePtr;			//The queue was empty
	else
		backPtr->setNext(newNodePtr);	//The queue was not empty

	backPtr = newNodePtr;				//New node is at back
	return true;
} // end enqueue

template<class ItemType>
bool LinkedQueue<ItemType>::dequeue()
{
	bool result = false;
	if (!isEmpty())
	{
		// Queue is not empty; remove front
		auto nodeToDeletePtr = frontPtr;
		if (frontPtr == backPtr)
		{   //Special case: one node in queue
			//set frontPtr and backPtr to nullptr
			frontPtr.reset();
			backPtr.reset();
		}
		else
			frontPtr = frontPtr->getNext();

		//Maintain an accurate reference count for first node
		nodeToDeletePtr->setNext(nullptr);
		//Removed node will be deallocated when method ends

		result = true;
	} //end if

	return result;
} //end dequeue

template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const throw (PrecondViolatedExcept)
{
	if (isEmpty())
	{
		string message = "peekFront() called with an empty list";
		throw(PrecondViolatedExcept(message));
	}
	return frontPtr->getItem();
} //end peekFront

template<class ItemType>
LinkedQueue<ItemType> & LinkedQueue<ItemType>::operator = (const LinkedQueue<ItemType> & aQueue)
{
	if (this == &aQueue)
		return *this;

	while (!isEmpty())
		dequeue();
	//frontPtr = nullptr; //<-Will happen automatically during dequeue
	//backPtr = nullptr;
	if (!aQueue.isEmpty())
	{
		//Point to nodes in original chain
		std::shared_ptr<Node<ItemType>> originalChainPtr = aQueue.frontPtr;

		//Copy first node
		frontPtr = std::make_shared<Node<ItemType>>(originalChainPtr->getItem());
		//frontPtr = new Node<ItemType>();
		//frontPtr->setItem(originalChainPtr->getItem());

		//point to first node in new chain
		std::shared_ptr<Node<ItemType>> newChainPtr = frontPtr;

		//Update backPtr
		backPtr = newChainPtr;

		//Advance original-chain pointer
		originalChainPtr = originalChainPtr->getNext();

		//Copy remaining nodes
		while (originalChainPtr != nullptr)
		{
			//get next item from original chain
			ItemType nextItem = originalChainPtr->getItem();

			//Create a new node containing the next item
			auto newNodePtr = make_shared<Node<ItemType>>(nextItem);

			//Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);

			//Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();

			//Update backPtr
			backPtr = newChainPtr;

			//Advance original-chain pointer
			originalChainPtr = originalChainPtr->getNext();
		}//end while
		newChainPtr->setNext(nullptr); //Flag end of chain
	}
	return *this;
} // end operator = overload
#endif // !LINKED_QUEUE_
