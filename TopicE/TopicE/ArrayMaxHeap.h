/**************************************************************
CS M20 Topic E Project

Modified by Martin Chetlen
*************************************************************/
//  Created by Frank M. Carrano and Tim Henry.


/** Array-based implementation of the ADT heap.
 Listing 17-2.
 @file ArrayMaxHeap.h */ 
 
#ifndef _ARRAY_MAX_HEAP
#define _ARRAY_MAX_HEAP

#include <memory>  // added for smart pointers

#include "PrecondViolatedExcep.h"

template<class ItemType>
class ArrayMaxHeap 
{
private:
	static const int ROOT_INDEX{ 0 };         // Helps with readability
	static const int DEFAULT_CAPACITY{ 21 };  // Small capacity to test for a full heap
	unique_ptr<ItemType[]> items;             // Array of heap items
	int itemCount;                            // Current count of heap items
	int maxItems;                             // Maximum capacity of the heap
   
   // ---------------------------------------------------------------------
   // Most of the private utility methods use an array index as a parameter
   // and in calculations. This should be safe, even though the array is an
   // implementation detail, since the methods are private.
   // ---------------------------------------------------------------------
   
   // Returns the array index of the left child (if it exists).
   int getLeftChildIndex(const int nodeIndex) const;
   
   // Returns the array index of the right child (if it exists).
   int getRightChildIndex(int nodeIndex) const;
   
   // Returns the array index of the parent node.
   int getParentIndex(int nodeIndex) const;
   
   // Tests whether this node is a leaf.
   bool isLeaf(int nodeIndex) const;
   
   // Converts a semiheap to a heap.
   void heapRebuild(int subTreeRootIndex);
   
   // Creates a heap from an unordered array.
   void heapCreate();

   // Added these - Why?  What is the effect of having them here?
   ArrayMaxHeap( const ArrayMaxHeap & right ) {}
   ArrayMaxHeap & operator = ( const ArrayMaxHeap & right ) {}
     
public:
   ArrayMaxHeap( int = DEFAULT_CAPACITY );
   ArrayMaxHeap(const ItemType someArray[], const int arraySize);
   virtual ~ArrayMaxHeap();
   
   // HeapInterface Public Methods:
   bool isEmpty() const;
   int getNumberOfNodes() const;
   int getHeight() const;
   ItemType peekTop() const throw(PrecondViolatedExcep);
   bool add(const ItemType& newData);
   bool remove();
   void clear();
}; // end ArrayMaxHeap

/** Array-based implementation of the ADT heap.
 @file ArrayMaxHeap.cpp */ 
 
#include <cmath> // for log2
#include "PrecondViolatedExcep.h"

template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
}  // end getLeftChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 2;
}  // end getRightChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(const int nodeIndex) const
{
   return (nodeIndex - 1) / 2;
}  // end getParentIndex

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(const int nodeIndex) const
{
   return (getLeftChildIndex(nodeIndex) >= itemCount);
}  // end isLeaf

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(const int subTreeNodeIndex)
{
   if (!isLeaf(subTreeNodeIndex))
   {
      // Find larger child
	   int leftChildIndex{ getLeftChildIndex(subTreeNodeIndex) };   // A left child must exist
	  int largerChildIndex{ leftChildIndex };                      // Make assumption about larger child
	  int rightChildIndex{ getRightChildIndex(subTreeNodeIndex) }; // A right child might not exist
      
      // Check to see whether a right child exists
      if (rightChildIndex < itemCount)
      {
         // A right child exists; check whether it is larger
         if (items[rightChildIndex] > items[largerChildIndex])
            largerChildIndex = rightChildIndex; // Asssumption was wrong
      }  // end if
      
      // If root value is smaller that the value in the larger child, swap values
      if (items[subTreeNodeIndex] < items[largerChildIndex])
      {
         swap(items[largerChildIndex], items[subTreeNodeIndex]);
         
         // Continue with the recursion at that child
         heapRebuild(largerChildIndex);
      }  // end if
   }  // end if
}  // end heapRebuild



template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
   for (int index = itemCount / 2; index >= 0; index--)
   {
      heapRebuild(index);  
   }  // end for
}  // end heapCreate

//******************************************************************
// 
// Public methods start here
//
//******************************************************************

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(int capacity) : itemCount{ 0 }, maxItems{ capacity }
{ 
	if ( maxItems < DEFAULT_CAPACITY )  // do this or throw an exception?
		maxItems = DEFAULT_CAPACITY;
   items = make_unique<ItemType[]>(maxItems);
}  // end default constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::
ArrayMaxHeap(const ItemType someArray[], const int arraySize):
	itemCount{ arraySize }, maxItems{ 2 * arraySize }
{
	if (arraySize < 2)  // check is missing from text code
		throw PrecondViolatedExcep("Invalid array size passed to constructor");

   // Allocate the array
	items = make_unique<ItemType[]>(maxItems);
   
   // Copy given values into the array
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];
   
   // Reorganize the array into a heap
   heapCreate();
} // end constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{  
   items.reset();
}  // end destructor

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const
{
   return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const
{
//   return ceil(log2(itemCount + 1));
	// To generate logarithms for other bases, use the mathematical relation: log base b of a == natural log (a) / natural log (b).
	return static_cast<int>  (ceil( log( itemCount + 1.0 ) / log( 2.0 ) ) );  // From Visual Studio help - log requires a double to be unambiguous
}  // end getHeight

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const
{
   return itemCount;
}  // end getNumberOfNodes

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear()
{
   itemCount = 0;
}  // end clear

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const throw(PrecondViolatedExcep)
{
   if (isEmpty())
      throw PrecondViolatedExcep("Attempted peek into an empty heap.");
   
   return items[0];
} // end peekTop

template<class ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType& newData)
{
	bool isSuccessful{ false };
   if (itemCount < maxItems)
   {
      items[itemCount] = newData;

	  bool inPlace{ false };
	  int newDataIndex{ itemCount };
      while ((newDataIndex > 0) && !inPlace)
      {
		  int parentIndex{ getParentIndex(newDataIndex) };
         if (items[newDataIndex] < items[parentIndex]) 
         {
            inPlace = true;
         }
         else
         {
            swap(items[newDataIndex], items[parentIndex]);
            newDataIndex = parentIndex;
         }  // end if
      }  // end while

      itemCount++;
      isSuccessful = true;
   }  // end if
  
   return isSuccessful;
}  // end add

template<class ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
	bool isSuccessful{ false };
   if (!isEmpty()) 
   {
      items[ROOT_INDEX] = items[itemCount - 1];
      itemCount--;
      heapRebuild(ROOT_INDEX);
      isSuccessful = true;
   }  // end if
   
   return isSuccessful;
}  // end remove






#endif
