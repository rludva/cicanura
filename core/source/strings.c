//
#include <assert.h>
#include <stdlib.h>
#include <string.h>

//
#include "../include/strings.h"

//
char *strings_new(char *src)
{
	//
	char *ptr = NULL;

	//	
	if(src == NULL)
	{
		return NULL;
	}

	//
	ptr = malloc(sizeof(char)*strlen(src));

	//
	assert(ptr != NULL);

	//
	strcpy(ptr, src);

	//
	return ptr;
}

//
int strings_free(char *ptr)
{
	//
	if(ptr != NULL)
	{
		//
		free(ptr);

		//
		ptr = NULL;
	}

	//
	return 0;
}
