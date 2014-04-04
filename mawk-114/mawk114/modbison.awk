#
# This awk script removes bison's use of alloca()
#
# If the parser stack overflows, bison reallocates the stack using
# alloca().  The chance of parser overflow on an awk program is nil,
# and since mawk never uses alloca() and some systems don't have it
# the most portable solution is to #if 0  it out
#
# This script works with bison 1.14 and 1.18
#

# Also with bison 1.14, two arrays yyphrs[] and yyrhs[] slip
# through that aren't needed if YYDEBUG == 0 so this script
# also puts #if YYDEBUG != 0  conditionals around them.  This
# only matters to those with small (64K) or so memory.

# This script is useful for any bison output to be used for
# example under MsDOS with a small model program.



BEGIN { state = 0 }

NR==2 && $0 !~ /Bison/ {
  print "modbison: y.tab.c is not Bison output" | "cat 1>&2"
  exit 1
}


state == 0 && $0 ~ /^static const short yyprhs\[\] = {/ {

  print "#if YYDEBUG != 0"
  print
  state = 1
  next
}


state == 1 && $0 ~ /^#if YYDEBUG/ {

  print "#endif"
  print 
  state = 2
  next
}

state == 2 && $0 ~ /^[ \t]*if \(yyssp >= yyss \+ yystacksize - 1\)/ {

   print ; getline ; print
   print "/* bison output modified to quit on stack overflow */"
   print "\tfprintf(stderr ,\"bison parser overflow\\n\") ;"
   print "\treturn 2 ;"
   print "#if 0"
   state = 3
   next
}

state == 3 && $0 ~ /YYABORT/ {
   print
   print "#endif  /* if 0 */"
   state = 4
   next
}

{ print }
     
