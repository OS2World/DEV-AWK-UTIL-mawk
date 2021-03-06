
/********************************************
sun_os41.h
copyright 1991, 1992.   Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/


/* $Log: sun_os41.h,v $
 * Revision 1.4  1992/07/07  15:45:58  brennan
 * <stdlib.h> is non-standard
 *
 * Revision 1.3  1991/12/05  08:24:02  brennan
 * 1.1 pre-release
 *
*/

#ifndef  CONFIG_H
#define  CONFIG_H

/* this is missing (actually its in 5include) */
int fprintf() ;

/* this is not in <stdlib.h>  */
double strtod() ;


#include "config/Idefault.h"

#endif
