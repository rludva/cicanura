#include <stdlib.h>

//
#include "../include/ctest.h"

///
int test_ctest_01()
{
	//
	ctest_assert_pass("Simple Pass Test..");

	//
	return 0;
}

///
void test_ctest_assert_true()
{
	//
	int value = TRUE;
	
	//
	ctest_assert_true(value, "TRUE value PASS the test of assert_true..");
	
	//
	return 0;
}

///
void test_ctest_assert_false()
{
	//
	int value = FALSE;
	
	//
	ctest_assert_false(value, "FALSE value PASS the test of assert_false..");
	
	//
	return 0;
}

///
void ctest_test_ctest_register()
{
	ctest_test_functions_add("Kontrola testovacího mikro API", "ctest", &test_ctest_01);
	ctest_test_functions_add("Kontrola funkce ctest_assert_true", "ctest", &test_ctest_assert_true);
	ctest_test_functions_add("Kontrola funkce ctest_assert_false", "ctest", &test_ctest_assert_true);
}

