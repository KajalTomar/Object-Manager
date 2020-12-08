//------------------------------------------------------------------------------
// NAME: Kajal Tomar
// STUDENT NUMBER: 7793306
// COURSE: COMP2160, SECTION: A01
// INSTRUCTOR: Dr. Mehdi Niknam
// ASSIGNMENT: 4, QUESTION: 1
// 
// REMARKS: This is an implementaiont of an object manager. The clients will call 
// the functions avaliable in the interface to allocate and retrieve memory. 
// This memory manager will automatically clean up unused memory.  
//-------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"ObjectManager.h"

//-----------------------------------------------------------------------------
// CONSTANTS AND TYPES
//-----------------------------------------------------------------------------

// MEMORY_SIZE 1024*512
// #define NULL_REF 0
// typedef unsigned long Ref;
// typedef unsigned long ulong;
// typedef unsigned char uchar;

struct node 
{
	node * next; 
	ulong numBytes;
	uchar * startAddress; 
	Ref refCount;
	Ref id;
}; 

// typedef struct Node node;
static uchar buffer[MEMORY_SIZE];

static uchar * freePtr;
static node * head = NULL; 

static Ref lastID; // hold the last/most recent id that was added to the linked list

static ulong numOfObjects; 
static ulong bytesInUse;
static ulong bytesCollected; 

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------

static void compact(void);
static void removeNode(Ref);
static node * nodeAtID(Ref);
static void validateBuffer(void);


// JUST FOR TESTING
ulong getRefCount(Ref id)
{
	node * foundNode = nodeAtID(id);
	ulong count = NULL_REF;

	if (foundNode != NULL_REF)
	{
		count = foundNode -> refCount;
	}

	return count;
}

void displayNode(Ref id)
{
	node * displayNode = nodeAtID(id);

	if (displayNode != NULL_REF)
	{
		printf("ID: %lu\n", displayNode -> id);
		printf("Ref Count: %lu\n", displayNode -> refCount);
		printf("Number of Bytes: %lu\n", displayNode -> numBytes);
		printf("StartAddress: %p\n\n", displayNode -> startAddress);
	}
	else
	{
		printf("This object doesn't exist.\n\n");
	}
}
// -----------------------------------------------------------------------------------------------
// FUNCTIONS
// -----------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// insertObject
//
// PURPOSE: trys to allocate a block of given size from our buffer. It will fire the garbage
// collector as required.
// INPUT: the size of object (ulong)
// OUTPUT: On success it returns the reference number for the block of memory. On failure it
// returns NULL_REF (0)
// -----------------------------------------------------------------------------------------
Ref insertObject(ulong size)
{
	// PRECONDITIONS: either the buffer is empty or it is a valid buffer 
  	// POSTCONDITIONS: the buffer has at least one object, the buffer is valid
  	// freePtr is valid

	ulong allocatedID = NULL_REF; // for return value

	node * curr = head; // to iterate through the nodes
	node * newNode; 
	
	newNode = (struct node *)malloc(sizeof(struct node));
	
	if (bytesCollected + size < MEMORY_SIZE) // if we can fit this size into the buffer then insert it!
	{
		// assign values to newNode
		newNode -> numBytes = size;
		newNode -> startAddress = freePtr;
		newNode -> refCount = 1; // initially 
		
		if (!head && size < MEMORY_SIZE) // if no objects exist at the moment
		{
			assert(numOfObjects == 0);
			assert(bytesInUse == 0);
		
			newNode -> id = 1; // because it's the first one
			newNode -> next = head;
			head = newNode;
		
			assert(head);
		}
		else // if at least one object (head) exists
		{
			validateBuffer();
			
			assert(numOfObjects > 0);
			assert(bytesInUse >= 0);
	
			// look for the next available spot
			while (curr -> next != NULL)
			{
				curr = curr -> next;
			}		
			
			// update these values
			newNode -> id = lastID + 1;
			lastID = newNode -> id;
			curr -> next = newNode;
			newNode -> next = NULL;
		
		}
		
		allocatedID = newNode -> id; // this is what we are going to return

		// update the preePtr to the next available spot in the buffer (or the end if the
		// buffer if full)
		freePtr = &buffer[size]; 
		
		// update stats
		bytesInUse+= newNode -> numBytes;
		numOfObjects++;

		assert(numOfObjects > 0);
		assert(bytesInUse >= 0);
		validateBuffer();

		assert(freePtr != NULL);
	}

  	return allocatedID;

} // insertObject

// -----------------------------------------------------------------------------------------
// retrieveObject
//
// PURPOSE: returns a pointer to the object being requested given by the reference id.
// INPUT: The Ref for the object being requested.
// OUTPUT: returns the start adress for the object at Ref
// -----------------------------------------------------------------------------------------
void * retrieveObject(Ref id)
{
  	// PRECONDITIONS: if the buffer exists it is valid.  
  	// POSTCONDITIONS: the buffer is still valid
  	
	node * foundNode;
	uchar * objectID = NULL_REF; // we will return this
	 
	if(numOfObjects > 0)
	{
		validateBuffer();
	}
	
	foundNode = nodeAtID(id);
	
	if (foundNode)
	{
		objectID = foundNode -> startAddress;
	}
	
	if(numOfObjects > 0)
	{
		validateBuffer();
	}
	
	return objectID;

} // retrieveObject


// -----------------------------------------------------------------------------------------
// addReference
//
// PURPOSE: update object count to indicate that we have another reference to the given object.
// INPUT: The Ref for the given object.
// -----------------------------------------------------------------------------------------
void addReference( Ref id )
{
  	// PRECONDITIONS: if the buffer exists it is valid, the count at ref is greater than 0  
  	// POSTCONDITIONS: the buffer is still valid, the cound at ref is greater than 1
	
	node * IDnode = nodeAtID(id);

	if (numOfObjects >= 1)
	{
		validateBuffer();
	}

	if (IDnode != NULL_REF) // a node with this id exists
	{
		assert(IDnode -> refCount  > 0 );
	
		IDnode -> refCount ++;
	
		assert(IDnode -> refCount > 1);
	}

	if (numOfObjects >= 1)
	{
		validateBuffer();
	}

} // addReference


// -----------------------------------------------------------------------------------------
// dropReference
//
// PURPOSE: update our index to indicate that a reference is gone.
// INPUT: The Ref for the given object.
// -----------------------------------------------------------------------------------------
void dropReference( Ref id )
{
  	// PRECONDITIONS: 
  	// POSTCONDITIONS: 
  
	node * IDnode = nodeAtID(id);

	if(IDnode!= NULL_REF) // a node with this id exists
	{
		if (IDnode -> refCount <= 1)
		{
			IDnode -> refCount--;
			removeNode(id);
		}
		else // (IDnode -> refCount > 1)
		{
			IDnode -> refCount--;
		}
	}

} // dropReference

// -----------------------------------------------------------------------------------------
// initPool
//
// PURPOSE: initialize the object manager.
// -----------------------------------------------------------------------------------------
void initPool(void)
{
  	// PRECONDITIONS: the pool doesn't exist
  	// POSTCONDITIONS: 
	
	// destroy pool (just in case) 

	// initialize these
	head = NULL;
	numOfObjects = 0;
	bytesInUse = 0;
	bytesCollected = 0;
	
	freePtr = &buffer[0];

} // initPool

// -----------------------------------------------------------------------------------------
// destroyPool
//
// PURPOSE: clean up the object manager (before exiting).
// -----------------------------------------------------------------------------------------
void destroyPool(void)
{
  	// PRECONDITIONS: 
  	// POSTCONDITIONS: 
  
	// free(buffer);
	
	// free linked list too 

} // destroyPool

// -----------------------------------------------------------------------------------------
// dumpPool
//
// PURPOSE: traverses the index and prints the info in each entry corresponding to a block 
// of allocated memory (block's reference id, its starting address, and its size (in bytes).
// -----------------------------------------------------------------------------------------
void dumpPool(void)
{
  	// PRECONDITIONS: 
  	// POSTCONDITIONS: 
  
	node * curr = head; 

	printf("--------------------------------------------------------------------------------\n");
	printf("-----------------------------CURRENT POOL---------------------------------------\n");
	printf("--------------------------------------------------------------------------------\n");

	if (numOfObjects > 0)
	{
		while(curr != NULL)
		{
		printf("-------------------------\n");
		printf("Reference ID: %lu\n", curr -> id);
		printf("Starting address: %p\n", curr -> startAddress);
		printf("Size (in bytes): %lu\n", curr -> numBytes);
		printf("-------------------------\n\n");
		
		curr = curr -> next;
		}
	}
	else
	{
		printf("There is nothing in the pool.");
	}
	
	printf("Number of objects: %lu\n", numOfObjects);
	printf("Number of bytes in use %lu\n", bytesInUse);

	printf("--------------------------------------------------------------------------------\n");
	printf("-----------------------------END OF POOL----------------------------------------\n");
	printf("--------------------------------------------------------------------------------\n\n");

} // dumpPool

/*  Initiate garbage collection 
 * You will implement a Mark and Sweep Defragmenting/Mark-compact garbage 
 * collector, as described in class.
 * every time the garbage collector runs, print out the the statistics 
 * (to stdout): the number of objects that exist, current number of bytes 
 * in use and the number of bytes collected.
 */
 
// -----------------------------------------------------------------------------------------
// compact
//
// PURPOSE: Initiate garbage collection.
// -----------------------------------------------------------------------------------------
static void compact(void)
{
  	// PRECONDITIONS: 
  	// POSTCONDITIONS: 
  
} // compact

// -----------------------------------------------------------------------------------------
// removeNode
//
// PURPOSE: removes a node from the linked list
// INPUT: the id of the node to remove
// -----------------------------------------------------------------------------------------
void removeNode(Ref idToDel)
{
	node * curr = head; 
	node * prev = NULL;
	node * nextNode = NULL; 

	bool removed = false; 

	if (numOfObjects > 0)
	{
		if (head -> id == idToDel) // need to remove head 
		{
			bytesInUse -= head -> numBytes; 
			
			head = head -> next;
			
			free(curr); // be free!
			curr = NULL;
			
			removed = true;
		}
		else // node to be removed isn't the head node 
		{
			while (curr && !removed) // loop until end of linked list or until we find the id
			{
		
				prev = curr; 
				curr = curr -> next;

				if(curr -> id == idToDel) // found the id!
				{
					nextNode = curr -> next; 
					
					bytesInUse -= curr -> numBytes;

					free(curr); // free the memory!
					curr = NULL;
						
					// update pointers to exclude the node we want to remove
					prev -> next = nextNode;
						
					removed = true;
				}
			}
		}


		
		numOfObjects--;
	}


} //removeNode
// -----------------------------------------------------------------------------------------
// nodeAtID
// 
// PURPOSE: searches the nodes for the ref item. 
// INPUT: Ref to search for
// OUTPUT: Pointer to the node that contains that ref or NULL_REF if the ref does *not* exist
// ----------------------------------------------------------------------------------------- 
static node * nodeAtID(Ref id)
{
	// PRECONDITIONS: if the buffer exists it is valid.  
  	// POSTCONDITIONS: the buffer is still valid
	
	node * curr = head; // to iterate
	node * foundNode = NULL_REF; // to return
	
	bool foundID = false;
	
	if (curr)
	{
		validateBuffer();
	}

	while(curr && !foundID)
	{
		// check the ref for each object against the ref
		// we are trying to retrive.
		if(curr -> id == id)
		{
			// they match!

			foundNode = curr; // update return value
			foundID = true; // just so we don't loop needlessly
		}

		curr = curr -> next;
	}

	if(curr)
	{
		validateBuffer();
	}
	
	return foundNode;
}

// -----------------------------------------------------------------------------------------
// validateBuffer
//
// PURPOSE: validates the buffer. 
// -----------------------------------------------------------------------------------------
static void validateBuffer(void)
{
	node * curr = head;

	ulong countNumOfObjs = 0;
	ulong countBytesInUse = 0;
	// ulong countBytesCollected = 0;

	while(curr != NULL)
	{
		countNumOfObjs++;
		countBytesInUse += curr -> numBytes;
		
		assert(curr -> startAddress); // exists
		assert(curr -> refCount >= 0); // count shouldn't drop below 1
		assert(curr -> numBytes <= MEMORY_SIZE);
		curr = curr -> next;
	}

	assert(numOfObjects == countNumOfObjs);
	assert(countBytesInUse == bytesInUse);
	assert(bytesInUse <= MEMORY_SIZE);

} // validateBuffer








