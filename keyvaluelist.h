/*!
 *  \brief     keyvalue
 *  \details   create key/value bindings. implementation of a keyvalue list container
 *  \author    Daniel Kagemann
 *  \date      2012-01-18
 */

#ifndef KEYVALUELIST_H_
#define KEYVALUELIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct t_keyvalue {
	char		*key;
	char		*value;
};

struct t_keyvaluelist {
	size_t					size;
	size_t					capacity;
	struct t_keyvalue**		data;
};

typedef struct t_keyvalue		KeyValueItem;
typedef struct t_keyvaluelist	KeyValueList;

/* item interface */
KeyValueItem *kvitem_create ();
void kvitem_destroy (KeyValueItem* self);
void kvitem_setkey (KeyValueItem* self,const char *lpname, size_t len);
void kvitem_setvalue (KeyValueItem* self,const char *lpname, size_t len);

/* list interface */
KeyValueList* kv_create (int capacity);
void kv_destroy (KeyValueList* self);
void kv_add (KeyValueList* self, KeyValueItem* data);
void kv_dump (KeyValueList* self);
char* kv_valueForKey (KeyValueList* self, char* key);
KeyValueItem * kv_objectAtIndex (KeyValueList* self, int id);

#endif /* KEYVALUELIST_H_ */
