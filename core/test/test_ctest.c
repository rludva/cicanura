#include <stdlib.h>

//
#include "../include/ctest.h"

//
int test_ctest_01()
{
	//
	ctest_assert_pass("Simple Pass Test..");

	//
	return 0;
}

//
void ctest_test_ctest_register()
{
	ctest_test_functions_add("Kontrola testovacího mikro API", "ctest", &test_ctest_01);
}

