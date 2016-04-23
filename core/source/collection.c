#include <stdlib.h>
#include <assert.h>

//
#include "../include/collection.h"

///
struct collection_item *collection_item_new()
{
	//
	struct collection_item *ptr = (struct collection_item *) malloc(sizeof(struct collection_item));

	//
	ptr -> object = NULL;
	ptr -> next  = NULL;

	//
	return ptr;
}

///
struct collection *collection_new()
{
	//
	struct collection *ptr = (struct collection *) malloc(sizeof(struct collection));

	//
	ptr -> first_item = NULL;
	ptr -> last_item  = NULL;

	//
	ptr -> length = 0;

	//
	return ptr;
}

///
int collection_delete(struct collection *ptr)
{
	//
	struct collection_item *item;

	//
	if(ptr == NULL)
	{
		return -1;
	}

	// Budeme uvolňovat kolekci od prvního prvku..
	item = ptr -> first_item;

	// Uvolnění všech položekm kolekec (items)..
	while(item)
	{
		//
		struct collection_item *next = item -> next;

		//
		free(item);

		//
		item = next;
	}

	// Uvolnění samotné kolekce..
	free(ptr);

	//
	return 0;
}

///
int collection_add(struct collection *ptr, void *object)
{
	// Nová položka kolekce..
	struct collection_item *item;

	// Pokud kolekce nebyla vytvořena a neexistuje, tak nemáš kam přidat novou položku..
	if(ptr == NULL)
	{
		//
		return -1;
	}	
	
	// Vytvoříme ukazatel na novou položku kolekce..
	item = collection_item_new();

	// 
	if(item == NULL)
	{
		return -2;
	}

	// Nastavíme hodnoty pro položku kolekce s tím, že nová položka kolekce je poslední v kolekci..
	item -> object = object;
	item -> next = NULL;

	// Pokud již je první prvek v kolekci obsažen..
	if(ptr -> first_item != NULL)
	{
		//
		struct collection_item *i = ptr -> last_item;

		//
		i -> next = item;

		//
		ptr -> last_item = item;

		//
		ptr -> length++;
	}
	
	// Pokud není první prvek v kolekci obsažen..
	if(ptr -> first_item == NULL)
	{
		//
		ptr -> first_item = item;
		ptr -> last_item = item;

		//
		ptr -> length = 1;
	}

	//
	return 0;
}

///
void collection_object_delete(struct collection *ptr, void (*function)(void *object))
{
	//
	struct collection_item *item = ptr -> first_item;

	//
	while(item)
	{
		//
		void *object = item -> object;

		// Delete function..
		if(object)
		{
			function(object);
		}

		//
		object = NULL;

		//
		item = item -> next;
	}
}

///
int collection_foreach(struct collection *ptr, int (*function)(void *object))
{
	//
	struct collection_item *item = NULL;

	//
	if(ptr == NULL)
	{
		return 0;
	}

	//
	item = ptr -> first_item;
	
	//
	while(item)
	{
		//
		function(item -> object);

		//
		item = item -> next;
	}

	//
	return 0;
}
