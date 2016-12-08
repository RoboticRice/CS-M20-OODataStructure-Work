/** Link-based implimentation of the ADT binary search tree.
@file BinarySearchTree.h */

#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"
#include <memory>

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
//I decided to comment out the lines that were originally in the BST header file from the textbook
//so I could see the changes i made, and so I knew which functions were expected to work with the BST,
//that were coming from the BNT.
private:
	//std::shared_ptr<BinaryNode<ItemType>> rootPtr;
protected:
	//------------------------------------------------------------
	//	Protected Utility Methods Section.
	//	Recursive helper methods for the public methods
	//------------------------------------------------------------
	// Places a given node at its proper position in this binary
	// search tree
	std::shared_ptr<BinaryNode<ItemType>> placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		std::shared_ptr<BinaryNode<ItemType>> newNode); //replaced auto return type

	// Removes the given target value from the tree while maintaining
	// a binary search tree.
	std::shared_ptr<BinaryNode<ItemType>> removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		const ItemType target,
		bool& isSuccessful) override; //replaced auto return type

	// Removes a given node from a tree while maintaining a binary search tree
	//auto removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr);

	// Removes the leftmost node in the left subtree of the node
	// pointed to by nodePtr.
	// Sets inorderSuccessor to the value in this node.
	// Returns a pointer to the revised subtree.
	//auto removeLeftMostNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
	//	ItemType& inorderSuccessor);

	// Returns a pointer to the node containing the given value,
	// or nullptr if not found.
	std::shared_ptr<BinaryNode<ItemType>> findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
		const ItemType& target) const; //replaced auto return type

public:
	//------------------------------------------------------------
	//	Constructor and Destructor Section.
	//------------------------------------------------------------
	//BinarySearchTree();
	//BinarySearchTree(const ItemType& rootItem);
	//BinarySearchTree(const BinarySearchTree<ItemType>& tree);
	//virtual ~BinarySearchTree();

	//------------------------------------------------------------
	//	Public Methods Section.
	//------------------------------------------------------------
	//bool isEmpty() const;
	//int getHeight() const;
	//int getNumberOfNodes() const;
	//ItemType getRootData() const throw(PrecondViolatedExcept);
	//void setRootData(const ItemType& newData);
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& target);
	//void clear();
	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;

	//------------------------------------------------------------
	//	Public Traversals Section.
	//------------------------------------------------------------
	//void preorderTraverse(void visit(ItemType&)) const;
	//void inorderTraverse(void visit(ItemType&)) const;
	//void postorderTraverse(void visit(ItemType&)) const;

	//------------------------------------------------------------
	//	Overloaded Operator Section.
	//------------------------------------------------------------
	BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rightHandSide);
}; // end BinarySearchTree

//#include "BinarySearchTree.cpp"
/************************************************************************************************************************************************************************************************************/
//Begin of .cpp file

//-----------------------------------
//
//		End CONSTRUCTORS
//
//		Start PROTECTED
//
//-----------------------------------

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, std::shared_ptr<BinaryNode<ItemType>> newNode)
{
	if (subTreePtr == nullptr)
		return newNode;
		//exit point
	if (newNode->getItem() >= subTreePtr->getItem()) //= to handle duplicates
	{
		auto rightPtr = subTreePtr->getRightChildPtr();
		rightPtr = placeNode(rightPtr, newNode);
		subTreePtr->setRightChildPtr(rightPtr);
	}
	else //if (newNode->getItem() > subTreePtr->getItem())
	{
		auto leftPtr = subTreePtr->getLeftChildPtr();
		leftPtr = placeNode(leftPtr, newNode);
		subTreePtr->setLeftChildPtr(leftPtr);
	}
	return subTreePtr;
} // end balancedAdd

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool& isSuccessful)
{
	if (subTreePtr == nullptr)
		isSuccessful = false;
	else if (subTreePtr->getItem() == target)
	{
		subTreePtr = removeNode(subTreePtr);
		isSuccessful = true;
	}
	else 
	{
		std::shared_ptr<BinaryNode<ItemType>> tempPtr = nullptr;
		if (subTreePtr->getItem() > target) 
		{
			tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
			subTreePtr->setLeftChildPtr(tempPtr);
		}
		else
		{
			tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
			subTreePtr->setRightChildPtr(tempPtr);
		}
	}
	return subTreePtr;
	/* Tried this first, but then realize it was returning the pointer to the nodeToBeRemoved, when I needed the pointer to the parent of that node
	else
	{ 
		std::shared_ptr<BinaryNode<ItemType>> tempPtr = nullptr;
		tempPtr = findNode(subTreePtr, target);
		if (tempPtr == nullptr)
			isSuccessful = false;
		else
		{	
			//This will only happen if found
			subTreePtr = removeNode(tempPtr);
			isSuccessful = true;
		}
	}
	*/
	return subTreePtr;
} // end removeValue

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType& target) const
{
	std::shared_ptr<BinaryNode<ItemType>> tempPtr = nullptr;
	if (treePtr == nullptr) {}
		//Do nothing, exit the if statement
	else if (treePtr->getItem() == target) //Found the target
		tempPtr = treePtr;
	else if (treePtr->getItem() > target)
		tempPtr = findNode(treePtr->getLeftChildPtr(), target);
	else //treePtr < target
		tempPtr = findNode(treePtr->getRightChildPtr(), target);
	return tempPtr;//If not found, then tempPtr should still be nullptr, otherwise tempPtr will be the ptr to the location of the node that was found
} // end findNode

//-----------------------------------
//
//		End PROTECTED
//
//		Start PUBLIC
//
//-----------------------------------

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData)
{
	auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newData);
	setRootPtr(placeNode(getRootPtr(), newNodePtr));

	return true;
} // end add

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& data)
{
	bool isSuccessful{ false };
	setRootPtr(removeValue(getRootPtr(), data, isSuccessful));
	return isSuccessful;
} // end remove

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	std::shared_ptr<BinaryNode<ItemType>> tempPtr = nullptr;
	tempPtr = findNode(getRootPtr(), anEntry);
	if (tempPtr==nullptr)
		throw NotFoundException("getEntry - Entry not found");
	return tempPtr->getItem();
} // end getEntry

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
	return (findNode(getRootPtr(), anEntry) != nullptr) ? true : false;
} // end contains

template<class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType>& rightHandSide)
{
	setRootPtr(copyTree(rightHandSide->getRootPtr()));
} // end overloaded = operator

#endif