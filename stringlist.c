/*!
 *  \brief     stringlist
 *  \details   implementation of a stringlist
 *  \author    Daniel Kagemann
 *  \date      2012-01-25
 */

#include "stringlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCREMENT_LIST		4

/* -------------------------------------------------------------- */
StringList* Stringlist_Construct (int capacity)
{
	StringList* list;
	int object_size = sizeof(char*);

	capacity = (capacity<=0) ? 20 : capacity;

	list = malloc(sizeof(StringList));
	list->capacity = capacity;
	list->data = malloc(object_size * capacity);
	list->size = 0;

	return list;
}
/* -------------------------------------------------------------- */
void Stringlist_EmptyPool (StringList* self)
{
	for (int i = 0; i < self->size; i++) {
		free (self->data[i]), self->data[i] = NULL;
	}
	self->size = 0;
}
/* -------------------------------------------------------------- */
void Stringlist_Destruct (StringList* self)
{
	if (self == NULL) {
		return;
	}

	Stringlist_EmptyPool (self);

	free (self->data), self->data = NULL;
	free (self);
}
/* -------------------------------------------------------------- */
void Stringlist_addObject (StringList* self, char* string)
{
	int old_size = self->size;
	int new_capacity;
	char**new_data;
	int object_size = sizeof(char*);

	(self->size)++;
	if (old_size == self->capacity) {
	  new_capacity = self->capacity + INCREMENT_LIST;
	  new_data = malloc(object_size * new_capacity);
	  memcpy(new_data, self->data, object_size * old_size);
	  free(self->data);
	  (self->data) = new_data;
	  self->capacity = new_capacity;
	}

	char * object = (char*)calloc (1, strlen(string) + 1);
	strcpy (object, string);
	(self->data)[old_size] = object;
}
/* -------------------------------------------------------------- */
char* Stringlist_objectAtIndex (StringList* self, int index)
{
	if (index < 0 || index >= self->capacity) {
		return NULL;
	}
	return self->data[index];
}
/* -------------------------------------------------------------- */
