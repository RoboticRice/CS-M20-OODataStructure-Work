/*************************************
CS M20 Topic F Project
Rice, Sammuel
**********************************/
/*	AVL Tree Library.
	Written by: G & F
	Date:       2/98
	
	Revised:    4/99 Converted to C++

	Brooks/Cole
	A division of Thomson Learning
	Copyright(c) 2001. All Rights Reserved
*/

//	==================== MACROS ====================
#define LH +1     // Left High 
#define EH  0     // Even High 
#define RH -1     // Right High 

#ifndef _NODE
#define _NODE

#include <memory>

// 	NODE Definitions
template <class TYPE> 
struct NODE 
//Chose to keep this a struct as we were told AVL was originally written for C, and structs are supposed to interface with C better. In addition, leaving the content public allows us to modify values in NODEs within the AVL without having to create several set and get functions to do it for us. Also, NODE should not be handled by the TopicF client, only by the AVL class, so we know exactly how node will be interfaced with and used. Lastly, the AVL was designed with a struct, so why fix what isn't borken?
{
	TYPE    data;
	std::shared_ptr<NODE<TYPE>>   left;
	int     bal;
	std::shared_ptr<NODE<TYPE>>   right;
} ; // NODE

// Class Declaration
template <class TYPE>//, class KTYPE> 
class AvlTree
	{
	 private: 
	    int          count;
		std::shared_ptr<NODE<TYPE>>	tree;

		std::shared_ptr<NODE<TYPE>>	_insert          (std::shared_ptr<NODE<TYPE>>	root,
			std::shared_ptr<NODE<TYPE>>	newPtr,
	                                  bool&       taller);

		std::shared_ptr<NODE<TYPE>>	leftBalance     (std::shared_ptr<NODE<TYPE>>	root,
	                                  bool&        taller);

		std::shared_ptr<NODE<TYPE>>	rotateLeft      (std::shared_ptr<NODE<TYPE>>	root);
		std::shared_ptr<NODE<TYPE>>	rightBalance    (std::shared_ptr<NODE<TYPE>>	root,
	                                  bool&        taller);
		std::shared_ptr<NODE<TYPE>>	rotateRight     (std::shared_ptr<NODE<TYPE>>	root);
		std::shared_ptr<NODE<TYPE>>	_delete          (std::shared_ptr<NODE<TYPE>>	root,
	                                  TYPE        dltKey,//Ktype
	                                  bool&        shorter,
	                                  bool&        success);

		std::shared_ptr<NODE<TYPE>>	dltLeftBalance  (std::shared_ptr<NODE<TYPE>>	root,
	                                  bool&        smaller);
		std::shared_ptr<NODE<TYPE>>	dltRightBalance (std::shared_ptr<NODE<TYPE>>	root,
	                                  bool&        shorter);
		std::shared_ptr<NODE<TYPE>>	_retrieve        (TYPE        key, //Ktype
			std::shared_ptr<NODE<TYPE>>	root);
	                                  
	    void  _traversal  (void (*process)(TYPE& dataProc),
			std::shared_ptr<NODE<TYPE>>	root);

	    void  _destroyAVL (std::shared_ptr<NODE<TYPE>>	root);

//  	The following function is used for debugging.
	    void  _print      (std::shared_ptr<NODE<TYPE>>	root, int   level);

	 public:
	          AvlTree();
	         ~AvlTree(); 
	    bool  AVL_Insert   (TYPE   dataIn); 
	    bool  AVL_Delete   (TYPE  dltKey);//Ktype
	    bool  AVL_Retrieve (TYPE  key,     TYPE& dataOut);//Ktype
	    void  AVL_Traverse (void (*process)(TYPE&  dataProc));

	    bool  AVL_Empty    ();
	    bool  AVL_Full     ();
	    int   AVL_Count    ();
	    
//      The following function is used for debugging.
	    void  AVL_Print    ();
	} ; // class AvlTree
	
/*	=================== Constructor ===================	
	Initializes private data.
	   Pre     class is being defined
	   Post    private data initialized
*/

template <class TYPE>
AvlTree<TYPE> ::  AvlTree (void) 
{
//	Statements 
	tree    = NULL;
	count   = 0;
}	//  Constructor

/*	==================== AVL_Insert ==================== 
	This function inserts new data into the tree.
	   Pre    dataIn contains data to be inserted
	   Post   data have been inserted or memory overflow 
	   Return success (true) or overflow (false)
*/

template <class TYPE>
bool   AvlTree<TYPE> :: AVL_Insert (TYPE dataIn) 
{
//	Local Definitions 
	std::shared_ptr<NODE<TYPE>>	newPtr = std::make_shared<NODE<TYPE>>();
	bool         taller;

//	Statements 
	if (!(newPtr))// = new NODE<TYPE>))
	   return false;
	newPtr->bal    = EH;
	newPtr->right  = nullptr;
	newPtr->left   = nullptr;
	newPtr->data   = dataIn;
   
	tree = _insert(tree, newPtr, taller);
	count++;
	return true;
}	//  Avl_Insert   

/*	======================= _insert =======================
	This function uses recursion to insert the new data into 
	a leaf node in the AVL tree.
	   Pre    application has called AVL_Insert, which passes 
	          root and data pointers
	   Post   data have been inserted
	   Return pointer to [potentially] new root
*/

template <class TYPE>
std::shared_ptr<NODE<TYPE>>	AvlTree<TYPE>
         ::  _insert (std::shared_ptr<NODE<TYPE>>  root, 
                      std::shared_ptr<NODE<TYPE>>  newPtr, 
                      bool&        taller)
{
//	Statements   
	if (!root)
	   {
	    root    = newPtr;
	    taller  = true;
	    return  root;
	   } //  if NULL tree 
 
	if (newPtr->data < root->data) //removed .key, but unsure why it was ever there... can't find a declaration for key
	   {
	    root->left = _insert(root->left, 
	                         newPtr, 
	                         taller);
	    if (taller)
	       //  Left subtree is taller 
	       switch (root->bal)
	          {
	           case LH: // Was left high--rotate 
	                    root = leftBalance (root, taller);
	                    break;

	           case EH: // Was balanced--now LH 
	                    root->bal = LH;
	                    break;

	           case RH: // Was right high--now EH 
	                    root->bal = EH;
	                    taller    = false;
	                    break;
	          } // switch 
	   } //  new < node 
	else 
	   //  new data >= root data 
	   {
	    root->right = _insert (root->right, 
	                           newPtr, 
	                           taller);
	    if (taller)
	       // Right subtree is taller
	       switch (root->bal)
	           {
	            case LH: // Was left high--now EH 
	                     root->bal = EH;
	                     taller    = false;
	                     break;
	            
	            case EH: // Was balanced--now RH
	                     root->bal = RH;
	                     break;
	
	            case RH: // Was right high--rotate 
	                     root = rightBalance (root, taller);
	                     break;
	           } //  switch 
	   } //  else new data >= root data 
	return root;
}	//  _insert 

/*	===================== leftBalance ===================== 
	The tree is out of balance to the left. This function 
	rotates the tree to the right.
	   Pre     the tree is left high 
	   Post    balance restored  
	   Returns potentially new root 
*/

template <class TYPE>
std::shared_ptr<NODE<TYPE>>	AvlTree<TYPE>
         :: leftBalance (std::shared_ptr<NODE<TYPE>>	root,
                         bool&        taller) 
{
// 	Local Definitions 
	std::shared_ptr<NODE<TYPE>>	rightTree;
	std::shared_ptr<NODE<TYPE>>	leftTree;

//	Statements 
	leftTree = root->left;
	switch (leftTree->bal)
	   {
	    case LH: // Left High--Rotate Right 
	                root->bal     = EH;
	                leftTree->bal = EH;
	             
	             // Rotate Right 
	                root     = rotateRight (root);
	                taller   = false;
	             break;
	    case EH: // This is an error 
	                cout <<"\n\a\aError in leftBalance\n";
	                exit (100); 
	    case RH: // Right High - Requires double rotation: 
	             // first left, then right 
	                rightTree = leftTree->right;
	                switch (rightTree->bal)
	                   {
	                    case LH: root->bal     = RH;
	                             leftTree->bal = EH;
	                             break;
	                    case EH: root->bal     = EH;
	                             leftTree->bal = EH;
	                             break;
	                    case RH: root->bal     = EH;
	                             leftTree->bal = LH;
	                             break;
	                   } //  switch rightTree 
	             
	                rightTree->bal = EH;
	                //  Rotate Left 
	                root->left = rotateLeft (leftTree);
	             
	                // Rotate Right 
	                root    = rotateRight (root);
	                taller  = false;
	   } // switch leftTree
	return root;
}	// leftBalance 

/*	===================== rotateLeft ====================== 
	This function exchanges pointers so as to rotate the  
	tree to the left.
	   Pre  root points to tree to be rotated 
	   Post NODE rotated and new root returned 
*/

template <class TYPE>
std::shared_ptr<NODE<TYPE>>	AvlTree<TYPE>
          :: rotateLeft (std::shared_ptr<NODE<TYPE>>	root)
{
//	Local Definitions 
	std::shared_ptr<NODE<TYPE>>	tempPtr;

//	Statements 
	tempPtr        = root->right;
	root->right    = tempPtr->left;
	tempPtr->left  = root;

	return tempPtr;
}	//  rotateLeft 

/*	===================== rotateRight ===================== 
	This function exchanges pointers to rotate the tree
	to the right.
	   Pre   root points to tree to be rotated 
	   Post  NODE rotated and new root returned 
*/

template <class TYPE>
std::shared_ptr<NODE<TYPE>>	AvlTree<TYPE>
          :: rotateRight (std::shared_ptr<NODE<TYPE>>	root)
{
//	Local Definitions 
	std::shared_ptr<NODE<TYPE>>	tempPtr;

//	Statements 
	tempPtr         = root->left;
	root->left      = tempPtr->right;
	tempPtr->right  = root;

	return tempPtr;
}	//  rotateRight  

/*	====================  rightBalance ===================
	The tree is out-of-balance to the right. This function 
	rotates the tree to the left.
	   Pre     The tree is right high 
	   Post    Balance restored 
	   Returns potentially new root 
*/

template <class TYPE>
std::shared_ptr<NODE<TYPE>>	AvlTree<TYPE>
         :: rightBalance (std::shared_ptr<NODE<TYPE>>	root, bool& taller)
{

//	Local Definitions 
	std::shared_ptr<NODE<TYPE>>	rightTree;
	std::shared_ptr<NODE<TYPE>>	leftTree;
 
//	Statements 
	rightTree = root->right;
	switch (rightTree->bal)
	   {
	    case LH: // Left High - Requires double rotation:
	             //             first right, then left 
	                leftTree = rightTree->left;
  	 	 			
	                //  First Rotation - Left 
	                switch (leftTree->bal) 
	                   {
	                    case RH: root->bal      = LH;
	                             rightTree->bal = EH;
	                             break;

	                    case EH: root->bal      = EH;
	                             rightTree->bal = EH;
	                             break;
	
	                    case LH: root->bal      = EH;
	                             rightTree->bal = RH;
	                             break;
	                   } //  switch 
  	 	 			leftTree->bal = EH;
  	 	 			
	                root->right   = rotateRight (rightTree);
	                root          = rotateLeft  (root);
	                taller        = false;
	                break;

	     case EH: // Deleting from balanced node 
				     root->bal = EH;
	                 taller    = false;
	                 break;
						 	 
   	 	 case RH: // Right High - Rotate Left 
	                 root->bal       = EH;
	                 rightTree->bal  = EH;
	                 root            = rotateLeft (root);
	                 taller          = false;
	                 break;
  	 	} // switch 
	return root;
}	//  rightBalance   

/*	====================== AVL_Delete ====================== 
	This function deletes a node from the tree and rebalances 
	it if necessary. 
	   Pre    dltKey contains key to be deleted
	   Post   the node is deleted and its space recycled
	          -or- an error code is returned 
	   Return success (true) or not found (false)
*/

template <class TYPE>
bool  AvlTree <TYPE> :: AVL_Delete (TYPE  dltKey)//Ktype
{
//	Local Definitions 
	bool shorter;
	bool success;

	std::shared_ptr<NODE<TYPE>>	newRoot;

//	Statements 
	newRoot = _delete (tree, dltKey, shorter, success);
	if (success)
	   {
	    tree = newRoot;
	    count--;
	   } // if 
	return success;
}	// AVL_Delete

/*	======================== _delete ======================= 
	This function deletes a node from the tree and rebalances 
	it if necessary. 
	   Pre    dltKey contains key of node to be deleted
	          shorter is Boolean indicating tree is shorter
	   Post   the node is deleted and its space recycled
	          -or- if key not found, tree is unchanged 
	   Return true if deleted, false if not found
	          pointer to root
*/

template <class TYPE>
std::shared_ptr<NODE<TYPE>>	AvlTree<TYPE>
          :: _delete (std::shared_ptr<NODE<TYPE>>	root,
                      TYPE       dltKey,//Ktype
                      bool&       shorter,
                      bool&       success) 
{
//  Local Definitions 
	std::shared_ptr<NODE<TYPE>>	dltPtr;
	std::shared_ptr<NODE<TYPE>>	exchPtr;
	std::shared_ptr<NODE<TYPE>>	newRoot;

// 	Statements 
	if (!root)
	   {
	    shorter = false;
	    success = false;
	    return NULL;
	   } //  if -- base case 
	
	if (dltKey < root->data)
	    {
	     root->left = _delete (root->left, dltKey, 
	                           shorter,    success);
	     if (shorter)
	         root   = dltRightBalance (root, shorter);
	    } // if less 
	else if (dltKey > root->data)
	    {
	     root->right = _delete (root->right, dltKey,
	                            shorter,     success);
	     if (shorter)
	         root = dltLeftBalance (root, shorter);
	    } //  if greater 
	else
	    //  Found equal node 
	    {
	     dltPtr  = root;
	     if (!root->right)
	         // Only left subtree 
	         {
	          newRoot  = root->left;
	          success  = true;
	          shorter  = true;
	          //delete (dltPtr);
			  dltPtr = nullptr;
	          return newRoot;            //  base case 
	         } //  if true 
	     else
	         if (!root->left)
	             //  Only right subtree 
	             {
	              newRoot  = root->right;
	              success  = true;
	              shorter  = true;
	              //delete (dltPtr);
				  dltPtr = nullptr;
	              return newRoot;        // base case 
	            } //  if 
	         else
	             //  Delete NODE has two subtrees 
	             {
	              exchPtr = root->left;
	              while (exchPtr->right)
	                  exchPtr = exchPtr->right;
	                  
	              root->data = exchPtr->data;
	              root->left = _delete (root->left, 
	                                    exchPtr->data,
	                                    shorter, 
	                                    success); 
	              if (shorter)
	                  root = dltRightBalance (root, shorter); 
	             } //  else 
	
	    } // equal node 
	return root; 
}	// _delete 

  // ================== dltLeftBalance ==================
/*	The tree is out-of-balance to the left (left high)--
	rotates the tree to the right.
	   Pre     The tree is left high 
	   Post    Balance has been restored 
	   Returns potentially new root 
*/

template <class TYPE>
std::shared_ptr<NODE<TYPE>>	AvlTree<TYPE>
        ::  dltLeftBalance  (std::shared_ptr<NODE<TYPE>>	root,
                             bool&        smaller) 
{
//	Local Definitions 
	std::shared_ptr<NODE<TYPE>>	rightTree;
	std::shared_ptr<NODE<TYPE>>	leftTree;
  	 
//	Statements 
	switch (root->bal)
	    {
	     case RH:  root->bal	= EH;
	               break;
  	 	 			
	     case EH:  // Delete occurred on right 
		           root->bal  = LH;
		           smaller    = false;
		           break;
						  	 	 
	     case LH:  leftTree = root->left;
		           switch (leftTree->bal) 
		              {
		               case LH:
		               case EH: // Rotate Single Left 
		                        if (leftTree->bal  == EH)
		                           {
		                            root->bal     = LH;
		                            leftTree->bal = RH;
		                            smaller       = false;
		                           } // if
		                        else
		                           {
		                            root->bal     = EH;
		                            leftTree->bal = EH;
		                           } // else

		                        root = rotateRight (root);
		                        break;
  	 	 				 			
		               case RH:	//Double Rotation 
		                        rightTree = leftTree->right;
		                        switch (rightTree->bal)
		                           {
		                            case LH: root->bal     = RH;
		                                     leftTree->bal = EH;
		                                     break;
		                            case EH: root->bal     = EH;
		                                     leftTree->bal = EH;
		                                     break;
		                            case RH: root->bal     = EH;
		                                     leftTree->bal = LH;
		                                     break;
		                           } //  switch 
		                        rightTree->bal = EH;
		                        root->left     = rotateLeft (leftTree);
		                        root           = rotateRight (root);
		                        break;
		              } //  switch : leftTree->bal  
  	 	 				   	 	 			
 	 	} //  switch : root->bal 
	return root; 
}	// dltLeftBalance 

/*	=================== dltRightBalance ==================  
	The tree is shorter after a delete on the left. 
	Adjust the balance factors and rotate the tree 
	to the left if necessary.
	   Pre     the tree is shorter 
	   Post    balance factors adjusted and balance restored 
	   Returns potentially new root 
*/

template <class TYPE>
std::shared_ptr<NODE<TYPE>>	AvlTree<TYPE>
         ::  dltRightBalance (std::shared_ptr<NODE<TYPE>>	root,
                              bool&        shorter) 
{
//  Local Definitions 
	std::shared_ptr<NODE<TYPE>>	rightTree;
	std::shared_ptr<NODE<TYPE>>	leftTree;
	
//	Statements
	switch (root->bal)
	   {
	    case LH: //  Deleted Left--Now balanced 
	             root->bal  = EH;
	             break;
	    case EH: //  Now Right high 
	             root->bal  = RH;
	             shorter    = false;
	             break;
	    case RH: //  Right High - Rotate Left 
	             rightTree = root->right;
	             if (rightTree->bal == LH)
	                 // Double rotation required 
	                 {
	                  leftTree  = rightTree->left;
	               
	                  switch (leftTree->bal)
	                      {
	                       case LH: rightTree->bal = RH;
	                                root->bal      = EH;
	                                break;
	                       case EH: root->bal      = EH;
	                                rightTree->bal = EH;
	                                break;
	                       case RH: root->bal      = LH;
	                                rightTree->bal = EH;
	                                break;
	                      } // switch 
	                   
	                  leftTree->bal = EH;
	               
	                  // Rotate Right then Left 
	                  root->right = rotateRight (rightTree);
	                  root        = rotateLeft  (root);
	                 } //  if rightTree->bal == LH 
	             else
	                {
	                 //  Single Rotation Only 
	                 switch (rightTree->bal)
	                    {
	                     case LH:
	                     case RH: root->bal      = EH;
	                              rightTree->bal = EH;
	                              break;
	                     case EH: root->bal      = RH;
	                              rightTree->bal = LH;
	                              shorter        = false;
	                              break;
	                    } // switch rightTree->bal 
	                 root = rotateLeft (root);
	                } // else 
	    } //  switch root bal 
	return root;
}	//  dltRightBalance 

/*	==================== AVL_Retrieve ===================  
	Retrieve node searches the tree for the node containing 
	the requested key and returns pointer to its data.
	   Pre     dataOut is variable to receive data
	   Post    tree searched and data returned
	   Return  true if found, false if not found
*/

template <class TYPE>
bool   AvlTree<TYPE> 
   ::  AVL_Retrieve  (TYPE   key, TYPE& dataOut)//Ktype
{
//	Local Definitions
	std::shared_ptr<NODE<TYPE>>	node;
	
//	Statements 
	if (!tree)
	   return false;
	   
	node    = _retrieve (key, tree);
	if (node)
	   {
	    dataOut = node->data;
	    return true;
	   } // if found
	else
	   return false;
}	//  AVL_Retrieve 

/*	===================== _retrieve ===================== 
	Retrieve searches tree for node containing requested 
	key and returns its data to the calling function.
	   Pre     AVL_Retrieve called: passes key to be located 
	   Post    tree searched and data pointer returned 
	   Return  address of matching node returned 
	           if not found, NULL returned 
*/

template <class TYPE>
std::shared_ptr<NODE<TYPE>>	AvlTree<TYPE>
        ::  _retrieve (TYPE       key, //Ktype
			std::shared_ptr<NODE<TYPE>>	root)
{
//	Statements 
	if (root)
	    {
	     if (key < root->data)
	         return _retrieve (key, root->left);
	     else if (key > root->data)
	         return _retrieve (key, root->right);
	     else
	         // Found equal key 
	         return (root);
	    } // if root 
	else
	    //Data not in tree 
	    return root;
}	//  _retrieve 

/*	==================== AVL_Traverse ==================== 
	Process tree using inorder traversal. 
	   Pre   process used to "visit" nodes during traversal 
	   Post  all nodes processed in LNR (inorder) sequence 
*/

template <class TYPE>
void  AvlTree<TYPE> 
  ::  AVL_Traverse (void (*process)(TYPE& dataProc))
{
//	Statements 
	_traversal (process, tree);
	return;
}	// end AVL_Traverse 

/*	===================== _traversal ===================== 
	Traverse tree using inorder traversal. To process a
	node, we use the function passed when traversal is called.
	   Pre   tree has been created (may be null) 
	   Post  all nodes processed 
*/

template<class TYPE>
void AvlTree<TYPE>::_traversal(void(*process)(TYPE& dataProc), std::shared_ptr<NODE<TYPE>> root)
{
	//	Statements 
	if (root)
	{
		_traversal(process, root->left);
		process(root->data);
		_traversal(process, root->right);
	} //  if 
	  return;
}	//  _traversal 

/*	=================== AVL_Empty ==================	
	Returns true if tree is empty, false if any data.
	   Pre      tree has been created; may be null 
	   Returns  true if tree empty, false if any data 
*/

template <class TYPE>
bool   AvlTree<TYPE> ::  AVL_Empty ()
{
//	Statements 
	return (count == 0);
}	//  AVL_Empty 

/*	=================== AVL_Full =================== 
	If there is no room for another node, returns true.
	   Pre      tree has been created
	   Returns  true if no room, false if room 
*/

template <class TYPE>
bool   AvlTree<TYPE> ::  AVL_Full ()
{
//	Statements 
	std::shared_ptr<NODE<TYPE>>	newPtr = std::make_shared<NODE<TYPE>>();
	if (newPtr)
	   {
	    newPtr == nullptr;
	    return false;
	   } // if
	else
	   return true;
}	//  AVL_Full 

/*	=================== AVL_Count ===================
	Returns number of nodes in tree.
	   Pre     tree has been created
	   Returns tree count 
*/

template <class TYPE>
int  AvlTree<TYPE> ::  AVL_Count ()
{
// 	Statements 
	return (count);
}	//  AVL_Count 

/*	=================== Destructor =================== 
	Deletes all data in tree and recycles memory.
	The nodes are deleted by calling a recursive
	function to traverse the tree in inorder sequence.
	   Pre      tree is a pointer to a valid tree 
	   Post     all data have been deleted 
*/

template <class TYPE>
AvlTree<TYPE> :: ~AvlTree  () 
{
//	Statements 
	if (tree)
	   _destroyAVL (tree);
}	// Destructor

/*	=================== _destroyAVL =================== 
	Deletes all data in tree and recycles memory.
	The nodes are deleted by calling a recursive
	function to traverse the tree in postorder sequence.   
	   Pre   tree is being destroyed 
	   Post  all data have been deleted 
*/

template <class TYPE>
void  AvlTree<TYPE> 
  ::  _destroyAVL (std::shared_ptr<NODE<TYPE>>	root)
{
	root = nullptr;
/* Original Code
//	Statements 
	if (root)
	   {
	    _destroyAVL (root->left);
	    _destroyAVL (root->right);
	    delete root;
	   } // if 
	   */
	return;
}	//  _destroyAVL

/*  ============================= AVL_Print ============================= 
	This function prints the AVL tree by calling a recursive inorder 
	traversal. NOTE: THIS IS NOT AN APPLICATION ADT FUNCTION. IT IS 
	USED ONLY FOR DEBUGGING PURPOSES.
	
	To correctly visualize the tree when turned sideways, the actual 
	traversal is RNL.
	Pre	 Tree must be initialized. Null tree is OK.
		 Level is node level: root == 0
	Post Tree has been printed.
*/
template <class TYPE>
void  AvlTree<TYPE> :: AVL_Print () 
{
/*  statements */
    _print (tree, 0);
    return;
}   /* AVL_PRINT */

/*  ============================= _print ============================= 
	This function is not a part of the ADT. It is included to verify
	that the tree has been properly built by printing out the tree
	structure.
*/

/*  This function uses recursion to print the tree. At each level, the 
    level number is printed along with the node contents (an integer).
    Pre		root is the root of a tree or subtree
            level is the level of the tree: tree root is 0
    Post    Tree has been printed.
*/
template <class TYPE>
void  AvlTree<TYPE> ::  _print (std::shared_ptr<NODE<TYPE>> root,
                                       int         level) 
{
 /* Local Definitions */
 	int i;
 	
 /* Statements */
 	if (root)
 		{
		 _print ( root->right, level + 1 );
	 
	     cout << "bal "     << setw(3) << root->bal 
	          << ": Level " << setw(3) << level;

 		 for (i = 0; i <= level; i++ )
 		 	cout << "....";
  		 cout << setw(3) << root->data;
  		 if (root->bal == LH)
  		    cout << " (LH)\n";
  		 else if (root->bal == RH)
  		    cout << " (RH)\n";
  		 else
  		    cout << " (EH)\n";
  		    
 		 _print ( root->left, level + 1 );
 		} /* if */
 
 } /* AVL_Print */

 #endif