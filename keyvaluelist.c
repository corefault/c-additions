/*!
 *  \brief     keyvalue
 *  \details   create key/value bindings. implementation of a keyvalue list container
 *  \author    Daniel Kagemann
 *  \date      2012-01-18
 */

#define INCREMENT_KV		4

#include "keyvaluelist.h"

/* -------------------------------------------------------------- */
KeyValueList* kv_create (int capacity)
{
	KeyValueList	*self = calloc (1,sizeof(KeyValueList));

	capacity = (capacity<=0) ? INCREMENT_KV : capacity;
	self->capacity = capacity;
	self->size	   = 0;
	self->data     = calloc (1,capacity * sizeof (KeyValueItem*));
	memset (self->data,0,capacity * sizeof (KeyValueItem*));

	return self;
}
/* -------------------------------------------------------------- */
void kv_destroy (KeyValueList* self)
{
	size_t i = 0;

	if (self) {
		for (i = 0; i < self->size; i++) {
			kvitem_destroy(self->data[i]);
		}
		free (self->data);
		free (self);
	}
}
/* -------------------------------------------------------------- */
void kv_add (KeyValueList* self, KeyValueItem* data)
{
	if (self == NULL || data == NULL) {
		return;
	}

	size_t old_size = self->size;
	int new_capacity;
	KeyValueItem**new_data;
	int object_size = sizeof(KeyValueItem);

	(self->size)++;
	if (old_size == self->capacity) {
	  new_capacity = self->capacity + INCREMENT_KV;
	  new_data = malloc(object_size * new_capacity);
	  memcpy(new_data, self->data, object_size * old_size);
	  free(self->data);
	  (self->data) = new_data;
	  self->capacity = new_capacity;
	}

	(self->data)[old_size] = data;
}
/* -------------------------------------------------------------- */
KeyValueItem * kv_objectAtIndex (KeyValueList* self, int id)
{
	if (id < 0 || id >= (int)self->size) {
		return NULL;
	}
	return self->data[id];
}
/* -------------------------------------------------------------- */
void kv_dump (KeyValueList* self)
{
	size_t i = 0;
	for (i = 0; i < self->size; i++) {
		printf ("key(%s) = %s\n", self->data[i]->key, self->data[i]->value);
	}
}
/* -------------------------------------------------------------- */
KeyValueItem *kvitem_create ()
{
	return calloc (1,sizeof (KeyValueItem));
}
/* -------------------------------------------------------------- */
void kvitem_destroy (KeyValueItem* self)
{
	if (self) {
		free (self->key), self->key = NULL;
		free (self->value), self->value = NULL;
		free (self);
	}
}
/* -------------------------------------------------------------- */
void kvitem_setkey (KeyValueItem* self,const char *lpname, size_t len)
{
	if (self && lpname) {
		self->key = calloc (len+1, sizeof(char));
		strncpy (self->key,lpname, len);
	}
}
/* -------------------------------------------------------------- */
void kvitem_setvalue (KeyValueItem* self,const char *lpname, size_t len)
{
	if (self && lpname) {
		self->value = calloc (len+1, sizeof(char));
		strncpy (self->value,lpname, len);
		self->value[len] = 0;
	}
}
/* -------------------------------------------------------------- */
char* kv_valueForKey (KeyValueList* self, char* key)
{
	size_t i = 0;
	for (i = 0; i < self->size; i++) {
		if (strcmp (self->data[i]->key, key) == 0) {
			return self->data[i]->value;
		}
	}
	return 0;
}
/* -------------------------------------------------------------- */
