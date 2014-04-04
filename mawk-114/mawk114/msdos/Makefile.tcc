
#  this is a makefile for mawk under DOS
#  with Borland make
#
#   make    --  mawk.exe
#   make  -DLARGE   -- bmawk.exe

#  for a unix style command line add
#  -DREARV=your_reargv_file without the extension
#
#  e.g. -DREARGV=argvmks

#$Log: Makefile.tcc,v $
#Revision 1.4  1993/01/14  13:07:48  mike
#RM macro
#
#Revision 1.3  1992/12/27  01:44:11  mike
#have to use -G- to fit small model
#a bunch of small changes
#
#Revision 1.2  1991/11/12  09:59:26  brennan
#changed tcc to $(CC) and .o to .obj
#
#Revision 1.1  91/10/29  07:45:29  brennan
#Initial revision
#

.SWAP

# user settable
# change here or override from command line e.g. -DCC=bcc

!if ! $d(CC)
CC=tcc   # bcc or ? 
!endif

!if ! $d(LIBDIR)
LIBDIR =c:\lib    # where are your Borland C libraries ?
!endif  

!if !  $d(FLOATLIB)
FLOATLIB=emu   #  or  fp87 if you have fp87 hardware
!endif

!if ! $d(WILDCARD)
WILDCARD=$(LIBDIR)\wildargs.obj
!endif

# compiler flags
# -G optimize for speed
# -d merge duplicate strings
# -v- symbolic debugging off
# -O  optimize
CFLAGS = -c -d -v- -O 

!if $d(LARGE)
OPT = -G
!else
OPT = -G-  # opt for size (getting too big)
!endif


LFLAGS = /c  #case sensitive linking

# how to delete a file
!if ! $d(RM)
RM = del    # rm
!endif

# how to rename a file
!if ! $d(RENAME)
RENAME = rename  # mv
!endif

##############################
# end of user settable
#

!if ! $d(LARGE)
MODEL=s
TARGET=mawk
!else  
MODEL=l
TARGET=bmawk
CFLAGS=$(CFLAGS) -DHAVE_SMALL_MEMORY=0
!endif

CFLAGS=-m$(MODEL) $(OPT) $(CFLAGS)


!if  $d(REARGV)
CFLAGS=$(CFLAGS) -DHAVE_REARGV=1 # over rides def in tcc_dos.h
!endif

OBS = parse.obj \
array.obj \
bi_funct.obj \
bi_vars.obj \
cast.obj \
code.obj \
da.obj \
error.obj \
execute.obj \
fcall.obj \
field.obj \
files.obj \
fin.obj \
hash.obj \
init.obj \
jmp.obj \
kw.obj \
main.obj \
matherr.obj \
memory.obj \
print.obj \
re_cmpl.obj \
scan.obj \
scancode.obj \
split.obj \
zmalloc.obj  \
version.obj  \
dosexec.obj

!if  $d(REARGV)  
OBS = $(OBS) $(REARGV).obj
!endif

!if  ! $d(LARGE)
OBS=$(OBS) xdosexec.obj
!endif

REXP_OBS = rexp.obj \
rexp0.obj \
rexp1.obj \
rexp2.obj \
rexp3.obj

LIBS = $(LIBDIR)\$(FLOATLIB) \
$(LIBDIR)\math$(MODEL) $(LIBDIR)\c$(MODEL)

$(TARGET).exe : $(OBS)  $(REXP_OBS)
	tlink $(LFLAGS) @&&!
	$(LIBDIR)\c0$(MODEL) $(WILDCARD) $(OBS) $(REXP_OBS)
	$(TARGET),$(TARGET)
	$(LIBS)
!

.c.obj :
	$(CC) $(CFLAGS) {$*.c }


scancode.c :  makescan.c  scan.h
	$(CC) makescan.c
	makescan.exe > scancode.c
	$(RM) makescan.obj  
	$(RM) makescan.exe

xdosexec.obj  :  msdos\xdosexec.see
	$(CC) msdos\see2obj.c
	see2obj < msdos\xdosexec.see > xdosexec.obj
	$(RM) see2obj.exe

#xdosexec.obj  :  xdosexec.asm
#	masm /mx /z xdosexec ;

###################################################
# parse.c is provided in distribution( made with byacc)
# so you don't need to make it.
# 
# But if you do:  here's how:
# To make it with bison1.14 under msdos
# parse.c : parse.y parse2.xc
#	bison -dy parse.y
#	bmawk -f modbison.awk y_tab.c parse2.xc > parse.c
#	$(RENAME) y_tab.h parse.h
#	$(RM) y_tab.c
########################################


clean  :
	$(RM)  *.obj


RFLAGS=-Irexp -DMAWK

!if  $d(LARGE)
RFLAGS=$(RFLAGS) -DLMDOS
!endif

# there must be a better way to do this
rexp.obj  :  rexp/rexp.c  rexp/rexp.h
	$(CC) $(CFLAGS) $(RFLAGS) rexp/rexp.c

rexp0.obj  :  rexp/rexp0.c  rexp/rexp.h
	$(CC) $(CFLAGS) $(RFLAGS) rexp/rexp0.c

rexp1.obj  :  rexp/rexp1.c  rexp/rexp.h
	$(CC) $(CFLAGS) $(RFLAGS) rexp/rexp1.c

rexp2.obj  :  rexp/rexp2.c  rexp/rexp.h
	$(CC) $(CFLAGS) $(RFLAGS) rexp/rexp2.c

rexp3.obj  :  rexp/rexp3.c  rexp/rexp.h
	$(CC) $(CFLAGS) $(RFLAGS) rexp/rexp3.c


#  dependencies of .objs on .h
array.obj : bi_vars.h sizes.h zmalloc.h memory.h types.h field.h mawk.h config.h symtype.h config/Idefault.h
bi_funct.obj : fin.h bi_vars.h sizes.h memory.h zmalloc.h regexp.h types.h field.h repl.h files.h bi_funct.h mawk.h config.h symtype.h init.h config/Idefault.h
bi_vars.obj : bi_vars.h sizes.h memory.h zmalloc.h types.h field.h mawk.h config.h symtype.h config/Idefault.h init.h
cast.obj : parse.h sizes.h memory.h zmalloc.h types.h field.h scan.h repl.h mawk.h config.h symtype.h config/Idefault.h
code.obj : sizes.h memory.h zmalloc.h types.h field.h code.h jmp.h mawk.h config.h symtype.h config/Idefault.h init.h
da.obj : sizes.h memory.h zmalloc.h types.h field.h repl.h code.h bi_funct.h mawk.h config.h symtype.h config/Idefault.h
error.obj : parse.h bi_vars.h sizes.h types.h scan.h mawk.h config.h symtype.h config/Idefault.h
execute.obj : bi_vars.h fin.h sizes.h memory.h zmalloc.h regexp.h types.h field.h code.h repl.h bi_funct.h mawk.h config.h symtype.h config/Idefault.h
fcall.obj : sizes.h memory.h zmalloc.h types.h code.h mawk.h config.h symtype.h config/Idefault.h
field.obj : parse.h bi_vars.h sizes.h memory.h zmalloc.h regexp.h types.h field.h scan.h repl.h mawk.h config.h symtype.h config/Idefault.h init.h
files.obj : fin.h sizes.h memory.h zmalloc.h types.h files.h mawk.h config.h config/Idefault.h
fin.obj : parse.h fin.h bi_vars.h sizes.h memory.h zmalloc.h types.h field.h scan.h mawk.h config.h symtype.h config/Idefault.h
hash.obj : sizes.h memory.h zmalloc.h types.h mawk.h config.h symtype.h config/Idefault.h
init.obj : bi_vars.h sizes.h memory.h zmalloc.h types.h field.h code.h mawk.h config.h symtype.h config/Idefault.h init.h
jmp.obj : sizes.h memory.h zmalloc.h types.h code.h mawk.h jmp.h config.h symtype.h config/Idefault.h init.h
kw.obj : parse.h sizes.h types.h mawk.h config.h symtype.h config/Idefault.h init.h
main.obj : fin.h bi_vars.h sizes.h memory.h zmalloc.h types.h field.h code.h files.h mawk.h config.h symtype.h config/Idefault.h init.h
makescan.obj : parse.h scan.h symtype.h
matherr.obj : sizes.h types.h mawk.h config.h config/Idefault.h
memory.obj : sizes.h memory.h zmalloc.h types.h mawk.h config.h config/Idefault.h
parse.obj : bi_vars.h sizes.h memory.h zmalloc.h types.h field.h code.h files.h bi_funct.h mawk.h jmp.h config.h symtype.h config/Idefault.h
print.obj : bi_vars.h parse.h sizes.h memory.h zmalloc.h types.h field.h scan.h files.h bi_funct.h mawk.h config.h symtype.h config/Idefault.h
re_cmpl.obj : parse.h sizes.h memory.h zmalloc.h regexp.h types.h scan.h repl.h mawk.h config.h symtype.h config/Idefault.h
scan.obj : parse.h fin.h sizes.h memory.h zmalloc.h types.h field.h scan.h repl.h code.h files.h mawk.h config.h symtype.h config/Idefault.h init.h
split.obj : bi_vars.h parse.h sizes.h memory.h zmalloc.h regexp.h types.h field.h scan.h bi_funct.h mawk.h config.h symtype.h config/Idefault.h
version.obj : patchlev.h sizes.h types.h mawk.h config.h config/Idefault.h
zmalloc.obj : sizes.h zmalloc.h types.h mawk.h config.h config/Idefault.h
dosexec.obj : fin.h sizes.h memory.h zmalloc.h types.h files.h mawk.h config/Idefault.h config.h
