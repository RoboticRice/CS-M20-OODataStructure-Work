/** ADT priority queue: Heap-based implimentation.
@file HeapPriorityQueue.h */
#ifndef HEAP_PRIORITY_QUEUE_
#define HEAP_PRIORITY_QUEUE_
#include "ArrayMaxHeap.h"
//#include "PriorityQueueInterface.h"

template<class ItemType>
class HeapPriorityQueue : private ArrayMaxHeap<ItemType>//, public PriorityQueueInterface<ItemType>
{
public:
	HeapPriorityQueue();
	HeapPriorityQueue(const int maxsize);
	bool isEmpty() const;
	bool enqueue(const ItemType& newEntry);
	bool dequeue();

	/** @pre The priority queue is not empty. */
	ItemType peekFront() const throw(PrecondViolatedExcept);
}; // end HeapPriorityQueue

/** Heap-Based implimentation of the ADT priority queue.
@file HeapPriorityQueue.cpp */

template<class ItemType>
HeapPriorityQueue<ItemType>::HeapPriorityQueue()
{
	ArrayMaxHeap<ItemType>();
} // end constructor

template<class ItemType>
HeapPriorityQueue<ItemType>::HeapPriorityQueue(const int maxsize)
{
	ArrayMaxHeap<ItemType>::ArrayMaxHeap(maxsize);
} // end constructor

template<class ItemType>
bool HeapPriorityQueue<ItemType>::isEmpty() const
{
	return ArrayMaxHeap<ItemType>::isEmpty();
} // end isEmpty

template<class ItemType>
bool HeapPriorityQueue<ItemType>::enqueue(const ItemType& newEntry)
{
	return ArrayMaxHeap<ItemType>::add(newEntry);
} // end enqueue

template<class ItemType>
bool HeapPriorityQueue<ItemType>::dequeue()
{
	return ArrayMaxHeap<ItemType>::remove();
} // end dequeue

template<class ItemType>
ItemType HeapPriorityQueue<ItemType>::peekFront() const throw(PrecondViolatedExcept)
{
	try
	{
		return ArrayMaxHeap<ItemType>::peekTop();
	}
	catch (PrecondViolatedExcept e)
	{
		throw PrecondViolatedExcept("Attempted peek into an empty priority queue.");
	} // end try/catch
} // end peekFront

#endif