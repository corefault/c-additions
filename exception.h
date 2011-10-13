/*
 * exception.h
 *
 *  Created on: 29.09.2011
 *      Author: kagemann
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

/* macros */
#define EXCEPTION_TRY		do {
#define EXCEPTION_CATCH	}while(0);
#define EXCEPTION_THROW(ok,e,func)	if ((e=func)!=ok) {break;}

/* using the macros
 *
 * int func (int arg)
 * {
 * 	  return arg;
 * }
 *
 * int main ()
 * {
 *   int err = 0;
 *
 * 	  EXCEPTION_TRY
 * 	  		EXCEPTION_THROW(0,err,func(0));
 * 	  		printf ("first\n");

 * 	  		EXCEPTION_THROW(0,err,func(1));
 * 	  		printf ("second\n");

 * 	  		EXCEPTION_THROW(0,err,func(2));
 * 	  		printf ("third\n");
 *
 * 	  EXCEPTION_CATCH
 *
 * 	  printf ("done\n");
 *
 * 	  return err;
 * }
 *
 * output:
 *   first
 *   done
 *
 * */


#endif /* EXCEPTION_H_ */
