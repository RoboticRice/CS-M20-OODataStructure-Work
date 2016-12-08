

// Modified by Martin Chetlen
//  CS M20 Topic D Project

/** Link-based implementation of the ADT binary search tree.
 @file BinarySearchTree.h */
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include <memory>
using namespace std;

#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{

private:
 // use rootPtr in BinaryNodeTree
//   BinaryNode<ItemType>* rootPtr;

	void setRootData() = delete; // clients of this class should not have access to this function
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   // Recursively finds where the given node should be placed and
   // inserts it in a leaf at that point.
	shared_ptr<BinaryNode<ItemType>> insertInorder(shared_ptr<BinaryNode<ItemType>>  subTreePtr,
	   shared_ptr<BinaryNode<ItemType>>  newNode);
   

   // Removes the given target value from the tree while maintaining a
   // binary search tree.
	shared_ptr<BinaryNode<ItemType>> removeValue(shared_ptr<BinaryNode<ItemType>>  subTreePtr,
                                     const ItemType target,
                                     bool& success) override;


   // Returns a pointer to the node containing the given value,
   // or nullptr if not found.
   shared_ptr<BinaryNode<ItemType>> findNode(shared_ptr<BinaryNode<ItemType>> treePtr,
                                  const ItemType& target) const;
   
public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   BinarySearchTree() = default;
   BinarySearchTree(const ItemType& rootItem);
   BinarySearchTree(const BinarySearchTree<ItemType>& tree);
   // virtual ~BinarySearchTree();
   
   //------------------------------------------------------------
   // Public Methods Section.
   //------------------------------------------------------------


   bool add(const ItemType& newEntry) override;

   bool remove(const ItemType& anEntry) override;


   ItemType getEntry(const ItemType& anEntry) const  throw(NotFoundException) override;
   bool contains(const ItemType& anEntry) const override;


   //------------------------------------------------------------
   // Overloaded Operator Section.
   //------------------------------------------------------------
   BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rightHandSide);   
}; // end BinarySearchTree

// #include "BinarySearchTree.cpp"

   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.


   //------------------------------------------------------------
   // Recursively finds where the given node should be placed and
   // inserts it in a leaf at that point.
   template<class ItemType>
   shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::insertInorder(shared_ptr<BinaryNode<ItemType>>  subTreePtr,
	   shared_ptr<BinaryNode<ItemType>> newNode)
   {
	   if ( subTreePtr == nullptr )
	   {
		   return newNode;
	   }
	   else if ( newNode->getItem() < subTreePtr->getItem() )
		   subTreePtr->setLeftChildPtr( insertInorder( subTreePtr->getLeftChildPtr(), newNode ) );
	   else
		   subTreePtr->setRightChildPtr( insertInorder( subTreePtr->getRightChildPtr(), newNode ) );

	   return subTreePtr;
   } // end insertInorder

   
   // Returns a pointer to the node containing the given value,
   // or nullptr if not found.
   template<class ItemType>
   shared_ptr<BinaryNode<ItemType>>  BinarySearchTree<ItemType>::findNode(shared_ptr<BinaryNode<ItemType>> treePtr,
                                  const ItemType& target) const
   {
	   if ( treePtr != nullptr && treePtr->getItem() != target )  // order matters here
	   {
		   if ( target < treePtr->getItem() )
			   return findNode( treePtr->getLeftChildPtr(), target );
		   else
			   return findNode( treePtr->getRightChildPtr(), target );
	   }
	   else
		   return treePtr;
   }  // end findNode


   // Removes the given target value from the tree while maintaining a
   // binary search tree.
   template<class ItemType>
   shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr,
																const ItemType target,
																bool& success)
{
	if ( subTreePtr == nullptr )  // target not found
	{
		success = false;
		return subTreePtr;
	}

// ItemType it = subTreePtr->getItem();  // ***********************

	if( subTreePtr->getItem() == target )  // found target
	{
		success = true;
		return this->foundRemoveValue( subTreePtr );
	}  // end found target
	else  // Did not find target - keep trying
	{
		if ( target < subTreePtr->getItem () )
			subTreePtr->setLeftChildPtr( removeValue( subTreePtr->getLeftChildPtr(), target, success ) );
		else
			subTreePtr->setRightChildPtr( removeValue( subTreePtr->getRightChildPtr(), target, success ) );

		return subTreePtr;
	}
}  // end removeValue


   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------

   template<class ItemType>
   BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem) : BinarySearchTree<ItemType>::BinaryNodeTree( rootItem ) {}
 
   template<class ItemType>
   BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& tree) : BinarySearchTree<ItemType>::BinaryNodeTree( tree ) {}

   //------------------------------------------------------------
   // Public Methods Section.
   //------------------------------------------------------------

   template<class ItemType>
   bool BinarySearchTree<ItemType>::add(const ItemType& newEntry)
   {
	   shared_ptr<BinaryNode<ItemType>> newNode = make_shared<BinaryNode<ItemType>>( newEntry );
	   this->rootPtr = insertInorder( this->rootPtr, newNode );

	   return true;
   }  // end InsertInorder

   template<class ItemType>
   bool BinarySearchTree<ItemType>::remove(const ItemType& anEntry)
{								
	if ( this->isEmpty() )
		return false;

	bool success = false;

	this->rootPtr = this->removeValue( this->rootPtr, anEntry, success );

	return success;
}  // end remove

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
	// bool success = false;

	auto temp = this->findNode( this->rootPtr, anEntry );

	if ( temp != nullptr )
		return true;
	else
		return false;
}  // end contains


template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	// bool success = false;

	auto temp = this->findNode( this->rootPtr, anEntry );

	if ( temp == nullptr )
		throw NotFoundException( "The entry was not found " );

	return temp->getItem();
}  // end getEntry


   template<class ItemType>
   BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType>& rightHandSide)
   {
	  BinaryNodeTree<ItemType>::operator = ( rightHandSide );

	  return *this;
   }




#endif
