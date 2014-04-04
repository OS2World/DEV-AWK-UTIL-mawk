
/********************************************
sysVr4i386.h
copyright 1992, Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/


/* 

 On Intel platforms and maybe others,
 for some strange reason, division by zero traps but overflow
 does not, so we have to turn on the overflow trap.
 (This seems like a small bug to me.)
 If the trap is on, it won't hurt to turn it on some more.

 If you have ieee754 hardware *and* a math lib that
 supports it use sysV_ieeefp.h instead.

*/

/*$Log: sysVr4i386.h,v $
 * Revision 1.3  1992/07/14  14:23:35  brennan
 * fixed typo
 *
 * Revision 1.2  1992/07/07  15:40:02  brennan
 * DONT_PROTO_OPEN
 *
 * Revision 1.1  1992/07/01  18:07:47  brennan
 * Initial revision
 *
*/

#ifndef    CONFIG_H
#define    CONFIG_H		1

#define		FPE_TRAPS_ON		1
#define		NOINFO_SIGFPE		1

#define  USE_IEEEFP_H
#define  TURN_ON_FPE_TRAPS()  (void)fpsetmask(fpgetmask()|FP_X_OFL)

#define  DONT_PROTO_OPEN

#include  "config/Idefault.h"

#endif   /* CONFIG_H */
