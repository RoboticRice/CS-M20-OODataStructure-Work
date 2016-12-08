/** @file Node.h 
    Listing 4-1 */
/**************************************************
	CS M20

	Modified to add copy constructor and assignment operator

**********************************************************/


#ifndef _NODE
#define _NODE

#include <memory>   // Add in for shared_pointer
using namespace std;

template<class ItemType>
class Node
{
private:
   ItemType        item; // A data item
   std::shared_ptr<Node<ItemType>>  next; // Pointer to next node

   Node( const Node<ItemType> & node ) {}
   Node<ItemType> & operator = ( const Node<ItemType> & node ) {}
   
public:
   Node();
   Node(const ItemType& anItem);
   Node(const ItemType& anItem, shared_ptr<Node<ItemType>>  nextNodePtr);
   void setItem(const ItemType& anItem);
   void setNext(shared_ptr<Node<ItemType>>  nextNodePtr);
   ItemType getItem() const ;
   auto getNext() const ;  //Node<ItemType>*
}; // end Node

//#include "Node.cpp"
/** @file Node.cpp
Listing 4-2 */
// #include "Node.h"
// #include <cstddef>



template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
} // end constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, shared_ptr<Node<ItemType>>  nextNodePtr) :
	item{ anItem }, next{ nextNodePtr }
{
} // end constructor

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
} // end setItem

template<class ItemType>
void Node<ItemType>::setNext(shared_ptr<Node<ItemType>>  nextNodePtr)
{
	next = nextNodePtr;
} // end setNext

template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
	return item;
} // end getItem

template<class ItemType>
auto Node<ItemType>::getNext() const
{
	return next;
} // end getNext




#endif