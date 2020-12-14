//------------------------------------------------------------------------------
// NAME: Kajal Tomar
// STUDENT NUMBER: 7793306
// COURSE: COMP2160, SECTION: A01
// INSTRUCTOR: Dr. Mehdi Niknam
// ASSIGNMENT: 4, QUESTION: 1
// 
// REMARKS: This is an implemention of mark and sweek defragmenting / Mark-compact
// garbage collector. The clients will call functions avaliable in the interface 
// to allocate and retrieve memory. 
// This memory manager will automatically clean up unused memory.  
//-------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"ObjectManager.h"

//-----------------------------------------------------------------------------
// CONSTANTS AND TYPES
//-----------------------------------------------------------------------------

struct node 
{
	node * next; 
	ulong numBytes;
	uchar * startAddress; 
	Ref refCount;
	Ref id;
}; 

static uchar buffer_1[MEMORY_SIZE];
static uchar buffer_2[MEMORY_SIZE];

static uchar * currentBuffer; // points to current buffer
static uchar * freePtr; // points to next free spot in the current buffer
static node * head = NULL; 

static Ref lastID; // hold the last / most recent id that was added to the linked list

static ulong numOfObjects; 
static ulong bytesInUse;
static ulong bytesCollected; 

//------------------------------------------------------------------------------
// PROTOTYPES
//------------------------------------------------------------------------------

static void compact(void);
bool noMemoryLeft(ulong, uchar *, uchar *);
static void removeNode(Ref);
static node * nodeAtID(Ref);
static void validateBufferAndPool(void);

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
	// PRECONDITIONS: if the pool exists then it is valid. The buffer is valid.
  	// POSTCONDITIONS: the buffer and pool have at least one object, the buffer and pool 
	// are valid.
	ulong allocatedID = NULL_REF; // for return value

	node * curr = head; // to iterate through the nodes
	node * newNode; 
	
	newNode = (struct node *)malloc(sizeof(struct node));
	
    // if there is no memory left in the current buffer then call compact
	if(noMemoryLeft(size, freePtr, currentBuffer))
	{
		compact();
	}

	if (size > 0 && size <= MEMORY_SIZE && bytesInUse + size <= MEMORY_SIZE) // if we can fit this size into the buffer then insert it!
	{		
		// assign values to newNode
		newNode -> numBytes = size;
		newNode -> refCount = 1; // always 1 initially 
		
		if (!head && size <= MEMORY_SIZE) // if no objects exist at the moment
		{	
			assert(numOfObjects == 0);
		
			newNode -> startAddress = freePtr;
			newNode -> id = 1; // because it's the first one
			lastID = newNode -> id; 

			newNode -> next = head;
			head = newNode;
		
			assert(head);
		}
		else // if at least one object (head) exists
		{
			validateBufferAndPool();
			
			assert(numOfObjects > 0);
			assert(bytesInUse >= 0);
	
			// look for the next available spot
			while (curr -> next != NULL)
			{
				curr = curr -> next;
			}		
			
			// update these values
			newNode -> startAddress = freePtr;
			newNode -> id = lastID + 1;
			
			// so that this id is preserved as the most recent one
			// even if the object at id gets removed due to refCoun <= 0
			lastID = newNode -> id; 

			// update the next pointers
			curr -> next = newNode;
			newNode -> next = NULL;
				
		}
		
		// update the freePtr to the next available spot in the buffer (or the end if the
		// buffer if full)
		freePtr = freePtr + size;

		allocatedID = newNode -> id; // this is what we are going to return
		
		// update stats
		bytesInUse+= newNode -> numBytes;
		numOfObjects++;

		assert(numOfObjects > 0);
		assert(bytesInUse >= 0);
		validateBufferAndPool();

		assert(freePtr != NULL);
	}
	else {
		printf("\nUnable to successfully complete memory allocation request.\n");
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
  	// PRECONDITIONS: if the pool exists it is valid. The buffer is valid.
  	// POSTCONDITIONS: the buffer and pool are still valid.

	node * foundNode;
	uchar * objectID = NULL_REF; // we will return this
	
	if (id == 0 || id > lastID)
	{
		printf("Invalid id exception with id %lu, terminating process.\n", id);
		//exit(0);
	}
	else {

		if(numOfObjects > 0)
		{
			validateBufferAndPool();
		}
		
		// returns NULL_REF if no object with this id exists on the linked list
		foundNode = nodeAtID(id); 
		
		if (foundNode != NULL_REF) 
		{
			// retrieve the object's start address
			objectID = foundNode -> startAddress;
		}
		else
		{
			 printf("Invalid id exception with id %lu, terminating process.\n", id);
		}
		
		if(numOfObjects > 0)
		{
			validateBufferAndPool();
		}
	
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
  	// PRECONDITIONS: if the pool exists then it is valid,  buffer is valid. the refCount at 
	// id is greater than 0.  
  	// POSTCONDITIONS: the buffer and pool are still valid, the refCount at id is greater than 1.
	
	// get the node with the given id
	// returns NULL_REF if no such node exists
	node * IDnode = nodeAtID(id); 

	if (numOfObjects >= 1)
	{
		validateBufferAndPool();
	}

	if (IDnode != NULL_REF) // a node with this id exists
	{
		assert(IDnode -> refCount  > 0 );
	
		// update refCount
		IDnode -> refCount ++;
	
		assert(IDnode -> refCount > 1);
	}

	if (numOfObjects >= 1)
	{
		validateBufferAndPool();
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
  	// PRECONDITIONS: if the pool exists, it is valid. The buffer is valid. numOfObjects >= 0
  	// POSTCONDITIONS: the buffer and pool are still valid. numOfObjects >= 0. countRef for 
	// the given id is greater than 0 or the id no longer exists
  
	// find node at with the given id
	// returns NULL_REF if the if no such node exists
	node * IDnode = nodeAtID(id);

	if(IDnode!= NULL_REF) // a node with this id exists
	{
		validateBufferAndPool();

		if (IDnode -> refCount <= 1) // if the ref count will become zero after dropping this ref
		{
			removeNode(id); // remove the node from the linked list
			
			assert(numOfObjects >= 0);
			(assert(!nodeAtID(id))); // no node with this id exists anymore
		}
		else // (IDnode -> refCount > 1)
		{
			// update refCount
			IDnode -> refCount--; 
			
			assert(numOfObjects > 0);
			assert(IDnode -> refCount > 0);
		}

		if(numOfObjects > 0)
		{
			validateBufferAndPool();
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
  	// PRECONDITIONS: The pool doesn't exist
  	// POSTCONDITIONS: freePtr is not null, freePtr is pointing to buffer_1, head is NULL
	// numOfObjects, bytesInUse and bytesCollected are all 0
	// currentBuffer is pointing to buffer_1. 
	destroyPool(); // just in case
	
	// initialize these
	head = NULL;
	numOfObjects = 0;
	bytesInUse = 0;
	bytesCollected = 0;
	
	currentBuffer = buffer_1;
	freePtr = currentBuffer;

	assert(freePtr);
	assert(freePtr = buffer_1);
	assert(!head);
	assert(numOfObjects == 0 && bytesInUse == 0 && bytesCollected == 0);
	assert(currentBuffer == buffer_1);

} // initPool

// -----------------------------------------------------------------------------------------
// destroyPool
//
// PURPOSE: clean up the object manager (before exiting).
// -----------------------------------------------------------------------------------------
void destroyPool(void)
{
  	// PRECONDITIONS: numOfObjects >= 0, if the pool exists it is valid. Buffer is valid. 
  	// POSTCONDITIONS: numOfObjects == 0, bytesInUse == 0, head == NULL. 
	node * curr = head; // to iterate
	node * temp = NULL; 

	if (curr)
	{
		assert(head);
		assert(numOfObjects >= 1);
		assert(bytesInUse >= 0);

		validateBufferAndPool();
	}

	// go through each node in the linked list
	while(curr)
	{
		// decrement bytesInUse for each object
		bytesInUse -= curr -> numBytes; 

		temp = curr;
		curr = curr -> next;
		
		free(temp); // be free!
		temp = NULL;
		
		// decrement numOfObjects by one
		numOfObjects--;
	}
	
	bytesInUse = 0;

	head = NULL;

	assert(numOfObjects == 0);
	assert(bytesInUse == 0);
	assert(head == NULL);

	// NOTE: we don't have to free the buffers because they were *not* dynamically allocated. 

} // destroyPool

// -----------------------------------------------------------------------------------------
// dumpPool
//
// PURPOSE: traverses the index and prints the info in each entry corresponding to a block 
// of allocated memory (block's reference id, its starting address, and its size (in bytes).
// -----------------------------------------------------------------------------------------
void dumpPool(void)
{
  	// PRECONDITIONS: if the pool exists, it is valid. Buffer is valid.
  	// POSTCONDITIONS: the pool and buffer are still valid, numOfObjects >= 0, bytesInUse >= 0
  
	node * curr = head; // to traverse the linked list
	printf("\n-----------------------------CURRENT POOL---------------------------------------\n");

	if (numOfObjects > 0)
	{
		validateBufferAndPool();

		// go through each node until we get to the end
		while(curr != NULL)
		{

		printf("Reference ID: %lu | ", curr -> id);
		printf("Starting address: %p | ", curr -> startAddress);
		printf("Size (in bytes): %lu\n", curr -> numBytes);
		
		curr = curr -> next;
		}

		validateBufferAndPool();
	}
	else // (if numOfObjects == 0)
	{
		printf("There is nothing in the pool.\n");
	}
	
	assert(numOfObjects >= 0);
	assert(bytesInUse >= 0);

	printf("\nNumber of objects: %lu\n", numOfObjects);
	printf("Number of bytes in use: %lu\n", bytesInUse);

	printf("-----------------------------END OF POOL----------------------------------------\n\n");
}
// -----------------------------------------------------------------------------------------
// compact
//
// PURPOSE: Initiate garbage collection using mark and sweek defragmenting/ Mark-compact
// garbage collector. Prints out the stats. 
// -----------------------------------------------------------------------------------------
static void compact(void)
{
  	// PRECONDITIONS: the buffer and pool are valid, freePtr pointing within one of the 
	// two buffers, numOfObjects > 0, bytesInUse >= 0
  	// POSTCONDITIONS: the buffer and pool are valid, freePtr is pointing within one of 
	// the two buffers, numOfObjects > 0, bytesInUse >= 0
	node * curr = head;
	bytesCollected = 0; // reset 
	ulong bytesFreed = 0;

	validateBufferAndPool();

	assert(numOfObjects > 0 && bytesInUse > 0 && bytesInUse < MEMORY_SIZE);

	// switch buffers
	if(currentBuffer == buffer_1)
	{
		currentBuffer = buffer_2;
	}
	else // (currentBuffer == buffer_2)
	{
		currentBuffer = buffer_1;
	}
	
	// update free pointer to be at the start of the new current buffer
	freePtr = currentBuffer;

	// assert that free pointer is withing whichever buffer is the current buffer
	assert(freePtr >= currentBuffer && freePtr <= &currentBuffer[MEMORY_SIZE]);

	// go through each node on the linked list
	while(curr)
	{
		// update startPointer to the adjacent free spot
		curr -> startAddress = freePtr; 
		
		// update free pointer to the end of this spot
		freePtr += curr -> numBytes;
		
		// update the amount of bytes we collected for the 'other' buffer
		bytesCollected += curr -> numBytes;

		curr = curr -> next;
	}

	bytesFreed = bytesInUse - bytesCollected;
	bytesInUse = bytesCollected; 

	// make sure the pool is still valid
	validateBufferAndPool();

	assert(numOfObjects > 0 && bytesInUse > 0 && bytesInUse < MEMORY_SIZE);
	
	// display stats
	printf("\nGarbage collector statistics:\n");
	printf("objects: %lu | ", numOfObjects);
	printf("bytes in use: %lu | ", bytesInUse);
	printf("bytes freed: %lu\n", bytesFreed);
	
	// reset bytes collected for next time compact is called
	bytesCollected = 0;

} // compact

// -----------------------------------------------------------------------------------------
// noMem
// 
// PURPOSE: To check if we have run out of memory for the current buffer.
// INPUT: size of object we are trying to add, freePtr, pointer to current buffer
// OUTPUT: returns bool. True for we have run out of memory and false when we have not. 
// -----------------------------------------------------------------------------------------
bool noMemoryLeft(ulong size, uchar * freePtr, uchar * buffer)
{
	// PRECONDITIONS: size <= MEMORY_SIZE, if the pool exists then it is valid, buffer is 
	// valid.
	// POSTCONDITIONS: if the pool exists, then it is still valid, buffer is valid.
	bool noMemoryLeft = false;

	assert(freePtr >= buffer);

	if(numOfObjects > 0)
	{
		validateBufferAndPool();
	}

	// if adding an object of this size with point the freePtr outside the 
	// range of the buffer then noMemoryLeft is true.
	if((freePtr + size) > (&buffer[MEMORY_SIZE-1]+1))
	{
		noMemoryLeft = true;
	}
	
	assert(freePtr >= buffer);

	if(numOfObjects > 0)
	{
		validateBufferAndPool();
	}
	
	return noMemoryLeft;
} // noMem

// -----------------------------------------------------------------------------------------
// removeNode
//
// PURPOSE: removes a node from the linked list
// INPUT: the id of the node to remove
// -----------------------------------------------------------------------------------------
void removeNode(Ref idToDel)
{
  	// PRECONDITIONS: if the pool exists then it is valid, buffer is valid. numOfObjects >= 0  
  	// POSTCONDITIONS: the buffer and pool are still valid, numOfObject >= 0, if numOfObjects 
	// is more than 0 then head still exists.
	node * curr = head; 
	node * prev = NULL;
	node * nextNode = NULL; 

	bool removed = false; 

	if (numOfObjects > 0) // only need to remove if at least on node exists
	{

		validateBufferAndPool();
		assert(numOfObjects > 0);
		
		if (head -> id == idToDel) // need to remove head 
		{
			assert(head);

			head -> refCount--; // making the refCount == 0

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
					curr -> refCount--; // making the refCount == 0

					nextNode = curr -> next; // nextNode will become the node after prev to exclude curr 

					free(curr); // free the memory!
					curr = NULL;
						
					// update pointers to exclude the node we want to remove
					prev -> next = nextNode;
						
					removed = true;
				}
			}
		}

		// update the number of objects
		numOfObjects--;
		
		assert(numOfObjects >= 0);

		if(numOfObjects > 0)
		{
			assert(head);
			validateBufferAndPool();
		}

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
	// PRECONDITIONS: if the pool exists it is valid. Buffer is valid.  
  	// POSTCONDITIONS: the buffer and pool are still valid.
	node * curr = head; // to iterate
	node * foundNode = NULL_REF; // to return
	
	bool foundID = false;
	
	if (curr)
	{
		validateBufferAndPool();
	}
	
	// go therough the entire linked list or until we find an object with this id
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
		validateBufferAndPool();
	}
	
	return foundNode;
}

// -----------------------------------------------------------------------------------------
// validateBufferAndPool
//
// PURPOSE: validates the buffer (and also the pool). 
// -----------------------------------------------------------------------------------------
static void validateBufferAndPool(void)
{
	node * curr = head;

	ulong countNumOfObjs = 0;
	ulong countBytesInUse = 0;

	// make sure the buffer is valid

	// currentBuffer should always point to one of the two buffers
	assert(currentBuffer == buffer_1 || currentBuffer == buffer_2);

	// freePtr should be within the buffer or one spot over if the buffer is completly full
	assert(freePtr >= currentBuffer && freePtr <= &currentBuffer[MEMORY_SIZE]);
	
	// make sure the linked list is valid
	
	// traverse the entire pool
	while(curr != NULL)
	{
		// recounf the number of objects and the number of bytes
		countNumOfObjs++;
		countBytesInUse += curr -> numBytes;
		
		assert(curr -> startAddress); // exists
		assert(curr -> refCount >= 1); // count shouldn't drop below 1
		assert(curr -> numBytes > 0 && curr -> numBytes <= MEMORY_SIZE); // number of bytes should never be more than memory size or 0
		
		curr = curr -> next;
	}

	// assert the recounts
	assert(numOfObjects == countNumOfObjs);
	assert(countBytesInUse <= bytesInUse);
	
	assert(bytesInUse <= MEMORY_SIZE);

} // validateBufferAndPool








