  
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

// These functions test specific functions and display the result
static void testInsertObject(ulong, bool);
static void testRetrieveObject(Ref, bool);
static void testDestroyPool(void);
static void testCompact(void);
static void testAddReference(void);
static void testDropReference(void);
static void testDestroyPool(void);

ulong getRefCount(Ref);
	
int main(void)
{
	insertObjectCases();
	retrieveObjectCases();
	testAddReference(); 
	testDropReference();
	testDestroyPool();
	testCompact(); 

	dumpPool();
	destroyPool();

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
	destroyPool();
	initPool();
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");

	printf("Inserting an object of size 5...\n");
	testInsertObject(5, true);

	printf("Inserting an object that is too big for the buffer...\n");
	testInsertObject(MEMORY_SIZE+1, false);
	
	destroyPool();
	initPool();
 	printf("Inserting an object of exactly MEMORY_SIZE into an empty buffer...\n");
	testInsertObject(MEMORY_SIZE, true);
	
	destroyPool();
	
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR insert()\n");
	
	printf("Testing typical cases.\n\n");
	// test and print out the progress from the typical cases
	
	initPool();
	
	printf("Inserting an object of size 100...\n");
	testInsertObject(100, true);
	
	printf("Inserting an object of size 1234...\n");
	testInsertObject(1234, true);

	printf("Inserting an object of size 12...\n");
	testInsertObject(12, true);

	printf("Inserting an object of size 0...\n");
	testInsertObject(0, false);
	
	insertObject(123);

	dumpPool();

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
	
	printf("Retrieving object at refID 2...\n");
	testRetrieveObject(2, true);

	printf("Retrieving object at refID 3..\n");
	testRetrieveObject(3, true);
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	
	printf("Retrieving object at the first refID...\n");
	testRetrieveObject(1, true);

	printf("Retrieving object at the last refID...\n");
	testRetrieveObject(4, true);
	
	printf("Retrieving object at refID 7 (which doesn't exist)...\n");
	testRetrieveObject(7, false);
	
	printf("----------------------------------------------------------------------------------------------------------\n\n");
} // retrieveObjectCases

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
			printf("Passed! The object with the id number %lu was successfully retrieved. Return address: %p\n", ref, retrievedObject);
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
			printf("FAILED: The object with the id number of %lu should have been retrieved, but it was *not*. Returned Address: %p\n", ref, retrievedObject);
		}

		failedTests++;
	}
	
	totalTests++;

} // testRetrieveObject

// -----------------------------------------------------------------------------
// testAddReference
// 
// PURPOSE: tests normal and edge cases for the addReference function.
// -----------------------------------------------------------------------------
static void testAddReference(void)
{
	destroyPool();
	initPool();

	insertObject(100);
	insertObject(1234);
	insertObject(12);
	insertObject(123);
	
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR addReference()\n");
	
	printf("Testing typical cases.\n\n");
	// test and print out the progress from the typical cases
	
	printf("Adding 5 references to id 2...\n");
	addReference(2);	
	addReference(2);	
	addReference(2);	
	addReference(2);
	dumpPool();
	
	printf("Adding 3 references to id 3...\n");
	addReference(3);
	addReference(3);
	addReference(3);	
	dumpPool();
	
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	
	printf("Adding 3 references to the first id (=1)...\n");
	addReference(1);
	addReference(1);
	addReference(1);
	dumpPool();
	
	printf("Adding a reference to the last id (=4) ...\n");
	addReference(4);
	dumpPool();
	
	printf("Adding a reference to an id (=7) that doesn't exist...\n");
	addReference(7);
	dumpPool();
	
	printf("Dropping the reference of id 4 to 0, then trying to add a reference to it...\n");
	dropReference(4);
	dropReference(4);
	addReference(4);
	dumpPool();
	
	printf("----------------------------------------------------------------------------------------------------------\n\n");
} // addReferenceCases

// -----------------------------------------------------------------------------
// testDropReference
// 
// PURPOSE: tests normal and edge cases for the dropReference function.
// -----------------------------------------------------------------------------
static void testDropReference(void)
{
	destroyPool();
	initPool();
	
	insertObject(100);
	insertObject(1234);
	insertObject(12);
	insertObject(123);
	
	for(int i = 0; i < 50; i++)
	{
		addReference(2);	
	}
	
	addReference(3);
	addReference(3);
	
	addReference(1);
	addReference(1);
	
	addReference(4);
	
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR dropReference()\n");
	
	printf("Testing typical cases.\n\n");
	// test and print out the progress from the typical cases
	
	printf("Dropping the a reference for id 2...\n");
	dumpPool();
	dropReference(2);
	dumpPool();

	printf("Dropping a reference for id 3...\n");
	dumpPool();
	dropReference(3);
	dumpPool();
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");

	printf("Dropping all the references for the first node on the list...\n");
	dumpPool();
	dropReference(1);
	dropReference(1);
	dropReference(1);
	dumpPool();
	
	printf("Dropping all the references for the last node on the list...\n");
	dumpPool();
	dropReference(4);
	dropReference(4);
	dumpPool();

	printf("----------------------------------------------------------------------------------------------------------\n\n");
	destroyPool();
	
} //dropRefrenceCases

// testDestroyPool
// 
// PURPOSE: tests normal and edge cases for the destroyPool function.
// -----------------------------------------------------------------------------
static void testDestroyPool(void)
{
	initPool();
	
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR destroyPool()\n");
	
	printf("Testing typical cases.\n\n");
	// test and print out the progress from the typical cases
	
	// adding objects to create a typical pool
	insertObject(100);
	insertObject(1234);
	insertObject(12);
	insertObject(123);
	insertObject(1);
	
	addReference(2);
	addReference(2);
	addReference(3);
	addReference(1);

	printf("This is the pool we are going to destroy...\n");
	dumpPool();

	printf("Destroying pool...\n");
	destroyPool();
	dumpPool();
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	
	initPool();
	insertObject(34);
	printf("Destroying a pool with only on object...\n");
	dumpPool();
	destroyPool();
	dumpPool();

	initPool();
	insertObject(1);
	printf("Destroying a pool with only one object of size 1...\n");
	dumpPool();
	destroyPool();
	dumpPool();
	
	initPool();
	insertObject(MEMORY_SIZE);
	printf("Destroying a pool with only one object of the max memory size...\n");
	dumpPool();
	destroyPool();
	dumpPool();
		
	printf("----------------------------------------------------------------------------------------------------------\n\n");
} // destroyPoolCases

// -----------------------------------------------------------------------------
// compact
// 
// PURPOSE: Test if the compact function correctly destroys uses the two buffers
// as necessary. Then print the results.
// -----------------------------------------------------------------------------
static void testCompact()
{
	printf("Testing compact()\n");
	
	destroyPool();
	initPool();

	// should get added without needing compact
	printf("Adding an object of size 131072...\n");
	insertObject(131072); 
	printf("Adding an object of size 131072...\n");
	insertObject(131072);
	printf("Dropping the reference to id=2...\n");
	dropReference(2);
	printf("Adding an object of size 131072...\n");
	insertObject(131072);
	printf("Adding an object of size 131072... this should get added if the id=2 was dropped and the space was freed...\n");
	insertObject(131072);
	printf("Adding a reference to id=1...\n");
	addReference(1);
	printf("Adding an object of size 131072..\n");
	insertObject(131072); // should get added
	printf("Dropping the reference to id=3...\n");
	dropReference(3);	
	printf("Adding an object of size 5000... this will only get added if id=3 was dropped and the free space was freed.\n");
	insertObject(5000); // shouldn't be added
}


