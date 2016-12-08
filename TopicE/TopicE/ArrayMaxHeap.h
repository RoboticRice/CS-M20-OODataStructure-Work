/** Array-based implimentation of the ADT heap.
@file ArrayMaxHeap.h */
#ifndef ARRAY_MAX_HEAP_
#define ARRAY_MAX_HEAP_

#include <memory> // This was NOT in the textbook, but is REQUIRED for unique_ptr! If this is left out, build will fail. NOTE* It was not in any included files either...
//#include"HeapInterface.h"
#include "PrecondViolatedExcept.h"

template<class ItemType>
class ArrayMaxHeap //: public HeapInterface<ItemType>
{
private:
	static const int ROOT_INDEX = 0;		// Helps with readability
	static const int DEFAULT_CAPACITY = 21;	// Small capacity for testing
	std::unique_ptr<ItemType[]> items;		// Array of heap items
	int itemCount;							// Current count of heap items
	int maxItems;							// Max capacity of the heap 

	// ---------------------------------------------------------------------
	// Most of the private utility methods use an array index as a parameter
	// and in calculations. this should be safe, even though the array is an
	// implimentation detail, since the methods are private.
	// ---------------------------------------------------------------------

	// Returns the array index of the left child (if it exists).
	int getLeftChildIndex(const int nodeIndex) const;

	// Returns the array index of the right child (if it exists).
	int getRightChildIndex(const int nodeIndex) const;

	// Returns the array index of the parent node.
	int getParentIndex(int nodeIndex) const;

	// Tests whether this node is a leaf.
	bool isLeaf(int nodeIndex) const;

	// Converts a semiheap to a heap.
	void heapRebuild(int nodeIndex);

	// Creates a heap from an unordered array.
	void heapCreate();

public:
	ArrayMaxHeap();
	ArrayMaxHeap(const int arraySize);
	ArrayMaxHeap(const ItemType someArray[], const int arraySize);
	virtual ~ArrayMaxHeap();

protected:
	// HeapInterface Public Methods:
	bool isEmpty() const;
	int getNumberOfNodes() const;
	int getHeight() const;
	ItemType peekTop() const throw(PrecondViolatedExcept);
	bool add(const ItemType& newData);
	bool remove();
	void clear();
}; // end ArrayMaxHeap
//#include "ArrayMaxHeap.cpp"

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
	// Allocate the array
	items = std::make_unique<ItemType[]>(maxItems); //this line creates error C3931 '_Elem': cannot call a function that has restriction specifiers that are incompatible with the ambient context when no default constructor for topicEData
} // end default constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const int arraySize) : itemCount(0), maxItems(arraySize)
{
	// Allocate the array
	items = std::make_unique<ItemType[]>(maxItems);
} // end default constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const ItemType someArray[], const int arraySize) : itemCount(arraySize), maxItems(2 * arraySize)
{
	// Allocate the array
	items = std::make_unique<ItemType[]>(maxItems);

	// Copy given values into the array
	for (int i = 0; i < itemCount; i++)
		items[i] = someArray[i];

	// Reorganize the array into a heap
	heapCreate();
} // end constructor

template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
	return (2 * nodeIndex) + 1;
} // end getLeftChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
	return (2 * nodeIndex) + 2;
} // end getRightChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(const int nodeIndex) const
{
	return (nodeIndex - 1) / 2;
} // end getParentIndex

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(int nodeIndex) const
{
	return (items[getLeftChildIndex(nodeIndex)]==0 || items[getRightChildIndex(nodeIndex)]==0); //HELP THIS!!!!???
} // end isLeaf

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(int nodeIndex)
{
	if (!isLeaf(nodeIndex))
	{
		int leftChildIndex = 2 * nodeIndex + 1;
		int rightChildIndex = leftChildIndex + 1;
		int largerChildIndex = rightChildIndex;

		if ((largerChildIndex >= itemCount) || (items[leftChildIndex] > items[rightChildIndex]))
			largerChildIndex = leftChildIndex;

		if (items[largerChildIndex] > items[nodeIndex])
		{
			ItemType placeholder = items[nodeIndex];
			items[nodeIndex] = items[largerChildIndex];
			items[largerChildIndex] = placeholder;
			
			heapRebuild(largerChildIndex);
		}
	}
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
	for (int index = itemCount / 2 - 1; index >= 0; index--)
		heapRebuild(index);
} // end heapCreate

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const
{
	return (itemCount==0);
} // end isLeaf 

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const
{
	return itemCount;
} // end getNumberOfNodes

template<class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const
{
	return ceil(log(itemCount + 1.0) / log(2.0));
} // end getHeight

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const throw(PrecondViolatedExcept)
{
	if (isEmpty())
		throw PrecondViolatedExcept("Attempted peek into an empty heap.");
	return items[0];
} // end peekTop

template<class ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType& newData)
{
	items[itemCount] = newData;

	int newDataIndex = itemCount;
	bool inPlace = false;
	while ((newDataIndex >= 0) && !inPlace)
	{
		int parentIndex = (newDataIndex - 1)/2;
		if (items[newDataIndex] <= items[parentIndex])
			inPlace = true;
		else
		{
			items[newDataIndex] = items[parentIndex];
			items[parentIndex] = newData;
			newDataIndex = parentIndex;
		}
	}
	itemCount++;
	return inPlace;
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
	items[ROOT_INDEX] = items[itemCount-1];
	itemCount--;
	heapRebuild(ROOT_INDEX);
	return true;
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear()
{
	itemCount = 0;
}

template<class ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
	clear();
}

#endif