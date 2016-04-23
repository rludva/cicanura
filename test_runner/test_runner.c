//
#include <stdio.h>

//
#include "../core/include/ctest.h"

// Deklarace registračních funkcí: ctest_nazevbalíčku_register();
void ctest_test_strings_register();
void ctest_test_collection_register();
void ctest_test_ctest_register();
void ctest_test_bunkai_ichi_register();

//
int main()
{
	//
	ctest_open();

	// Registrace testovacích funkcí..
	ctest_test_strings_register();
	ctest_test_collection_register();
	ctest_test_ctest_register();
	ctest_test_bunkai_ichi_register();

	//
	ctest_run();
	
	//
	puts("");
	puts("Výsledky test:");
	ctest_print_asserts_count();
	puts("");

	// Vypsání špatných testů..
	if(ctest_get_asserts_fail_count())
	{
		puts("");
		puts("List of fails:");
		ctest_ls_fails();
		puts("\n");
	}

	//
	ctest_close();
}
