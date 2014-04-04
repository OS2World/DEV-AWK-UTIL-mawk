
/*
   see2obj.c
   This program recovers xdosexec.obj from xdosexec.see

   xdosexec.see lists each byte of xdosexec.obj as
	printf("%02x\n", byte)

   This program converts back from hex reading
   stdin to stdout
*/

/*$Log: see2obj.c,v $
 * Revision 1.1  1991/10/29  07:53:53  brennan
 * Initial revision
 *
*/


#include <ctype.h>
#include <stdio.h>

#ifndef  UNIX
#include <fcntl.h>
#endif

#define  hex(c) (isdigit(c)?(c)-'0':(c)-'a'+10)


main(argc, argv)
  int argc ; char **argv ;
{ int c1, c0 ;

#ifndef   UNIX
  setmode(1, O_BINARY) ;
#endif


  while ( (c1 = getchar()) != EOF )
  {
    c0 = getchar() ;

    if ( getchar() != '\n' )
    {
      fprintf(stderr, "%s: corrupt input\n", argv[0]) ;
      exit(1) ;
    }

    c1 = (hex(c1)<<4) + hex(c0) ;
    putchar(c1) ;
  }

  return 0 ;
}

  
  
