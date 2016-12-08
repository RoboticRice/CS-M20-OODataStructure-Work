/** ADT binary tree: Link-base implementation.
@file BinaryNodeTree.h */

#ifndef BINARY_NODE_TREE_
#define BINARY_NODE_TREE_

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PrecondViolatedExcept.h"
#include "NotFoundException.h"
#include <memory>
#include <algorithm>

template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
private:
	std::shared_ptr<BinaryNode<ItemType>> rootPtr;

protected:
//---------------------------------------------------
//	Protected Utility Methods Section:
//	Recursive helper methods for the public methods.
//---------------------------------------------------
	int getHeightHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const;
	int getNumberOfNodesHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const;

	//Recursively add a new node to the tree in a left/right fashion to keep tree balanced.
	std::shared_ptr<BinaryNode<ItemType>> balancedAdd(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		std::shared_ptr<BinaryNode<ItemType>> newNodePtr); //replaced auto return type

	//Removes this target value from the tree.
	virtual std::shared_ptr<BinaryNode<ItemType>> removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		const ItemType target, bool& isSuccessful); //replaced auto return type

	//Removes the data item in the node pointed to by notePtr
	//returns a pointer to the node at this location after the removal
	//Uses removeLeftmostNode to ensure replaced node is inorderSuccessor
	std::shared_ptr<BinaryNode<ItemType>> removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr); //Added function

	//Removes the leftmost node in the left subtree of the node pointed to by nodePtr.
	//Sets inorderSuccessor to the value in this node.
	//Returns a pointer to the revised subtree.
	std::shared_ptr<BinaryNode<ItemType>> removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr, ItemType& inorderSuccessor); //Added function

	//Copies values up the tree to overwrite value in current node until
	//a leaf is reached; the leaf is then removed, since its value is stored in the parent.
	//std::shared_ptr<BinaryNode<ItemType>> moveValuesUpTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr); //replaced auto return type
	//Removed this function due to it not being used.

	//Recursivly searches for target value.
	virtual std::shared_ptr<BinaryNode<ItemType>> findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
		const ItemType& target, bool& isSuccessful) const; //replaced auto return type

	//Copies the tree rooted at treePtr and returns a pointer to the root of the copy
	std::shared_ptr<BinaryNode<ItemType>> copyTree(const std::shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const; //replaced auto return type

	//Recursivly deletes all nodes from the tree.
	void destroyTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr);

	//Recursive traversal helper methods:
	void preorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
	void inorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
	void postorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
//------------------------------------------------------
//	My functions I added to access rootPtr
//------------------------------------------------------
	void setRootPtr(std::shared_ptr<BinaryNode<ItemType>> treePtr);
	std::shared_ptr<BinaryNode<ItemType>> getRootPtr() const;

public:
//------------------------------------------------------
//	Constructor and Destructor Section.
//------------------------------------------------------
	BinaryNodeTree();
	BinaryNodeTree(const ItemType& rootItem);
	BinaryNodeTree(const ItemType& rootItem,
		const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr, 
		const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr);
	BinaryNodeTree(const std::shared_ptr<BinaryNodeTree<ItemType>>& tree);
	virtual ~BinaryNodeTree();

//------------------------------------------------------
//	Public BinaryTreeInterface Methods Section
//------------------------------------------------------
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const throw(PrecondViolatedExcept);
	void setRootData(const ItemType& newData);
	bool add(const ItemType& newData); // Adds an item to the tree
	bool remove(const ItemType& data); // Removes specified item from the tree
	void clear();
	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;

//------------------------------------------------------
//	Public Traversals Section
//------------------------------------------------------
	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;

//------------------------------------------------------
//	Overloaded Operator Section.
//------------------------------------------------------
	BinaryNodeTree& operator=(const BinaryNodeTree& rightHandSide);
}; // end BinaryNodeTree

//#include "BinaryNodeTree.cpp"
/************************************************************************************************************************************************************************************************************/
//Begin of .cpp file

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{
} // end default constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem) : rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr))
{
} // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
	const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
	const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr) : rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem, copyTree(leftTreePtr->rootPtr), copyTree(rightTreePtr->rootPtr)))
{
} // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const std::shared_ptr<BinaryNodeTree<ItemType>>& tree)
//BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr)
{
	rootPtr = copyTree(tree.rootPtr); //rootPtr = copyTree(treePtr.rootPtr);
	//Why was this not written correctly in the book? Version error, or other reason?
} // end copy constructor

//-----------------------------------
//
//		End CONSTRUCTORS
//
//		Start PROTECTED
//
//-----------------------------------

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
} // end getHeightHelper

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
} // end getNumberOfNodesHelper

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::balancedAdd(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, std::shared_ptr<BinaryNode<ItemType>> newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;
	else
	{
		auto leftPtr = subTreePtr->getLeftChildPtr();
		auto rightPtr = subTreePtr->getRightChildPtr();

		if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
		{
			rightPtr = balancedAdd(rightPtr, newNodePtr);
			subTreePtr->setRightChildPtr(rightPtr);
		}
		else
		{
			leftPtr = balancedAdd(leftPtr, newNodePtr);
			subTreePtr->setLeftChildPtr(leftPtr);
		} // end if

		return subTreePtr;
	} // end if
} // end balancedAdd

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool& isSuccessful)
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
		tempPtr = subTreePtr->getLeftChildPtr();
		if (tempPtr != nullptr)
		{
			tempPtr = removeValue(tempPtr, target, isSuccessful);
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
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr)
{
	if (nodePtr->isLeaf())
	{
		//if no children
		nodePtr = nullptr;
		return nodePtr;
	}
	else if ((nodePtr->getLeftChildPtr() != nullptr) && (nodePtr->getRightChildPtr() != nullptr))
	{
		//if two children
		std::shared_ptr<BinaryNode<ItemType>> tempPtr = nullptr;
		ItemType newNodeValue;
		tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue);
		nodePtr->setRightChildPtr(tempPtr);
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
	else
	{
		//if one child
		std::shared_ptr<BinaryNode<ItemType>> nodeToConnectPtr = nullptr;
		if (nodePtr->getLeftChildPtr() != nullptr) //if has left child only
			nodeToConnectPtr = nodePtr->getLeftChildPtr();
		else //if has right child only
			nodeToConnectPtr = nodePtr->getRightChildPtr();

		return nodeToConnectPtr;
	} // end if
	  //will never reach this point
} // end removeNode

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr, ItemType& inorderSuccessor)
{
	if (nodePtr->getLeftChildPtr() == nullptr)
	{
		inorderSuccessor = nodePtr->getItem();
		return removeNode(nodePtr);
	}
	else
	{
		std::shared_ptr<BinaryNode<ItemType>> tempPtr = nullptr;
		tempPtr = removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor);
		nodePtr->setLeftChildPtr(tempPtr);
		return nodePtr;
	}
} // end removeLeftmostNode

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType& target, bool& isSuccessful) const
{
	std::shared_ptr<BinaryNode<ItemType>> tempPtr = nullptr;
	if (treePtr == nullptr)
	{
		isSuccessful = false;
	}
	else if (treePtr->getItem() == target)
	{
		//Found the target
		tempPtr = treePtr;
		isSuccessful = true;
	}
	else if (((tempPtr = findNode(treePtr->getLeftChildPtr(), target, isSuccessful)) != nullptr) || ((tempPtr = findNode(treePtr->getRightChildPtr(), target, isSuccessful)) != nullptr)) {}
		//if target is found in Left, then the second half of the || operator will not happen.
		//If target is found in right or left, then target found
	// end if

	return tempPtr;//If not found, then tempPtr should still be nullptr, otherwise tempPtr will be the ptr to the location of the node that was found
} // end findNode

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::copyTree(const std::shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const
{
	std::shared_ptr<BinaryNode<ItemType>> newTreePtr;

	// Copy tree nodes during a preorder traversal
	if (oldTreeRootPtr != nullptr)
	{
		// Copy node
		newTreePtr = std::make_shared<BinaryNode<ItemType>>(oldTreeRootPtr->getItem(), nullptr, nullptr);
		newTreePtr->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr()));
		newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
	} // end if
	// Else tree is empty (newTreePtr is nullptr)

	return newTreePtr;
} // end copyTree

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		subTreePtr.reset(); // Decrement reference count to node
	} // end if
} // end destroyTree

template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		preorder(visit, treePtr->getLeftChildPtr());
		preorder(visit, treePtr->getRightChildPtr());
	} // end if
} // end preorder

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		inorder(visit, treePtr->getLeftChildPtr());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		inorder(visit, treePtr->getRightChildPtr());
	} // end if
} // end inorder

template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		postorder(visit, treePtr->getLeftChildPtr());
		postorder(visit, treePtr->getRightChildPtr());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
	} // end if
} // end postorder

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootPtr(std::shared_ptr<BinaryNode<ItemType>> treePtr)
{
	rootPtr = treePtr;
} // end setRootPtr

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::getRootPtr() const
{
	return rootPtr;
} // end getRootPtr

//-----------------------------------
//
//		End PROTECTED
//
//		Start PUBLIC
//
//-----------------------------------

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
	return (rootPtr == nullptr);
} // end isEmpty

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
} // end getHeight

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(rootPtr);
} // end getNumberOfNodes

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const throw(PrecondViolatedExcept)
{
	if (isEmpty())
		throw PrecondViolatedExcept("getRootData - Root empty");
	return rootPtr->getItem();
} // end getRootData

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newData)
{
	rootPtr->setItem(newData);
} // end setRootData

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
	auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newData);
	rootPtr = balancedAdd(rootPtr, newNodePtr);

	return true;
} // end add

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& data)
{
	bool isSuccessful { false };
	rootPtr = removeValue(rootPtr, data, isSuccessful);
	return isSuccessful;
} // end remove

template<class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
	destroyTree(rootPtr);
} // end clear

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	bool isSuccessful = false;
	std::shared_ptr<BinaryNode<ItemType>> tempPtr = nullptr;
	tempPtr = findNode(rootPtr, anEntry, isSuccessful);
	if (!isSuccessful)
		throw NotFoundException("getEntry - Entry not found");
	return tempPtr->getItem();
} // end getEntry

template<class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const
{
	bool isSuccessful = false;
	findNode(rootPtr, anEntry, isSuccessful);
	return isSuccessful;
} // end contains

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	preorder(visit, rootPtr);
} // end preorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	inorder(visit, rootPtr);
} // end inorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
	postorder(visit, rootPtr);
} // end postorderTraverse

template<class ItemType>
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree<ItemType>& rightHandSide)
{
	rootPtr = copyTree(rightHandSide.rootPtr);
} // end overloaded = operator

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
	destroyTree(rootPtr);
} // end destructor

#endif