#ifndef __COLLECTION_H__
#define __COLLECTION_H__

//
struct collection
{
	//
	struct collection_item *first_item;
	struct collection_item *last_item;

	//
	int length;
};

//
struct collection_item
{
	void *object;
	void *next;
};

//
struct collection *collection_new();
int collection_delete(struct collection *ptr);

//
struct collection_item *collection_item_new();

//
int collection_add(struct collection *ptr, void *object);
void collection_object_delete(struct collection *ptr, void (*function)(void *object));

//
int collection_foreach(struct collection *ptr, int (*function)(void *object));

#endif
