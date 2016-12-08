/** ADT stack: Linked-based implimentation.
@file LinkedStack.h */

#ifndef LINKED_STACK_
#define LINKED_STACK_

#include "Node.h"

template<class ItemType>
class LinkedStack
{
private:
	std::shared_ptr<Node<ItemType>> topPtr; //Pointer to first node in the chain;
											//this node contains the stack's top

public:
//Constructor and destructor:
	LinkedStack();
	LinkedStack(const LinkedStack<ItemType>& aStack);
	virtual ~LinkedStack();

//Stack operations:
	bool isEmpty() const;
	bool push(const ItemType& newwItem);
	bool pop();
	ItemType peek() const;

	LinkedStack<ItemType> & operator = (const LinkedStack<ItemType> & aStack);
}; // end LinkedStack

//end of .h file, start of .cpp file

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr)
{
} //end default constructor

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack)
{
	//Point to nodes in original chain
	std::shared_ptr<Node<ItemType>> originalChainPtr = aStack.topPtr;
	if (originalChainPtr == nullptr)
		topPtr = nullptr; //Original Stack is empty
	else
	{
		//Copy first node
		//topPtr = new Node<ItemType>();
		//topPtr->setItem(originalChainPtr->getItem());
		topPtr = std::make_shared<Node<ItemType>>(originalChainPtr->getItem());

		//point to first node in new chain
		std::shared_ptr<Node<ItemType>> newChainPtr = topPtr;

		//Advance original-chain pointer
		originalChainPtr = originalChainPtr->getNext();

		//Copy remaining nodes
		while (originalChainPtr != nullptr)
		{
			//get next item from original chain
			ItemType nextItem = originalChainPtr->getItem();

			//Create a new node containing the next item
			//Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
			auto newNodePtr = make_shared<Node<ItemType>>(nextItem);

			//Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);

			//Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();

			//Advance original-chain pointer
			originalChainPtr = originalChainPtr->getNext();
		}//end while
		newChainPtr->setNext(nullptr); //Flag end of chain
	}//end if
}//end copy constructor

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
	//Pop until stack is empty
	while (!isEmpty())
		pop();
}//end destructor

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
	auto newNodePtr = std::make_shared<Node<ItemType>>(newItem);
	if (isEmpty())
		topPtr = newNodePtr;
	else
	{
		newNodePtr->setNext(topPtr);
		topPtr = newNodePtr;
	}
	return true;
} //end push

template<class ItemType>
bool LinkedStack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		//Stack is not empty; delete top
		//Node<ItemType>* nodeToDeletedPtr = topPtr;
		topPtr = topPtr->getNext();

		//return deleted node to system
		//nodeToDeletedPtr->setNext(nullptr);
		//delete nodeToDeletedPtr;
		//nodeToDeletedPtr = nullptr;

		result = true;
	}//end if

	return result;
}//end pop

template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const
{
	//assert(!isEmpty()); //Enforce precondition during debugging

	//Stack is not emptty; return top
	return topPtr->getItem();
}//end peek

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
	return topPtr == nullptr;
} //end ifEmpty

template<class ItemType>
LinkedStack<ItemType> & LinkedStack<ItemType>::operator = (const LinkedStack<ItemType> & aStack)
{
	if (this == &aStack)
		return *this;

	while (!isEmpty())
		pop();

	if (!aStack.isEmpty())
	{
		//Point to nodes in original chain
		std::shared_ptr<Node<ItemType>> originalChainPtr = aStack.topPtr;
		//Copy first node
		//topPtr = new Node<ItemType>();
		//topPtr->setItem(originalChainPtr->getItem());
		topPtr = std::make_shared<Node<ItemType>>(originalChainPtr->getItem());

		//point to first node in new chain
		std::shared_ptr<Node<ItemType>> newChainPtr = topPtr;

		//Advance original-chain pointer
		originalChainPtr = originalChainPtr->getNext();

		//Copy remaining nodes
		while (originalChainPtr != nullptr)
		{
			//get next item from original chain
			ItemType nextItem = originalChainPtr->getItem();

			//Create a new node containing the next item
			//Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
			auto newNodePtr = make_shared<Node<ItemType>>(nextItem);

			//Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);

			//Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();

			//Advance original-chain pointer
			originalChainPtr = originalChainPtr->getNext();
		}//end while
		newChainPtr->setNext(nullptr); //Flag end of chain
	}
	return *this;
}
#endif // !LINKED_STACK
