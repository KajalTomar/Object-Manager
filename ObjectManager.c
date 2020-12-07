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
	Ref ref;
	ulong count;
}; 

// typedef struct Node node;
static uchar buffer[MEMORY_SIZE];

static uchar * freePtr;
static node * head = NULL; 

static ulong numOfObjects; 
static ulong bytesInUse;
static ulong bytesCollected; 

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------

static void compact(void);
static void validateBuffer(void);

// -----------------------------------------------------------------------------------------------
// FUNCTIONS
// -----------------------------------------------------------------------------------------------

/*
 * This function trys to allocate a block of given size from our buffer.
 * It will fire the garbage collector as required.
 * We always assume that an insert always creates a new object...
 * On success it returns the reference number for the block of memory
 * allocated for the object.
 * On failure it returns NULL_REF (0)
 */
 
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

	Ref allocatedRef = NULL_REF;

	node * curr = head;
	node * newNode;
	
	newNode = (struct node *)malloc(sizeof(struct node));
	
	if (bytesCollected + size < MEMORY_SIZE)
	{
		newNode -> numBytes = size;
		newNode -> startAddress = freePtr;
		newNode -> count = 1;
		
		if (!head && size < MEMORY_SIZE)
		{
			assert(numOfObjects == 0);
			assert(bytesInUse == 0);
		
			newNode -> ref = 1;
			newNode -> next = head;
			head = newNode;
		
			assert(head);
		}
		else // if at least one item (head) exists
		{
			validateBuffer();
			
			assert(numOfObjects > 0);
			assert(bytesInUse >= 0);
	
			// look for the next available spot
			while (curr -> next != NULL)
			{
				curr = curr -> next;
			}		
			
			newNode -> ref = (curr -> ref) + 1;
			curr -> next = newNode;
			newNode -> next = NULL;
		
		}
		
		allocatedRef = newNode -> ref; 

		freePtr = &buffer[size];
		
		bytesInUse+= newNode -> numBytes;
		numOfObjects++;

		assert(numOfObjects > 0);
		assert(bytesInUse >= 0);
		validateBuffer();

		assert(freePtr != NULL);
	}

  	return allocatedRef;
} // insertObject

// -----------------------------------------------------------------------------------------
// retrieveObject
//
// PURPOSE: returns a pointer to the object being requested given by the reference id.
// INPUT: The Ref for the object being requested.
// OUTPUT: returns the start adress for the object at Ref (&buffer[startAddr] 
// -----------------------------------------------------------------------------------------
void * retrieveObject(Ref ref)
{
  	// PRECONDITIONS: 
  	// POSTCONDITIONS: 
  	
	return freePtr;
} // retrieveObject


// -----------------------------------------------------------------------------------------
// addReference
//
// PURPOSE: update our index to indicate that we have another reference to the given object.
// INPUT: The Ref for the given object.
// -----------------------------------------------------------------------------------------
void addReference( Ref ref )
{
  	// PRECONDITIONS: 
  	// POSTCONDITIONS: 
  
} // addReference


// -----------------------------------------------------------------------------------------
// dropReference
//
// PURPOSE: update our index to indicate that a reference is gone.
// INPUT: The Ref for the given object.
// -----------------------------------------------------------------------------------------
void dropReference( Ref ref )
{
  	// PRECONDITIONS: 
  	// POSTCONDITIONS: 
  
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
		printf("Reference id: %lu\n", curr -> ref);
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
		assert(curr -> count >= 0); // count shouldn't drop below 1
		assert(curr -> numBytes <= MEMORY_SIZE);
		curr = curr -> next;
	}

	assert(numOfObjects == countNumOfObjs);
	assert(countBytesInUse == bytesInUse);
	assert(bytesInUse <= MEMORY_SIZE);

} // validateBuffer







