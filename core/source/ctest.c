//
// MicroAPI for my tests..
//

//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//
#include "../include/strings.h"
#include "../include/collection.h"

//
#include "../include/ctest.h"

// Collection of test assert..
struct collection *ta_collection;

// Collection of test functions..
struct collection *tf_collection;

// Counts the asserts..
int asserts_count;
int asserts_pass_count;
int asserts_fail_count;

///
int ctest_open()
{
	//
	ta_collection = collection_new();
	tf_collection = collection_new();

	//
	assert(ta_collection != NULL);
	assert(tf_collection != NULL);

	//
	asserts_count = 0;
	asserts_pass_count = 0;
	asserts_fail_count = 0;

	//
	return 0;
}

///
struct test_assert *ctest_test_assert_new(int count, int result, char *nazev)
{
	//
	struct test_assert *ta_pointer = malloc(sizeof(struct test_assert));

	//
	assert(ta_pointer != NULL);

	//
	if(ta_pointer)
	{
		ta_pointer -> count = count;
		ta_pointer -> result = result;
		ta_pointer -> message = strings_new(nazev);
	}

	//
	assert(ta_pointer -> message != NULL);

	//
	return ta_pointer;
}

///
struct test_function *ctest_test_function_new(char *nazev, char *kategorie, int (*funkce)())
{
	//
	struct test_function *tf_pointer = malloc(sizeof(struct test_function));

	//
	assert(tf_pointer);

	//
	if(tf_pointer)
	{
		tf_pointer -> nazev = strings_new(nazev);
		tf_pointer -> kategorie = strings_new(kategorie);
		tf_pointer -> the_function = funkce;
	}

	//
	assert(tf_pointer -> nazev != NULL);
	assert(tf_pointer -> kategorie != NULL);
	assert(tf_pointer -> the_function != NULL);

	//
	return tf_pointer;
}

///
void ctest_test_assert_delete(void *ptr)
{
	//
	struct test_assert *ta_ptr = (struct test_assert *) ptr;

	//
	if(ta_ptr)
	{
		//
		free(ta_ptr -> message);

		//
		free(ta_ptr);
	}
}

///
void ctest_test_function_delete(void *ptr)
{
	//
	struct test_function *tf_ptr = (struct test_function *) ptr;

	//
	if(tf_ptr)
	{
		//
		free(tf_ptr -> nazev);
		free(tf_ptr -> kategorie);

		//
		free(tf_ptr);
	}
}

///
int ctest_close()
{
	//
	if(ta_collection != NULL)
	{
		// Smazání samotných objektů v kolekci (ta_collection)..
		collection_object_delete(ta_collection, &ctest_test_assert_delete);

		//
		free(ta_collection);

		//
		ta_collection = NULL;
	}

	//
	if(tf_collection != NULL)
	{
		// Smazání samotných objektů v kolekci (tf_collection)..
		collection_object_delete(tf_collection, &ctest_test_function_delete);

		//
		free(tf_collection);

		//
		tf_collection = NULL;
	}

	//
	return 0;
}

/// Jak tuto vnořenou funkci otestovat?
void increment_asserts_count(int result)
{
	// Počítání statistiky..
	asserts_count++;

	//
	if(result == TEST_FAIL)
	{
		asserts_fail_count++;
	}

	//
	if(result == TEST_PASS)
	{
		asserts_pass_count++;
	}
}

///
int ctest_test_assert_add(int result, char *message)
{
    	//
	int count = ta_collection -> length + 1;

	//
	struct test_assert *ta_pointer = ctest_test_assert_new(count, result, message);

	//
	collection_add(ta_collection, ta_pointer);

	//
	increment_asserts_count(ta_pointer -> result);
}

///
int ctest_ls_fails()
{
	///
	int function(void *object_ptr)
	{
		//
		struct test_assert *ta_pointer = (struct test_assert *) object_ptr;

		//
		if(ta_pointer)
		{
			//
			if(ta_pointer -> result)
			{
				printf("Test %u has field: '%s'\n", ta_pointer -> count, ta_pointer -> message);
			}
		}
	}

	//
	collection_foreach(ta_collection, &function);

	//
	return 0;
}

///
int ctest_ls()
{
	///
	int function(void *object_ptr)
	{
		//
		struct test_assert *ta_pointer = (struct test_assert *) object_ptr;

		//
		if(ta_pointer)
		{
			//
			printf("Test %u has field: '%s'\n", ta_pointer -> count, ta_pointer -> message);
		}
	}

	//
	collection_foreach(ta_collection, &function);

	//
	return 0;
}

///
int ctest_assert_fail(char *message)
{
	//
	ctest_test_assert_add(TEST_FAIL, message);

	//
	return -1;
}

///
int ctest_assert_pass(char *message)
{
	//
	ctest_test_assert_add(TEST_PASS, message);

	//
	return -1;
}

///
int ctest_assert_true(int avalue, char *message)
{
	//
	if(avalue == TRUE)
	{
		// Přidej další instanci testu..
		ctest_test_assert_add(TEST_PASS, message);

		//
		return 0;
	}

	// Přidej další instanci testu..
	ctest_test_assert_add(TEST_FAIL, message);

	//
	return -1;
}

///
int ctest_assert_zero(int avalue, char *message)
{
	//
	if(avalue == 0)
	{
		// Přidej další instanci testu..
		ctest_test_assert_add(TEST_PASS, message);

		//
		return 0;
	}

	// Přidej další instanci testu..
	ctest_test_assert_add(TEST_FAIL, message);

	//
	return -1;
}

///
int ctest_assert_null(void *avalue, char *message)
{
	//
	if(avalue == NULL)
	{
		// Přidej další instanci testu..
		ctest_test_assert_add(TEST_PASS, message);

		//
		return 0;
	}

	// Přidej další instanci testu..
	ctest_test_assert_add(TEST_FAIL, message);

	//
	return -1;
}

///
int ctest_assert_ptr(void *avalue, char *message)
{
	//
	if(avalue != NULL)
	{
		// Přidej další instanci testu..
		ctest_test_assert_add(TEST_PASS, message);

		//
		return 0;
	}

	// Přidej další instanci testu..
	ctest_test_assert_add(TEST_FAIL, message);

	//
	return -1;
}

///
int ctest_test_functions_add(char *nazev, char *kategorie, int (*funkce)())
{
	//
	struct test_function *tf_pointer = ctest_test_function_new(nazev, kategorie, funkce);

	//
	collection_add(tf_collection, tf_pointer);

	//
	return 0;
}

///
int ctest_run()
{
	//
	struct collection_item *item = NULL;

	//
	if(tf_collection)
	{
		item = tf_collection -> first_item;
	}

	// Čištění statistikých dat, budou nová..
	asserts_count = 0;
	asserts_pass_count = 0;
	asserts_fail_count = 0;

	//
	while(item)
	{
		//
		struct test_function *tf_pointer = item -> object;

		//
		if(tf_pointer)
		{
			tf_pointer -> the_function();
		}

		//
		item = item -> next;
	}
}

///
int ctest_get_asserts_count()
{
	return asserts_count;
}

///
int ctest_get_asserts_pass_count()
{
	return asserts_pass_count;
}

///
int ctest_get_asserts_fail_count()
{
	return asserts_fail_count;
}

///
int ctest_print_asserts_count()
{
	printf("Spuštěno %u testů (%u pass/%u fails)..\n", ctest_get_asserts_count(), ctest_get_asserts_pass_count(), ctest_get_asserts_fail_count());
}
