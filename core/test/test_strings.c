//
#include <stdio.h>
#include <string.h>

//
#include "../include/ctest.h"

//
#include "../include/strings.h"

//
int test_strings_new()
{
	/// 
	{
		//
		char *src = "This is a string..";
		char *str = strings_new(src);

		//
		char *assert_message = "Testing strings copy for regular string..";
		int assert_result = (strcmp(str, src) == 0) ? TRUE : FALSE;
		ctest_assert_true(assert_result, assert_message);

		//
		strings_free(str);
	}

	/// 
	{
		//
		char *src = "";
		char *str = strings_new(src);

		//
		char *assert_message = "Testing string copy for empty string..";
		int assert_result = (strcmp(str, src) == 0) ? TRUE : FALSE;
		ctest_assert_true(assert_result, assert_message);

		//
		strings_free(str);
	}

	/// 
	{
		//
		char *src = NULL;
		char *str = strings_new(src);

		//
		char *assert_message = "Testing string copy for NULL..";
		int assert_result = (str == NULL) ? TRUE : FALSE;
		ctest_assert_true(assert_result, assert_message);

		//
		strings_free(str);
	}


	//
	return 0;
}

//
int test_strings_free()
{
	/// 
	{
		//
		char *src = NULL;
		int result = strings_free(src);

		//
		char *assert_message = "Testing strings free for NULL..";
		int assert_result = (result == 0) ? TRUE : FALSE;
		ctest_assert_true(assert_result, assert_message);
	}

	//
	return 0;
}

void ctest_test_strings_register()
{
	ctest_test_functions_add("Kontrola funkce strings_new()", "strings", &test_strings_new);
	ctest_test_functions_add("Kontrola funkce strings_free()", "strings", &test_strings_free);
}
