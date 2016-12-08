//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2017 __Pearson Education__. All rights reserved.

// Modified by Martin Chetlen
//  CS M20 Topic D Project

/** ADT binary tree: Link-based implementation.
 Listing 16-3.
 @file BinaryNodeTree.h */
 
#ifndef _BINARY_NODE_TREE
#define _BINARY_NODE_TREE

#include <iostream>
#include <memory>
#include <algorithm>  // for max in getHeightHelper

using namespace std;

#include  "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PrecondViolatedExcept.h"
#include "NotFoundException.h"

template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
protected:
	shared_ptr<BinaryNode<ItemType>> rootPtr;  // what are the advantages and drawbacks of making this protected?
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   
   int getHeightHelper(shared_ptr<BinaryNode<ItemType>>  subTreePtr) const;
   int getNumberOfNodesHelper(shared_ptr<BinaryNode<ItemType>>  subTreePtr) const;
   
   // Recursively deletes all nodes from the tree.
   void destroyTree(shared_ptr<BinaryNode<ItemType>>  subTreePtr);
   
   // Recursively adds a new node to the tree in a left/right fashion to
   // keep the tree balanced.
   shared_ptr<BinaryNode<ItemType>>  balancedAdd(shared_ptr<BinaryNode<ItemType>>  subTreePtr,
	   shared_ptr<BinaryNode<ItemType>>  newNodePtr);
   
   // Removes the target value from the tree by calling moveValuesUpTree
   // to overwrite value with value from child.
   virtual shared_ptr<BinaryNode<ItemType>> removeValue(shared_ptr<BinaryNode<ItemType>>  subTreePtr,
                                     const ItemType target, bool& success);

   // added
   shared_ptr<BinaryNode<ItemType>> foundRemoveValue(shared_ptr<BinaryNode<ItemType>>  subTreePtr );
   // added
   shared_ptr<BinaryNode<ItemType>> getInOrderSuccessor(shared_ptr<BinaryNode<ItemType>> subTreePtr );
   
   // Copies values up the tree to overwrite value in current node until
   // a leaf is reached; the leaf is then removed, since its value is
   // stored in the parent.
 //  BinaryNode<ItemType>* moveValuesUpTree(shared_ptr<BinaryNode<ItemType>>  subTreePtr);
   
   // Recursively searches for target value in the tree by using a
   // preorder traversal.
   shared_ptr<BinaryNode<ItemType>> findNode(shared_ptr<BinaryNode<ItemType>>  treePtr,
                                  const ItemType& target,
                                  bool& success) const;
   
   // Copies the tree rooted at treePtr and returns a pointer to
   // the copy.
   shared_ptr<BinaryNode<ItemType>>  copyTree(const shared_ptr<BinaryNode<ItemType>>  treePtr) const;
   
   // Recursive traversal helper methods:
   void preorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>>  treePtr) const;
   void inorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>>  treePtr) const;
   void postorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>>  treePtr) const;
   
public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
	BinaryNodeTree() = default;
   BinaryNodeTree(const ItemType& rootItem);

   BinaryNodeTree(const ItemType& rootItem,
                  const shared_ptr<BinaryNodeTree<ItemType>>  leftTreePtr,
                  const shared_ptr<BinaryNodeTree<ItemType>>  rightTreePtr);

   BinaryNodeTree(const BinaryNodeTree<ItemType> &  tree);
   virtual ~BinaryNodeTree();  // why virtual?
   
   //------------------------------------------------------------
   // Public BinaryTreeInterface Methods Section.
   //------------------------------------------------------------
   bool isEmpty() const;
   int getHeight() const;
   int getNumberOfNodes() const;
   ItemType getRootData() const throw(PrecondViolatedExcept);
   void setRootData(const ItemType& newData);
   bool add(const ItemType& newData); // Adds a node
   bool remove(const ItemType& data); // Removes a node
   void clear();
   ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
   bool contains(const ItemType& anEntry) const;
   
   //------------------------------------------------------------
   // Public Traversals Section.
   //------------------------------------------------------------
   void preorderTraverse(void visit(ItemType&)) const;
   void inorderTraverse(void visit(ItemType&)) const;
   void postorderTraverse(void visit(ItemType&)) const;
   
   //------------------------------------------------------------
   // Overloaded Operator Section.
   //------------------------------------------------------------
   BinaryNodeTree& operator=(const BinaryNodeTree& rightHandSide);
}; // end BinaryNodeTree

//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(shared_ptr<BinaryNode<ItemType>>  subTreePtr) const
{
   if (subTreePtr == nullptr)
      return 0;
   else
      return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), 
                     getHeightHelper(subTreePtr->getRightChildPtr()));
}  // end getHeightHelper

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(shared_ptr<BinaryNode<ItemType>>  subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr())
				 + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
} // end getNumberOfNodesHelper

template<class ItemType>
shared_ptr<BinaryNode<ItemType>>  BinaryNodeTree<ItemType>::balancedAdd(shared_ptr<BinaryNode<ItemType>>  subTreePtr,
	shared_ptr<BinaryNode<ItemType>>  newNodePtr)
{
   if (subTreePtr == nullptr)
      return newNodePtr;
   else
   {
      auto leftPtr = subTreePtr->getLeftChildPtr();
      auto rightPtr = subTreePtr->getRightChildPtr();
      
      if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
      {
         rightPtr = balancedAdd(rightPtr , newNodePtr);
         subTreePtr->setRightChildPtr(rightPtr );
      }
      else
      {
         leftPtr = balancedAdd(leftPtr, newNodePtr);
         subTreePtr->setLeftChildPtr(leftPtr);
      }  // end if
      
      return subTreePtr;
   }  // end if
}  // end balancedAdd

template<class ItemType>
shared_ptr<BinaryNode<ItemType>>  BinaryNodeTree<ItemType>::copyTree(const shared_ptr<BinaryNode<ItemType>>  treePtr) const
{
	shared_ptr<BinaryNode<ItemType>> newTreePtr;
   
   // Copy tree nodes during a preorder traversal
   if (treePtr != nullptr)
   {
      // Copy node
	   newTreePtr = make_shared<BinaryNode<ItemType>> (treePtr->getItem(), nullptr, nullptr);
	   newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
      newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
   }  // end if
   
   return newTreePtr;
}  // end copyTree

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(shared_ptr<BinaryNode<ItemType>> subTreePtr)
{
   if (subTreePtr != nullptr)
   {
      destroyTree(subTreePtr->getLeftChildPtr());
      destroyTree(subTreePtr->getRightChildPtr());
      subTreePtr.reset(); // decrement reference count
   }  // end if
}  // end destroyTree

// added
template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::findNode(shared_ptr<BinaryNode<ItemType>>  treePtr,
	const ItemType& target,
	bool& success) const
{
	if ( treePtr == nullptr )  // target not found
		return treePtr;

	shared_ptr<BinaryNode<ItemType>> temp;

	if ( treePtr->getItem() == target )  // found it
	{
		success = true;
		return treePtr;
	}
	else
	{
		temp  = findNode( treePtr->getLeftChildPtr(), target, success );

		if ( !success )
		  temp = findNode( treePtr->getRightChildPtr(), target, success );
	}

	return temp;  // return at function scope not in the else
} // end findNode


// added
template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::removeValue(shared_ptr<BinaryNode<ItemType>>  subTreePtr,
                                     const ItemType target, bool& success)
{
	if ( subTreePtr == nullptr )  // target not found
	{
		success = false;
		return subTreePtr;
	}

	if( subTreePtr->getItem() == target )  // found target
	{
		success = true;
		return foundRemoveValue( subTreePtr );
	}  // end found target
	else  // Did not find target - keep trying
	{
		subTreePtr->setLeftChildPtr( removeValue( subTreePtr->getLeftChildPtr(), target, success ) );

		if ( !success )
			subTreePtr->setRightChildPtr( removeValue( subTreePtr->getRightChildPtr(), target, success ) );

		return subTreePtr;
	}
}  // end removeValue


// added
template<class ItemType>
shared_ptr<BinaryNode<ItemType>>  BinaryNodeTree<ItemType>::foundRemoveValue(shared_ptr<BinaryNode<ItemType>> subTreePtr )
{
	if( subTreePtr->isLeaf() )
	{
		subTreePtr.reset();
		return nullptr;
	}
	else if ( subTreePtr->getLeftChildPtr() == nullptr )  // single child - right
	{
		shared_ptr<BinaryNode<ItemType>> temp = subTreePtr->getRightChildPtr();

		subTreePtr.reset();

		return temp;
	}
	else if ( subTreePtr->getRightChildPtr() == nullptr ) // single child - left
	{
		shared_ptr<BinaryNode<ItemType>> temp = subTreePtr->getLeftChildPtr();

		subTreePtr.reset();

		return temp;
	}
	else   // two children
	{
		shared_ptr<BinaryNode<ItemType>> toDel = getInOrderSuccessor( subTreePtr->getRightChildPtr() );
		subTreePtr->setItem( toDel->getItem() );

		if ( subTreePtr->getRightChildPtr() == toDel )  // if the right child IS the inorder successor
			subTreePtr->setRightChildPtr( toDel->getRightChildPtr() );

		toDel.reset();
		return subTreePtr;
	}
}

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::getInOrderSuccessor(shared_ptr<BinaryNode<ItemType>> subTreePtr )
{
	shared_ptr<BinaryNode<ItemType>> parent;

	while( subTreePtr->getLeftChildPtr() != nullptr )
	{
		parent = subTreePtr;
		subTreePtr = subTreePtr->getLeftChildPtr();
	}

	if ( parent != nullptr )  // if the right child of the original subTreePtr is NOT the inorder successor
		parent->setLeftChildPtr( subTreePtr->getRightChildPtr() );

	return subTreePtr;
} // end getInOrderSuccessor

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const
{
   if (treePtr != nullptr)
   {
      inorder(visit, treePtr->getLeftChildPtr());
      ItemType theItem = treePtr->getItem();
      visit(theItem);
      inorder(visit, treePtr->getRightChildPtr());
   }  // end if
}  // end inorder

// added
template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const
{
   if (treePtr != nullptr)
   {
      ItemType theItem = treePtr->getItem();
      visit(theItem);
      preorder(visit, treePtr->getLeftChildPtr());
      preorder(visit, treePtr->getRightChildPtr());
   }  // end if
}  // end preorder

// added
template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const
{
   if (treePtr != nullptr)
   {
      postorder(visit, treePtr->getLeftChildPtr());
      postorder(visit, treePtr->getRightChildPtr());
      ItemType theItem = treePtr->getItem();
      visit(theItem);
   }  // end if
}  // end preorder


//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

#if 0
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{
}  // end default constructor
#endif

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem) : rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr))
{
}  // end constructor


template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
                                         const shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
                                         const shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr)
{
    rootPtr = make_shared<BinaryNode<ItemType>>(rootItem, copyTree(leftTreePtr->rootPtr),
                                                 copyTree(rightTreePtr->rootPtr));
}  // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType> & treePtr)
{
   rootPtr = copyTree(treePtr.rootPtr);
}  // end copy constructor

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
   destroyTree(rootPtr);
}  // end destructor

//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
	auto newNodePtr = make_shared<BinaryNode<ItemType>>(newData);
   rootPtr = balancedAdd(rootPtr, newNodePtr);
   return true;
}  // end add

// added
template<class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const
{
	bool success = false;

	auto temp = findNode( rootPtr, anEntry, success );

	return success;
}  // end contains

// added
template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	bool success = false;

	auto temp = findNode( rootPtr, anEntry, success );

	if ( !success )
		throw NotFoundException( "Entry was not found " );

	return temp->getItem();
}  // end getEntry


template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
	return rootPtr == nullptr;
}  // end isEmpty

// added
template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
	return getHeightHelper( rootPtr );
}  // end getHeight

// added
template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
	return getNumberOfNodesHelper( rootPtr );
} // end getNumberOfNodes

// added
template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const throw(PrecondViolatedExcept)
{
	if ( isEmpty() )
		throw PrecondViolatedExcept( "getRootData called with empty tree" );

	return rootPtr->getItem();
}  // end getRootData

// added
template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData( const ItemType& newData )
{
	if ( isEmpty() )
		rootPtr = make_shared<BinaryNode<ItemType>>( newData, nullptr, nullptr );
	else
		rootPtr->setItem( newData );
}  // end setRootData

// added
template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& data) // Removes a node
{								
	if ( isEmpty() )
		return false;

	bool success = false;

	rootPtr = removeValue( rootPtr, data, success );

	return success;
}  // end remove

// added
template<class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
	destroyTree( rootPtr );
	rootPtr.reset();
} // end clear


//added
template<class ItemType>
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree<ItemType>& rightHandSide)
{
	if ( this == &rightHandSide )
		return *this;

	clear();

	rootPtr = copyTree( rightHandSide.rootPtr );

	return *this;
}

//////////////////////////////////////////////////////////////
//      Public Traversals Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
   inorder(visit, rootPtr);
}  // end inorderTraverse

//added
template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
   preorder(visit, rootPtr);
}  // end preorderTraverse

// added
template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
   postorder(visit, rootPtr);
}  // end inorderTraverse




#endif
