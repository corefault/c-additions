/*!
 *  \brief     stringlist
 *  \details   implementation of a stringlist
 *  \author    Daniel Kagemann
 *  \date      2012-01-25
 */

#ifndef stringlist_h_
#define stringlist_h_

typedef struct t_stringlist {
	int		capacity;
	int 	size;
	char	**data;
} StringList;

StringList* Stringlist_Construct (int capacity);
void Stringlist_Destruct (StringList* self);
void Stringlist_addObject (StringList* self, char* string);
char* Stringlist_objectAtIndex (StringList* self, int index);
void Stringlist_EmptyPool (StringList* self);

#endif
