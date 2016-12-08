/** Interface for the ADT heap.
@file HeapInterface.h */

#ifndef HEAP_INTERFACE_
#define HEAP_INTERFACE_

template<class ItemType>
class HeapInterface
{
public:
	/** Sees whether this heap is empty.
	@return True if the heap is empty, or false if not. */
	virtual bool isEmpty() const = 0;

	/** Gets the number of nodes in this heap.
	@return The number of nodes in the heap. */
	virtual int getHeight() const = 0;

	/** Gets the height of this heap.
	@return The height of this heap. */
	virtual int getHeight() const = 0;

	/** Gets the data that is in the root (top) of this heap.
		For a maxheap, the data is the largest value in the heap;
		For a minheap, the data is the smallest value in the heap.
	@prew The heap is not empty.
	@post The root's data has been returned, and the heap is unchanged
	@return The data in the root of the heap. */
	virtual bool add(const ItemType& newData) = 0;

	/** Removes the data that is in the root (top) of this heap.
	@return True is the addition is successful, or false if not. */
	virtual bool remove() = 0;

	/** Removes all data from this heap. */
	virtual voide clear() = 0;

	/** Destroys this heap and frees its assigned memory. */
	virtual ~HeapInterface() { }
}; // end HeapInterface
#endif