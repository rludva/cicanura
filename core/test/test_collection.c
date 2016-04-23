//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//
#include "../include/ctest.h"

//
#include "../include/collection.h"

///
int test_collection_01()
{
	//
	struct collection *col;

	//
	col = collection_new();
	collection_delete(col);

	//
	char *assert_message = "Testing collection for simple new/delete..";
	ctest_assert_pass(assert_message);

	//
	return 0;
}

///
int test_collection_02()
{
	//
	struct collection *col = NULL;

	// Pokud to proběhne bez toho aniž by spadlo na neoprávněný přístup do paměti, je to OK (snad)..
	collection_delete(col);

	//
	char *assert_message = "Testing collection for delete NULL..";
	ctest_assert_pass(assert_message);

	//
	return 0;
}

///
int test_collection_03()
{
	//
	struct collection *col = NULL;

	// Pokud to proběhne bez toho aniž by spadlo na neoprávněný přístup do paměti, je to OK (snad)..
	col = collection_new();
	collection_add(col, NULL);
	collection_delete(col);

	//
	char *assert_message = "Testing collection for new/add(null)/delete..";
	ctest_assert_pass(assert_message);

	//
	return 0;
}

///
int test_collection_04()
{
	//
	struct collection *col = NULL;

	// Pokud to proběhne bez toho aniž by spadlo na neoprávněný přístup do paměti, je to OK (snad)..
	col = collection_new();

	//
	collection_add(col, NULL);
	collection_add(col, NULL);
	collection_add(col, NULL);
	collection_add(col, NULL);
	collection_add(col, NULL);
	collection_add(col, NULL);
	collection_add(col, NULL);
	collection_add(col, NULL);

	// Zde budu testovat hodnoty položky kolekce..
	struct collection_item *item = col -> first_item;
	while(item)
	{
		//
		void *object = NULL;

		//
		if(item -> object)
		{
			object = item -> object;
		}

		//
		if(object != NULL)
		{
			ctest_assert_null(object, "Hodnota položky object v kolekci je neplatná měla by být NULL..");
			break;
		}

		//
		item = item -> next;
	}

	//
	collection_delete(col);

	//
	char *assert_message = "Testing collection for new/several add(null)/delete..";
	ctest_assert_pass(assert_message);

	//
	return 0;
}

///
int test_collection_05()
{
	//
	struct collection *col = NULL;

	//
	int my_number = 1234;
	int *my_object = &my_number;

	// Pokud to proběhne bez toho aniž by spadlo na neoprávněný přístup do paměti, je to OK (snad)..
	col = collection_new();

	//
	collection_add(col, my_object);
	collection_add(col, my_object);
	collection_add(col, my_object);
	collection_add(col, my_object);

	//
	struct collection_item *item = col -> first_item;

	//
	while(item)
	{
		//
		void *object = NULL;

		//
		object = item -> object;
	
		//
		if(object == NULL)
		{
			ctest_assert_fail("Object has to by valid object to pass this test!");
			break;
		}

		//
		if(object != my_object)
		{
			ctest_assert_fail("Object address is not the expected one!");
			break;
		}

		//
		int value = *(int *) object;
		if(value != my_number)
		{
			ctest_assert_fail("Object value is not the excepted one!");
			break;
		}

		//
		item = item -> next;
	}

	//
	collection_delete(col);

	//
	char *assert_message = "Testing collection for new/several add(null)/delete..";
	ctest_assert_pass(assert_message);

	//
	return 0;
}

///
int test_collection_object_delete()
{
	// Vytvoření objektu, který se bude vkládat do kolekce..
	int *object = malloc(sizeof(int));
	*object = 333;

	// Funkce, která maže objekt umístěný do kolekce..
	void delete_function(void *ptr)
	{
		// Informace o objektu..
		int i = *(int*) ptr;

		// 
		{
			char *assert_message = "Hodnota objektu kolekce se schoduje s hodnotou původního objektu..";
			int assert_result = (i == *object) ? TRUE : FALSE;
			ctest_assert_true(assert_result, assert_message);
		}

		// Samotné odebrání objektu..
		free(ptr);

		// 
		{
			char *assert_message = "Adresa objektu pro uvolnění paměti se schoduje s adresou alokovanou..";
			int assert_result = (object == ptr) ? TRUE : FALSE;
			ctest_assert_true(assert_result, assert_message);
		}
	}

	// Vytvoření kolekce..
	struct collection *col = collection_new();

	// Vložení objektu do kolekce..
	collection_add(col, object);

	// A nyní objekt odstraňujeme
	collection_object_delete(col, &delete_function);

	// Odebrání samotné kolekce a ukončení testu..
	collection_delete(col);
}

///
int test_collection_foreach_01()
{
	//
	int sum = 0;

	//
	int a = 11;
	int b = 22;
	int c = 33;

	//
	int sum_expected = a + b + c;

	///
	int sum_items(void *object_ptr)
	{
		if(object_ptr)
		{
			sum += *((int *) object_ptr);
		}
	}

	//
	struct collection *col = collection_new();
	
	//
	collection_foreach(col, &sum_items);

	//
	{
		char *assert_message = "Volání funkce collection_foreach v situaci, kdy neobsahuje žádnou položku!";
		int assert_result = (sum == 0) ? TRUE : FALSE;
		ctest_assert_true(assert_result, assert_message);
	}
	
	//
	collection_add(col, NULL);

	//
	collection_foreach(col, &sum_items);

	//
	{
		char *assert_message = "Volání funkce collection_foreach v situaci, kdy objekt, který obsahuje je NULL!";
		int assert_result = (sum == 0) ? TRUE : FALSE;
		ctest_assert_true(assert_result, assert_message);
	}

	//
	collection_add(col, &a);

	//
	collection_foreach(col, &sum_items);
	
	//
	{
		char *assert_message = "Volání funkce collection_foreach v situaci, kdy obsahuje jen jednu položku!";
		int assert_result = (sum == a) ? TRUE : FALSE;
		ctest_assert_true(assert_result, assert_message);
	}

	//
	collection_delete(col);

	//
	col = collection_new();

	//
	collection_add(col, &a);
	collection_add(col, &b);
	collection_add(col, &c);

	//
	sum = 0;

	//
	collection_foreach(col, &sum_items);

	//
	{
		char *assert_message = "Aritmetická suma objektů typu int v kolekci je dobře spočítána..";
		int assert_result = (sum == sum_expected) ? TRUE : FALSE;
		ctest_assert_true(assert_result, assert_message);
	}
	
	//
	collection_delete(col);
}

///
void ctest_test_collection_register()
{
	ctest_test_functions_add("Kontrola funkce vytvoření a zrušení kolekce..", "collection", &test_collection_01);
	ctest_test_functions_add("Kontrolní funkce při rušení neexistující kolekce..", "collection", &test_collection_02);
	ctest_test_functions_add("Kontrolní funkce pro vytvoření a zrušení kolekce s přidáním jednoho prvku..", "collection", &test_collection_03);
	ctest_test_functions_add("Kontrolní funkce pro vytvoření a zrušení kolekce s přidáním několika prvků..", "collection", &test_collection_04);
	ctest_test_functions_add("Kontrolní funkce pro obsah položek v kolekci.obsah položek v kolekci..", "collection", &test_collection_05);
	ctest_test_functions_add("Kontrolní funkce pro odebrání dynamických objektů v kolekci..", "collection", &test_collection_object_delete);
	ctest_test_functions_add("Kontrolní funkce pro spuštění kódu na všemi objekty kolekce (01)..", "collection", &test_collection_foreach_01);
}
