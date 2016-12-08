

/** ADT stack: Link-based implementation.
    Listing 7-3.
    @file LinkedStack.h */

/**********************************
	Topic B Project - Balanced symbols

	CS M20

	Modified to include:
		* Exceptions
		* Assignment operator - move copy constructor code here
		* Change to copy constructor
		* C++ 11

	Exclude stack interface
***********************************/
 
#ifndef _LINKED_STACK
#define _LINKED_STACK

#include <memory>
using namespace std;

#include "Node.h"
#include "PrecondViolatedExcept.h"

template<class ItemType>
class LinkedStack
{
private:
	shared_ptr<Node<ItemType>>  topPtr; // Pointer to first node in the chain;
                           // this node contains the stack's top

public:
// Constructors and destructor:
	LinkedStack() {}                                   // Default constructor
   LinkedStack(const LinkedStack<ItemType>& aStack);// Copy constructor 
	virtual ~LinkedStack();                          // Destructor
	
// Stack operations:
	bool isEmpty() const;
	bool push(const ItemType& newItem);
	bool pop()  throw ( PrecondViolatedExcept );  //changed
	ItemType peek() const throw ( PrecondViolatedExcept );  //changed

	LinkedStack<ItemType> & operator = ( const LinkedStack<ItemType> &right );  //added

}; // end LinkedStack

/******************************** Implementation******************************/


template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack) : topPtr(nullptr)  //changed
{
	*this = aStack;  //changed
}  // end copy constructor


template<class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
	topPtr.reset();
}  // end destructor

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
	return topPtr == nullptr;
}  // end isEmpty

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
	auto newNodePtr = make_shared<Node<ItemType>>(newItem, topPtr);
	topPtr = newNodePtr;
   newNodePtr = nullptr;
      
	return true;
}  // end push

template<class ItemType>
bool LinkedStack<ItemType>::pop()  throw ( PrecondViolatedExcept )  //Changed
{
	bool result = false;
	if (!isEmpty())
	{
      // Stack is not empty; delete top
		auto nodeToDeletePtr = topPtr;
		topPtr = topPtr->getNext();
		

      result = true;
	}  // end if
	else
		throw PrecondViolatedExcept( "pop called with empty stack" );
   
	return result;	
}  // end pop

template<class ItemType>	
ItemType LinkedStack<ItemType>::peek() const  throw ( PrecondViolatedExcept )  //Changed
{
	if ( isEmpty() )
		throw PrecondViolatedExcept( "peek called with empty stack" );

	// Stack is not empty; return top
	return topPtr->getItem();
}  // end getTop

template<class ItemType>
LinkedStack<ItemType> & LinkedStack<ItemType>::operator = ( const LinkedStack<ItemType> &aStack )  //added
{
	if ( this == &aStack )
		return *this;

	topPtr = nullptr;

    // Point to nodes in original chain
   auto origChainPtr = aStack.topPtr;  //changed -> to .
   
   if (origChainPtr == nullptr)
      topPtr = nullptr;  // Original bag is empty
   else
   {
      // Copy first node
      topPtr = make_shared<Node<ItemType>>();
      topPtr->setItem(origChainPtr->getItem());
      
      // Point to last node in new chain
      auto newChainPtr = topPtr;     
      
      // Copy remaining nodes
      while (origChainPtr->getNext() != nullptr)  //changed - added ->getNext()
      {
         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext(); 
         
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();
         
         // Create a new node containing the next item 
         auto newNodePtr = make_shared<Node<ItemType>>(nextItem);
         
         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr); 
         
         // Advance pointer to new last node      
         newChainPtr = newChainPtr->getNext();   
      }  // end while
      
      newChainPtr->setNext(nullptr);           // Flag end of chain
   }  // end if

   return *this;
}


// End of implementation file.
#endif
