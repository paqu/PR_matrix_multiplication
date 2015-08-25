#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
// #include "CUnit/Automated.h"
// #include "CUnit/Console.h"
//
#include <stdio.h>
#include <string.h>

int init_suite1(void)
{
	return 0;
}
int clean_suite1(void)
{
	return 0;
}

void example_test(void)
{
	CU_ASSERT(0 == 0);
}
void example_test1(void)
{
	CU_ASSERT(0 == 1);
}

int main(void)
{
	CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("Suite_1", init_suite1,clean_suite1);
	if( NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(( NULL == CU_add_test(pSuite, " example_test ", example_test)) ||
	   ( NULL == CU_add_test(pSuite, " example_test1", example_test1))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
