#include "LinkedListValue.h"

template<class ItemType>
LinkedListValue<ItemType>::LinkedListValue()
{
	subList = new LinkedList();
} //end default constructor

template<class ItemType>
LinkedListValue<ItemType>::LinkedListValue(const LinkedListValue<ItemType>& aList)
{
	//TBA
} //end copy constructor

template<class ItemType>
ItemType LinkedListValue<ItemType>::getEntry(int position) const
{
	subList.getEntry(position);
} //end getEntry

//Do not let client use this function
//template<class ItemType>
//ItemType LinkedListValue<ItemType>::replace(int position, const ItemType& newEntry)
//{
//	subList.replace(position, newEntry);
//} //end replace

template<class ItemType>
Node<ItemType>* LinkedListValue<ItemType>::getNodeAt(int position) const
{
	return subList.getNodeAt(position);
} // end getNodeAt

template<class ItemType>
bool LinkedListValue<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
	return subList.insert(newPosition, newEntry);
} //end insert

template<class ItemType>
bool LinkedListValue<ItemType>::remove(int position)
{
	return subList.remove(position);
} //end remove

template<class ItemType>
void LinkedListValue<ItemType>::clear()
{
	subList.clear();
} //end clear

template<class ItemType>
LinkedListValue<ItemType>::~LinkedListValue()
{
	clear();
} //end destructor