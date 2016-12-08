

/** ADT queue: Link-based implementation.
 Listing 14-3.
 @file LinkedQueue.h */

/**********************************
	Topic B Project - Balanced symbols

	CS M20

	Modified to include:
		* Assignment operator
		* Implementations for:
			* Constructor
			* Destructor
			* Copy constructor
			* isEmpty
			* peekFront
		* C++ 11

	Exclude queue interface
***********************************/


#ifndef _LINKED_QUEUE
#define _LINKED_QUEUE

#include <memory>
using namespace std;

#include "Node.h"
#include "PrecondViolatedExcept.h"

template<class ItemType>
class LinkedQueue
{
private:
   // The queue is implemented as a chain of linked nodes that has 
   // two external pointers, a head pointer for front of the queue and
   // a tail pointer for the back of the queue.
	shared_ptr<Node<ItemType>>  backPtr;
	shared_ptr<Node<ItemType>>  frontPtr;

public:
	LinkedQueue() {}  //changed
    LinkedQueue  (const LinkedQueue& aQueue);
   ~LinkedQueue();

    bool isEmpty() const { return ( ( frontPtr == nullptr ) ? true : false );  }  //modified
	bool enqueue(const ItemType& newEntry);
	bool dequeue();
   
   /** @throw PrecondViolatedExcep if the queue is empty */
	ItemType peekFront() const throw(PrecondViolatedExcept);

	LinkedQueue<ItemType> & operator = ( const LinkedQueue<ItemType> &right );  //added

}; // end LinkedQueue

/******************************** Implementation******************************/

template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry)
{
	auto  newNodePtr{ make_shared<Node<ItemType>>(newEntry) };

   // Insert the new node
   if (isEmpty())
      frontPtr = newNodePtr;        // Insertion into empty queue
   else
      backPtr->setNext(newNodePtr); // Insertion into nonempty queue
   
   backPtr = newNodePtr;            // New node is at back
   
	return true;
}  // end enqueue

template<class ItemType>
bool LinkedQueue<ItemType>::dequeue()
{
	bool result{ false };
	if (!isEmpty())
	{
      // Queue is not empty; delete front
		auto  nodeToDeletePtr{ frontPtr };
      if (frontPtr == backPtr)
      {  // Special case: one node in queue
         frontPtr = backPtr = nullptr;
      }
      else
		   frontPtr = frontPtr->getNext();
		
      result = true;
	}  // end if
   
	return result;	
}  // end dequeue

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue  (const LinkedQueue& aQueue)
{
	backPtr = frontPtr = nullptr;
	*this = aQueue; 
}  // end copy constructor



template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue()
{
	backPtr.reset();
	frontPtr.reset();
}

   /** @throw PrecondViolatedExcep if the queue is empty */
template<class ItemType>  //added
ItemType LinkedQueue<ItemType>::peekFront() const throw(PrecondViolatedExcept)
{
	if ( isEmpty() )
		throw PrecondViolatedExcept( "peekFront - Queue empty" );
		
	return frontPtr->getItem();
}

template<class ItemType>  //added
LinkedQueue<ItemType> &  LinkedQueue<ItemType>::operator = ( const LinkedQueue<ItemType> &right )  //added
{
	if ( this == &right )
		return *this;

	frontPtr = backPtr = nullptr;

	if ( right.frontPtr == nullptr )
	{
		return *this;
	}

	auto curr{ right.frontPtr };

	while ( curr != nullptr )
	{
		enqueue( curr->getItem() );
		curr = curr->getNext();
	}

	return *this;
}



#endif
