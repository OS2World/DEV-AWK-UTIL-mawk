
/********************************************
os2.h

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/

/*
  OS/2 2.0
*/

/* $Log$
*/

#ifndef  CONFIG_H
#define  CONFIG_H	1

/* system compiler is gcc and has <stdlib.h> */
#define  HAVE_STDLIB_H     1
#define  HAVE_STRERROR     1

/* OS/2 has real pipes */
#define HAVE_REAL_PIPES    1

#include "config/Idefault.h"

#endif

