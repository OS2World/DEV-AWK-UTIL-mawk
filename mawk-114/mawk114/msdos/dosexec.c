
/********************************************
dosexec.h
copyright 1991, Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/

/*$Log: dosexec.c,v $
 * Revision 1.4  1992/12/05  22:29:43  mike
 * dos patch 112d:
 * don't use string_buff
 * check COMSPEC
 *
 * Revision 1.3  1992/07/10  16:21:57  brennan
 * store exit code of input pipes
 *
 * Revision 1.2  1991/11/16  10:27:18  brennan
 * BINMODE
 *
 * Revision 1.1  91/10/29  09:45:56  brennan
 * Initial revision
 * 
*/

/* system() and pipes() for MSDOS */

#include "mawk.h"

#if MSDOS
#include "memory.h"
#include "files.h"
#include "fin.h"

#include <process.h>

static void PROTO(get_shell, (void)) ;

static char *shell ;     /* e.g.   "c:\\sys\\command.com"  */
static char *command_opt ;  /*  " /c"  */

static void get_shell()
{ char *s , *p ;
  int len ;

  if ( s = getenv("MAWKSHELL") )
  {
    /* break into shell part and option part */
    p = s ;
    while ( *p != ' ' && *p != '\t' ) p++ ;
    len = p - s ;
    shell = (char *) zmalloc(len+1) ;
    memcpy(shell, s, len) ; shell[len] = 0 ;
    command_opt = p ;
  }
  else
  if ( s = getenv("COMSPEC") )
  {
    shell = s ;
    command_opt = " /c" ;
	/* leading space needed because of bug in command.com */
  }
  else
  {
    errmsg(0,
    "cannot exec(), must set MAWKSHELL or COMSPEC in environment" ) ;
    exit(1) ;
  }
}


/* large model use spawnl() so we don't have to understand
   far memory management

   small model use assembler routine xDOSexec() to save code
   space
*/

int DOSexec( command )
  char *command ;
{
#if  SM_DOS
  extern int PROTO(xDOSexec, (char *, void*)) ;
  struct {
    int env_seg ;
    char far *cmdline ;
    unsigned fcb[4] ;
  } block ;
  int len ;
#endif

  char xbuff[256] ;

  if ( ! shell )  get_shell() ;

  (void) sprintf(xbuff+1, "%s %s", command_opt, command) ;

#if  SM_DOS
  block.env_seg = 0 ;
  block.cmdline = xbuff ;
  (void) memset(block.fcb, 0xff, sizeof(block.fcb)) ;
  len = strlen(xbuff+1) ;
  if ( len > 126 ) len = 126 ;
  xbuff[0] = len ;
  xbuff[len+1] = '\r' ;
#endif

  (void) fflush(stderr) ; (void) fflush(stdout) ;

#if SM_DOS
  return xDOSexec(shell, &block) ;
#else
  return   spawnl(P_WAIT, shell, shell, xbuff+1, (char *) 0 ) ;
#endif
}


static int next_tmp ;  /* index for naming temp files */
static char *tmpdir ;  /* directory to hold temp files */
static unsigned mawkid ; /* unique to this mawk process */


/* compute the unique temp file name associated with id */
char *tmp_file_name(id, buffer )
  int id ;
  char *buffer ;
{
  if ( mawkid == 0 )
  {
    /* first time */
    union {
    void far *ptr ;
    unsigned w[2] ;
    } xptr ;

    xptr.ptr = (void far*)&mawkid ;
    mawkid = xptr.w[1] ;

    tmpdir = getenv("MAWKTMPDIR") ;
    if ( ! tmpdir || strlen(tmpdir) > 80 ) tmpdir = "" ;
  }

  (void) sprintf(buffer, "%sMAWK%04X.%03X",tmpdir, mawkid, id) ;
  return buffer ;
}

/* open a pipe, returning a temp file identifier by
   reference
*/

PTR  get_pipe( command, type, tmp_idp)
  char *command ;
  int type, *tmp_idp ;
{
  PTR  retval ;
  char xbuff[256] ;
  char *tmpname ;


  *tmp_idp = next_tmp ;
  tmpname = tmp_file_name(next_tmp, xbuff+163) ;

  if ( type == PIPE_OUT )  
  {
    retval = (PTR) fopen(tmpname, (binmode()&2)? "wb":"w") ;
  }
  else
  { 
    sprintf(xbuff, "%s > %s" , command, tmpname) ;
    tmp_idp[1] = DOSexec(xbuff) ;
    retval = (PTR) FINopen(tmpname, 0) ;
  }

  next_tmp++ ;
  return retval ;
}

/* closing a fake pipes involves running the out pipe 
   command
*/

int close_fake_outpipe(command, tid)
  char *command ;
  int tid ; /* identifies the temp file */
{
  char xbuff[256] ;
  char *tmpname = tmp_file_name(tid, xbuff+163) ;
  int retval ;

  sprintf(xbuff, "%s < %s", command, tmpname) ;
  retval = DOSexec(xbuff) ;
  (void) unlink(tmpname) ;
  return retval ;
}

#endif  /* MSDOS */
