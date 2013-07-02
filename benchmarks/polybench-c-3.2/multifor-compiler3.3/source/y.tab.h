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
extern YYSTYPE yylval;
