  
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
typedef enum BOOL { false, true } bool;

char *ptr;
int i; 

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------

// These functions call the test functions in order to test different general and edge cases
static void insertCases(void);
static void retrieveObjectCases(void);
static void addReferenceCases(void);
static void initPoolCases(void);
static void destroyPoolCases(void);

// These functions test specific functions and display the result
static void testInsert(void);
static void testRetrieveObject(void);
static void testAddReference(void);
static void testInitPool(void);
static void testDestroyPool(void);

int main(void)
{

	initPool();
	
	dumpPool();
	
	

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
static void insertCases(void)
{
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("TESTS FOR insert()\n");
	
	printf("Testing typical cases.\n\n");
	// test and print out the progress from the typical cases
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	
	printf("----------------------------------------------------------------------------------------------------------\n\n");
} // insertCases

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
	
	printf("---------------------------\n");
	printf("Testing edge cases.\n\n");
	
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
// testInsert
// 
// PURPOSE: Test if the insert function creates (or or does not create) the new
// object like we expect. Display the outcome.
// INPUT: the size, the expected result (Boolean) to compare the results with.
// -----------------------------------------------------------------------------
static void testInsert(ulong size, Boolean expectedResult)
{
	
} // testInsert

// -----------------------------------------------------------------------------
// testRetrieveObject
// 
// PURPOSE: Test if the retrieveObject function correctly retrives (or does not
// retrieve an object based on a reference. 
// INPUT: the ref to retrieve the object from, the expected result (Boolean) to 
// compare the results with.
// -----------------------------------------------------------------------------
static void testRetrieveObject(Ref ref, Boolean expectedResult)
{
	
} // testRetrieveObject

// -----------------------------------------------------------------------------
// testAddReference
// 
// PURPOSE: Test if the addReference function correctly adds another reference
// (or does not add one) to an object.
// INPUT: ref of the object to add another reference to, the expected result 
// (Boolean) to compare the results with.
// -----------------------------------------------------------------------------
static void testAddReference(Ref ref, Boolean expectedResult)
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
static void testDropReference(Ref red, Boolean expectedResult)
{
	
} // testDropReference

//***

static void testInitPool()
{
	
} // testInitPool

static void testDestroyPool()
{
	
} // testDestroyPool

**//

