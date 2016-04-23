#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//
#include "../../core/include/ctest.h"

//
#include "../include/bunkai_ichi.h"

//
int test_hello()
{
	//
	int condition;

	//
	condition = strcmp(hello(), "hello") == 0;

	//
	ctest_assert_true(condition, "Kontrola návratové hodnoty..");

	//
	return 0;
}

//
void ctest_test_bunkai_ichi_register()
{
	ctest_test_functions_add("Kontrola funkce bunkai_ichi::hello() na návratovou hodnotu..", "bunkai_ichi", &test_hello);
}
