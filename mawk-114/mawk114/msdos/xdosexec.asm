
;********************************************
; xdosexec.asm
; copyright 1991, Michael D. Brennan
; 
; This is a source file for mawk, an implementation of
; the AWK programming language.
; 
; Mawk is distributed without warranty under the terms of
; the GNU General Public License, version 2, 1991.
;*******************************************/

; This is only used for small model DOS
; It executes a program via int 0x21 0x4b00
;

public  _xDOSexec

.model  small

;  _xDOSexec(char *command, void *blockp)

command  equ  [bp+4]
blockp   equ  [bp+6]

.data
extrn  _errno : word
.code

ss_save   dw   ?
sp_save   dw   ?

_xDOSexec  proc  near

     push  bp
     mov   bp, sp
     push  si
     push  di
     push  ds
     mov   ax, ds
     mov   es, ax
     mov   cs:ss_save, ss
     mov   cs:sp_save, sp
     mov   ax, 4b00h
     mov   bx, blockp
     mov   dx, command
     int   21h
     jc    @error
     cli            ;   restore  stack
     mov   ss, cs:ss_save
     mov   sp, cs:sp_save
     sti
     mov   ax, 4d00h
     int   21h      ;  get child exit code
@exit:
     pop   ds
     pop   di
     pop   si
     pop   bp
     ret
@error:
     mov   _errno, ax
     mov   ax, -1
     jmp   @exit

_xDOSexec  endp
end
