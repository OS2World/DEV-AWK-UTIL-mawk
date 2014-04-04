
/********************************************
ztc_dos.h
copyright 1992, Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/

/* Zortech C++ under MSDOS */

/* $Log: ztc_dos.h,v $
 * Revision 1.1  1992/12/27  01:42:50  mike
 * Initial revision
 *
 * Revision 4.2.1  92/06/01  00:00:00  bmyers
 * create Zortech C++ version from Borland C++ version
 * ZTC has matherr function and no info for floating point exceptions.
 *
*/

#ifndef   CONFIG_H
#define   CONFIG_H      1

#define   MSDOS                 1

#define   HAVE_PROTOS           1
#define   HAVE_STDARG_H         1
#define   HAVE_STDLIB_H		1
#define   HAVE_TIME_H		1
#define   HAVE_STRERROR		1

#define   HAVE_MATHERR          0




#define  FPE_TRAPS_ON		1
#define  NOINFO_SIGFPE          1


#ifndef   HAVE_SMALL_MEMORY   /* allow large model override */
#define   HAVE_SMALL_MEMORY     1
#endif

#if  HAVE_SMALL_MEMORY==0
/* how to test far pointers have the same segment */
#include <dos.h>
#define  SAMESEG(p,q)	(FP_SEG(p)==FP_SEG(q))
#endif

#include "config/Idefault.h"


#endif  /* CONFIG_H  */
