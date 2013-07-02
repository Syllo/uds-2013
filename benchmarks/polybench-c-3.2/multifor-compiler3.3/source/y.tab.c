#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20120115

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 17 "AnaSyntxMul.y"
/* C declarations and includes*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glib.h>
# include <cloog/cloog.h>
#include "arbre.h"
int nbInit, nbComp, nbInc, nbGrain, nbOffset ;
extern char * yytext;
extern int maxRef;
extern int oldmaxRef;
extern int maxRefAc;
extern int create_Max_Min;
int nbErr;
int nbLigne;
GNode* root;
GNode* pere;
GNode* frere;
GPtrArray* lesFor;
GPtrArray* lesGardes;
GPtrArray* lesIndices;
GPtrArray* coefNivSup;
GPtrArray* toutcoefNivSup;
GPtrArray* blocks;
GSList * MesssInstr ;

FILE * fichier;

GList * parameters;/* Besoin de ça pour la matrice contexte */
int nbParameters;

GList * operand =NULL; 
int lastOpCal=0; /*dernier element évalué */
int test=0;
int nested=1;
int prem=0;
int testt=0;
int clee=0;
int deal = 1;
int gp=0;

/* Les Données de CLOOG*/
CloogState *state;
CloogInput *input;
CloogOptions * options ;
CloogDomain * context;
CloogDomain * domain;
CloogUnionDomain *ud;
CloogMatrix *matrixCtxt;
int NbRows, NbColumns ;
struct clast_stmt *rootCloog;

#line 71 "AnaSyntxMul.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
int nombre; 
char * chaine;} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 83 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define Fleche 257
#define ET 258
#define OU 259
#define BREAK 260
#define FOR 261
#define IF 262
#define ELSE 263
#define DO 264
#define WHILE 265
#define Switch 266
#define Case 267
#define Default 268
#define Multifor 269
#define Pouv 270
#define Pferm 271
#define Accouv 272
#define Accferm 273
#define OpAff 274
#define Pvirg 275
#define Dpoint 276
#define Virg 277
#define Plus 278
#define Moin 279
#define Div 280
#define Mod 281
#define Mul 282
#define Ajout 283
#define Sous 284
#define DivAff 285
#define MulAff 286
#define Incr 287
#define Decr 288
#define Entier 289
#define Var 290
#define OpRel 291
#define CrochOuv 292
#define CrochFerm 293
#define texte 294
#define NBRR 295
#define MOINSU 296
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,   67,   67,   68,   69,   69,   70,   70,   70,   72,
   72,   72,    5,    6,    6,    6,    7,    7,    8,    8,
    8,    8,    8,    8,    8,    8,   10,   10,   10,   10,
    3,    3,   13,   13,   18,   18,   18,   18,   14,   14,
   15,   16,   16,   16,   22,   22,   21,   21,   25,   25,
   25,   19,   19,   24,   24,   23,   23,   20,   26,   27,
   33,   29,   29,   30,   30,   34,   34,   34,   34,   34,
   34,   34,   32,   32,   32,   31,   31,   28,   41,   41,
   36,   42,   42,   37,   43,   43,   38,   44,   44,   39,
   45,   45,   40,   46,   46,   56,   56,   47,   47,   35,
   50,   50,   51,   51,   51,   49,   48,   53,   53,   58,
   58,   59,   59,   57,   55,   55,   54,   54,   61,   61,
   60,   60,   52,   17,   17,   17,   17,   17,   17,   17,
   17,   17,   17,   17,   73,   73,   74,   74,   71,    9,
    9,   12,   12,   11,   11,    4,    4,   62,   75,   75,
   63,   76,   76,    1,    1,    1,   64,    2,    2,    2,
    2,   77,   77,   65,   78,   78,   66,   79,   79,
};
static const short yylen[] = {                            2,
   13,    2,    4,    0,    1,    2,    0,    1,    2,    0,
    1,    2,    2,    0,    4,    2,    0,    4,    3,    3,
    3,    3,    3,    3,    2,    1,    2,    1,    1,    1,
    1,    2,    0,    2,    0,    4,    3,    2,    0,    2,
    5,    3,    3,    3,    0,    2,    1,    4,    0,    2,
    2,    3,    4,    0,    2,    0,    2,    6,    5,    7,
    3,    0,    1,    0,    1,    1,    1,    2,    2,    2,
    2,    2,    2,    2,    2,    0,    1,    9,    0,    3,
    2,    0,    3,    2,    0,    3,    2,    0,    3,    2,
    0,    3,    2,    0,    2,    3,    1,    1,    4,   13,
    1,    1,    0,    5,    3,    5,    7,    0,    2,    1,
    1,    0,    3,    4,    1,    1,    0,    2,    0,    1,
    0,    4,    6,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    1,    4,    0,    2,    3,    1,
    1,    1,    2,    3,    1,    3,    1,    4,    0,    2,
    4,    0,    2,    2,    2,    2,    2,    1,    1,    2,
    2,    0,    2,    2,    0,    2,    2,    0,    2,
};
static const short yydefred[] = {                         0,
    0,    0,  149,    0,    0,  152,  150,    0,    0,    0,
    0,  162,  153,    0,    0,   28,    0,   29,   30,    0,
  142,    0,  145,    0,    0,    0,  143,    0,    0,    0,
   27,  140,  141,    0,    0,  165,  163,    0,    0,    0,
  157,    0,    0,   38,    0,    0,    0,   26,    0,    0,
    0,  144,    0,    0,  156,  155,    0,    0,  158,  159,
  154,    0,    0,   13,    0,    0,    0,    0,    0,    0,
    0,    0,   40,   37,    0,  168,  166,    0,   31,  164,
  160,  161,   16,    0,   24,   34,    0,    0,    0,    0,
    0,    0,   36,    0,    0,   32,    0,    0,    0,  169,
    0,   15,    0,    0,    1,    0,   18,    0,    5,    0,
    0,    2,    0,    0,   11,    0,    6,    0,    0,    0,
    0,    0,    0,    0,    0,  133,    0,    0,    0,    0,
  124,  125,  135,  126,  127,  128,  129,  130,  131,  132,
  139,    8,    3,    0,   12,  134,    0,    0,    0,   47,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   66,   67,    0,    9,    0,
    0,   63,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   43,   44,    0,  109,    0,    0,    0,
    0,    0,    0,   42,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   81,    0,  138,
  136,    0,    0,    0,    0,   65,    0,    0,    0,    0,
    0,   52,    0,   46,   48,    0,   59,    0,    0,    0,
    0,   41,    0,    0,    0,    0,    0,   53,   50,   51,
    0,   58,    0,    0,    0,   80,    0,   84,    0,    0,
    0,    0,  118,  116,  123,    0,    0,    0,    0,   77,
   57,   60,  102,  101,    0,  107,    0,    0,    0,  122,
    0,  111,    0,   74,   75,   73,    0,    0,   83,    0,
   87,    0,    0,    0,   78,    0,    0,    0,    0,    0,
  114,    0,    0,  106,   86,    0,   90,    0,  113,    0,
    0,    0,    0,    0,    0,  105,   89,    0,   93,    0,
    0,    0,    0,    0,   97,  100,   98,  104,   92,    0,
    0,    0,    0,   96,   99,   95,
};
static const short yydgoto[] = {                        115,
   41,   61,   80,   20,  130,   64,   93,  174,   34,   48,
   22,   23,   73,   49,  131,  132,  150,   31,  216,  134,
  151,  203,  242,  200,  222,  135,  136,  137,  171,  217,
  259,  260,  172,  168,  138,  181,  231,  269,  289,  304,
  208,  248,  281,  297,  309,  322,  316,  139,  245,  265,
  294,  140,  160,  236,  253,  323,  272,  273,  284,  214,
  234,    4,    9,   24,   53,   94,  105,  106,  110,  143,
  116,  117,  141,  183,    5,   10,   25,   54,   95,
};
static const short yysindex[] = {                      -245,
 -178,    0,    0, -239, -259,    0,    0, -170, -205, -168,
   -8,    0,    0, -165, -226,    0, -235,    0,    0,   -6,
    0, -148,    0, -160,  -58,   -8,    0, -147, -137, -137,
    0,    0,    0,   -8,   -8,    0,    0, -101,  -83,  229,
    0,   -6, -230,    0, -137, -137,  228,    0,  -53,   60,
 -148,    0, -110, -191,    0,    0, -191, -191,    0,    0,
    0, -147, -137,    0,  -30,  -59, -137, -137, -137, -137,
 -137, -137,    0,    0,  -61,    0,    0,  -62,    0,    0,
    0,    0,    0,   85,    0,    0,  -85,  -85,  -59,  240,
  -59, -137,    0, -238,   -8,    0,  -61,  110,  -37,    0,
   -6,    0,  -61, -237,    0, -245,    0,  -21,    0,   -9,
 -237,    0, -159, -237,    0, -237,    0,    3,   14,   23,
  161,   27,   43,   67,  177,    0, -147, -147, -242,  194,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -237,    0,    0, -147,  165,  177,    0,
   79,  165, -137, -147,  177,   76,   83, -137,   80,   86,
 -137, -137, -137, -137, -137,    0,    0,  108,    0,  113,
  119,    0,  165,   37,  136,  177,  140,  148,  205,  147,
  175,  177,  167,    0,    0,  182,    0,  166,  240,  240,
  240,  240,  240,    0, -137,  165,  -80,  192, -137,   63,
  161,  177,  201,  165,  161,  199, -147,    0,  165,    0,
    0,  214, -137,  237,  240,    0,  250,   63,  240,  165,
  165,    0,  263,    0,    0,  232,    0,  260,  147,  251,
  254,    0,  240,  238, -149,  255,   59,    0,    0,    0,
  161,    0,  257,  172,  261,    0,  165,    0,   59,  166,
 -149,  240,    0,    0,    0, -147, -147,  194,  262,    0,
    0,    0,    0,    0,  259,    0,  251,  264,  265,    0,
  240,    0,  266,    0,    0,    0,  161,  161,    0,   59,
    0,  247, -149,  269,    0,  223,  264,  267,  270,  266,
    0,  172,  271,    0,    0,  248,    0,  249,    0,  272,
  161,  267,  273,  268,  161,    0,    0,  274,    0, -218,
  223,  273, -211,  275,    0,    0,    0,    0,    0, -211,
  177,  276, -211,    0,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -65,    0,    0,  -72,
    0,  217,    0,    0,    0,    0,    0,    0,  281,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    8, -103,    0,    0,    0,  282,    0,    0,    0,
  222,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -35,  281,    0,    0,    0,
    0,    0,    0,    0,   52,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  127,  138,   77, -198,
  102,    0,    0,    0,    0,    0,   21,    0,  277,    0,
 -123,    0,   21,    0,    0,    0,    0,    0,    0,    0,
  283,    0,    0,    2,    0,  283,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -124,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    2,    0,    0,  279,    0,    0,    0,
    0,    0,    0,   94,  284,    0,    0,  281,  278,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -38,    0,  285,    0,    0,    0,  280,
    0,  284,    0,    0,    0,    0,    0,  -15, -157,   49,
  137,  157,  195,    0,    0,  286,  256,    0,    0,  227,
    0,  285,    0,    0,    0,    0,   94,    0,   97,    0,
    0,    0,  287,  289,  124,    0,    0,  227,  198,    0,
    0,    0,    1,    0,    0,    0,    0,    0,  280,  290,
    0,    0,  288,    0,    0,    0,  291,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   97,    0,  170,  -15,
    0,  292,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  290,  294,    0,    0,
 -190,    0,  293,    0,    0,    0,    0,    0,    0,  170,
    0,    0,    0,    0,    0,  297,  294,  296,    0,  293,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  296,  301,    0,    0,    0,    0,    0,    0,    0,
  297,  301,    0,    0,    0,    0,    0,    0,    0,  300,
    0,    0,  300,    0,    0,    0,
};
static const short yygindex[] = {                         5,
    0,    0,  466,  -19,   -3,    0,   89,  -26,    0,   -5,
  525,  539,    0,  -67,    0,    0, -102,    0, -139,    0,
 -193,  358,    0,    0,  357,    0,    0,    0, -140, -192,
 -231,    0,    0,  318, -224,    0,    0,    0,    0,    0,
  348,  311,  295,  298,  299,  302,    0,    0,    0,  303,
  304,    0,  420,    0,    0, -216,  349,  305,  306,  333,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  441,
  -88,  470,    0,  405,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 625
static const short yytable[] = {                         86,
   56,    7,   47,   50,    2,   21,   42,  223,  175,   27,
  133,  227,  178,  180,   62,  111,  230,  268,   65,   66,
   21,   28,  155,    1,   44,  144,   62,  158,   21,   21,
    8,    1,   99,  198,   29,    6,   84,    7,  100,  159,
   47,   87,   88,   89,   90,   91,  176,  261,  287,   63,
  124,  108,  182,  313,  267,  144,   30,  124,   83,   22,
   22,   63,   16,   17,  226,   98,  229,   18,   19,   12,
  314,   13,   22,  202,   22,  101,   22,  314,   22,  182,
  239,  240,  110,  285,  286,  315,  110,   78,  315,   21,
  186,    3,   22,  317,   22,  315,  320,   79,  315,  202,
  118,  119,  120,   11,  121,  122,  123,  306,  109,  124,
  112,  311,  125,   72,   36,  126,   37,   72,  142,   72,
   45,   14,  251,  156,  157,   26,  179,  127,  128,   46,
  129,   47,   45,   35,  189,  190,  191,  192,  193,   16,
   17,   46,   43,  170,   18,   19,  197,  167,  142,   14,
  170,   16,   17,  167,   14,   14,   18,   19,   14,   14,
   14,   14,   14,   14,   76,  108,   77,   14,  215,   14,
   14,   14,  219,   14,   14,   14,   14,   14,   14,   14,
   14,   14,   14,   14,   14,  102,  233,   14,   55,   14,
   85,  107,   35,   35,   70,   71,   72,   68,   69,   70,
   71,   72,  148,  170,  148,   35,   56,   35,  252,   35,
  199,   35,   35,   35,   35,   35,   35,   74,  324,   54,
   54,   71,   25,   25,  271,   35,   96,   35,   38,   39,
   92,   40,   54,  258,  104,   25,   54,   25,   54,   25,
   85,   25,   25,   25,   25,  258,   25,   68,   69,   70,
   71,   72,  274,  275,  113,   25,  271,   25,  121,  121,
   56,   56,   56,  114,   56,   56,   56,   56,   56,   56,
   15,   32,   33,   56,    7,   56,  258,  146,   17,   17,
   16,   17,  151,  147,  151,   18,   19,   56,   56,   56,
   56,   17,  148,   17,   17,   17,  152,   17,   17,   17,
   17,   17,   17,   17,   17,   17,   17,   17,   17,   17,
   17,   17,  153,   17,   68,   69,   70,   71,   72,   68,
  220,  221,   17,   68,   17,   68,   17,  199,   17,   17,
   17,   17,   17,   17,   23,   23,  154,   68,   69,   70,
   71,   72,   17,  177,   17,  256,  257,   23,   43,   23,
  184,   23,   75,   23,   23,   23,   23,  185,   23,   21,
   21,  159,   68,   69,   70,   71,   72,   23,   62,   23,
   62,   64,   21,   64,   21,  188,   21,   97,   21,   21,
   21,   21,  194,   21,   19,   19,  195,   68,   69,   70,
   71,   72,   21,  196,   21,   20,   20,   19,   61,   19,
   61,   19,  103,   19,   19,   19,  201,   69,   20,  204,
   20,   69,   20,   69,   20,   20,   20,   19,  205,   19,
  118,  119,  120,  207,  121,  122,  123,   70,   20,  124,
   20,   70,  149,   70,  173,  126,  118,  119,  120,  211,
  121,  122,  123,   46,   76,  124,   76,  127,  128,  209,
  129,  126,  212,   16,   17,   55,   55,  213,   18,   19,
  263,  264,  218,  127,  128,   71,  129,  161,   55,   71,
  228,   71,   55,  225,   55,  206,  162,  163,  164,  165,
  166,  167,   68,   69,   70,   71,   72,  147,  232,  292,
  293,  147,  146,  147,  147,  147,  146,   49,  146,  146,
  146,   49,  243,   49,   67,   68,   69,   70,   71,   72,
  235,   57,   58,   54,   54,   59,   60,   68,   69,   70,
   71,   72,   81,   82,  237,  241,  244,  247,  249,  255,
  250,  262,  277,  266,  278,  288,  302,  303,  310,  282,
  280,  291,  283,  296,  298,    4,  301,  305,  325,  308,
  321,   39,   33,   62,   79,   10,  137,   45,   51,  224,
   64,   76,  312,  117,   82,  112,  115,  108,   85,  103,
   88,   91,   94,   52,  238,  276,  246,  279,  187,  119,
  120,  295,  270,  254,  169,  145,  210,  290,    0,    0,
    0,    0,    0,    0,  300,  299,    0,    0,    0,  307,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  319,    0,    0,    0,  318,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  326,
};
static const short yycheck[] = {                         67,
    0,    0,   29,   30,    0,   11,   26,  201,  148,   15,
  113,  205,  152,  154,  257,  104,  209,  249,   45,   46,
   26,  257,  125,  269,   28,  114,  257,  270,   34,   35,
  290,  269,  271,  173,  270,  275,   63,  277,  277,  282,
   67,   68,   69,   70,   71,   72,  149,  241,  280,  292,
  269,  289,  155,  272,  247,  144,  292,  269,   62,  258,
  259,  292,  289,  290,  204,   92,  207,  294,  295,  275,
  289,  277,  271,  176,  273,   95,  275,  289,  277,  182,
  220,  221,  273,  277,  278,  310,  277,  279,  313,   95,
  158,  270,  291,  310,  293,  320,  313,  289,  323,  202,
  260,  261,  262,  274,  264,  265,  266,  301,  104,  269,
  106,  305,  272,  271,  275,  275,  277,  275,  114,  277,
  270,  290,  272,  127,  128,  291,  153,  287,  288,  279,
  290,  158,  270,  282,  161,  162,  163,  164,  165,  289,
  290,  279,  290,  147,  294,  295,  173,  271,  144,  274,
  154,  289,  290,  277,  258,  259,  294,  295,  283,  284,
  285,  286,  287,  288,  275,  290,  277,  271,  195,  273,
  274,  275,  199,  277,  278,  279,  280,  281,  282,  283,
  284,  285,  286,  287,  288,   97,  213,  291,  290,  293,
  271,  103,  258,  259,  280,  281,  282,  278,  279,  280,
  281,  282,  275,  207,  277,  271,  290,  273,  235,  275,
  291,  277,  278,  279,  280,  281,  282,  271,  321,  258,
  259,  281,  258,  259,  251,  291,  289,  293,  287,  288,
  292,  290,  271,  237,  272,  271,  275,  273,  277,  275,
  271,  277,  278,  279,  280,  249,  282,  278,  279,  280,
  281,  282,  256,  257,  276,  291,  283,  293,  274,  275,
  260,  261,  262,  273,  264,  265,  266,  267,  268,  269,
  279,  278,  279,  273,  273,  275,  280,  275,  258,  259,
  289,  290,  275,  270,  277,  294,  295,  287,  288,  289,
  290,  271,  270,  273,  274,  275,  270,  277,  278,  279,
  280,  281,  282,  283,  284,  285,  286,  287,  288,  258,
  259,  291,  270,  293,  278,  279,  280,  281,  282,  271,
  258,  259,  271,  275,  273,  277,  275,  291,  277,  278,
  279,  280,  281,  282,  258,  259,  270,  278,  279,  280,
  281,  282,  291,  265,  293,  287,  288,  271,  290,  273,
  275,  275,  293,  277,  278,  279,  280,  275,  282,  258,
  259,  282,  278,  279,  280,  281,  282,  291,  275,  293,
  277,  275,  271,  277,  273,  290,  275,  293,  277,  278,
  279,  280,  275,  282,  258,  259,  274,  278,  279,  280,
  281,  282,  291,  275,  293,  258,  259,  271,  275,  273,
  277,  275,  293,  277,  278,  279,  271,  271,  271,  270,
  273,  275,  275,  277,  277,  278,  279,  291,  271,  293,
  260,  261,  262,  277,  264,  265,  266,  271,  291,  269,
  293,  275,  272,  277,  270,  275,  260,  261,  262,  273,
  264,  265,  266,  279,  275,  269,  277,  287,  288,  275,
  290,  275,  271,  289,  290,  258,  259,  292,  294,  295,
  289,  290,  271,  287,  288,  271,  290,  274,  271,  275,
  272,  277,  275,  273,  277,  271,  283,  284,  285,  286,
  287,  288,  278,  279,  280,  281,  282,  271,  275,  267,
  268,  275,  271,  277,  278,  279,  275,  271,  277,  278,
  279,  275,  271,  277,  277,  278,  279,  280,  281,  282,
  274,  283,  284,  258,  259,  287,  288,  278,  279,  280,
  281,  282,   57,   58,  275,  263,  267,  277,  275,  275,
  293,  275,  271,  273,  276,  289,  289,  289,  271,  275,
  277,  273,  277,  277,  275,  269,  276,  276,  273,  277,
  276,  271,  271,  275,  275,  273,  273,  273,   34,  202,
  275,  271,  289,  275,  275,  273,  275,  290,  275,  273,
  275,  271,  273,   35,  218,  258,  229,  267,  159,  293,
  293,  287,  250,  235,  144,  116,  182,  283,   -1,   -1,
   -1,   -1,   -1,   -1,  292,  290,   -1,   -1,   -1,  302,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  312,   -1,   -1,   -1,  311,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  323,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 296
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Fleche","ET","OU","BREAK","FOR",
"IF","ELSE","DO","WHILE","Switch","Case","Default","Multifor","Pouv","Pferm",
"Accouv","Accferm","OpAff","Pvirg","Dpoint","Virg","Plus","Moin","Div","Mod",
"Mul","Ajout","Sous","DivAff","MulAff","Incr","Decr","Entier","Var","OpRel",
"CrochOuv","CrochFerm","texte","NBRR","MOINSU",
};
static const char *yyrule[] = {
"$accept : mul",
"mul : Multifor Pouv init Pvirg comp Pvirg inc Pvirg grain Pvirg offset Pferm corps",
"corps : CropssansAcc mul",
"corps : Accouv block Accferm ResteProg",
"CropssansAcc :",
"block : mul",
"block : inst ResteProg2",
"ResteProg :",
"ResteProg : mul",
"ResteProg : inst ResteProg",
"ResteProg2 :",
"ResteProg2 : mul",
"ResteProg2 : inst ResteProg2",
"Variable : Var SuiteVar",
"SuiteVar :",
"SuiteVar : CrochOuv expression CrochFerm SuiteSuiteVar",
"SuiteVar : Fleche Variable",
"SuiteSuiteVar :",
"SuiteSuiteVar : CrochOuv expression CrochFerm SuiteSuiteVar",
"expression : expression Plus expression",
"expression : expression Moin expression",
"expression : expression Mul expression",
"expression : expression Mod expression",
"expression : expression Div expression",
"expression : Pouv expression Pferm",
"expression : Moin expression",
"expression : terme",
"terme : Var SuiteVar2",
"terme : Entier",
"terme : texte",
"terme : NBRR",
"NegEntier : Entier",
"NegEntier : Moin Entier",
"suiteParamFonct :",
"suiteParamFonct : Virg paramFonct",
"SuiteVar2 :",
"SuiteVar2 : CrochOuv expression CrochFerm SuiteSuiteVar",
"SuiteVar2 : Pouv paramFonct Pferm",
"SuiteVar2 : Fleche Variable",
"paramFonct :",
"paramFonct : expression suiteParamFonct",
"appelFonction : Var Pouv paramFonct Pferm Pvirg",
"exprArithTab : Variable suiteOpIncr Pvirg",
"exprArithTab : Incr Variable Pvirg",
"exprArithTab : Decr Variable Pvirg",
"suiteInstructions2 :",
"suiteInstructions2 : typeInstruction suiteInstructions2",
"blockInstr : typeInstruction",
"blockInstr : Accouv typeInstruction suiteInstructions2 Accferm",
"suiteSuiteCondIF :",
"suiteSuiteCondIF : ET condIF",
"suiteSuiteCondIF : OU condIF",
"condIF : expression suiteCondIF suiteSuiteCondIF",
"condIF : Pouv condIF Pferm suiteSuiteCondIF",
"suiteCondIF :",
"suiteCondIF : OpRel expression",
"suiteControleIF :",
"suiteControleIF : ELSE blockInstr",
"controleIF : IF Pouv condIF Pferm blockInstr suiteControleIF",
"controleWHILE : WHILE Pouv condIF Pferm blockInstr",
"controleDOWHILE : DO blockInstr WHILE Pouv condIF Pferm Pvirg",
"exprArithTab2 : Variable OpAff expression",
"initFOR :",
"initFOR : exprArithTab2",
"condFOR :",
"condFOR : condIF",
"suiteOpIncr : Incr",
"suiteOpIncr : Decr",
"suiteOpIncr : Ajout expression",
"suiteOpIncr : Sous expression",
"suiteOpIncr : DivAff expression",
"suiteOpIncr : MulAff expression",
"suiteOpIncr : OpAff expression",
"opIncr : Variable suiteOpIncr",
"opIncr : Incr Variable",
"opIncr : Decr Variable",
"incrFOR :",
"incrFOR : opIncr",
"controleFOR : FOR Pouv initFOR Pvirg condFOR Pvirg incrFOR Pferm blockInstr",
"suiteaffectmul :",
"suiteaffectmul : Virg initFOR suiteaffectmul",
"affectmul : initFOR suiteaffectmul",
"suitecompmul :",
"suitecompmul : Virg condFOR suitecompmul",
"compmul : condFOR suitecompmul",
"suiteincrmtmul :",
"suiteincrmtmul : Virg incrFOR suiteincrmtmul",
"incrmtmul : incrFOR suiteincrmtmul",
"suitegrainmul :",
"suitegrainmul : Virg Entier suitegrainmul",
"grainmul : Entier suitegrainmul",
"suiteoffsetmul :",
"suiteoffsetmul : Virg Entier suiteoffsetmul",
"offsetmul : Entier suiteoffsetmul",
"suiteInstructions3 :",
"suiteInstructions3 : typeInstruction2 suiteInstructions3",
"typeInstruction2 : Entier Dpoint typeInstruction",
"typeInstruction2 : controleMULTIFOR",
"blockInstr2 : typeInstruction2",
"blockInstr2 : Accouv typeInstruction2 suiteInstructions3 Accferm",
"controleMULTIFOR : Multifor Pouv affectmul Pvirg compmul Pvirg incrmtmul Pvirg grainmul Pvirg offsetmul Pferm blockInstr2",
"valeur : Var",
"valeur : Entier",
"suitecasSwitch :",
"suitecasSwitch : Case valeur Dpoint blockInstr suitecasSwitch",
"suitecasSwitch : Default Dpoint blockInstr",
"casSwitch : Case valeur Dpoint blockInstr suitecasSwitch",
"controleSwitch : Switch Pouv expression Pferm Accouv casSwitch Accferm",
"pointeur :",
"pointeur : Mul pointeur",
"elementTab : expression",
"elementTab : listeTab",
"suiteListeTab :",
"suiteListeTab : Virg elementTab suiteListeTab",
"listeTab : Accouv elementTab suiteListeTab Accferm",
"suiteDeclaration2 : expression",
"suiteDeclaration2 : listeTab",
"suiteDeclaration :",
"suiteDeclaration : OpAff suiteDeclaration2",
"expression2 :",
"expression2 : expression",
"suiteDecTab :",
"suiteDecTab : CrochOuv expression2 CrochFerm suiteDecTab",
"declaration : Var pointeur Var suiteDecTab suiteDeclaration Pvirg",
"typeInstruction : appelFonction",
"typeInstruction : exprArithTab",
"typeInstruction : controleIF",
"typeInstruction : controleWHILE",
"typeInstruction : controleDOWHILE",
"typeInstruction : controleFOR",
"typeInstruction : controleMULTIFOR",
"typeInstruction : controleSwitch",
"typeInstruction : declaration",
"typeInstruction : Pvirg",
"typeInstruction : BREAK Pvirg",
"lesInstructions : typeInstruction",
"lesInstructions : Accouv typeInstruction suiteInstructions Accferm",
"suiteInstructions :",
"suiteInstructions : typeInstruction suiteInstructions",
"inst : Entier Dpoint lesInstructions",
"OP_ADD : Plus",
"OP_ADD : Moin",
"facteurBA : terme",
"facteurBA : Moin terme",
"termeBA : termeBA Mul facteurBA",
"termeBA : facteurBA",
"bAffine : bAffine OP_ADD termeBA",
"bAffine : termeBA",
"init : initSuite Var OpAff bAffine",
"initSuite :",
"initSuite : init Virg",
"comp : compSuite Var OpRel bAffine",
"compSuite :",
"compSuite : comp Virg",
"incVar : Var suite",
"incVar : Decr Var",
"incVar : Incr Var",
"inc : incSuite incVar",
"suite : Incr",
"suite : Decr",
"suite : Ajout NegEntier",
"suite : Sous NegEntier",
"incSuite :",
"incSuite : inc Virg",
"grain : grainSuite NegEntier",
"grainSuite :",
"grainSuite : grain Virg",
"offset : offsetSuite bAffine",
"offsetSuite :",
"offsetSuite : offset Virg",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 1589 "AnaSyntxMul.y"

   /* C language program (the rest) */


void printList (GList * llist)
{ int longgg=g_list_length(llist) ;
  int jj=0;
  Element *  ellll;
  while (jj<longgg)
  {  ellll =  g_list_nth_data (llist, jj);
     printf("Param:%s | Coef:%d -> ",ellll->inconnu,ellll->coef);
     jj++;
  }
printf("\n");
}



GList * copyListe(GList * source)
{
   GList * cible = NULL;
   int longgg=g_list_length(source) ;
   int jj=0;
   Element *  ellll;
   while (jj<longgg)
   {
     ellll =  g_list_nth_data (source, jj);
     Element * opElement= NULL;
     opElement= malloc(sizeof(Element));
     if (opElement == NULL) 
     {printf("L'allocation mémoire a échoué !\n");
       exit(0);
     }
     char * chAux5=NULL;
     chAux5= malloc(100);
     if (chAux5 == NULL) 
       {printf("L'allocation mémoire a échoué !\n");
        exit(0);}
     sprintf(chAux5,"%s",ellll->inconnu);
     opElement->inconnu = chAux5;
     opElement->coef=0;
     cible = g_list_append(cible, opElement);
     jj++;
   }
return cible;
}


void coefMAJ(InputClooG * bCloog)
{ GList * source=bCloog->parameters;
//  printList(source);
  GList * cible=bCloog->iterators;
  GList * cible1 = NULL;// pointeur vers les paramètres
  int longgg=g_list_length(source) ;
  int jj=0;
  Element *  element;
  while (jj<longgg)
  { element =  g_list_nth_data (source, jj);
    if(strcmp(element->inconnu,"")==0)
      bCloog->constante = bCloog->constante + element->coef;
    else
    { if (addIterator(cible,element)==0) //si paramètre
      { if (addIterator(cible1,element)==0)
        {
          Element * opElement = NULL;
          opElement = malloc(sizeof(Element));
          if (opElement == NULL) 
          {printf("L'allocation mémoire a échoué !\n");
            exit(0);
          }
          opElement->inconnu = element->inconnu ;
          opElement->coef = element->coef ;
          cible1 = g_list_append(cible1, opElement);
          bCloog->nbParameters ++;
        } 
        if (addIterator(parameters,element)==0)// Besoin de ça pour la matrice contexte 
        {
          Element * opElement = NULL;
          opElement = malloc(sizeof(Element));
          if (opElement == NULL) 
          {printf("L'allocation mémoire a échoué !\n");
            exit(0);
          }
          opElement->inconnu = element->inconnu ;
          opElement->coef = element->coef ;
          parameters = g_list_append(parameters, opElement);
          nbParameters ++;
        }
      } 
    }
    jj++;
  }
  bCloog->parameters=cible1;
  g_list_free(source);
}



int addIterator(GList * cible,Element * element)
{
  int longueur=g_list_length(cible) ;
  int jj=0;
  Element *  elementc;
  while (jj<longueur)
  {
    elementc =  g_list_nth_data (cible, jj);
    if(strcmp(elementc->inconnu,element->inconnu)==0)
    {  elementc->coef = elementc->coef + element->coef ;
       return 1 ;
    }
    jj++;
  }
  return 0 ;
}



GList * copyListe_2(GList * source)
{  GList * cible = NULL;
   int longgg=g_list_length(source) ;
   int jj=0;
   Element *  ellll;
   while (jj<longgg)
   {
     ellll =  g_list_nth_data (source, jj);
     Element * opElement= NULL;
     opElement= malloc(sizeof(Element));
     if (opElement == NULL) 
     {printf("L'allocation mémoire a échoué !\n");
       exit(0);
     }
     char * chAux5=NULL;
     chAux5= malloc(100);
     if (chAux5 == NULL) 
       {printf("L'allocation mémoire a échoué !\n");
        exit(0);}
     sprintf(chAux5,"%s",ellll->inconnu);
     opElement->inconnu =chAux5 ;
     opElement->coef=ellll->coef;
     cible = g_list_append(cible, opElement);
     jj++;
   }
return cible;
}



GList * opListe_Add_Sous (GList * cible, GList * source, enum op_Arith op)
{
  int length = g_list_length(cible);
  int longgg=g_list_length(source) ;
  int jj=0;
  Element *  element;
  while (jj<longgg)
  { element =  g_list_nth_data (source, jj);
    if (oprElement(cible,element,op)==0) //si nouvel élément
      { 
          Element * opElement = NULL;
          opElement = malloc(sizeof(Element));
          if (opElement == NULL) 
          {printf("L'allocation mémoire a échoué !\n");
            exit(0);
          }
         char * chAux5=NULL;
         chAux5= malloc(100);
         if (chAux5 == NULL) 
         {printf("L'allocation mémoire a échoué !\n");
             exit(0);}
          sprintf(chAux5,"%s",element->inconnu);
          opElement->inconnu=chAux5 ;
          if(op == MOIN)
            opElement->coef = element->coef * (-1);
          if(op == PLUS)
            opElement->coef = element->coef ;
          cible = g_list_append(cible, opElement);
          length ++;
      } 
    jj++;
  }
  return cible;
}


InputClooG * opBAff_InputClooG_Add_Sous (InputClooG * bSupCloog, InputClooG * bInfCloog, enum op_Arith op)
{ 
  if (op != PLUS && op != MOIN ) printf("invalid Operation ! \n");
  InputClooG* inputclg= NULL;
  inputclg= malloc(sizeof(InputClooG));
  if (inputclg == NULL) 
  {printf("L'allocation mémoire a échoué !\n");
    exit(0);
  }
  inputclg->iterators = copyListe_2(bSupCloog->iterators);
  inputclg->parameters = copyListe_2(bSupCloog->parameters);
  inputclg->constante = bSupCloog->constante;
  inputclg->nbiterators = bSupCloog->nbiterators;
  inputclg->nbParameters = bSupCloog->nbParameters;
  inputclg->iterators = opListe_Add_Sous (inputclg->iterators, bInfCloog->iterators, op);
  inputclg->parameters = opListe_Add_Sous (inputclg->parameters, bInfCloog->parameters, op);
  inputclg->nbiterators = g_list_length(inputclg->iterators);
  inputclg->nbParameters = g_list_length(inputclg->parameters);
  if(op == PLUS)
     inputclg->constante = inputclg->constante + bInfCloog->constante;
  if(op == MOIN)
     inputclg->constante = inputclg->constante - bInfCloog->constante;
  return inputclg ;
}



void majInputClooG (GPtrArray* auxTest,GPtrArray* lesFor) // MAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJ 
{
      InputClooG* decalage= NULL;
      decalage= malloc(sizeof(InputClooG));
      if (decalage == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
        exit(0);
      }
      int p;
      int nbIncices =lesFor->len;
      for( p=0;p<nbIncices;p++)
      { 
        InfoFor * itForpere = g_ptr_array_index(auxTest,p);
        InfoFor * itFor = g_ptr_array_index(lesFor,p);
// offsetCloog ** Copie des itérateurs du niveau Supérieur
        GList * source = itForpere->offsetCloog->iterators; 
        GList * cible = NULL;
        cible = copyListe( source);
        Element * opElement3= NULL;
        opElement3= malloc(sizeof(Element));
        if (opElement3 == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        opElement3->inconnu = itForpere->indice;
        opElement3->coef=0;
        cible = g_list_append(cible, opElement3);
        itFor->offsetCloog->iterators = cible;
        itFor->offsetCloog->nbiterators = g_list_length(cible);
        //MAJ des itérateurs + paramètres
        coefMAJ (itFor->offsetCloog);
 // Vérifier que l'offset n'est pas fonction des indices englobants

        int longgg=g_list_length(itFor->offsetCloog->iterators) ;
        int jj=0;
        Element *  ellll;
        int OkIdEng=1;
        while (jj<longgg && OkIdEng)
        {  ellll =  g_list_nth_data (itFor->offsetCloog->iterators, jj);
           if (ellll->coef) OkIdEng=0;
           jj++;
        }
        if (OkIdEng == 0)
        {  printf("ERREUR : L'offset ne peut pas être fonction des indices englobants !\n");
           nbErr++;
        }

// bInfCloog ** Copie des itérateurs du niveau Supérieur
        GList * source1 = itForpere->bInfCloog->iterators;
        GList * cible1 = copyListe( source1);
        Element * opElement1= NULL;
        opElement1= malloc(sizeof(Element));
        if (opElement1 == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        opElement1->inconnu = itForpere->indice;
        opElement1->coef=0;
        cible1 = g_list_append(cible1, opElement1);
        itFor->bInfCloog->iterators = cible1;
        itFor->bInfCloog->nbiterators = g_list_length(cible1);
        //MAJ des itérateurs + paramètres
        coefMAJ (itFor->bInfCloog);
        // si le coef du père dans la borne inf est != de 0 alors rajouter coef * offset père à la borne sup 
        opElement1= g_list_nth_data(itFor->bInfCloog->iterators, g_list_length(itFor->bInfCloog->iterators)-1);
        //   decalage=decalage+opElement1->coef*itForpere->offset;
        decalage->iterators = copyListe_2(itForpere->offsetCloog->iterators); 
        decalage->parameters = copyListe_2(itForpere->offsetCloog->parameters);
        decalage->constante = itForpere->offsetCloog->constante;
        decalage->nbiterators = itForpere->offsetCloog->nbiterators;
        decalage->nbParameters = itForpere->offsetCloog->nbParameters;
        opBAff_InputClooG_Mul_Div (decalage, MUL, opElement1->coef);//  printf(" \n opElement1->coef:%d  \n",opElement1->coef);
// bSupCloog ** Copie des itérateurs du niveau Supérieur
        GList * source2 = itForpere->bSupCloog->iterators;
        GList * cible2 = copyListe( source2);
        Element * opElement2= NULL;
        opElement2= malloc(sizeof(Element));
        if (opElement2 == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        opElement2->inconnu = itForpere->indice;
        opElement2->coef=0;
        cible2 = g_list_append(cible2, opElement2);
        itFor->bSupCloog->iterators = cible2;
        itFor->bSupCloog->nbiterators = g_list_length(cible2);
        //MAJ des itérateurs + paramètres
        coefMAJ (itFor->bSupCloog);
        // si le coef du père dans la borne sup est != de 0 alors soustraire coef * offset père à la borne sup
        opElement1= g_list_nth_data(itFor->bSupCloog->iterators, g_list_length(itFor->bSupCloog->iterators)-1);
        // decalage=decalage-opElement1->coef*itForpere->offset;
      InputClooG* decalage2= NULL;
      decalage2= malloc(sizeof(InputClooG));
      if (decalage2 == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
        exit(0);
      }
      decalage2->iterators = copyListe_2(itForpere->offsetCloog->iterators);
      decalage2->parameters = copyListe_2(itForpere->offsetCloog->parameters);
      decalage2->constante = itForpere->offsetCloog->constante;
      decalage2->nbiterators = itForpere->offsetCloog->nbiterators;
      decalage2->nbParameters = itForpere->offsetCloog->nbParameters;
      opBAff_InputClooG_Mul_Div (decalage2, MUL, opElement1->coef);
      InputClooG* decalage3= opBAff_InputClooG_Add_Sous (decalage, decalage2,MOIN);
      itFor->bSupCloog = opBAff_InputClooG_Add_Sous (itFor->bSupCloog, decalage3,PLUS);
      // itFor->bSupCloog->constante=itFor->bSupCloog->constante+decalage;
      }//fin for
}



gboolean afficher(GNode* n, gpointer data) {
int i,j;
GPtrArray* aux=n->data;
printf("\n      ★ ★ ★ A Node Depth is %d has %d children ★ ★ ★\n\n",g_node_depth(n),g_node_n_children(n));
for(i=0;i<aux->len;i++)
{   printf(" ★ ★ ★ ★ ★ ★ L'indice N°=%d \n",i);
    InfoFor* aux2= g_ptr_array_index(aux,i);
    printf("indice : %s \n",(*aux2).indice);
    printf("type : %s \n",aux2->type);
    printf("opRel : %s \n",(*aux2).opRel);
    printf("bInf : %s \n",aux2->bInf);
    printf("bSup : %s \n",aux2->bSup);
    printf("incr : %d \n",aux2->incr);
    printf("grain : %d \n",aux2->grain);
    printf("offset : %s \n",aux2->offset);
    GSList * aux3 =aux2->instr;
    printf("Longeur de la chaine des instructions : %d \n",g_slist_length(aux3));
   for(j=0;j<g_slist_length(aux3);j++)
   {    Instruc* inst=g_slist_nth_data(aux3, j);
        printf("instruction n° %d : %s ----",j,inst->instr);
        printf("index : %d \n",inst->index);
   }
    if(aux2->bInfCloog!=NULL)
   {  printf("=== bInfCloog ===\n");
      printf("Iterators = ");
      printList (aux2->bInfCloog->iterators);
      printf("Parameters = ");
      printList (aux2->bInfCloog->parameters);
      printf("constante : %d \n",aux2->bInfCloog->constante);
      printf("nbiterators : %d \n",aux2->bInfCloog->nbiterators);
      printf("nbParameters : %d \n",aux2->bInfCloog->nbParameters);
   }
   else printf("bInfCloog est NULL ! \n");
    if(aux2->bSupCloog!=NULL)
   {  printf("=== bSUPCloog ===\n");
      printf("Iterators = ");
      printList (aux2->bSupCloog->iterators);
      printf("Parameters = ");
      printList (aux2->bSupCloog->parameters);
      printf("constante : %d \n",aux2->bSupCloog->constante);
      printf("nbiterators : %d \n",aux2->bSupCloog->nbiterators);
      printf("nbParameters : %d \n",aux2->bSupCloog->nbParameters);
   }
   else printf("bSupCloog est NULL ! \n");
    if(aux2->offsetCloog!=NULL)
   {  printf("=== offsetCloog ===\n");
      printf("Iterators = ");
      printList (aux2->offsetCloog->iterators);
      printf("Parameters = ");
      printList (aux2->offsetCloog->parameters);
      printf("constante : %d \n",aux2->offsetCloog->constante);
      printf("nbiterators : %d \n",aux2->offsetCloog->nbiterators);
      printf("nbParameters : %d \n",aux2->offsetCloog->nbParameters);
   }
   else printf("offsetCloog est NULL ! \n");

}
return FALSE; //si je retourne TRUE je vais interrompre le parcourt de l'arbre
}



int isInteger  (char * ch,int taille)
{
   int i=0; 
   int ok=1;
   if (ch[0]=='-') i++;
   while (ok==1 && i<taille)
   {
   if(ch[i]>='0' && ch[i]<='9')
     i++;
   else ok=0;
   }
   if(ok==1)
     return 1; // c'est un entier
   return 0;// C'est une variable
}



char * indexx(InfoFor* aux2, char* bInf, int modified,char* indiceRef)
{  
    char * chAux4=NULL; 
    chAux4= malloc(200);
    if (chAux4 == NULL) 
       {printf("L'allocation mémoire a échoué !\n");
        exit(0);}
    char * chAux5=NULL;
    chAux5= malloc(200);
    if (chAux5 == NULL) 
       {printf("L'allocation mémoire a échoué !\n");
        exit(0);}
// Calculer bInf+incr*(i-offset)/grain

    if (strstr(aux2->offset,"-")!=NULL || strstr(aux2->offset,"+")!=NULL)
    {  char * ooffset=NULL; 
       ooffset= malloc(200);
       if (ooffset == NULL) 
          {printf("L'allocation mémoire a échoué !\n");
           exit(0);}
       sprintf(ooffset,"(%s)",aux2->offset);
       aux2->offset=ooffset;
    }

    if(strcmp(aux2->offset,"0")==0)
    {  if(aux2->incr==1)
          sprintf(chAux5,":%s:",indiceRef);
       else
          sprintf(chAux5,"%d*:%s:",aux2->incr,indiceRef);
    }
    else
    {  if(aux2->incr==1)
          sprintf(chAux5,"(:%s:-%s)",indiceRef,aux2->offset);
       else
          sprintf(chAux5," %d*(:%s:-%s)",aux2->incr,indiceRef,aux2->offset);
    }
    if((aux2->grain)>1)
    {  if(strcmp(aux2->bInf,"0")!=0)
          sprintf(chAux4,"%s+%s/%d",aux2->bInf,chAux5,(aux2->grain));
       else
          sprintf(chAux4,"%s/%d",chAux5,(aux2->grain));
    }    
    else
    {  if(strcmp(aux2->bInf,"0")!=0)
          sprintf(chAux4,"%s+%s",aux2->bInf,chAux5);
       else
          sprintf(chAux4,"%s",chAux5);
    }    
    if(chAux4[0]=='(' && chAux4[strlen(chAux4)-1]==')')
    {  int hh;
       for(hh=0 ; hh<strlen(chAux4) ; hh++)
       chAux4[hh]=chAux4[hh+1];
       chAux4[strlen(chAux4)-1]='\0';
    }  
    if(modified) //***
    {  int hh;
       for(hh=0 ; hh<strlen(chAux4)-1 ; hh++)
       chAux5[hh]=chAux4[hh+1];
       chAux5[strlen(chAux4)-2]='\0';
       if(strcmp(chAux5,indiceRef)==0)
          sprintf(chAux5,"%s-%s",bInf,chAux4);
       else      
          sprintf(chAux5,"%s-(%s)",bInf,chAux4);
    }
    else
       sprintf(chAux5,"%s",chAux4);
return (chAux5);
}







int oprElement(GList * cible,Element * element,int op)
{ int longueur=g_list_length(cible) ;
  int jj=0;
  Element *  elementc;
  while (jj<longueur)
  { elementc =  g_list_nth_data (cible, jj);
    if(strcmp(elementc->inconnu,element->inconnu)==0)
    { if(op == PLUS)
        elementc->coef = elementc->coef + element->coef ;
      if(op == MOIN)
        elementc->coef = elementc->coef - element->coef ;
      return 1 ;
    }
    jj++;
  }
  return 0 ;
}



void opListe_Mul_Div (GList * cible, enum op_Arith op, int coef)
{ 
  int length = g_list_length(cible);
  int jj=0;
  Element *  element;
  while (jj<length)
  {  element =  g_list_nth_data (cible, jj);
     if(op == MUL)
       element->coef = element->coef * coef;
     if(op == DIV)
       element->coef = ceil( (float) element->coef/coef);
     jj++;
  }
}



void opBAff_InputClooG_Mul_Div (InputClooG * bSupCloog, enum op_Arith op, int coef)
{  
  opListe_Mul_Div (bSupCloog->iterators, op,coef);
  opListe_Mul_Div (bSupCloog->parameters, op,coef);
  if(op == MUL)
    bSupCloog->constante = bSupCloog->constante * coef;
  if(op == DIV)
    bSupCloog->constante = ceil( (float) bSupCloog->constante / coef);
}



int isEqual (InputClooG * bSupCloog, InputClooG * bInfCloog) // Rend 0 s'il sont égaux
{ 
int h=0;
Element * ellment1;
Element * ellment2;
if(bSupCloog->constante != bInfCloog->constante)   return 1 ;
if(bSupCloog->nbiterators != bInfCloog->nbiterators)   return 1 ;
if(bSupCloog->nbParameters != bInfCloog->nbParameters)   return 1 ;
    
for (h=0;h<bSupCloog->nbiterators;h++)
{  ellment1= g_list_nth_data (bSupCloog->iterators, h);
   ellment2= g_list_nth_data (bInfCloog->iterators, h);
   if(ellment1->coef != ellment2->coef) return 1 ;
}
for (h=0;h<bSupCloog->nbParameters;h++)
{  ellment1= g_list_nth_data (bSupCloog->parameters, h);
   ellment2= g_list_nth_data (bInfCloog->parameters, h);
   if(ellment1->coef != ellment2->coef) return 1 ;
}
  return 0 ;
}



gboolean constMatCloog (GNode* n) { // Construction de l'Input Pour CloOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoG  :-)

int i,j,jj;
GPtrArray* aux=n->data;
char * bInf;
int modified=0;
char * indiceRef=NULL;
Instruc* inst;
GSList * aux3;
CloogMatrix *matrixDomain;
GPtrArray* mesMatrixDomain=g_ptr_array_new ();
char * chAuxx=NULL;
chAuxx= malloc(150);
if (chAuxx == NULL) 
{   printf("L'allocation mémoire a échoué !\n");
    exit(0);
}
indiceRef= malloc(50);
if (indiceRef == NULL) 
{   printf("L'allocation mémoire a échoué !\n");
    exit(0);
}
char * eqIn ;
char * indiceCourbSup;
char * bbinf=NULL;
char * bbsup=NULL;
bbinf= malloc(150);
if (bbinf == NULL) 
{   printf("L'allocation mémoire a échoué !\n");
    exit(0);
}
bbsup= malloc(150);
if (bbsup == NULL) 
{   printf("L'allocation mémoire a échoué !\n");
    exit(0);
}
if(n!=root)
{  int longId=0;
   GNode* np = n->parent;
   while(np!=root)
   {  GPtrArray* auxxx=np->data;
      longId=longId+(auxxx->len);  
      np=np->parent;
   }
   GPtrArray* auxxx=np->data;
   longId=longId+(auxxx->len); 
   if(lesGardes->len >  longId)
       g_ptr_array_remove_range (lesGardes, longId, lesGardes->len - longId);
   if(lesIndices->len >  longId)
       g_ptr_array_remove_range (lesIndices, longId, lesIndices->len - longId);
}
sprintf(indiceRef,"_mfr_ref%d",g_node_depth(n)-1+oldmaxRef);
// Parcourt de tout les indices du Multifor Pour chaque indice calculer bsup et binf ( ramener les binf à 0 )
for(i=0;i<aux->len;i++) 
{   indiceCourbSup="-1";
    sprintf(bbinf, "");
    sprintf(bbsup, "");
    modified=0;
    eqIn ="1";
    InfoFor* aux2= g_ptr_array_index(aux,i);
// Traiter tout les OP_REL en fonction de l'incrément 
// Ce que je dois faire  < et l'opérateur --      >  avec l'opérateur ++ ?!
    if(strcmp(aux2->opRel, "==")==0) //OK :-)
    {// Si binf != bsup -> 0 itération 
        eqIn ="0";
        aux2->bSupCloog->constante++;
 //       addBlock=1-isEqual(aux2->bInfCloog, aux2->bSupCloog); // Rend 0 s'il sont égaux
    }
    if(strcmp(aux2->opRel, "!=")==0) // Pas tout à fait , revoir ça !¡!¡!¡!!
    {// Si binf == bsup -> 0 itération 
        if(aux2->incr > 0 )
           aux2->opRel="<";
        else 
           aux2->opRel=">";
   //     addBlock=isEqual(aux2->bInfCloog, aux2->bSupCloog); // Rend 0 s'il sont égaux
    }
    if(strcmp(aux2->opRel, ">=")==0)//OK :-)
    {   aux2->opRel=">";
        aux2->bSupCloog->constante--;
    }
    if(strcmp(aux2->opRel, "<")==0) //OK :-)
    {  // Si binf >= bsup -> 0 itération 
       if(aux2->incr < 0 )
       {  if ( aux2->bInfCloog->constante < aux2->bSupCloog->constante )   // boucle infinie 
           indiceCourbSup="1"; 
           bInf=aux2->bInf;        
           aux2->bInf="0";
           aux2->incr=(aux2->incr)*-1;
           modified=1;
       }
    }
    if(strcmp(aux2->opRel, ">")==0) //OK :-)
    {   if(aux2->incr<0)
        {  bInf=aux2->bInf; 
           aux2->bInf="0";
           aux2->incr=(aux2->incr)*-1;
           modified=1;
        }
        else
        {  if ( aux2->bInfCloog->constante > aux2->bSupCloog->constante )   // boucle infinie 
              indiceCourbSup="1"; 
        }
           InputClooG * ipaux=aux2->bSupCloog;
           aux2->bSupCloog=aux2->bInfCloog;
           aux2->bInfCloog=ipaux;
    }
    if(strcmp(aux2->opRel, "<=")==0)//OK :-)
    {   aux2->bSupCloog->constante++;
        aux2->opRel="<";
    }
    //max=(ceil( (float) (aux2->bSup-aux2->bInf)/aux2->incr)-1)*(aux2->grain)+(aux2->offset)+1;

    InputClooG * nlb =aux2->offsetCloog;
    InputClooG * nub = opBAff_InputClooG_Add_Sous (aux2->bSupCloog, aux2->bInfCloog,MOIN); //{ PLUS, MOIN, MUL,DIV }
    opBAff_InputClooG_Mul_Div (nub, DIV, aux2->incr);
    nub->constante--;
    opBAff_InputClooG_Mul_Div (nub, MUL, aux2->grain);
    // nub->constante = nub->constante + (aux2->offset)+1;

    nub = opBAff_InputClooG_Add_Sous (nub, aux2->offsetCloog,PLUS);
    nub->constante = nub->constante+1;

    NbRows = g_node_depth(n)*2; //Le nombre de Lignes dans la matrice cloog égal à 2* profondeur du noeud
    NbColumns=nub->nbiterators+nbParameters+3;
    // Définition des matrices domaines

    matrixDomain = cloog_matrix_alloc(NbRows, NbColumns);

    /* Adding constraints to matrixDomain->p    Contrainte sur les indices  */

    // Supprimer les coefs des niveaux inférieur !!
    if(n!=root)
    {  coefNivSup = g_ptr_array_index(toutcoefNivSup,i);
       if(coefNivSup->len >  NbRows-2)
          g_ptr_array_remove_range (coefNivSup, NbRows-2, coefNivSup->len - NbRows+2);
    }
    else
    {  //printf("C'est le RoOT\n");
       coefNivSup=g_ptr_array_new ();
       g_ptr_array_add (toutcoefNivSup, coefNivSup);
    }
    // copier les contrainte de 0 à NbRows-2 à partir des multifor englobant
    for(j=0;j<NbRows-2;j++)
    {  char * val;
       val= malloc(10);
       if (val == NULL) 
       {   printf("L'allocation mémoire a échoué !\n");
           exit(0);
       }
       int nbIT=nub->nbiterators+2;
       InputClooG* inputclg = g_ptr_array_index(coefNivSup,j);

       for (jj=0;jj<inputclg->nbiterators;jj++)
          cloog_int_read(matrixDomain->p[j][jj],  g_list_nth_data (inputclg->iterators, jj)); 

       for (jj=inputclg->nbiterators;jj<nbIT;jj++)
          cloog_int_read(matrixDomain->p[j][jj], "0");

       for (jj=0;jj<inputclg->nbParameters;jj++)
          cloog_int_read(matrixDomain->p[j][jj+nbIT],  g_list_nth_data (inputclg->parameters, jj)); 

       sprintf(val,"%d",inputclg->constante);
       cloog_int_read(matrixDomain->p[j][NbColumns-1], val); 
    }
// Les contraines sur La borne Inférieure ÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//je dois également sauvegarder les coefs de ce niveau !!

      InputClooG* inputclg= NULL; //nlb
      inputclg= malloc(sizeof(InputClooG));
      if (inputclg == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      inputclg->iterators = NULL;
      inputclg->parameters = NULL; 
      inputclg->constante = 0;
      inputclg->nbiterators = 0;
      inputclg->nbParameters = 0;
      cloog_int_read(matrixDomain->p[NbRows-2][0], eqIn); // >=0
      sprintf(bbinf, "%s%s", bbinf, eqIn);
      inputclg->iterators = g_list_append(inputclg->iterators, eqIn);
      inputclg->nbiterators++;
      Element *  ellll;
      opBAff_InputClooG_Mul_Div (nlb, MUL, -1);

      for (j=0;j<nlb->nbiterators;j++)
      {  ellll =  g_list_nth_data (nlb->iterators, j);
         char * val;
         val= malloc(10);
         if (val == NULL) 
         {   printf("L'allocation mémoire a échoué !\n");
             exit(0);
         }
         sprintf(val,"%d",ellll->coef);
      cloog_int_read(matrixDomain->p[NbRows-2][j+1], val);
      sprintf(bbinf, "%s%s", bbinf,val);
      inputclg->iterators = g_list_append(inputclg->iterators, val);
      inputclg->nbiterators++;
      } 
      cloog_int_read(matrixDomain->p[NbRows-2][nlb->nbiterators+1], "1");// L'indice Courant !!
      sprintf(bbinf, "%s1", bbinf);
      inputclg->iterators = g_list_append(inputclg->iterators, "1");
      inputclg->nbiterators++;

      for (j=0;j<nbParameters;j++) // Les paramètres
      {   char * val;
          val= malloc(10);
          if (val == NULL) 
          {   printf("L'allocation mémoire a échoué !\n");
              exit(0);
          }
          Element *  elment;
          elment =  g_list_nth_data (parameters, j); // chercher le coef dans nlb->parameters sinon 0

          int jj=0;
          Element *  ellll;
          int found = 0;
          cloog_int_read(matrixDomain->p[NbRows-2][j+nlb->nbiterators+2], "0");
          sprintf(val,"%d",0);
          while (jj<nlb->nbParameters && found == 0)
          {  ellll =  g_list_nth_data (nlb->parameters, jj);
             if(strcmp(ellll->inconnu,elment->inconnu)==0)
             {  sprintf(val,"%d",ellll->coef); 
                cloog_int_read(matrixDomain->p[NbRows-2][j+nlb->nbiterators+2], val);
                found = 1;
             }
             jj++;
          }  
          inputclg->parameters = g_list_append(inputclg->parameters, val);
          sprintf(bbsup, "%s%s", bbsup, val);
          inputclg->nbParameters++;
      }

      char * val1;
      val1= malloc(10);
      if (val1 == NULL) 
      {   printf("L'allocation mémoire a échoué !\n");
          exit(0);
      }
      sprintf(val1,"%d",nlb->constante);
      cloog_int_read(matrixDomain->p[NbRows-2][NbColumns-1], val1);
      sprintf(bbinf, "%s%s", bbinf, val1);
      inputclg->constante = nlb->constante;
      g_ptr_array_add (coefNivSup, inputclg);

// Les contraines sur La borne Supérieure ÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷÷
//je dois également sauvegarder les coefs de ce niveau !!
      InputClooG* inputclg2= NULL;
      inputclg2= malloc(sizeof(InputClooG));
      if (inputclg2 == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      inputclg2->iterators = NULL;
      inputclg2->parameters = NULL; 
      inputclg2->constante = 0;
      inputclg2->nbiterators = 0;
      inputclg2->nbParameters = 0;
      cloog_int_read(matrixDomain->p[NbRows-1][0], eqIn);// Eq/Ineq  >=0
      sprintf(bbsup, "%s%s", bbsup, eqIn);
      inputclg2->iterators = g_list_append(inputclg2->iterators, eqIn);
      inputclg2->nbiterators++;
      jj=0;

      while (jj<nub->nbiterators)
      {  char * val;
         val= malloc(10);
         if (val == NULL) 
         {   printf("L'allocation mémoire a échoué !\n");
             exit(0);
         }
         ellll =  g_list_nth_data (nub->iterators, jj);
         //   printf("Param:%s | Coef:%d -> ",ellll->inconnu,ellll->coef);
         if(strcmp(eqIn, "0")==0) 
            sprintf(val,"%d",ellll->coef*-1);
         else
            sprintf(val,"%d",ellll->coef);
         cloog_int_read(matrixDomain->p[NbRows-1][jj+1], val);
         sprintf(bbsup, "%s%s", bbsup, val);
         jj++;
         inputclg2->iterators = g_list_append(inputclg2->iterators, val);
         inputclg2->nbiterators++;
      }
      if(strcmp(eqIn, "0")==0) 
      {   cloog_int_read(matrixDomain->p[NbRows-1][nub->nbiterators+1], "1");// L'indice Courant !!
          sprintf(bbsup, "%s1", bbsup);
      }
      else
      {   cloog_int_read(matrixDomain->p[NbRows-1][nub->nbiterators+1], indiceCourbSup);// L'indice Courant !!
          sprintf(bbsup, "%s%s", bbsup,indiceCourbSup);
      }
      inputclg2->iterators = g_list_append(inputclg2->iterators, indiceCourbSup);
      inputclg2->nbiterators++;

      for (j=0;j<nbParameters;j++) // Les paramètres
      {   char * val;
          val= malloc(10);
          if (val == NULL) 
          {   printf("L'allocation mémoire a échoué !\n");
              exit(0);
          }
          Element *  elment;
          elment =  g_list_nth_data (parameters, j); // chercher le coef dans nub->parameters sinon 0
          int jj=0;
          Element *  ellll;
          int found = 0;
          cloog_int_read(matrixDomain->p[NbRows-1][j+nub->nbiterators+2], "0");
          sprintf(val,"%d",0);
          while (jj<nub->nbParameters && found == 0)
          {  ellll =  g_list_nth_data (nub->parameters, jj);
             if(strcmp(ellll->inconnu,elment->inconnu)==0)
             {  if(strcmp(eqIn, "0")==0) 
                   sprintf(val,"%d",(ellll->coef)*-1);
                else
                   sprintf(val,"%d",(ellll->coef)*atoi(indiceCourbSup)*-1);
                cloog_int_read(matrixDomain->p[NbRows-1][j+nub->nbiterators+2], val);
                found = 1;
             }
             jj++;
          }
          inputclg2->parameters = g_list_append(inputclg2->parameters, val);
          sprintf(bbsup, "%s%s", bbsup, val);
          inputclg2->nbParameters++;
      }
     char * val2;
     val2= malloc(10);
     if (val2 == NULL) 
     {   printf("L'allocation mémoire a échoué !\n");
         exit(0);
     }
      if(strcmp(eqIn, "0")==0) 
         sprintf(val2,"%d",(nub->constante-1)*-1 );
      else
         sprintf(val2,"%d",nub->constante-1);
      cloog_int_read(matrixDomain->p[NbRows-1][NbColumns-1], val2);// La constante
      sprintf(bbsup, "%s%s", bbsup, val2);
      inputclg2->constante = nub->constante-1;
      g_ptr_array_add (coefNivSup, inputclg2);

      // printf("\nmatrixDomain :\n");
      // cloog_matrix_print_structure(stdout, matrixDomain,"   ", "");

      g_ptr_array_add (mesMatrixDomain, matrixDomain);
//**************************************************************************************************** NEW
// Construction des gardes
    char * chAux2=NULL;
    chAux2= malloc(150);
    if (chAux2 == NULL) 
    {   printf("L'allocation mémoire a échoué !\n");
        exit(0);
    }
    if (aux2->grain>1)
    {  if ( strcmp(aux2->offset,"0")==0)
          sprintf(chAux2,"(%s% %%d)==0", indiceRef, aux2->grain);
       else
          sprintf(chAux2,"((%s-%s)% %%d)==0", indiceRef, aux2->offset, aux2->grain);
    }
    else
    sprintf(chAux2,"");
    char * chAuxxx=NULL;
    chAuxxx= malloc(300);
    if (chAuxxx == NULL) 
    {   printf("L'allocation mémoire a échoué !\n");
        exit(0);
    }
    char * chIndex=NULL;
    chIndex= malloc(300);
    if (chIndex == NULL) 
    {   printf("L'allocation mémoire a échoué !\n");
        exit(0);
    }

    if (n!=root)
    { if(strcmp(chAux2,"")==0 && strcmp(g_ptr_array_index(lesGardes,i+clee),"")==0 )
         sprintf(chAuxxx,"");
      else
      {  if(strcmp(chAux2,"")==0)
            sprintf(chAuxxx,"%s", g_ptr_array_index(lesGardes,i+clee));
         else
         {  if(strcmp(g_ptr_array_index(lesGardes,i+clee),"")==0)
               sprintf(chAuxxx,"%s", chAux2);
            else // Les 2 chaines ne sont pas vides !
               sprintf(chAuxxx,"%s && %s", g_ptr_array_index(lesGardes,i+clee), chAux2);
         }
      }
       //exprimer l'ancien indice en fonction de l'indice de référence  
       sprintf(chIndex,"%s %s=%s;", g_ptr_array_index(lesIndices,i+clee), aux2->indice, indexx(aux2,bInf,modified,indiceRef));
    }
    else
    {  sprintf(chAuxxx,"%s", chAux2);
        //exprimer l'ancien indice en fonction de l'indice de référence
        sprintf(chIndex,"%s=%s;", aux2->indice, indexx(aux2,bInf,modified,indiceRef)); 
    }
    g_ptr_array_add (lesGardes, chAuxxx);
    g_ptr_array_add (lesIndices, chIndex);

    int nbInstrucs=0;
    aux3 =aux2->instr;
    j=0;
    //Extraction des instructions    
    if (g_slist_length(aux3)>0)
    {  InfoBlock* unblock= NULL;
       unblock= malloc(sizeof(InfoBlock));
       if (unblock == NULL) 
       { printf("L'allocation mémoire a échoué !\n");
         exit(0); 
       }
       unblock->indiceRef=chIndex; 
       sprintf(chAuxxx,"%s", chAuxxx);
       unblock->garde = chAuxxx;
       unblock->instr=NULL;
       while (j<g_slist_length(aux3))
       {  inst=g_slist_nth_data(aux3, j);
          if (inst->index==-1)
          {  nbInstrucs++;
             unblock->instr=g_list_append (unblock->instr, inst->instr);
          }
          j++;
       }
       if(nbInstrucs==0)
          free(unblock);
       else
       {  g_ptr_array_add (blocks, unblock); 
          domain = cloog_domain_from_cloog_matrix(state, matrixDomain, nbParameters);
          // Rajouter le domaine à l'union      
          cloog_union_domain_add_domain(ud, NULL, domain, NULL, NULL); 
       }
    }
    modified=0;
}//Fin du for

if(n!=root)
{  GPtrArray* auxxx=n->parent->data;
   clee=clee+(auxxx->len);  
}
//***********
    int nbreChild=g_node_n_children (n);
    int childNum=0;
    while (childNum < nbreChild)
    {  char * chAux3=NULL;
       chAux3= malloc(150);
       if (chAux3 == NULL) 
       {   printf("L'allocation mémoire a échoué !\n");
           exit(0);
       }
       constMatCloog (g_node_nth_child (n, childNum));
       clee=clee-aux->len;  
       if(coefNivSup->len >  NbRows-2)
           g_ptr_array_remove_range (coefNivSup, NbRows-2, coefNivSup->len - NbRows+2);

       for(i=0;i<aux->len;i++)
       {  matrixDomain= g_ptr_array_index(mesMatrixDomain,i);  
          // printf("\nmatrixDomain :********************\n");
          // cloog_matrix_print_structure(stdout, matrixDomain,"   ", "********************");
          InfoFor* aux2= g_ptr_array_index(aux,i);  
          int nbInstrucs=0;
          aux3 =aux2->instr;
          j=0;
          GList * maListeAux=NULL;
          while (j<g_slist_length(aux3))
          {  inst=g_slist_nth_data(aux3, j);
             if (inst->index==childNum)
             {  nbInstrucs++;
                maListeAux=g_list_append (maListeAux, inst->instr);
             }
             j++;
          }
          if(nbInstrucs>0)
          {  char * garde=NULL;
             garde= malloc(300);
             if (garde == NULL) 
             {   printf("L'allocation mémoire a échoué !\n");
                 exit(0);
             }
             sprintf(garde,"%s", g_ptr_array_index(lesGardes,i+clee));  
             char * indiceReff=NULL;
             indiceReff= malloc(100);
             if (indiceReff == NULL) 
             {   printf("L'allocation mémoire a échoué !\n");
                 exit(0);
             }
             sprintf(indiceReff,"%s", g_ptr_array_index(lesIndices,i+clee));  
             InfoBlock* unblock= NULL;
             unblock= malloc(sizeof(InfoBlock));
             if (unblock == NULL) 
             { printf("L'allocation mémoire a échoué !\n");
               exit(0); 
             }
             unblock->indiceRef = indiceReff; 
             unblock->garde = garde;
             unblock->instr=maListeAux;
             g_ptr_array_add (blocks, unblock); 
             domain = cloog_domain_from_cloog_matrix(state, matrixDomain, nbParameters);
              // Rajouter le domaine à l'union      
             cloog_union_domain_add_domain(ud, NULL, domain, NULL, NULL); 
          }
       }//fin for
       childNum++;
    }//fin while
for(i=0;i< mesMatrixDomain->len ; i++)
    free ( g_ptr_array_index (mesMatrixDomain, i));
g_ptr_array_free (mesMatrixDomain, TRUE);
return FALSE;
}


int pgcd (int A, int B)
{  int R;
   if ( A<B )
   {  R=A;
      A=B;
      B=R;
   }
   while(B!=0)
   {  R=A%B;
      A=B;
      B=R;
   }
   return A;
}



void insertInstr(FILE *temp) //iiiiiiiiiiiiiiiiiiiiiiiiii
{  int i,mm;
//*** Pour la compression du domaine :-)
   int *tabdyn; // Pour Calculer le PGCD !
   tabdyn = malloc(g_node_max_height(root)*2*sizeof(int));
   if (tabdyn == NULL) 
   {  printf("L'allocation mémoire a échoué !\n");
      exit(0);
   } 
   for(mm=0;mm<g_node_max_height(root)*2;mm++)
      tabdyn[mm]=0;
   long *filePosTab;
   filePosTab = malloc(g_node_max_height(root)*2*sizeof(long));
   if (filePosTab == NULL) 
   {  printf("L'allocation mémoire a échoué !\n");
      exit(0);
   } 
   int nbreForImb = 0;
   long *gardePosTab;
   gardePosTab = malloc(500*sizeof(long));
   if (gardePosTab == NULL) 
   {  printf("L'allocation mémoire a échoué !\n");
      exit(0);
   } 
   long *fingardePosTab; // les positions des accolades fermantes
   fingardePosTab = malloc(500*sizeof(long));
   if (fingardePosTab == NULL) 
   {  printf("L'allocation mémoire a échoué !\n");
      exit(0);
   } 
   char **gardeTab;
   gardeTab = malloc(500*sizeof(char*));
   if (gardeTab == NULL) 
   {  printf("L'allocation mémoire a échoué !\n");
      exit(0);
   } 
   long *indexPosTab;
   indexPosTab = malloc(500*sizeof(long));
   if (indexPosTab == NULL) 
   {  printf("L'allocation mémoire a échoué !\n");
      exit(0);
   } 
   char **indexxTab;
   indexxTab = malloc(500*sizeof(char*));
   if (indexxTab == NULL) 
   {  printf("L'allocation mémoire a échoué !\n");
      exit(0);
   } 
   int nbgardePos =0;
   GPtrArray *BlockForTab =g_ptr_array_new ();
   int c;
   fseek(temp, 0L, SEEK_SET);
   while ((c = getc(temp)) != EOF)
   { 
      if(c=='f')
      {  fprintf(fichier,"%c",c);
         c = getc(temp);
         if(c=='o')
         {  fprintf(fichier,"%c",c);
            c = getc(temp);
            if(c=='r')
            {
               fprintf(fichier,"%c",c);
               c = getc(temp); // C'est un espace
               while(c=='\n' || c=='\t' || c==' ')
               {  fprintf(fichier,"%c",c);
                  c = getc(temp);
               }
               if(c=='(')
               {
                  fprintf(fichier,"%c",c);
                  char* indiceCour= NULL;  
                  indiceCour= malloc(150);
                  if (indiceCour == NULL) 
                  {  printf("L'allocation mémoire a échoué !\n");
                     exit(0);
                  }
                  sprintf(indiceCour,"");
                  char* bInff= NULL;
                  bInff= malloc(200);
                  if (bInff == NULL) 
                  {  printf("L'allocation mémoire a échoué !\n");
                     exit(0);
                  }
                  sprintf(bInff,"");
                  c = getc(temp); 
                  while (c!='=')
                  {  sprintf(indiceCour,"%s%c",indiceCour,c);
                     c = getc(temp);
                  }
                  fputs(indiceCour,fichier);
                  fprintf(fichier,"%c",c);
                  c = getc(temp); 
                  while (c!=';')
                  {  sprintf(bInff,"%s%c",bInff,c);
                     c = getc(temp);
                  }
                  fputs(bInff,fichier);
                  fprintf(fichier,"%c",c);
                  c = getc(temp);

                  BlockFor* unnblok= NULL;
                  int lll=8;  
                  char* nombre= NULL;
                  nombre= malloc(150);
                  if (nombre == NULL) 
                  {  printf("L'allocation mémoire a échoué !\n");
                     exit(0);
                  }  
                  sprintf(nombre,""); 
                  while (lll<strlen(indiceCour)) 
                  {  sprintf(nombre,"%s%c",nombre,indiceCour[lll]);
                     lll++;
                  }
                  int Position=atoi(nombre);
//  printf("\n*************** %s  indiceCour:%s     bInff:%s **************\n",nombre,indiceCour,bInff);
                  if(Position<BlockForTab->len)  
                  {  unnblok = g_ptr_array_index (BlockForTab, Position);
                     unnblok->indiceRef = indiceCour;
                     unnblok->borneInf = bInff; 
                     unnblok->nbOffset = 0;
                  }
                  else
                  {  int oo;
                     for(oo=BlockForTab->len ; oo<=Position ; oo++)
                     {  char * nom=NULL;
                        nom=malloc(50);
                        if (nom==NULL)
                        { printf("L'allocation mémoire a échoué !\n");
                          exit(0);
                        }
                        sprintf(nom,"_mfr_ref%d",oo+oldmaxRef);
                        unnblok= malloc(sizeof(BlockFor));
                        if (unnblok == NULL) 
                        { printf("L'allocation mémoire a échoué !\n");
                          exit(0);
                        }
                        unnblok->indiceRef = nom;
                        unnblok->borneInf = "0"; 
                        char **taboffset; // Pour Calculer le PGCD !
                        taboffset = malloc(1000*sizeof(char*));
                        if (taboffset == NULL) 
                        {  printf("L'allocation mémoire a échoué !\n");
                           exit(0);
                        } 
                        unnblok->offset = taboffset;
                        unnblok->nbOffset = 0;
                        g_ptr_array_add (BlockForTab, unnblok);
                     }
                  }
               } //fin if(c=='(')
            //   else
              //    fprintf(fichier,"%c",c);
            }// fin if "for"
         }
      }
//***
      if(c=='+')
      {  fprintf(fichier,"%c",c);
         c = getc(temp);
         if(c=='+')
         {  filePosTab[nbreForImb]=ftell(fichier);
            nbreForImb++;
            fputs("        ",fichier);
            while ((c = getc(temp)) != '{') ;
            c = getc(temp); 
         }
         else
         {  fprintf(fichier,"%c",c);
            c = getc(temp); 
         }
      }
      if(c=='S')
      {  int accc=0; // printf("  nbreForImb= %d\n",nbreForImb);
         int indexFor=0;
         char* nombre= NULL;
         nombre= malloc(50);
         if (nombre == NULL) 
         {  printf("L'allocation mémoire a échoué !\n");
            exit(0);
         }  
         sprintf(nombre,""); 
         while ((c = getc(temp)) != '(') 
         {  sprintf(nombre,"%s%c",nombre,c);
         }       
         InfoBlock * blockss =  g_ptr_array_index (blocks, atoi(nombre)-1) ;  
         char * maaagarde=blockss->garde;
         int lengaaaarde=strlen(blockss->garde);
         char* gardFin=NULL;
         gardFin= malloc(500);
         if (gardFin == NULL) 
         {  printf("L'allocation mémoire a échoué !\n");
            exit(0);
         }
         sprintf(gardFin,"");  
         char* autregarde=NULL;
         autregarde= malloc(500);
         if (autregarde == NULL) 
         {  printf("L'allocation mémoire a échoué !\n");
            exit(0);
         }
         sprintf(autregarde,"");  
         char* unegard=NULL;
         unegard= malloc(200);
         if (unegard == NULL) 
         {  printf("L'allocation mémoire a échoué !\n");
            exit(0);
         }
         sprintf(unegard,""); 
         char* indexxFin=NULL;
         indexxFin= malloc(300);
         if (indexxFin == NULL) 
         {  printf("L'allocation mémoire a échoué !\n");
            exit(0);
         }
         sprintf(indexxFin,"");  
         int print = 1; // si 1 afficher les indices + les instructions. Pas d'affichage sinon
         if(strcmp(blockss->garde, "")!=0) // traitement de la garde
         {  sprintf(gardFin,"if(");
            sprintf(autregarde,"if(");    
         }
         // si la boucle fait 1 itération juste j'affiche le numéro de l'itération exécutée
         int finnn=0; 
         char * maaaliste=blockss->indiceRef;
         int pss=0;
         int ppss=0;
         while ( finnn==0  )
         {  c = getc(temp);
            sprintf(nombre,"");
            // Traitement des indices
            char* partieGauche=NULL;
            partieGauche= malloc(100);
            if (partieGauche == NULL) 
            {  printf("L'allocation mémoire a échoué !\n");
               exit(0);
            }
            char* indice=NULL;
            indice= malloc(100);
            if (indice == NULL) 
            {  printf("L'allocation mémoire a échoué !\n");
               exit(0);
            }
            char* partieDroite=NULL;
            partieDroite= malloc(100);
            if (partieDroite == NULL) 
            {  printf("L'allocation mémoire a échoué !\n");
               exit(0);
            }
            sprintf(partieGauche,"");  
            sprintf(indice,"");  
            sprintf(partieDroite,""); 
//****
            while ( c!= ',' && c != ')' )
            {  sprintf(nombre,"%s%c",nombre,c);
               c = getc(temp);
            }
            while ( maaaliste[pss]!= ':' )
            {  sprintf(partieGauche,"%s%c",partieGauche,maaaliste[pss]);
               pss++;
            }
            pss++;
            while ( maaaliste[pss]!= ':' )
            {  sprintf(indice,"%s%c",indice,maaaliste[pss]);
               pss++;
            }
            pss++;
            while ( maaaliste[pss]!= ';' )
            {  sprintf(partieDroite,"%s%c",partieDroite,maaaliste[pss]);
               pss++;
            }
            sprintf(partieDroite,"%s%c",partieDroite,maaaliste[pss]);
            pss+=2;
            int r=0;
            char* LinDice=NULL;
            LinDice= malloc(100);
            if (LinDice == NULL) 
            {  printf("L'allocation mémoire a échoué !\n");
               exit(0);
            }
            sprintf(LinDice,"");
            while(r< strlen(partieGauche) && partieGauche[r]!='=')
            {   sprintf(LinDice,"%s%c",LinDice,partieGauche[r]);
                r++;
            }
            sprintf(LinDice,"%s%c",LinDice,partieGauche[r]);
            r++; 
            int vbinf, vincr, voffset, vgrain;
            vbinf=0;
            vincr=1;
            voffset=0;
            vgrain=1;
            char* vnombre= NULL;
            vnombre= malloc(100);
            if (vnombre == NULL) 
            {  printf("L'allocation mémoire a échoué !\n");
               exit(0);
            }  
            sprintf(vnombre,""); 
            while(r< strlen(partieGauche) && (partieGauche[r]!='+' && partieGauche[r]!='-' && partieGauche[r]!='*'))
            {  sprintf(vnombre,"%s%c",vnombre,partieGauche[r]);
               r++;
            }
            int addd =1;
            char* intbinf= NULL;
            intbinf= malloc(100);
            if (intbinf == NULL) 
            {  printf("L'allocation mémoire a échoué !\n");
               exit(0);
            }  
            sprintf(intbinf,""); 

            char* intoffset= NULL;
            intoffset= malloc(100);
            if (intoffset == NULL) 
            {  printf("L'allocation mémoire a échoué !\n");
               exit(0);
            }  
            sprintf(intoffset,""); 


            if(r< strlen(partieGauche))
            {  if(partieGauche[r]=='+' || partieGauche[r]=='-')
               {  if(partieGauche[r]=='-')
                     addd =0;
                  if(  isdigit(vnombre[0]) != 0) // si c'est un nombre 
                     vbinf=atoi(vnombre);
                  else
                     sprintf(intbinf,"%s",vnombre); 
                  sprintf(vnombre,""); 
                  r++;
                  while(r< strlen(partieGauche) && partieGauche[r]!='*')
                  {  sprintf(vnombre,"%s%c",vnombre,partieGauche[r]);
                     r++;
                  }
                  if(r< strlen(partieGauche))
                     vincr=atoi(vnombre);
               }
               else
                  vincr=atoi(vnombre);
            }
            r=0; 
            if(partieDroite[0]=='-')
            {  r++;
               sprintf(vnombre,""); 
               if(strstr(partieDroite,"(")!=NULL)
               { 
                  while(r< strlen(partieDroite) && partieDroite[r]!=')')
                  {  sprintf(vnombre,"%s%c",vnombre,partieDroite[r]);
                     r++;
                  }
                  sprintf(vnombre,"%s%c",vnombre,partieDroite[r]);
                  r++;
                  sprintf(intoffset,"%s",vnombre); 
               }
               else 
               {
                  while(r< strlen(partieDroite) && partieDroite[r]!=')')
                  {  sprintf(vnombre,"%s%c",vnombre,partieDroite[r]);
                     r++;
                  }
                  if(isInteger(vnombre,strlen(vnombre)))
                  voffset=atoi(vnombre);
                  sprintf(intoffset,"%s",vnombre); 
               }
               r++;
            }

            if(r< strlen(partieDroite))
            {  if( partieDroite[r]=='/') 
               {  r++;
                  sprintf(vnombre,""); 
                  while(r< strlen(partieDroite))
                  {  sprintf(vnombre,"%s%c",vnombre,partieDroite[r]);
                     r++;
                  }
                  vgrain=atoi(vnombre);
               }
            } 
            if(nbreForImb>0)
            {  tabdyn[indexFor]=pgcd(tabdyn[indexFor],vgrain);
//  printf("BlockForTab->len : %d   indexFor : %d   nbreForImb: %d \n",BlockForTab->len,indexFor,nbreForImb);
               BlockFor * unbblk = g_ptr_array_index (BlockForTab, indexFor);
               unbblk->offset[unbblk->nbOffset] = intoffset;
               unbblk->nbOffset=unbblk->nbOffset+1;
               indexFor++;
            } 
            if(  isdigit(nombre[0]) != 0) // si c'est un nombre 
            {  if(strcmp(intbinf,"")==0)
               {  if(isInteger(intoffset,strlen(intoffset)))
                  {  if(addd)
                        sprintf(indexxFin,"%s%s%d;\n",indexxFin,LinDice,vbinf+vincr*(atoi(nombre)-voffset)/vgrain);
                     else
                        sprintf(indexxFin,"%s%s%d;\n",indexxFin,LinDice,vbinf-vincr*(atoi(nombre)-voffset)/vgrain);
                  }
                  else
                  {  if(vincr>1 && vgrain>1)
                     {
                        if(addd)                                           
                           sprintf(indexxFin,"%s%s%d+%d*(%s-%s)/%d;\n",indexxFin,LinDice,vbinf,vincr,nombre,intoffset,vgrain);
                        else                                               
                           sprintf(indexxFin,"%s%s%d-%d*(%s-%s)/%d;\n",indexxFin,LinDice,vbinf,vincr,nombre,intoffset,vgrain);
                     }
                     else
                     {  if(vincr==1 && vgrain==1)
                        {
                        if(addd)                                           
                           sprintf(indexxFin,"%s%s%d+%s-%s;\n",indexxFin,LinDice,vbinf,nombre,intoffset);
                        else                                               
                           sprintf(indexxFin,"%s%s%d-(%s-%s);\n",indexxFin,LinDice,vbinf,nombre,intoffset);
                        }
                        else
                        {  if(vincr==1 )
                          {
                            if(addd)                                           
                              sprintf(indexxFin,"%s%s%d+(%s-%s)/%d;\n",indexxFin,LinDice,vbinf,nombre,intoffset,vgrain);
                            else                                               
                             sprintf(indexxFin,"%s%s%d-(%s-%s)/%d;\n",indexxFin,LinDice,vbinf,nombre,intoffset,vgrain);
                          }
                          if( vgrain==1)
                          {
                            if(addd)                                           
                              sprintf(indexxFin,"%s%s%d+%d*(%s-%s);\n",indexxFin,LinDice,vbinf,vincr,nombre,intoffset);
                            else                                               
                             sprintf(indexxFin,"%s%s%d-%d*(%s-%s);\n",indexxFin,LinDice,vbinf,vincr,nombre,intoffset);
                          }
                        }
                     }
                    char * indexxFintest = strstr(indexxFin,"=0+");
                    if (indexxFintest!=NULL)
                    {  int cptt;  
                       char * shch=NULL;
                       shch=malloc(100);
                       if (shch==NULL)
                       {  printf("L'allocation mémoire a échoué !\n");
                          exit(0);
                       }  
                       sprintf(shch,"");
                       for(cptt=0;cptt<=(indexxFintest-indexxFin);cptt++)
                          sprintf(shch,"%s%c",shch,indexxFin[cptt]);
                       sprintf(shch,"%s%s",shch,indexxFintest+3);
                       indexxFin=shch;
                    }
                    indexxFintest = strstr(indexxFin,"=0-");
                    if (indexxFintest!=NULL)
                    {  int cptt; 
                       char * shch=NULL;
                       shch=malloc(100);
                       if (shch==NULL)
                       {  printf("L'allocation mémoire a échoué !\n");
                          exit(0);
                       }  
                       sprintf(shch,"");
                       for(cptt=0;cptt<=(indexxFintest-indexxFin);cptt++)
                          sprintf(shch,"%s%c",shch,indexxFin[cptt]);
                       sprintf(shch,"%s%s",shch,indexxFintest+2);
                       indexxFin=shch;
                    }
                  }

               }
               else
               {  if(isInteger(intoffset,strlen(intoffset)))
                  {  if(addd)
                        sprintf(indexxFin,"%s%s%s+%d;\n",indexxFin,LinDice,intbinf,vincr*(atoi(nombre)-voffset)/vgrain);
                     else
                        sprintf(indexxFin,"%s%s%s-%d;\n",indexxFin,LinDice,intbinf,vincr*(atoi(nombre)-voffset)/vgrain);
                  }
                  else
                  {  
                     if(vincr>1 && vgrain>1)
                     {
                     if(addd)                                                      
                        sprintf(indexxFin,"%s%s%s+%d*(%s-%s)/%d;\n",indexxFin,LinDice,intbinf,vincr,nombre,intoffset,vgrain);
                     else
                        sprintf(indexxFin,"%s%s%s-%d*(%s-%s)/%d;\n",indexxFin,LinDice,intbinf,vincr,nombre,intoffset,vgrain);
                     }
                     else
                     {  if(vincr==1 && vgrain==1)
                        {
                         if(addd)                                                      
                           sprintf(indexxFin,"%s%s%s+%s-%s;\n",indexxFin,LinDice,intbinf,nombre,intoffset);
                         else
                           sprintf(indexxFin,"%s%s%s-(%s-%s);\n",indexxFin,LinDice,intbinf,nombre,intoffset);
                        }
                        else
                        {  if(vincr==1 )
                          {
                           if(addd)                                                      
                              sprintf(indexxFin,"%s%s%s+(%s-%s)/%d;\n",indexxFin,LinDice,intbinf,nombre,intoffset,vgrain);
                           else
                              sprintf(indexxFin,"%s%s%s-(%s-%s)/%d;\n",indexxFin,LinDice,intbinf,nombre,intoffset,vgrain);
                          }
                          if( vgrain==1)
                          {
                          if(addd)                                                      
                             sprintf(indexxFin,"%s%s%s+%d*(%s-%s);\n",indexxFin,LinDice,intbinf,vincr,nombre,intoffset);
                          else
                             sprintf(indexxFin,"%s%s%s-%d*(%s-%s);\n",indexxFin,LinDice,intbinf,vincr,nombre,intoffset);
                          }
                        }
                     }
                  char * indexxFintest = strstr(indexxFin,"=0+");
                  if (indexxFintest!=NULL)
                  {  int cptt;  
                     char * shch=NULL;
                     shch=malloc(100);
                     if (shch==NULL)
                     {  printf("L'allocation mémoire a échoué !\n");
                        exit(0);
                     }  
                     sprintf(shch,"");
                     for(cptt=0;cptt<=(indexxFintest-indexxFin);cptt++)
                        sprintf(shch,"%s%c",shch,indexxFin[cptt]);
                     sprintf(shch,"%s%s",shch,indexxFintest+3);
                     indexxFin=shch;
                  }
                  indexxFintest = strstr(indexxFin,"=0-");
                  if (indexxFintest!=NULL)
                  {  int cptt; 
                     char * shch=NULL;
                     shch=malloc(100);
                     if (shch==NULL)
                     {  printf("L'allocation mémoire a échoué !\n");
                        exit(0);
                     }  
                     sprintf(shch,"");
                     for(cptt=0;cptt<=(indexxFintest-indexxFin);cptt++)
                        sprintf(shch,"%s%c",shch,indexxFin[cptt]);
                     sprintf(shch,"%s%s",shch,indexxFintest+2);
                     indexxFin=shch;
                  }
                  }
               }
               // Traitement des Gardessss         
               if(strcmp(unegard,"")==0)
               {  while (ppss<lengaaaarde && maaagarde[ppss]!='&' )
                  {  sprintf(unegard,"%s%c",unegard,maaagarde[ppss]);
                     ppss++;
                  }
                  while (ppss<lengaaaarde && (maaagarde[ppss]==' ' || maaagarde[ppss]=='&'))
                  {  ppss++;
                  }
               }
               if(strstr(unegard,indice)!=NULL)
                  if(isInteger(intoffset,strlen(intoffset)))
                  {  print=(atoi(nombre)-voffset)%vgrain==0;
                     sprintf(unegard,""); 
                  }
            } 
            else // si c'est un une variable (l'indice de référence)
            {  if(strcmp(unegard, "")==0)
               {  while (ppss<lengaaaarde && maaagarde[ppss]!='&' )
                  {  sprintf(unegard,"%s%c",unegard,maaagarde[ppss]);
                     ppss++;
                  }
                  while (ppss<lengaaaarde && (maaagarde[ppss]== ' ' || maaagarde[ppss]== '&'))
                  {  ppss++;
                  }
               }
               if (strstr( unegard, indice )!=NULL)
               {  if(gardFin[strlen(gardFin)-1]=='(')
                     sprintf(gardFin,"%s%s",gardFin,unegard);
                  else
                     sprintf(gardFin,"%s&& %s",gardFin,unegard);
                  sprintf(unegard,""); 
               }
               sprintf(indexxFin,"%s%s",indexxFin,partieGauche);
               sprintf(indexxFin,"%s%s",indexxFin,indice);
               sprintf(indexxFin,"%s%s\n",indexxFin,partieDroite);
            } 
            if (c==')')
               finnn=1;  
            if(BlockForTab->len <= indexFor)  
            {  int oo;
               for(oo=BlockForTab->len ; oo<=indexFor ; oo++)
               {  char * nom=NULL;
                  nom=malloc(50);
                  if (nom==NULL)
                  { printf("L'allocation mémoire a échoué !\n");
                    exit(0);
                  }
                  sprintf(nom,"_mfr_ref%d",oo+oldmaxRef);
                  BlockFor* unnblok= malloc(sizeof(BlockFor));
                  if (unnblok == NULL) 
                  { printf("L'allocation mémoire a échoué !\n");
                    exit(0);
                  }
                  unnblok->indiceRef = nom;
                  unnblok->borneInf = "0"; 
                  char **taboffset; // Pour Calculer le PGCD !
                  taboffset = malloc(1000*sizeof(char*));
                  if (taboffset == NULL) 
                  {  printf("L'allocation mémoire a échoué !\n");
                     exit(0);
                  } 
                  unnblok->offset = taboffset;
                  unnblok->nbOffset = 0;
                  g_ptr_array_add (BlockForTab, unnblok);
               }
            }
         } 
         if (print)
         {  // Afficher les gardes
            if(strcmp(blockss->garde, "")!=0)
            {  if(gardFin[strlen(gardFin)-1]!='(')    
               {  sprintf(gardFin,"%s) {",gardFin);
                  char * laaagarde;
                  laaagarde= malloc(300);
                  if (laaagarde == NULL) 
                  {   printf("L'allocation mémoire a échoué !\n");
                      exit(0);
                  }
                  sprintf(laaagarde,"");
                  int yy;
                  for(yy=3;yy<strlen(gardFin)-3;yy++)
                     sprintf(laaagarde,"%s%c",laaagarde,gardFin[yy]);
                  gardePosTab[nbgardePos]=ftell(fichier);   
                  gardeTab[nbgardePos]=laaagarde;
                  fputs(gardFin,fichier);
                  fputs("                                                                                                    \n",fichier);
                  indexPosTab[nbgardePos]=ftell(fichier);   
                  indexxTab[nbgardePos]=indexxFin;
                  nbgardePos++;
                  accc=1;
               }
            }
            // Afficher les indices
            fputs(indexxFin,fichier);
            if(accc==1)
              fputs("                                                                                                    \n",fichier);
            // Afficher les instructions
            int longgg=g_list_length(blockss->instr) ;
            int jj=0;
            while (jj<longgg-1)
            {  fprintf(fichier,"%s\n",g_list_nth_data (blockss->instr, jj));
               jj++;
            }
            fprintf(fichier,"%s", g_list_nth_data (blockss->instr, longgg-1));
            if(accc==1)
            {   fprintf(fichier,"\n");
                fingardePosTab[nbgardePos-1]=ftell(fichier);
                fprintf(fichier,"}");
            } 
         }
         while ((c = getc(temp)) != ';') ;   
      } // fin  if(c=='S')
      else
      {  fprintf(fichier,"%c",c);
         if(c=='}')
         {  if(nbreForImb>0)
            {  fseek(fichier, filePosTab[nbreForImb-1], SEEK_SET);
               BlockFor * unbblk = g_ptr_array_index (BlockForTab, nbreForImb-1);
               // Test sur les offsetss pour savoir si la compression est faisable ou non               
               /* printf("Affichage des offsets ************** \n");
               int ggg=0;
               for(ggg=0;ggg<unbblk->nbOffset;ggg++)
                  printf("%s     ",unbblk->offset[ggg]);
               printf("\n");*/
               int moduloo;
               int compprsss=1;
               if(isInteger(unbblk->offset[0],strlen(unbblk->offset[0])))
                  moduloo=atoi(unbblk->offset[0])%tabdyn[nbreForImb-1];
               else
                  compprsss=0;
               int ggg=1;
               while(ggg<unbblk->nbOffset && compprsss)
               {  if(isInteger(unbblk->offset[ggg],strlen(unbblk->offset[ggg])))
                  {  if( moduloo!= atoi(unbblk->offset[ggg])%tabdyn[nbreForImb-1])
                        compprsss=0;
                  }
                  else
                     compprsss=0;
                  ggg++;
               }

               if(tabdyn[nbreForImb-1]==1 || compprsss==0) // ajouter les test sur les offsetss !!!!
                  fprintf(fichier,"+) {");
               else
               {  // Mise à jours les gardes ! et les idices également !!
                  fprintf(fichier,"=%d) {",tabdyn[nbreForImb-1]);
                  int possss=nbgardePos-1;    
                  while( possss>=0 && filePosTab[nbreForImb-1] < gardePosTab[possss])
                  {  char* garddd=NULL;
                     garddd= malloc(500);
                     if (garddd == NULL) 
                     {  printf("L'allocation mémoire a échoué !\n");
                        exit(0);
                     }
                     sprintf(garddd,""); 
                     char* unegarddd=NULL;
                     unegarddd= malloc(100);
                     if (unegarddd == NULL) 
                     {  printf("L'allocation mémoire a échoué !\n");
                        exit(0);
                     }
                     sprintf(unegarddd,""); 
                     int pps=0;
                     int lengaaaard=strlen(gardeTab[possss]);
                     char* offsetGarde=NULL;//*************************************
                     offsetGarde= malloc(100);
                     if (offsetGarde == NULL) 
                     {  printf("L'allocation mémoire a échoué !\n");
                        exit(0);
                     }
                     sprintf(offsetGarde,""); 

                     while (pps<lengaaaard)
                     {  while (pps<lengaaaard && gardeTab[possss][pps]!='&' )
                        {  sprintf(unegarddd,"%s%c",unegarddd,gardeTab[possss][pps]);
                           pps++;
                        }
                        while (pps<lengaaaard && (gardeTab[possss][pps]== ' ' || gardeTab[possss][pps]== '&'))
                        {  pps++;
                        }
                        char* sh=NULL;
                        sh= malloc(100);
                        if (sh == NULL) 
                        {  printf("L'allocation mémoire a échoué !\n");
                           exit(0);
                        }
                        sprintf(sh,""); 
                        int id=0;
                        while(unegarddd[id]=='(')id++;
                        while(unegarddd[id]!='-'&&unegarddd[id]!='%')
                        {  sprintf(sh,"%s%c",sh,unegarddd[id]);
                           id++;
                        }
                        if(unegarddd[id]=='-')
                        {  id++;
                           char* nbbb=NULL;
                           nbbb= malloc(100);
                           if (nbbb == NULL) 
                           {  printf("L'allocation mémoire a échoué !\n");
                              exit(0);
                           }
                           sprintf(nbbb,""); 
                           while(unegarddd[id]!=')')
                           {  sprintf(nbbb,"%s%c",nbbb,unegarddd[id]);
                              id++;
                           }
                           sprintf(offsetGarde,"%s",nbbb);                       
                        }
                        if (strcmp(unbblk->indiceRef,sh)==0)
                        {  sprintf(sh,""); 
                           while(unegarddd[id]!='%') id++; id++;
                           while(unegarddd[id]!=')')
                           {  sprintf(sh,"%s%c",sh,unegarddd[id]);
                              id++;
                           }
                           if(tabdyn[nbreForImb-1]==atoi(sh)) // grain == pgcd => supprimer garde !
                              sprintf(unegarddd,"");
                           else
                           {  if(strcmp(unbblk->borneInf,"0")==0)
                                 sprintf(unegarddd,"(%s% %%s)==0",unbblk->indiceRef,sh);
                              else
                                 sprintf(unegarddd,"((%s-%s)% %%s)==0",unbblk->indiceRef,unbblk->borneInf,sh);
                           }
                        }
                        if(strcmp(unegarddd,"")!=0)
                        {  if(strcmp(garddd,"")==0)
                              sprintf(garddd,"%s",unegarddd);
                           else
                              sprintf(garddd,"%s && %s",garddd,unegarddd);
                        }
                        sprintf(unegarddd,"");
                     } 
                     gardeTab[possss]=garddd;  
                     // remplacer l'indice de référence avec indiceRef-Binf%pgcd(grain i)
                     char* lesindiceee=NULL;
                     lesindiceee= malloc(450);
                     if (lesindiceee == NULL) 
                     {  printf("L'allocation mémoire a échoué !\n");
                        exit(0);
                     }
                     sprintf(lesindiceee,""); 
                     char* unIndiceeee=NULL;
                     unIndiceeee= malloc(50);
                     if (unIndiceeee == NULL) 
                     {  printf("L'allocation mémoire a échoué !\n");
                        exit(0);
                     }
                     pps=0;
                     int lengindexxxx=strlen(indexxTab[possss]); 
                     while (pps<lengindexxxx)
                     {  sprintf(unIndiceeee,""); 
                        while (pps<lengindexxxx && indexxTab[possss][pps]!=';' )
                        {  sprintf(unIndiceeee,"%s%c",unIndiceeee,indexxTab[possss][pps]);
                           pps++;
                        }
                        sprintf(unIndiceeee,"%s%c\n",unIndiceeee,indexxTab[possss][pps]);
                        pps++;
                        while (pps<lengindexxxx && (indexxTab[possss][pps]== ' ' || indexxTab[possss][pps]== '\n'))
                        {  pps++;
                        }
                        int ggrain=1;
                        char* oofset=NULL;
                        oofset=malloc(100);
                        if(oofset==NULL)
                        {  printf("L'allocation mémoire a échoué !\n");
                           exit(0);
                        }
                        sprintf(oofset,""); 

                        char *strch = strstr(unIndiceeee,unbblk->indiceRef);
                        if (strch==NULL)
                           sprintf(lesindiceee,"%s%s",lesindiceee,unIndiceeee);
                        else
                        { //reformuler l'indice
                           char*ssh=NULL;
                           ssh=malloc(100);
                           if(ssh==NULL)
                           {  printf("L'allocation mémoire a échoué !\n");
                              exit(0);
                           }
                           sprintf(ssh,""); 
                           int comptt=strlen(unbblk->indiceRef);
                           if(strch[comptt]=='-')
                           {  comptt++;
                              while(strch[comptt]!=')')
                              {  sprintf(ssh,"%s%c",ssh,strch[comptt]);
                                 comptt++;
                              }
                              comptt++; 
                              sprintf(oofset,"%s",ssh); 
                              sprintf(ssh,""); 
                           }
                           if(strch[comptt]=='/') comptt++;
                           while(strch[comptt]!=';')
                           {  sprintf(ssh,"%s%c",ssh,strch[comptt]);
                              comptt++;
                           }
                           ggrain=atoi(ssh);
                           int mmm,lonng;
                           if(isInteger(oofset,strlen(oofset)))
                           {  if (atoi(oofset))
                                 lonng=strlen(unIndiceeee)-strlen(strch)-1;
                              else
                                 lonng=strlen(unIndiceeee)-strlen(strch);
                           }
                           else
                              lonng=strlen(unIndiceeee)-strlen(strch);

                           sprintf(ssh,""); 
                           for(mmm=0;mmm<lonng;mmm++)
                              sprintf(ssh,"%s%c",ssh,unIndiceeee[mmm]);
                           int isnumber=1;
                           isnumber=isdigit(unbblk->borneInf[0]);
                           char * renomm=NULL;
                           renomm= malloc(300);
                           if (renomm == NULL) 
                           {  printf("L'allocation mémoire a échoué !\n");
                              exit(0);
                           } 
                          sprintf(renomm,"");
                          int moodulo = atoi(unbblk->borneInf)%tabdyn[nbreForImb-1];
	       if (isnumber && isInteger(offsetGarde,strlen(offsetGarde)) && isInteger(oofset,strlen(oofset))) 
	       {  if(moodulo==atoi(offsetGarde))
	             isnumber=0;
	          else
	          {  if (moodulo>0)
	             {  if(atoi(oofset)<ggrain)
	                   sprintf(renomm,"%s(%s+%d)/%d;\n",ssh,unbblk->indiceRef,moodulo,ggrain);
	                else
	                   sprintf(renomm,"%s(%s-%d)/%d;\n",ssh,unbblk->indiceRef,moodulo+((atoi(oofset)-moodulo)/ggrain)*ggrain,ggrain);
	             }
	             else
	             {  if(atoi(oofset)<ggrain)
	                   sprintf(renomm,"%s%s/%d;\n",ssh,unbblk->indiceRef,ggrain);
	                else
                         sprintf(renomm,"%s(%s-%d)/%d;\n",ssh,unbblk->indiceRef,(atoi(oofset)/ggrain)*ggrain,ggrain);
	             }
	          }
	       }
	       else
	       {  char* mooduloo=NULL;
                mooduloo= malloc(150);
                if (mooduloo == NULL) 
                {  printf("L'allocation mémoire a échoué !\n");
                   exit(0);
                }
                sprintf(mooduloo,""); 
                sprintf(mooduloo,"(%s)% %%d",unbblk->borneInf,tabdyn[nbreForImb-1]); 
                if(isInteger(oofset,strlen(oofset)))
		    {  if(atoi(oofset)<ggrain)
                      sprintf(renomm,"%s(%s+%s)/%d;\n",ssh,unbblk->indiceRef,mooduloo,ggrain);
		    }
                else
               sprintf(renomm,"%s(%s-(%s+((%s-%s)/%d)*%d))/%d;\n",ssh,unbblk->indiceRef,mooduloo,oofset,mooduloo,ggrain,ggrain,ggrain);
	          isnumber=1;
	       }
                           if(isnumber)
                              sprintf(lesindiceee,"%s%s",lesindiceee,renomm);
                           else
                              sprintf(lesindiceee,"%s%s",lesindiceee,unIndiceeee);
                        }
                     }// FIN while !! 
                     indexxTab[possss] = lesindiceee;
                     possss--;
                  } 
               }
               tabdyn[nbreForImb-1]=0;
               unbblk->nbOffset=0;
               // g_ptr_array_remove_index(BlockForTab,nbreForImb-1);
               nbreForImb--;
               // si compression alors mise à jour de tout les gardes !!
               if(nbreForImb==0)
               {  int it;  
                  for (it=nbgardePos-1;it>=0;it--)
                  {  fseek(fichier, indexPosTab[it], SEEK_SET);
                     fputs(indexxTab[it],fichier);
                     fputs("                      ",fichier);
                     if(strcmp(gardeTab[it],"")==0)
                     {  fseek(fichier, fingardePosTab[it], SEEK_SET);
                        fputs(" ",fichier); 
                        fseek(fichier, gardePosTab[it], SEEK_SET);
                fprintf(fichier,"                                                                                                 \n");
                     }
                     else
                     {  fseek(fichier, gardePosTab[it], SEEK_SET);
                        fprintf(fichier,"if(%s) {                                                          \n",gardeTab[it]);
                     } 
                  }
                  nbgardePos =0;
               }
               fseek(fichier, 0L, SEEK_END);
            }
         }
      }
   }
   free(tabdyn); 
   for(i=0;i< BlockForTab->len ; i++)
      free ( g_ptr_array_index (BlockForTab, i)); 
   g_ptr_array_free (BlockForTab, TRUE);
   free(filePosTab); 
   free(gardePosTab);
   free(fingardePosTab);
   free(gardeTab);  
}



extern FILE *yyin;
extern FILE *yyout;

int multifor_parser (char * inputFile) {
  root=NULL;
  pere=NULL;
  frere=NULL;
  nested=1;
  nbErr=0;
  yyin = fopen(inputFile,"r");//stdin  ; 
  if (yyin == NULL)
  {
   printf("Impossible d'ouvrir le fichier %s\n",inputFile);
   exit(0);
  }
//  yyout = fopen("CodeCFinal.c","w");
  nbLigne=0;
  parameters=NULL;// Besoin de ça pour la matrice contexte 
  nbParameters=0;
  FILE * temp;
  yyparse(); //Appel de l'analyseur syntaxique
  if (nbErr==0) 
  {
//     printf(" -  Generated by Multifor-compiler  - \n");
//   printf("\n\n\t★  Affichage du contenu de l'arbre  ★\n\n");
//   g_node_traverse(root, G_PRE_ORDER, G_TRAVERSE_ALL, -1, afficher, NULL);   //visits a node, then its children.
//       printf ("\n g_node_max_height : %d \n",g_node_max_height(root));
     if (maxRef < (g_node_max_height(root)-1))
        maxRef = g_node_max_height(root)-1;
     maxRefAc= g_node_max_height(root);
     //  Faire un parcourt de l'arbre pour préparer les données Pour Cloog
     //  printf ("\n  Construction des matrices de Cloog :\n");
     /* Setting options and reading program informations. */
     state = cloog_state_malloc();
     options = cloog_options_malloc(state);
     options->strides=1;//1 if user wants to handle non-unit strides (then loop increment can be something else than one), 0 otherwise
     // La matrice contexte
     matrixCtxt = cloog_matrix_alloc(1, nbParameters+2);
     /* Adding constraints to matrixCtxt->p    Contrainte sur les paramètres  */
     int i,j;
     cloog_int_read(matrixCtxt->p[0][0], "1");
     for (i=1;i<nbParameters+2;i++)
        cloog_int_read(matrixCtxt->p[0][i], "0");// Pas de contrainte sur les paramètre 1>= 0 tjours vrai
     context = cloog_domain_from_cloog_matrix(state, matrixCtxt, nbParameters);
     // printf("\nmatrixCtxt : \n");
     // cloog_matrix_print_structure(stdout, matrixCtxt,"   ", "");    
     // Créer l'union des domaines
     ud = cloog_union_domain_alloc(nbParameters);
     lesGardes=g_ptr_array_new ();
     lesIndices=g_ptr_array_new ();
     toutcoefNivSup=g_ptr_array_new ();
     blocks=g_ptr_array_new (); 
     constMatCloog(root);         // Définition des matrices domaines 
     for (i=0;i<nbParameters;i++) // renommer les paramètres
     { Element * opElement =g_list_nth_data(parameters,i);
       ud = cloog_union_domain_set_name(ud, CLOOG_PARAM, i,  opElement->inconnu);
     }
     char * indiceRef=NULL;
     indiceRef= malloc(50);
     if (indiceRef == NULL) 
     {  printf("L'allocation mémoire a échoué !\n");
        exit(0);
     }
     for (i=0;i<g_node_max_height(root);i++) // renommer les Itérateurs
     {  sprintf(indiceRef,"_mfr_ref%d",i+oldmaxRef);
        ud = cloog_union_domain_set_name(ud, CLOOG_ITER, i, indiceRef);
     }
     //printf ("\n  Le code généré par  Cloog :\n\n");
     input = cloog_input_alloc(context, ud); // Créer l'input
     /* Generating and printing the code. */
     rootCloog = cloog_clast_create_from_input(input, options);
     fichier = fopen( "_multifor_Compiler_IBB_temp2.c", "w+");
     if (fichier == NULL)
        printf("Impossible d'ouvrir le fichier _multifor_Compiler_IBB_temp2.c");
     else
     {   //clast_pprint(stdout, rootCloog, 0, options);
         temp = fopen( "_multifor_Compiler_IBB_temp.c", "w+");
         if (temp == NULL)
            printf("Impossible d'ouvrir le fichier _multifor_Compiler_IBB_temp.c");
         else
         {  clast_pprint(temp, rootCloog, 0, options);
            // Insertion des instruction + compression du domaine d'itération si nécessaire :)
            //printf ("\n  Insertion des instructions + Compression du domaine d'itération ...\n\n"); 
            insertInstr(temp);
            fclose(temp);
         }
         fclose(fichier);
     } 
     // Libérer les structures de données
     cloog_clast_free(rootCloog);
     cloog_options_free(options) ;
     cloog_state_free(state);
     g_ptr_array_free (lesGardes, TRUE);
     g_ptr_array_free (lesIndices, TRUE);
     for(i=0 ; i<toutcoefNivSup->len ; i++)
        g_ptr_array_free ( g_ptr_array_index(toutcoefNivSup,i) , TRUE);
     g_ptr_array_free (toutcoefNivSup, TRUE);
     g_ptr_array_free (blocks, TRUE);
     g_node_destroy(root);
  }//Fin Else
fclose(yyin); 
//fclose(yyout);
return (nbErr);
}

int yywrap() {
return(1);
}


int yyerror(char *err) {
nbErr++;
printf("Syntax Error : %s\n",err);
}
#line 2807 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 4:
#line 194 "AnaSyntxMul.y"
	{
      gp++;
      if(test==1)
      {  char* res="";/*"Nombre d'éléments vérifié";*/
         if( nbInit !=nbOffset)
         {  nbErr++;
            res="ERREUR : Les paramètres doivent avoir le même nombre d'éléments !";
            printf("\n  %s  \n",res);
         }
         test=2; 
      }}
break;
case 5:
#line 207 "AnaSyntxMul.y"
	{ 
         /*Mise à jour du père, du frère et de la table de pointeurs lesFor*/
         frere=frere->parent; /* Le père devient FRERE*/
         if(frere!=NULL)
         {  pere=frere->parent;
         }
         if(frere==NULL)
            {  frere=root; 
               pere =root;
            }
         if(pere==NULL)
         {  pere =root;
         }
         lesFor=pere->data;
      }
break;
case 6:
#line 222 "AnaSyntxMul.y"
	{  
      nested=0;  
      while(gp>0)
      {
      /* Mise à jour du père, du frère et de la table de pointeurs lesFor*/
         frere=frere->parent; /* Le père devient FRERE*/
         if(frere!=NULL)
           pere=frere->parent;
         if(frere==NULL)
           {  frere=root; 
              pere =root;
           }
         if(pere==NULL)
           pere =root;
         lesFor=pere->data;
         gp--;
      }
      if(pere!=NULL && pere->parent==NULL)
      {  prem=0; }
      if(prem>0)
         {
      /*Mise à jour du père, du frère et de la table de pointeurs lesFor*/
         frere=frere->parent;  /* Le père devient FRERE*/
         if(frere!=NULL)
         {  pere=frere->parent;
            if(pere!=NULL && pere->parent==NULL)
                {  prem=0; 
                   if(deal == 0)
                   {  lesFor=frere->data;
                      testt=0;
                      deal=1;
                   }
                   else
                     { lesFor=pere->data;
                       testt=1;
                     }
                }
                else
                  { lesFor=pere->data;
                    testt=1;
                  }
         }
         if(frere==NULL)
            {  frere=root; 
               pere =root;
               lesFor=pere->data;
               testt=1;
            }
         if(pere==NULL)
         {  pere =root;
            lesFor=pere->data;
            testt=1;
         }
         }
      else 
         { 
           prem=1;            
           testt=1;
           lesFor=pere->data;
         }
      nbInit=lesFor->len;
      }
break;
case 7:
#line 286 "AnaSyntxMul.y"
	{deal=1;
       }
break;
case 10:
#line 292 "AnaSyntxMul.y"
	{ deal=0; }
break;
case 13:
#line 297 "AnaSyntxMul.y"
	{ 
      char* chain= NULL;
      chain= malloc(250);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
      yyval.chaine=chain;
      }
break;
case 14:
#line 309 "AnaSyntxMul.y"
	{yyval.chaine="";  }
break;
case 15:
#line 310 "AnaSyntxMul.y"
	{ 
      char* chain= NULL;
      chain= malloc(300);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"[%s]%s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
      yyval.chaine=chain;
 }
break;
case 16:
#line 320 "AnaSyntxMul.y"
	{  
      char* chain= NULL;
      chain= malloc(300);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"->%s",yystack.l_mark[0].chaine); 
      yyval.chaine=chain;
 }
break;
case 17:
#line 333 "AnaSyntxMul.y"
	{yyval.chaine="";  }
break;
case 18:
#line 334 "AnaSyntxMul.y"
	{ 
      char* chain= NULL;
      chain= malloc(300);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"[%s]%s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
      yyval.chaine=chain;
}
break;
case 19:
#line 346 "AnaSyntxMul.y"
	{ 
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s+%s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
      yyval.chaine=chain; }
break;
case 20:
#line 355 "AnaSyntxMul.y"
	{
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s-%s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
      yyval.chaine=chain; }
break;
case 21:
#line 364 "AnaSyntxMul.y"
	{
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s*%s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
      yyval.chaine=chain; }
break;
case 22:
#line 373 "AnaSyntxMul.y"
	{
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s % %s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
      yyval.chaine=chain; }
break;
case 23:
#line 382 "AnaSyntxMul.y"
	{      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s/%s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
      yyval.chaine=chain; }
break;
case 24:
#line 390 "AnaSyntxMul.y"
	{
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"(%s)",yystack.l_mark[-1].chaine); 
      yyval.chaine=chain; }
break;
case 25:
#line 399 "AnaSyntxMul.y"
	{ 
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"-%s",yystack.l_mark[0].chaine); 
      yyval.chaine=chain;}
break;
case 27:
#line 411 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(200);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
       }
break;
case 28:
#line 421 "AnaSyntxMul.y"
	{ sprintf(yyval.chaine,"%s",yystack.l_mark[0].nombre); }
break;
case 29:
#line 422 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine;}
break;
case 30:
#line 423 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine;}
break;
case 31:
#line 426 "AnaSyntxMul.y"
	{yyval.nombre=atoi(yystack.l_mark[0].nombre);}
break;
case 32:
#line 427 "AnaSyntxMul.y"
	{yyval.nombre=atoi(yystack.l_mark[0].nombre)*-1;}
break;
case 33:
#line 430 "AnaSyntxMul.y"
	{ yyval.chaine="";}
break;
case 34:
#line 431 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(200);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
       }
break;
case 35:
#line 443 "AnaSyntxMul.y"
	{yyval.chaine=""; }
break;
case 36:
#line 444 "AnaSyntxMul.y"
	{ 
      char* chain= NULL;
      chain= malloc(200);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"[%s]%s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
      yyval.chaine=chain;
      }
break;
case 37:
#line 454 "AnaSyntxMul.y"
	{ 
      char* chain= NULL;
      chain= malloc(200);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"(%s)",yystack.l_mark[-1].chaine); 
      yyval.chaine=chain;
      }
break;
case 38:
#line 464 "AnaSyntxMul.y"
	{  
      char* chain= NULL;
      chain= malloc(200);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"->%s",yystack.l_mark[0].chaine); 
      yyval.chaine=chain;
 }
break;
case 39:
#line 476 "AnaSyntxMul.y"
	{ yyval.chaine="";}
break;
case 40:
#line 477 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(400);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
       }
break;
case 41:
#line 489 "AnaSyntxMul.y"
	{ 
        char* chain= NULL;
        chain= malloc(800);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s(%s);",yystack.l_mark[-4].chaine,yystack.l_mark[-2].chaine); 
        yyval.chaine=chain;
      }
break;
case 42:
#line 501 "AnaSyntxMul.y"
	{ 
        char* chain= NULL;
        chain= malloc(1000);
        if (chain == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(chain,"%s%s;",yystack.l_mark[-2].chaine,yystack.l_mark[-1].chaine); 
        yyval.chaine=chain;
       }
break;
case 43:
#line 511 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(80);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"++%s;",yystack.l_mark[-1].chaine); 
        yyval.chaine=chain;
     }
break;
case 44:
#line 521 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(80);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"--%s;",yystack.l_mark[-1].chaine); 
        yyval.chaine=chain; }
break;
case 45:
#line 533 "AnaSyntxMul.y"
	{ yyval.chaine="";}
break;
case 46:
#line 534 "AnaSyntxMul.y"
	{
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"%s \n %s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine);
        yyval.chaine=maInst;
      }
break;
case 47:
#line 546 "AnaSyntxMul.y"
	{ 
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"\n%s\n",yystack.l_mark[0].chaine);
        yyval.chaine=maInst;
     }
break;
case 48:
#line 556 "AnaSyntxMul.y"
	{ 
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"{\n%s\n%s\n}\n",yystack.l_mark[-2].chaine,yystack.l_mark[-1].chaine);
        yyval.chaine=maInst;
       }
break;
case 49:
#line 568 "AnaSyntxMul.y"
	{yyval.chaine=""; }
break;
case 50:
#line 569 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain," && %s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
       }
break;
case 51:
#line 579 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain," || %s",yystack.l_mark[0].chaine);
        yyval.chaine=chain;
       }
break;
case 52:
#line 591 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s%s",yystack.l_mark[-2].chaine,yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
       }
break;
case 53:
#line 601 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"(%s)%s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
       }
break;
case 54:
#line 613 "AnaSyntxMul.y"
	{yyval.chaine="";}
break;
case 55:
#line 614 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(300);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
     }
break;
case 56:
#line 626 "AnaSyntxMul.y"
	{yyval.chaine=""; }
break;
case 57:
#line 627 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"else %s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
     }
break;
case 58:
#line 639 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"if(%s)%s%s",yystack.l_mark[-3].chaine,yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 59:
#line 651 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"while(%s)%s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 60:
#line 663 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"do%s \n while(%s);",yystack.l_mark[-5].chaine,yystack.l_mark[-2].chaine); 
        yyval.chaine=chain;
      }
break;
case 61:
#line 675 "AnaSyntxMul.y"
	{ 
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s=%s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 62:
#line 687 "AnaSyntxMul.y"
	{yyval.chaine=""; }
break;
case 63:
#line 688 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine;}
break;
case 64:
#line 691 "AnaSyntxMul.y"
	{yyval.chaine=""; }
break;
case 65:
#line 692 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 66:
#line 695 "AnaSyntxMul.y"
	{yyval.chaine="++";}
break;
case 67:
#line 696 "AnaSyntxMul.y"
	{yyval.chaine="--"; }
break;
case 68:
#line 697 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"+=%s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 69:
#line 707 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"-=%s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 70:
#line 717 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"/=%s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 71:
#line 727 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"*=%s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 72:
#line 737 "AnaSyntxMul.y"
	{ 
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"=%s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
       }
break;
case 73:
#line 749 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 74:
#line 759 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(80);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"++%s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
     }
break;
case 75:
#line 769 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(80);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"--%s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain; }
break;
case 76:
#line 780 "AnaSyntxMul.y"
	{yyval.chaine="";}
break;
case 77:
#line 781 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine;}
break;
case 78:
#line 784 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"for(%s;%s;%s)%s",yystack.l_mark[-6].chaine,yystack.l_mark[-4].chaine,yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 79:
#line 796 "AnaSyntxMul.y"
	{yyval.chaine="";}
break;
case 80:
#line 797 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(300);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 81:
#line 809 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(400);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 82:
#line 821 "AnaSyntxMul.y"
	{yyval.chaine="";}
break;
case 83:
#line 822 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(300);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 84:
#line 834 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(400);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 85:
#line 846 "AnaSyntxMul.y"
	{yyval.chaine="";}
break;
case 86:
#line 847 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(300);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 87:
#line 859 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(400);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 88:
#line 871 "AnaSyntxMul.y"
	{yyval.chaine=""; }
break;
case 89:
#line 872 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(150);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",yystack.l_mark[-1].nombre,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 90:
#line 884 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(200);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",yystack.l_mark[-1].nombre,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 91:
#line 896 "AnaSyntxMul.y"
	{yyval.chaine="";}
break;
case 92:
#line 897 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(150);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",yystack.l_mark[-1].nombre,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 93:
#line 909 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(200);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",yystack.l_mark[-1].nombre,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 94:
#line 921 "AnaSyntxMul.y"
	{ yyval.chaine="";}
break;
case 95:
#line 922 "AnaSyntxMul.y"
	{
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"%s \n %s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine);
        yyval.chaine=maInst;
      }
break;
case 96:
#line 934 "AnaSyntxMul.y"
	{
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"\n%s:%s\n",yystack.l_mark[-2].nombre,yystack.l_mark[0].chaine);
        yyval.chaine=maInst;
     }
break;
case 97:
#line 944 "AnaSyntxMul.y"
	{
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"\n%s",yystack.l_mark[0].chaine);
        yyval.chaine=maInst;
     }
break;
case 98:
#line 956 "AnaSyntxMul.y"
	{ yyval.chaine=yystack.l_mark[0].chaine;}
break;
case 99:
#line 957 "AnaSyntxMul.y"
	{ 
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"{\n%s\n%s\n}\n",yystack.l_mark[-2].chaine,yystack.l_mark[-1].chaine);
        yyval.chaine=maInst;
       }
break;
case 100:
#line 969 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"multifor(%s;%s;%s;%s;%s)%s",yystack.l_mark[-10].chaine,yystack.l_mark[-8].chaine,yystack.l_mark[-6].chaine,yystack.l_mark[-4].chaine,yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 101:
#line 981 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine;}
break;
case 102:
#line 982 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].nombre;}
break;
case 103:
#line 985 "AnaSyntxMul.y"
	{yyval.chaine="";}
break;
case 104:
#line 986 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(1000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"case %s:%s\n%s",yystack.l_mark[-3].chaine,yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 105:
#line 996 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(1000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"default:%s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 106:
#line 1008 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(1000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"case %s:%s\n%s",yystack.l_mark[-3].chaine,yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 107:
#line 1020 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"switch(%s){\n%s\n}",yystack.l_mark[-4].chaine,yystack.l_mark[-1].chaine); 
        yyval.chaine=chain;
      }
break;
case 108:
#line 1032 "AnaSyntxMul.y"
	{yyval.chaine=""; }
break;
case 109:
#line 1033 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(50);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"*%s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 110:
#line 1045 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 111:
#line 1046 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 112:
#line 1049 "AnaSyntxMul.y"
	{yyval.chaine=""; }
break;
case 113:
#line 1050 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 114:
#line 1062 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"{%s%s}",yystack.l_mark[-2].chaine,yystack.l_mark[-1].chaine); 
        yyval.chaine=chain;
      }
break;
case 115:
#line 1074 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 116:
#line 1075 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 117:
#line 1078 "AnaSyntxMul.y"
	{yyval.chaine=""; }
break;
case 118:
#line 1079 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"=%s",yystack.l_mark[0].chaine); 
        yyval.chaine=chain;
      }
break;
case 119:
#line 1091 "AnaSyntxMul.y"
	{yyval.chaine=""; }
break;
case 120:
#line 1092 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 121:
#line 1095 "AnaSyntxMul.y"
	{yyval.chaine="";  }
break;
case 122:
#line 1096 "AnaSyntxMul.y"
	{ 
      char* chain= NULL;
      chain= malloc(300);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"[%s]",yystack.l_mark[-2].chaine); 
      yyval.chaine=chain;
 }
break;
case 123:
#line 1109 "AnaSyntxMul.y"
	{
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s %s%s%s;",yystack.l_mark[-5].chaine,yystack.l_mark[-4].chaine,yystack.l_mark[-3].chaine,yystack.l_mark[-2].chaine,yystack.l_mark[-1].chaine); 
        yyval.chaine=chain;
      }
break;
case 124:
#line 1121 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 125:
#line 1122 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 126:
#line 1123 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 127:
#line 1124 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 128:
#line 1125 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 129:
#line 1126 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 130:
#line 1127 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 131:
#line 1128 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 132:
#line 1129 "AnaSyntxMul.y"
	{yyval.chaine=yystack.l_mark[0].chaine; }
break;
case 133:
#line 1130 "AnaSyntxMul.y"
	{yyval.chaine=";"; /* Instruction vide */ }
break;
case 134:
#line 1131 "AnaSyntxMul.y"
	{yyval.chaine="break;"; }
break;
case 135:
#line 1134 "AnaSyntxMul.y"
	{        
        MesssInstr=NULL;
        Instruc* uneIstr= NULL;
        uneIstr= malloc(sizeof(Instruc));
        if (uneIstr == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
 /* Vérifier auquel indice l'instruction se rattache*/
        sprintf(maInst,"%s",yystack.l_mark[0].chaine); /* Vérifier auquel indice l'instruction se rattache*/
        uneIstr->instr =maInst;  
        /*À quelle position l'instruction apparaît ?*/
        int indice; 
        if(testt==1)
           indice= g_node_n_children(pere)-1;
        else
           indice= g_node_n_children(frere)-1;
        uneIstr->index =indice; 
        MesssInstr=g_slist_prepend(MesssInstr,uneIstr); 
      }
break;
case 136:
#line 1160 "AnaSyntxMul.y"
	{ 
        Instruc* uneIstr= NULL;
        uneIstr= malloc(sizeof(Instruc));
        if (uneIstr == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
 /* Vérifier auquel indice l'instruction se rattache*/
        sprintf(maInst,"%s",yystack.l_mark[-2].chaine); /* Vérifier auquel indice l'instruction se rattache*/
        uneIstr->instr =maInst;  
        /*À quelle position l'instruction apparaît ?*/
        int indice;
        if(testt==1)
           indice= g_node_n_children(pere)-1;
        else
           indice= g_node_n_children(frere)-1;
        uneIstr->index =indice;
        MesssInstr=g_slist_prepend(MesssInstr,uneIstr);
      }
break;
case 137:
#line 1187 "AnaSyntxMul.y"
	{
        MesssInstr=NULL;
       }
break;
case 138:
#line 1190 "AnaSyntxMul.y"
	{
        Instruc* uneIstr= NULL;
        uneIstr= malloc(sizeof(Instruc));
        if (uneIstr == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
 /* Vérifier auquel indice l'instruction se rattache*/
        sprintf(maInst,"%s",yystack.l_mark[-1].chaine); /* Vérifier auquel indice l'instruction se rattache*/
        uneIstr->instr =maInst;  
        /*À quelle position l'instruction apparaît ?*/
        int indice;
        if(testt==1)
           indice= g_node_n_children(pere)-1;
        else
           indice= g_node_n_children(frere)-1;
        uneIstr->index =indice;
        MesssInstr=g_slist_prepend(MesssInstr,uneIstr);
      }
break;
case 139:
#line 1217 "AnaSyntxMul.y"
	{ 
      if(test==1)
      {  char* res="";  /* Nombre d'éléments vérifié*/
         if( nbInit !=nbOffset)
         {  nbErr++;
            res="ERREUR : Les paramètres doivent avoir le même nombre d'éléments !";
            printf("\n  %s  \n",res);
         }
         test=2;
      }
      /*Si l'indice est inexistant*/
      nbInit=lesFor->len;
      int etiq=atoi(yystack.l_mark[-2].nombre);
      if (etiq>=nbInit)
      {  printf("ERREUR : Entier hors limite %d ! le multifor contient seulement %d indice !\n",etiq,nbInit);
         nbErr++;
      }
      else 
      /*Je dois rajouter cette instruction à la liste chainée de l'indice correspondant */
      {   InfoFor* aux2= g_ptr_array_index(lesFor,etiq);
          aux2->instr=g_slist_concat(aux2->instr,MesssInstr);
      } }
break;
case 140:
#line 1241 "AnaSyntxMul.y"
	{yyval.chaine="+";}
break;
case 141:
#line 1242 "AnaSyntxMul.y"
	{yyval.chaine="-";}
break;
case 142:
#line 1245 "AnaSyntxMul.y"
	{
      sprintf(yyval.chaine,"%s",yystack.l_mark[0].chaine);
      Element * opElement= NULL;
      opElement= malloc(sizeof(Element));
      if (opElement == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
        exit(0);
      }
      if(isInteger(yyval.chaine,strlen(yyval.chaine))==1)
         {opElement->inconnu="";
          opElement->coef=atoi(yyval.chaine);
         }else
         {opElement->inconnu=yyval.chaine;
          opElement->coef=1;
         }
         operand = g_list_append(operand, opElement);
      }
break;
case 143:
#line 1262 "AnaSyntxMul.y"
	{ 
      Element * opElement= NULL;
      opElement= malloc(sizeof(Element));
      if (opElement == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      if(isInteger(yystack.l_mark[0].chaine,strlen(yystack.l_mark[0].chaine))==1)
      {
       opElement->inconnu="";
       opElement->coef=atoi(yystack.l_mark[0].chaine)*-1;
      }else
      {
       opElement->inconnu=yystack.l_mark[0].chaine;
       opElement->coef=-1;
      }
      operand = g_list_append(operand, opElement);
      char* chain= NULL;
      chain= malloc(50);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"-%s",yystack.l_mark[0].chaine); 
      yyval.chaine=chain;
       }
break;
case 144:
#line 1290 "AnaSyntxMul.y"
	{ 
      int longList =  g_list_length (operand) ;
      Element * op1=  g_list_nth_data (operand, longList-1);
      Element * op2= g_list_nth_data (operand, longList-2);
      if(strcmp(op1->inconnu,"")==0 && strcmp(op2->inconnu,"")==0 )
      {op2->coef = op2->coef * op1->coef;
       operand = g_list_delete_link (operand , g_list_last (operand));
      }
      else
      {
        if(strcmp(op1->inconnu,"")!=0 && strcmp(op2->inconnu,"")!=0 )
        {printf("ERREUR : Les bornes doivent être des fonctions affines !\n");
         nbErr++;
        }
        if(strcmp(op1->inconnu,"")==0 )
        {op2->coef = op2->coef * op1->coef;
         operand = g_list_delete_link (operand , g_list_last (operand));
        }
        if( strcmp(op2->inconnu,"")==0 )
        {op2->coef = op2->coef * op1->coef;
         op2->inconnu = op1->inconnu;
         operand = g_list_delete_link (operand , g_list_last (operand));
        }
      }
      char* chain= NULL;
      chain= malloc(50);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      sprintf(chain,"%s*%s",yystack.l_mark[-2].chaine,yystack.l_mark[0].chaine); 
      yyval.chaine=chain;
        }
break;
case 145:
#line 1323 "AnaSyntxMul.y"
	{ 
      char* chain= NULL;
      chain= malloc(50);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      sprintf(chain,"%s",yystack.l_mark[0].chaine); 
      yyval.chaine=chain;
        }
break;
case 146:
#line 1335 "AnaSyntxMul.y"
	{ 
      int longList =  g_list_length (operand) ;
      Element * op1=  g_list_nth_data (operand, longList-1);
      Element * op2= g_list_nth_data (operand, longList-2);
      if (strcmp(yystack.l_mark[-1].chaine,"-")==0)
        op1->coef = op1->coef *-1;
      if(strcmp(op1->inconnu,"")==0 && strcmp(op2->inconnu,"")==0 )
      {op2->coef = op2->coef + op1->coef;
       operand = g_list_delete_link (operand , g_list_last (operand));
      }
      char* chhain= NULL;
      chhain= malloc(50);
      if (chhain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      sprintf(chhain,"%s%s%s",yystack.l_mark[-2].chaine,yystack.l_mark[-1].chaine,yystack.l_mark[0].chaine); 
      yyval.chaine=chhain;
        }
break;
case 147:
#line 1354 "AnaSyntxMul.y"
	{  
      char* chhain= NULL;
      chhain= malloc(50);
      if (chhain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      sprintf(chhain,"%s",yystack.l_mark[0].chaine); 
      yyval.chaine=chhain;
      }
break;
case 148:
#line 1366 "AnaSyntxMul.y"
	{ 
      nbInit++; 
      /*Nouvel indice, alors créer une nouvelle structure*/
      InfoFor* pUnFor= NULL;
      pUnFor= malloc(sizeof(InfoFor));
      if (pUnFor == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0); 
      }
      pUnFor->indice=yystack.l_mark[-2].chaine;
      pUnFor->type ="int";
      pUnFor->bInf =yystack.l_mark[0].chaine;
      pUnFor->instr=NULL;
      g_ptr_array_add (lesFor, pUnFor);
      /* Rajouter les infos à pUnFor->bInfCloog*/
      InputClooG* inputclg= NULL;
      inputclg= malloc(sizeof(InputClooG));
      if (inputclg == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      inputclg->iterators = NULL;
      inputclg->parameters = operand; 
      inputclg->constante = 0;
      inputclg->nbiterators = 0;
      inputclg->nbParameters = 0;
      pUnFor->bInfCloog=inputclg;
      operand=NULL;
      }
break;
case 149:
#line 1397 "AnaSyntxMul.y"
	{  
      if(test==1)
      {  char* res="";  /* Nombre d'éléments vérifié";*/
         if( nbInit !=nbOffset)
         {  nbErr++;
            res="ERREUR : Les paramètres doivent avoir le même nombre d'éléments !";
            printf("\n  %s  \n",res);
         }
         test=2;  
      }
      nbInit=0;
      test=0; 
      lesFor=g_ptr_array_new ();      
      }
break;
case 150:
#line 1411 "AnaSyntxMul.y"
	{ operand=NULL;}
break;
case 151:
#line 1414 "AnaSyntxMul.y"
	{
      if(nbComp<nbInit){
      nbComp++; 
      InfoFor* aux2= g_ptr_array_index(lesFor,nbComp-1);
      aux2->bSup=yystack.l_mark[0].chaine;
      aux2->opRel =yystack.l_mark[-1].chaine;
      /* Rajouter les infos à pUnFor->bInfCloog*/
      InputClooG* inputclg= NULL;
      inputclg= malloc(sizeof(InputClooG));
      if (inputclg == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      inputclg->iterators = NULL;
      inputclg->parameters = operand;
      inputclg->constante = 0;
      inputclg->nbiterators = 0;
      inputclg->nbParameters = 0;
      aux2->bSupCloog=inputclg;
      operand=NULL; }
     else {
            nbErr++;
            printf("\n  ERREUR : Les paramètres doivent avoir le même nombre d'éléments !  \n");
            test=2;
     }
      }
break;
case 152:
#line 1442 "AnaSyntxMul.y"
	{nbComp=0; }
break;
case 154:
#line 1446 "AnaSyntxMul.y"
	{yyval.nombre=yystack.l_mark[0].nombre;}
break;
case 155:
#line 1447 "AnaSyntxMul.y"
	{yyval.nombre=-1;}
break;
case 156:
#line 1448 "AnaSyntxMul.y"
	{yyval.nombre=1;}
break;
case 157:
#line 1451 "AnaSyntxMul.y"
	{
     if(nbInc<nbInit){
      nbInc++; 
      InfoFor* aux2= g_ptr_array_index(lesFor,nbInc-1);
      aux2->incr=yystack.l_mark[0].nombre;
      if(aux2->incr==0){  printf("L'incrément ne peut pas être nul !\n");
        nbErr++;}}
      else {
            nbErr++;
            printf("\n  ERREUR : Les paramètres doivent avoir le même nombre d'éléments !  \n");
            test=2;
       }
      }
break;
case 158:
#line 1466 "AnaSyntxMul.y"
	{yyval.nombre=1;}
break;
case 159:
#line 1467 "AnaSyntxMul.y"
	{yyval.nombre=-1;}
break;
case 160:
#line 1468 "AnaSyntxMul.y"
	{yyval.nombre=yystack.l_mark[0].nombre;}
break;
case 161:
#line 1469 "AnaSyntxMul.y"
	{yyval.nombre=yystack.l_mark[0].nombre*-1;}
break;
case 162:
#line 1472 "AnaSyntxMul.y"
	{nbInc=0;}
break;
case 164:
#line 1476 "AnaSyntxMul.y"
	{ 
      if(nbGrain<nbInit){
      nbGrain++; 
      if(yystack.l_mark[0].nombre<1){printf("Le grain doit être supérieur ou égal à 1 !\n");
      nbErr++;}
      InfoFor* aux2= g_ptr_array_index(lesFor,nbGrain-1);
      aux2->grain =yystack.l_mark[0].nombre;
      }
      else {
            nbErr++;
            printf("\n  ERREUR : Les paramètres doivent avoir le même nombre d'éléments !  \n");
            test=2;
      }
}
break;
case 165:
#line 1492 "AnaSyntxMul.y"
	{nbGrain=0;}
break;
case 167:
#line 1496 "AnaSyntxMul.y"
	{
      if(test==0)
      {  char* res=""; /*  Nombre d'éléments vérifié";*/
         if(nbInit!=nbComp || nbInit!=nbInc || nbInit!=nbGrain)
         {  nbErr++;
            res="ERREUR : Les paramètres doivent avoir le même nombre d'éléments !";
            printf("\n  %s  \n",res);
         }
         test=1;
      }
      if(nbOffset<nbInit) {
         nbOffset++; 
         if (isInteger (yystack.l_mark[0].chaine,strlen(yystack.l_mark[0].chaine)))
         {   if(atoi(yystack.l_mark[0].chaine)<0) {
               printf("ERREUR : L'offset doit être supérieur ou égal à 0 !\n");
               nbErr++;}
         }
         else
            create_Max_Min=1;
         InfoFor* aux2= g_ptr_array_index(lesFor,nbOffset-1);
         aux2->offset =yystack.l_mark[0].chaine; 

     /* Rajouter les infos à aux2->offsetCloog*/
      InputClooG* inputclg= NULL;
      inputclg= malloc(sizeof(InputClooG));
      if (inputclg == NULL) 
      { printf("L'allocation mémoire a échoué !\n");
        exit(0);
      }
      inputclg->iterators = NULL;
      inputclg->parameters = operand; 
      inputclg->constante = 0;
      inputclg->nbiterators = 0;
      inputclg->nbParameters = 0;
      aux2->offsetCloog=inputclg;
      operand=NULL;

         if(nbOffset==nbInit)
         {  int i;   
            int nbIncices =lesFor->len;
            for(i=0;i<nbIncices;i++)
            {  InfoFor* aux2= g_ptr_array_index(lesFor,i);
               /*Initialiser la liste des instructions*/
               aux2->instr=NULL;
            } 
            if(root==NULL)
            {  /*C'est le premier Multifor=> Créer la racine de l'arbre*/
               root = g_node_new(lesFor);
               pere =root;
               frere=root;
               int p;
               for( p=0;p<nbIncices;p++)
               {  InfoFor * itFor = g_ptr_array_index(lesFor,p);
                  coefMAJ (itFor->bInfCloog);
                  coefMAJ (itFor->bSupCloog);
                  coefMAJ (itFor->offsetCloog);
               }
            }
            else 
            {    /*Inserts a new GNode as the last child of the given parent*/
               if(nested==1)
               {  pere=frere; /* printf("\n(nested==1)   ★ Le frère devient père ★\n");*/
                  prem=0;
               }  
               g_node_append_data(pere, lesFor);
               frere=g_node_last_child(pere);  /* printf("\n★ MAJ : frere=g_node_last_child(pere); ★\n");*/
               nested=1;
               testt=0;
               /* Faire le test : le neud fils ne peut pas avoir plus d'indice que le père*/
               GPtrArray* auxTest=pere->data;
               if(nbIncices > auxTest->len)
               {  printf("ERREUR : Le Multifor interne ne peut pas avoir plus d'indices que le multifor englobant !\n");
                  nbErr++;
               }
               else
               { majInputClooG( auxTest, lesFor);}/*fin else*/
            }
         }/* fin if*/
      }
     else {  nbErr++;
             printf("\n  ERREUR : Les paramètres doivent avoir le même nombre d'éléments !  \n");
             test=2;
          }
      }
break;
case 168:
#line 1582 "AnaSyntxMul.y"
	{nbOffset=0;}
break;
#line 4708 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
