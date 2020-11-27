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
#include"ObjectManager.h"

//-----------------------------------------------------------------------------
// CONSTANTS AND TYPES
//-----------------------------------------------------------------------------

// MEMORY_SIZE 1024*512
// #define NULL_REF 0
// typedef unsigned long Ref;
// typedef unsigned long ulong;
// typedef unsigned char uchar;
typedef Struct Node node;

Struct Node 
{
	Node * freePtr;
	ulong numBytes;
	ulong startAddr; 
	Ref ref;
	ulong count
} 

static uchar buffer[MEMORY_SIZE]; //???

static Node * head = NULL; 
static ulong numObject; 
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
	// PRECONDITIONS: 
  	// POSTCONDITIONS: 
  
  	return NULL_REF;
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
  
	return &buffer[startAddr];
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
  	// PRECONDITIONS: 
  	// POSTCONDITIONS: 
	
	// buffer = malloc(MEMORY_SIZE)? 

	// initialize these
	head = NULL; 
	numObjects = 0;
	bytesInUse = 0;
	bytesCollected = 0;
	
	ref = 1;
	freePtr = 0;

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

} // validateBuffer
