/**************************************************************
CS M20 Topic E Project

Modified by Martin Chetlen
*************************************************************/

/** ADT priority queue: Heap-based implementation.
    Listing 17-3.
 @file Heap_PriorityQueue.h */


#ifndef _HEAP_PRIORITY_QUEUE
#define _HEAP_PRIORITY_QUEUE

#include "ArrayMaxHeap.h"

template<class ItemType>
class Heap_PriorityQueue : private ArrayMaxHeap<ItemType>
{
public:
   Heap_PriorityQueue( int = ArrayMaxHeap<ItemType>::DEFAULT_CAPACITY);
   bool isEmpty() const;
   bool add(const ItemType& newEntry);
   bool remove();
   
   /** @pre The priority queue is not empty. */
   ItemType peek() const throw(PrecondViolatedExcep);
}; // end Heap_PriorityQueue

// Modified for CS M20 Topic E Project

/** Heap-based implementation of the ADT priority queue.
    Listing 17-4.
 @file Heap_PriorityQueue.cpp */


template<class ItemType>
Heap_PriorityQueue<ItemType>::Heap_PriorityQueue( int cap ) : ArrayMaxHeap<ItemType>( cap )  // Modified
{

}  // end constructor

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::isEmpty() const
{
   return ArrayMaxHeap<ItemType>::isEmpty();
}  // end isEmpty

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::add(const ItemType& newEntry)
{
   return ArrayMaxHeap<ItemType>::add(newEntry);
}  // end add

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::remove()
{
   return ArrayMaxHeap<ItemType>::remove();
}  // end remove

template<class ItemType>
ItemType Heap_PriorityQueue<ItemType>::peek() const throw(PrecondViolatedExcep)
{
   try
   {
      return ArrayMaxHeap<ItemType>::peekTop();
   }
   catch (PrecondViolatedExcep e)
   {
      throw PrecondViolatedExcep("Attempted peek into an empty priority queue.");
   }  // end try/catch
}  // end peek



#endif
