  
//------------------------------------------------------------------------------
// NAME: Kajal Tomar
// STUDENT NUMBER: 7793306
// COURSE: COMP2160, SECTION: A01
// INSTRUCTOR: Dr. Mehdi Niknam
// ASSIGNMENT: 4, QUESTION: 
// 
// REMARKS: This is the automated test suite for the Object-Manager. 
//-------------------------------------------------------------------------------

#include<stdio.h> 
#include "ObjectManager.h"

//-----------------------------------------------------------------------------
// CONSTANTS AND TYPES
//-----------------------------------------------------------------------------
char *ptr;
int i; 

int totalTests = 0;
int failedTests = 0;

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------

// These functions call the test functions in order to test different general and edge cases
static void insertObjectCases(void);
static void retrieveObjectCases(void);
static void addReferenceCases(void);
//static void initPoolCases(void);
//static void destroyPoolCases(void);

// These functions test specific functions and display the result
static void testInsertObject(ulong, bool);
static void testRetrieveObject(Ref, bool);
static void testAddReference(Ref, bool);
//static void testInitPool(bool);
//static void testDestroyPool(void, bool);

int main(void)
{

	insertObjectCases();
	retrieveObjectCases();

	printf("\n\n--------------------------------------------------------------------------------------------------\n");
	printf("TOTAL TESTS: %i: \n", totalTests);
	printf("TESTS PASSED: %i: \n", totalTests - failedTests);
	printf("TESTS FAILED: %i: \n", failedTests);
	printf("------------------------------------------------------------------------------------------------------\n");

	printf("\nend of processing.\n");
	return 0;	
} // main

// -------------------------------------------------------------------------------------------------------
// FUNCTIONS THAT CALL THE TEST FUNCIONS TO TEST TYPICAL AND EDGE CASES
// -------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// newSetCases
// 
// PURPOSE: calls the testInsert function to test normal and edge cases for
// the insert function.
// -----------------------------------------------------------------------------
static void insertObjectCases(void)
{
	initPool();
	
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR insert()\n");
	
	printf("Testing typical cases.\n\n");
	// test and print out the progress from the typical cases
	
	printf("Inserting an object of size 100...\n");
	testInsertObject(100, true);
	
	printf("Inserting an object of size 1234...\n");
	testInsertObject(1234, true);

	printf("Inserting an object of size 12...\n");
	testInsertObject(12, true);

	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");

	printf("Inserting an object of size 0...\n");
	testInsertObject(0, true);

	printf("Inserting an object that is too big for the buffer...\n");
	testInsertObject(MEMORY_SIZE+1, false);
	
	// first destroy pool
	// printf("Inserting an object of exactly MEMORY_SIZE into an empty buffer...");
	// testInsertObject(MEMORY_SIZE, true);
	
	// first destroy pool
	// printf("Inserting an object of size 0...");
	// testInsertObject(MEMORY_SIZE, true);

	dumpPool();

	// destroy Pool
	printf("----------------------------------------------------------------------------------------------------------\n\n");
} // insertObjectCases

// -----------------------------------------------------------------------------
// retrieveObjectCases
// 
// PURPOSE: calls the testRetrieveObject function to test normal and edge cases 
// for the retrieveObject function.
// -----------------------------------------------------------------------------
static void retrieveObjectCases(void)
{
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR retrieveObject()\n");
	
	printf("Testing typical cases.\n\n");
	// test and print out the progress from the typical cases
	
	printf("Retrieving object at ref 2...\n");
	testRetrieveObject(2, true);

	printf("Retrieving object at ref 3..\n");
	testRetrieveObject(3, true);
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	
	printf("Retrieving object at the first ref...\n");
	testRetrieveObject(1, true);

	printf("Retrieving object at the last ref...\n");
	testRetrieveObject(4, true);
	
	printf("Retrieving object at ref 7 (which doesn't exist)...\n");
	testRetrieveObject(7, false);
	
	printf("----------------------------------------------------------------------------------------------------------\n\n");
} // retrieveObjectCases

// -----------------------------------------------------------------------------
// addReferenceCases
// 
// PURPOSE: calls the testAddReference function to test normal and edge cases 
// for the addReference function.
// -----------------------------------------------------------------------------
static void addReferenceCases(void)
{
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR addReference()\n");
	
	printf("Testing typical cases.\n\n");
	// test and print out the progress from the typical cases
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	
	printf("----------------------------------------------------------------------------------------------------------\n\n");
} // addReferenceCases

// -----------------------------------------------------------------------------
// initPoolCases
// 
// PURPOSE: calls the testInitPool function to test normal and edge cases 
// for the initPool function.
// -----------------------------------------------------------------------------
static void initPoolCases(void)
{
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR initPool()\n");
	
	printf("Testing typical cases.\n\n");
	// test and print out the progress from the typical cases
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	
	printf("----------------------------------------------------------------------------------------------------------\n\n");

} // initPoolCases

// -----------------------------------------------------------------------------
// destroyPoolCases
// 
// PURPOSE: calls the destroyPoolCases function to test normal and edge cases 
// for the destroyPool function.
// -----------------------------------------------------------------------------
static void destroyPoolCases(void)
{
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR destroyPool()\n");
	
	printf("Testing typical cases.\n\n");
	// test and print out the progress from the typical cases
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	
	printf("----------------------------------------------------------------------------------------------------------\n\n");
} // destroyPoolCases

// -------------------------------------------------------------------------------------------------------
// FUNCTIONS THAT TEST AND PRINT THE RESULTS 
// -------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// testInsertObject
// 
// PURPOSE: Test if the insert function creates (or or does not create) the new
// object like we expect. Display the outcome.
// INPUT: the size, the expected result (Boolean) to compare the results with.
// -----------------------------------------------------------------------------
static void testInsertObject(ulong size, bool expectedResult)
{
	bool actualResult = true;
	Ref ref = insertObject(size); 
	
	if(ref == NULL_REF)
	{
		actualResult = false; 
	}
	
	if (actualResult == expectedResult)
	{
		if(actualResult)
		{
			printf("Passed! The object was successfully created and inserted.\n");
		}
		else
		{
			printf("Passed! As expected, the object was not inserted.\n");
		}
	}
	else
	{
		if(actualResult) // && (!expectedResult)
		{
			printf("FAILED: An object got inserted even though it should *NOT* have been inserted.\n");
		} 
		else // (!actualResult && expectedResult) 
		{
			printf("FAILED: The object was *NOT* created. We expected it to be created..\n");
		}

		failedTests++;
	}

	printf("\n");

	totalTests++;

} // testInsertObject

// -----------------------------------------------------------------------------
// testRetrieveObject
// 
// PURPOSE: Test if the retrieveObject function correctly retrives (or does not
// retrieve an object based on a reference. 
// INPUT: the ref to retrieve the object from, the expected result (Boolean) to 
// compare the results with.
// -----------------------------------------------------------------------------
static void testRetrieveObject(Ref ref, bool expectedResult)
{
	bool actualResult = true; 
	
	void * retrievedObject = retrieveObject(ref);

	if (retrievedObject == NULL_REF)
	{
		actualResult = false;
	}

	printf("Returned address: %p\n", retrievedObject);

	if (actualResult == expectedResult)
	{
		if(actualResult)
		{
			printf("Passed! The object with the ref number %lu was successfully retrieved. Return address: %p\n", ref, retrievedObject);
		}
		else 
		{
			printf("Passed! As expected, no object was retrieved. Return address: %p\n", retrievedObject);
		}

	} 
	else // (actualResult != expectedResult)
	{
		if(actualResult) // (actualResult && ! expectedResult)
		{
			printf("FAILED: An object was retrieved but it should not have been. Return Address: %p\n", retrievedObject);
		} 
		else
		{
			printf("FAILED: The object with the ref number of %lu should have been retrieved, but it was *not*. Returned Address: %p\n", ref, retrievedObject);
		}

		failedTests++;
	}
	
	totalTests++;

} // testRetrieveObject

// -----------------------------------------------------------------------------
// testAddReference
// 
// PURPOSE: Test if the addReference function correctly adds another reference
// (or does not add one) to an object.
// INPUT: ref of the object to add another reference to, the expected result 
// (Boolean) to compare the results with.
// -----------------------------------------------------------------------------
static void testAddReference(Ref ref, bool expectedResult)
{
	
} // testAddReference

// -----------------------------------------------------------------------------
// testDropReference
// 
// PURPOSE: Test if the dropReference function correctly drops a reference
// to an object.
// INPUT: ref of the object to drop the reference to, the expected result 
// (Boolean) to compare the results with.
// -----------------------------------------------------------------------------
static void testDropReference(Ref ref, bool expectedResult)
{
	
} // testDropReference

/***

static void testInitPool()
{
	
} // testInitPool

static void testDestroyPool()
{
	
} // testDestroyPool

**/

