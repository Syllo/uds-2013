# Please enter here the locations for the CLooG include and library if they
# aren't the default values (/usr/lib and /usr/include).
CLOOG_INC = /usr/include
CLOOG_LIB = /usr/lib64

LDLIBS= -lcloog-isl -lgmp
CFLAGS= -DCLOOG_INT_GMP -I $(CLOOG_INC) -L /usr/local/lib -L $(CLOOG_LIB) -I /usr/local/include

LEX = lex
YACC = yacc -d
CC = gcc
E =./
PKG_CONFIG_PATH := /usr/lib/pkgconfig
export PKG_CONFIG_PATH

IBB: multiforParser.c lex.oo.c lex.yyy.c y.tab.c lex.yy.c
	@ $(CC) -c `pkg-config --cflags glib-2.0` multiforParser.c lex.oo.c lex.yyy.c y.tab.c lex.yy.c -ll  $(CFLAGS)  $(LDLIBS)
	$(CC) -o $$PWD/../../IBB multiforParser.o lex.oo.o lex.yyy.o y.tab.o lex.yy.o `pkg-config --libs glib-2.0` -lm $(CFLAGS)  $(LDLIBS)
#	echo ${PKG_CONFIG_PATH}
lex.oo.c: miseEnForme.l
	@ $(LEX)  -Poo  miseEnForme.l
lex.yyy.c: extractMULTIFOR.l
	@ $(LEX)  -Pyyy  extractMULTIFOR.l 
y.tab.c: AnaSyntxMul.y
	@ $(YACC) AnaSyntxMul.y
lex.yy.c: AnaLexMul.l
	@ $(LEX) AnaLexMul.l
