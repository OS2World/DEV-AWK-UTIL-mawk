
/********************************************
coherent.h
copyright 1992.  Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/

/* This is for COHERENT 4.0 */

/*
$Log: coherent.h,v $
 * Revision 1.1  1992/11/22  18:35:43  mike
 * Initial revision
 *
*/

#ifndef  CONFIG_H
#define  CONFIG_H       1

#define HAVE_VOID_PTR   0
#define HAVE_MATHERR    0
#define HAVE_FMOD       0
#define HAVE_STDLIB_H   1
#define HAVE_STRERROR	1

#define USE_SIMPLE_VFPRINTF  /* no vfprintf() */

#define HAVE_STDARG_H   1

   /* but it not standard ! 
      so add  */

#define  VA_ALIST(type, arg) (arg) type arg; {
#define  VA_ALIST2(t1,a1,t2,a2)  (a1,a2) t1 a1; t2 a2; {


/* Until MWC improves floating point (December 1992, they tell me),
   or fixes the math library (log(-8) gives 0, for example), we'll
   have to put up with inconsistent handling. 
   
   Coherent 4.0 cannot be set up to pass fpe_test
*/

#define FPE_TRAPS_ON    1
#define NOINFO_SIGFPE   1


int printf();
int sprintf();

#include "config/Idefault.h"

#endif
