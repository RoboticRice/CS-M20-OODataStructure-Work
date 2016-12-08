//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2017 __Pearson Education__. All rights reserved.

// Modified by Martin Chetlen
//  CS M20 Topic D Project

/** A class of nodes for a link-based binary tree.
 Listing 16-2.
 @file BinaryNode.h */
 
#ifndef _BINARY_NODE
#define _BINARY_NODE

#include <memory>
using namespace std;

template<class ItemType>
class BinaryNode
{   
private:
   ItemType              item;           // Data portion
   shared_ptr<BinaryNode<ItemType>>  leftChildPtr;   // Pointer to left child
   shared_ptr<BinaryNode<ItemType>>  rightChildPtr;  // Pointer to right child

public:
	BinaryNode() = default;
   BinaryNode(const ItemType& anItem) : item( anItem ) {}  //added initializer list
   BinaryNode(const ItemType& anItem,
	   shared_ptr<BinaryNode<ItemType>>  leftPtr,
	   shared_ptr<BinaryNode<ItemType>>  rightPtr)  : item( anItem ), leftChildPtr( leftPtr ), rightChildPtr( rightPtr ) {}  //added initializer list

   // add copy constructor
   BinaryNode( const BinaryNode<ItemType> & right ) { *this = right; }

   // add assignment operator
   const BinaryNode<ItemType> &operator = ( const BinaryNode<ItemType> & right );

   void setItem(const ItemType& anItem) { item = anItem; }
   ItemType getItem() const { return item; }
   
   bool isLeaf() const { return ( leftChildPtr == nullptr && rightChildPtr == nullptr ? true : false ); }

   shared_ptr<BinaryNode<ItemType>>  getLeftChildPtr() const { return leftChildPtr; }  // not using auto return
   shared_ptr<BinaryNode<ItemType>>  getRightChildPtr() const  { return rightChildPtr; }
   
   void setLeftChildPtr(shared_ptr<BinaryNode<ItemType>> leftPtr) { leftChildPtr = leftPtr; }
   void setRightChildPtr(shared_ptr<BinaryNode<ItemType>> rightPtr) { rightChildPtr = rightPtr; }
}; // end BinaryNode

// Implementation

template<class ItemType>
const BinaryNode<ItemType> & BinaryNode<ItemType>::operator = ( const BinaryNode<ItemType> & right )
{
	if ( this == &right )
		return *this;

	item = right.item;
	leftChildPtr = right.leftChildPtr;
	rightChildPtr = right.rightChildPtr;

	return *this;
}

#endif 
