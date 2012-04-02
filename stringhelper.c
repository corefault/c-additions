/*!
 *  \brief     stringhelper
 *  \details   functions to handle strings
 *  \author    Daniel Kagemann
 *  \date      2012-01-18
 */

#include <ctype.h>
#include "stringhelper.h"

/* -------------------------------------------------------------- */
char * String_Construct (char* src)
{
	char * object = (char*)calloc (1, strlen(src) + 1);
	memcpy (object, src, strlen(src));
	return object;
}
/* -------------------------------------------------------------- */
void String_Append (char** dest, char* src)
{
	int	length = 0;

	if (src == NULL) {
		return;
	}

	if (*dest == NULL) {
		*dest = String_Construct (src);
	}
	else {
		size_t sl = strlen (src);
		size_t dl = strlen (*dest);
		length = sl + dl + 1;
		char	*newobj = calloc (1, length);
		memcpy (newobj, *dest, dl);
		memcpy (newobj+dl,src,sl);
		free (*dest), *dest=NULL;
		*dest = newobj;
	}
}
/* -------------------------------------------------------------- */
void String_AppendFormat (char** dest, char* fmt, ...)
{
	int				length = 0;
	char			*result = 0;
	va_list 		args;

	va_start (args,fmt);
	length = vsnprintf (0, 0, fmt, args);

	if (length > 0) {
		result = calloc (1, ++length);
		vsnprintf (result, length, fmt, args);

		String_Append (dest, result);
		free (result), result = 0;
	}

	va_end (args);
}
/* -------------------------------------------------------------- */
const char * String_FromLong (long l)
{
	static char	buf[10];
	snprintf (buf,sizeof(buf),"%ld", l);
	return buf;
}
/* -------------------------------------------------------------- */
void String_enclose (char** result, char * prefix, char * suffix )
{
	if (*result == NULL) {
		return;
	}

	char * buf = String_Construct (prefix);
	String_Append (&buf, *result);
	String_Append (&buf, suffix);

	free (*result), *result = NULL;

	*result = buf;
}
/* -------------------------------------------------------------- */
char* String_encode (const char* val)
{
	static char     buffer[1024];
	unsigned int	 id = 0, bid = 0;

	/*
	 * replace json related characters with corresponding html entities
	 * for more encoding have a look at http://www.homepage-total.de/html/unicode-tabelle.php
	 *
	 * [ is &#91;
	 * ] is &#93;
	 * " is &#34;
	 * { &#123;
	 * } &#125;
	 *
	 */

	memset (buffer,0,sizeof(buffer));

	for (id = 0; id < strlen (val); id++) {

		if (val[id] == '[') {
			buffer[bid] = '&', buffer[++bid] = '#', buffer[++bid] = '9', buffer[++bid] = '1', buffer[++bid] = ';', bid++;
		}
		else if (val[id] == ']') {
			buffer[bid] = '&', buffer[++bid] = '#', buffer[++bid] = '9', buffer[++bid] = '3', buffer[++bid] = ';', bid++;
		}
		else if (val[id] == '\n') {
			buffer[bid] = '<', buffer[++bid] = 'b', buffer[++bid] = 'r', buffer[++bid] = '/', buffer[++bid] = '>', bid++;
		}
		else if (val[id] == '\"') {
			buffer[bid] = '&', buffer[++bid] = '#', buffer[++bid] = '3', buffer[++bid] = '4', buffer[++bid] = ';', bid++;
		}
		else if (val[id] == '{') {
			buffer[bid] = '&', buffer[++bid] = '#', buffer[++bid] = '1', buffer[++bid] = '2', buffer[++bid] = '3', buffer[++bid] = ';', bid++;
		}
		else if (val[id] == '}') {
			buffer[bid] = '&', buffer[++bid] = '#', buffer[++bid] = '1', buffer[++bid] = '2', buffer[++bid] = '5', buffer[++bid] = ';', bid++;
		}
		else {
			buffer[bid++] = val[id];
		}
	}

	return buffer;
}
/* -------------------------------------------------------------- */
void String_trimEnd (char** result, char trim)
{
	if (*result == NULL) {
		return;
	}
	for (int i = strlen (*result)-1; i>=0 && (*result)[i] == trim; i--) {
		(*result)[i] = 0;
	}
}
/* -------------------------------------------------------------- */
void String_trimBegin (char** result, char trim)
{
	if (*result == NULL) {
		return;
	}
	size_t	i;
	for (i = 0; i < strlen (*result); i++) {
		if ( (*result)[i] == trim) {
			continue;
		}
		char * val = String_Construct((*result) + i);
		free (*result), *result = NULL;
		*result = val;
		return;
	}
}
/* -------------------------------------------------------------- */
_Bool String_isEqual (const char * src, const char * dest)
{
	//# avoid copy of src and dest with translation into lower- or uppercase
	size_t	sl = strlen (src);
	size_t  dl = strlen (dest);
	if (sl != dl) {
		return false;
	}

	for (size_t i = 0; i < sl; i++) {
		if (tolower(src[i]) != tolower(dest[i])) {
			return false;
		}
	}
	return true;
}
/* -------------------------------------------------------------- */

