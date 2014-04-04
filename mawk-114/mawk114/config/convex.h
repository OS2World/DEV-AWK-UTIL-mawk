
/********************************************
convex.h
copyright 1992, Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/


/* tested on ConvexOS 9.1

There is a bug in convex strtod(3) in OS 8.1, 9.0 and 9.1.

It is supposed to be fixed in 10.0

The patch is PR-25399

*/

/*$Log: convex.h,v $
 * Revision 1.1  1992/07/08  16:07:31  brennan
 * Initial revision
 *
*/

/* convex.h */

#ifndef   CONFIG_H
#define   CONFIG_H	1

#define	FPE_TRAPS_ON	1
#define	FPE_ZERODIVIDE	0x4
#define	FPE_OVERFLOW	0x3
#define	HAVE_MATHERR	0

#define  sys_nerr	__ap$sys_nerr
#define  sys_errlist	__ap$sys_errlist

#include "config/Idefault.h"
#endif /* CONFIG_H  */


