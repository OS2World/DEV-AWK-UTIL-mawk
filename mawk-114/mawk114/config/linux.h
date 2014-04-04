/*

linux.h
Sorta tested with Linux 0.98pl4 & gcc 2.2d7
Slapped together by Bob Hutchinson
Standard disclaimer: "Well, it worked for me..."

*/


#ifndef   CONFIG_H
#define   CONFIG_H      	1

#define HAVE_MATHERR		0
#define HAVE_STDLIB_H		1

#define  DONT_PROTO_OPEN

#define FPE_TRAPS_ON		1
#define NOINFO_SIGFPE		1

#include "config/Idefault.h"

#endif  /* CONFIG_H  */
