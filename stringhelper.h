/*!
 *  \brief     stringhelper
 *  \details   functions to handle strings
 *  \author    Daniel Kagemann
 *  \date      2012-01-18
 */

#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

char * String_Construct (char* src);
void   String_Append    (char** dest, char* src);
void   String_AppendFormat (char** dest, char* fmt, ...);
const char * String_FromLong (long l);
void String_enclose (char** result, char * prefix, char * suffix);
void String_trimEnd (char** result, char trim);
void String_trimBegin (char** result, char trim);

char* String_encode (const char* val);

_Bool String_isEqual (const char * src, const char * dest);


#endif /* STRINGHELPER_H_ */
