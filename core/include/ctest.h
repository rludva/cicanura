#ifndef __CTEST_H__
#define __CTEST_H__

// Maximální délka zprávy (přiděluje se dynamicky, ale zde je i tak její omezení)..
#define MAX_OF_TEST_INFO_MESSAGE_LENGTH 256

//
#define TEST_PASS 0
#define TEST_FAIL 1

//
#define TRUE 1
#define FALSE 0

//
struct test_assert
{
	int count;
	int result;
	char *message;
};

//
struct test_function
{
	char *nazev;
	char *kategorie;
	int (*the_function)();
};

//
int ctest_test_functions_clear();
int ctest_test_functions_add(char *nazev, char *kategorie, int (*function)());

//
int ctest_run();

//
int ctest_assert_fail(char *message);
int ctest_assert_pass(char *message);

//
int ctest_assert_true(int avalue, char *message);
int ctest_assert_zero(int avalue, char *message);
int ctest_assert_null(void *avalue, char *message);
int ctest_assert_ptr(void *avalue, char *message);

//
int ctest_open();
int ctest_close();

//
int ctest_test_assert_add(int result, char *message);

//
int ctest_ls_fails();	// Výpis jen chybných testů..
int ctest_ls();		// Výpis všech testů..

// Předání počtu realizovaných assertů..
int ctest_get_asserts_count();
int ctest_get_asserts_pass_count();
int ctest_get_asserts_fail_count();

//
int ctest_print_asserts_count();

#endif
