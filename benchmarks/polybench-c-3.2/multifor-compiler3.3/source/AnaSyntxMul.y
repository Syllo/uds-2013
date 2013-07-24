/*****************************************************************************
*                                                                            *
*                       Multifor-compiler                                    * 
*                                                                            * 
*                                                                            *
*   Auteurs : Pr. Philippe CLAUSS & Imen FASSI                               *
*   Première version : Octobre 2012                                          *
*   Deuxième version : avril 2013                                            *
*   Troisième version : mai 2013                                             *
*   Description :                                                            * 
*   Ce code permet de vérifier la syntaxe d'un "multifor"                    *
*   et de le traduire en des "for" classiques                                *
*   en utilisant l'outil Polyédrique Cloog                                   *
*                                                                            *
*****************************************************************************/

%{// C declarations and includes
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

GList * parameters;// Besoin de ça pour la matrice contexte 
int nbParameters;

GList * operand =NULL; 
int lastOpCal=0; //dernier element évalué 
int test=0;
int nested=1;
int prem=0;
int testt=0;
int clee=0;
int deal = 1;
int gp=0;

// Les Données de CLOOG
CloogState *state;
CloogInput *input;
CloogOptions * options ;
CloogDomain * context;
CloogDomain * domain;
CloogUnionDomain *ud;
CloogMatrix *matrixCtxt;
int NbRows, NbColumns ;
struct clast_stmt *rootCloog;

%}

%union{
int nombre; 
char * chaine;}

// Yacc token and type declarations 

%token Fleche
%token ET
%token OU
%token BREAK
%token FOR
%token IF
%token ELSE
%token DO
%token WHILE
%token Switch
%token Case
%token Default
%token Multifor 
%token  Pouv
%token  Pferm
%token  Accouv
%token  Accferm
%token  OpAff
%token  Pvirg
%token  Dpoint
%token  Virg
%token  Plus
%token  Moin
%token  Div
%token Mod
%token  Mul
%token Ajout
%token Sous
%token DivAff
%token MulAff
%token Incr
%token Decr
%token <nombre> Entier
%token <chaine> Var
%token <chaine> OpRel
%token <chaine> CrochOuv
%token <chaine> CrochFerm
%token <chaine> texte
%token <chaine> NBRR


%left Moin Plus
%left Div Mul
%right MOINSU

%type <nombre> incVar 
%type <nombre> suite
%type <nombre> NegEntier
%type <chaine> bAffine
%type <chaine> Variable
%type <chaine> SuiteVar
%type <chaine> SuiteSuiteVar
%type <chaine> expression
%type <chaine> OP_ADD
%type <chaine> terme
%type <chaine> termeBA
%type <chaine> facteurBA
%type <chaine> suiteParamFonct
%type <chaine> paramFonct
%type <chaine> appelFonction
%type <chaine> exprArithTab
%type <chaine> typeInstruction
%type <chaine> SuiteVar2
%type <chaine> condIF
%type <chaine> controleIF
%type <chaine> blockInstr
%type <chaine> suiteInstructions2
%type <chaine> suiteControleIF
%type <chaine> suiteCondIF
%type <chaine> suiteSuiteCondIF
%type <chaine> controleWHILE
%type <chaine> controleDOWHILE
%type <chaine> controleFOR
%type <chaine> initFOR
%type <chaine> condFOR
%type <chaine> incrFOR
%type <chaine> opIncr
%type <chaine> exprArithTab2
%type <chaine> suiteOpIncr
%type <chaine> controleMULTIFOR
%type <chaine> affectmul
%type <chaine> compmul
%type <chaine> incrmtmul
%type <chaine> grainmul  
%type <chaine> offsetmul 
%type <chaine> suiteaffectmul
%type <chaine> suitecompmul
%type <chaine> suiteincrmtmul
%type <chaine> suitegrainmul
%type <chaine> suiteoffsetmul
%type <chaine> suiteInstructions3
%type <chaine> blockInstr2
%type <chaine> controleSwitch
%type <chaine> casSwitch   
%type <chaine> valeur
%type <chaine> suitecasSwitch
%type <chaine> declaration
%type <chaine> pointeur
%type <chaine> suiteDeclaration
%type <chaine> suiteDeclaration2
%type <chaine> typeInstruction2
%type <chaine> listeTab
%type <chaine> elementTab
%type <chaine> suiteListeTab
%type <chaine> suiteDecTab
%type <chaine> expression2

%start  mul

%% // Yacc Specification in the form of grammer rules like this :
   mul     :   Multifor Pouv init Pvirg comp Pvirg inc Pvirg grain Pvirg offset Pferm corps 
         ;

   corps   :   CropssansAcc  mul 
         |  Accouv block Accferm ResteProg  
         ;

   CropssansAcc :  {
      gp++;
      if(test==1)
      {  char* res="";//"Nombre d'éléments vérifié";
         if( nbInit !=nbOffset)
         {  nbErr++;
            res="ERREUR : Les paramètres doivent avoir le même nombre d'éléments !";
            printf("\n  %s  \n",res);
         }
         test=2; 
      }}
         ;

   block   :  mul { 
         //Mise à jour du père, du frère et de la table de pointeurs lesFor
         frere=frere->parent; // Le père devient FRERE
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
      | inst ResteProg2   {  
      nested=0;  
      while(gp>0)
      {
      // Mise à jour du père, du frère et de la table de pointeurs lesFor
         frere=frere->parent; // Le père devient FRERE
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
      //Mise à jour du père, du frère et de la table de pointeurs lesFor
         frere=frere->parent;  // Le père devient FRERE
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
         ;

   ResteProg : {deal=1;
       }
      | mul  
      | inst ResteProg  
         ;

   ResteProg2 : { deal=0; }
      | mul  
      |  inst ResteProg2 
         ;

   Variable  :   Var SuiteVar { 
      char* chain= NULL;
      chain= malloc(250);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s%s",$1,$2); 
      $$=chain;
      }
         ;

   SuiteVar    :    {$$="";  }
      | CrochOuv expression CrochFerm SuiteSuiteVar { 
      char* chain= NULL;
      chain= malloc(300);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"[%s]%s",$2,$4); 
      $$=chain;
 }
      | Fleche Variable  {  
      char* chain= NULL;
      chain= malloc(300);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"->%s",$2); 
      $$=chain;
 }

         ;

   SuiteSuiteVar    :    {$$="";  }
      | CrochOuv expression CrochFerm SuiteSuiteVar { 
      char* chain= NULL;
      chain= malloc(300);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"[%s]%s",$2,$4); 
      $$=chain;
}
         ;

   expression   :   expression Plus expression { 
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s+%s",$1,$3); 
      $$=chain; }
      | expression Moin expression {
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s-%s",$1,$3); 
      $$=chain; }
      | expression Mul expression {
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s*%s",$1,$3); 
      $$=chain; }  
      | expression Mod expression {
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s % %s",$1,$3); 
      $$=chain; }
      | expression Div expression {      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"%s/%s",$1,$3); 
      $$=chain; }
      | Pouv expression Pferm {
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"(%s)",$2); 
      $$=chain; }
      | Moin expression %prec MOINSU { 
      char* chain= NULL;
      chain= malloc(600);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"-%s",$2); 
      $$=chain;}
      | terme
         ;

   terme        :    Var SuiteVar2  {
        char* chain= NULL;
        chain= malloc(200);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",$1,$2); 
        $$=chain;
       }
      | Entier   { sprintf($$,"%s",$1); }
      | texte {$$=$1;}
      | NBRR {$$=$1;}
         ;

   NegEntier    :    Entier    {$$=atoi($1);}
      |Moin Entier    {$$=atoi($2)*-1;}
         ;

   suiteParamFonct   :     { $$="";}
      | Virg paramFonct   {
        char* chain= NULL;
        chain= malloc(200);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s",$2); 
        $$=chain;
       }
         ;

   SuiteVar2    :    {$$=""; }
      |CrochOuv expression CrochFerm SuiteSuiteVar { 
      char* chain= NULL;
      chain= malloc(200);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"[%s]%s",$2,$4); 
      $$=chain;
      }
      |Pouv paramFonct Pferm { 
      char* chain= NULL;
      chain= malloc(200);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"(%s)",$2); 
      $$=chain;
      }
     | Fleche Variable  {  
      char* chain= NULL;
      chain= malloc(200);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"->%s",$2); 
      $$=chain;
 }
         ;

   paramFonct   :    { $$="";}
      | expression suiteParamFonct  {
        char* chain= NULL;
        chain= malloc(400);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",$1,$2); 
        $$=chain;
       }
         ;

   appelFonction :     Var Pouv paramFonct Pferm Pvirg  { 
        char* chain= NULL;
        chain= malloc(800);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s(%s);",$1,$3); 
        $$=chain;
      }
         ;

   exprArithTab :     Variable suiteOpIncr Pvirg  { 
        char* chain= NULL;
        chain= malloc(1000);
        if (chain == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(chain,"%s%s;",$1,$2); 
        $$=chain;
       }
      | Incr Variable Pvirg {
        char* chain= NULL;
        chain= malloc(80);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"++%s;",$2); 
        $$=chain;
     }
      | Decr Variable Pvirg {
        char* chain= NULL;
        chain= malloc(80);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"--%s;",$2); 
        $$=chain; }

         ;

   suiteInstructions2        :     { $$="";}
      | typeInstruction suiteInstructions2  {
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"%s \n %s",$1,$2);
        $$=maInst;
      }
         ;

   blockInstr  :    typeInstruction { 
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"\n%s\n",$1);
        $$=maInst;
     }
      | Accouv typeInstruction suiteInstructions2 Accferm { 
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"{\n%s\n%s\n}\n",$2,$3);
        $$=maInst;
       }
         ;

   suiteSuiteCondIF :  {$$=""; }
      | ET  condIF  {
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain," && %s",$2); 
        $$=chain;
       }
      | OU  condIF {
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain," || %s",$2);
        $$=chain;
       }
         ;

   condIF    :    expression suiteCondIF suiteSuiteCondIF  {
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s%s",$1,$2,$3); 
        $$=chain;
       }
      | Pouv condIF Pferm suiteSuiteCondIF {
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"(%s)%s",$2,$4); 
        $$=chain;
       }
         ;

   suiteCondIF :   {$$="";}
      | OpRel expression    {
        char* chain= NULL;
        chain= malloc(300);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",$1,$2); 
        $$=chain;
     }
         ;

   suiteControleIF :   {$$=""; }
      | ELSE blockInstr    {
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"else %s",$2); 
        $$=chain;
     }
         ;

   controleIF    :  IF Pouv condIF Pferm blockInstr  suiteControleIF  {
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"if(%s)%s%s",$3,$5,$6); 
        $$=chain;
      }
         ;

   controleWHILE    :  WHILE Pouv condIF Pferm blockInstr  {
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"while(%s)%s",$3,$5); 
        $$=chain;
      }
         ;

   controleDOWHILE   :  DO blockInstr WHILE Pouv condIF Pferm Pvirg {
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"do%s \n while(%s);",$2,$5); 
        $$=chain;
      }
         ;

   exprArithTab2 :     Variable OpAff expression { 
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s=%s",$1,$3); 
        $$=chain;
      }
         ;

   initFOR  :  {$$=""; }
      | exprArithTab2 {$$=$1;}
         ;

   condFOR  :   {$$=""; }
      | condIF {$$=$1; }
         ;

   suiteOpIncr  : Incr {$$="++";}
      | Decr {$$="--"; }
      | Ajout expression {
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"+=%s",$2); 
        $$=chain;
      }
      | Sous expression {
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"-=%s",$2); 
        $$=chain;
      }
      | DivAff expression {
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"/=%s",$2); 
        $$=chain;
      }
      | MulAff expression {
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"*=%s",$2); 
        $$=chain;
      }
      | OpAff expression { 
        char* chain= NULL;
        chain= malloc(500);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"=%s",$2); 
        $$=chain;
       }
         ;

   opIncr  : Variable suiteOpIncr {
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",$1,$2); 
        $$=chain;
      }
      | Incr Variable {
        char* chain= NULL;
        chain= malloc(80);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"++%s",$2); 
        $$=chain;
     }
      | Decr Variable {
        char* chain= NULL;
        chain= malloc(80);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"--%s",$2); 
        $$=chain; }
         ;

   incrFOR  :   {$$="";}
      | opIncr {$$=$1;}
         ;

   controleFOR  : FOR Pouv initFOR Pvirg condFOR Pvirg incrFOR Pferm blockInstr {
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"for(%s;%s;%s)%s",$3,$5,$7,$9); 
        $$=chain;
      }
         ;

   suiteaffectmul  :  {$$="";}
      | Virg initFOR suiteaffectmul {
        char* chain= NULL;
        chain= malloc(300);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",$2,$3); 
        $$=chain;
      }
         ;

   affectmul  :  initFOR suiteaffectmul {
        char* chain= NULL;
        chain= malloc(400);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",$1,$2); 
        $$=chain;
      }
         ;

   suitecompmul  :  {$$="";}
      | Virg condFOR suitecompmul {
        char* chain= NULL;
        chain= malloc(300);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",$2,$3); 
        $$=chain;
      }
         ;

   compmul  :  condFOR suitecompmul {
        char* chain= NULL;
        chain= malloc(400);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",$1,$2); 
        $$=chain;
      }
         ;

   suiteincrmtmul  :  {$$="";}
      | Virg incrFOR suiteincrmtmul {
        char* chain= NULL;
        chain= malloc(300);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",$2,$3); 
        $$=chain;
      }
         ;

   incrmtmul  :  incrFOR suiteincrmtmul {
        char* chain= NULL;
        chain= malloc(400);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",$1,$2); 
        $$=chain;
      }
         ;

   suitegrainmul  :  {$$=""; }
      | Virg Entier suitegrainmul {
        char* chain= NULL;
        chain= malloc(150);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",$2,$3); 
        $$=chain;
      }
         ;

   grainmul  :  Entier suitegrainmul {
        char* chain= NULL;
        chain= malloc(200);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",$1,$2); 
        $$=chain;
      }
         ;

   suiteoffsetmul  :  {$$="";}
      | Virg Entier suiteoffsetmul {
        char* chain= NULL;
        chain= malloc(150);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",$2,$3); 
        $$=chain;
      }
         ;

   offsetmul  :  Entier suiteoffsetmul {
        char* chain= NULL;
        chain= malloc(200);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s",$1,$2); 
        $$=chain;
      }
         ;

   suiteInstructions3        :     { $$="";}
      | typeInstruction2 suiteInstructions3  {
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"%s \n %s",$1,$2);
        $$=maInst;
      }
         ;

   typeInstruction2 : Entier Dpoint typeInstruction {
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"\n%s:%s\n",$1,$3);
        $$=maInst;
     }
      | controleMULTIFOR {
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"\n%s",$1);
        $$=maInst;
     }
         ;

   blockInstr2  :  typeInstruction2  { $$=$1;}
      | Accouv typeInstruction2 suiteInstructions3 Accferm { 
        char* maInst= NULL;
        maInst= malloc(2000);
        if (maInst == NULL) 
        { printf("L'allocation mémoire a échoué !\n");
          exit(0);
        }
        sprintf(maInst,"{\n%s\n%s\n}\n",$2,$3);
        $$=maInst;
       }
         ;

   controleMULTIFOR  : Multifor Pouv affectmul Pvirg compmul Pvirg incrmtmul Pvirg grainmul Pvirg offsetmul Pferm blockInstr2 {
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"multifor(%s;%s;%s;%s;%s)%s",$3,$5,$7,$9,$11,$13); 
        $$=chain;
      }
         ; 

   valeur  : Var {$$=$1;}
      | Entier {$$=$1;}
         ; 

   suitecasSwitch : {$$="";}
      | Case valeur Dpoint blockInstr suitecasSwitch {
        char* chain= NULL;
        chain= malloc(1000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"case %s:%s\n%s",$2,$4,$5); 
        $$=chain;
      }
      | Default Dpoint blockInstr {
        char* chain= NULL;
        chain= malloc(1000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"default:%s",$3); 
        $$=chain;
      }
         ; 

   casSwitch  : Case valeur Dpoint blockInstr suitecasSwitch {
        char* chain= NULL;
        chain= malloc(1000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"case %s:%s\n%s",$2,$4,$5); 
        $$=chain;
      }
         ; 

   controleSwitch : Switch Pouv expression Pferm Accouv casSwitch Accferm {
        char* chain= NULL;
        chain= malloc(2000);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"switch(%s){\n%s\n}",$3,$6); 
        $$=chain;
      }
         ; 

   pointeur : {$$=""; }
      | Mul pointeur  {
        char* chain= NULL;
        chain= malloc(50);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"*%s",$2); 
        $$=chain;
      }
         ;

   elementTab : expression {$$=$1; }
      |  listeTab {$$=$1; }
         ;

   suiteListeTab : {$$=""; }
      | Virg elementTab suiteListeTab {
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,",%s%s",$2,$3); 
        $$=chain;
      }
         ;

   listeTab : Accouv elementTab suiteListeTab Accferm {
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"{%s%s}",$2,$3); 
        $$=chain;
      }
         ;

   suiteDeclaration2 : expression {$$=$1; }
      |  listeTab {$$=$1; }
         ;

   suiteDeclaration : {$$=""; }
      | OpAff suiteDeclaration2  {
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"=%s",$2); 
        $$=chain;
      }
         ;

   expression2 :  {$$=""; }
      |  expression {$$=$1; }
         ;

   suiteDecTab    :    {$$="";  }
      | CrochOuv expression2 CrochFerm suiteDecTab { 
      char* chain= NULL;
      chain= malloc(300);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"[%s]",$2); 
      $$=chain;
 }
         ;


   declaration : Var pointeur Var suiteDecTab suiteDeclaration Pvirg {
        char* chain= NULL;
        chain= malloc(600);
        if (chain == NULL) 
        {printf("L'allocation mémoire a échoué !\n");
        exit(0);
        }
        sprintf(chain,"%s%s %s%s%s;",$1,$2,$3,$4,$5); 
        $$=chain;
      }
         ;

   typeInstruction : appelFonction {$$=$1; }
      | exprArithTab {$$=$1; }
      | controleIF {$$=$1; }
      | controleWHILE  {$$=$1; }
      | controleDOWHILE  {$$=$1; }
      | controleFOR {$$=$1; }
      | controleMULTIFOR {$$=$1; }
      | controleSwitch {$$=$1; }
      | declaration {$$=$1; }
      | Pvirg {$$=";"; /* Instruction vide */ }
      | BREAK Pvirg  {$$="break;"; }
         ;

   lesInstructions        :    typeInstruction  {        
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
 // Vérifier auquel indice l'instruction se rattache
        sprintf(maInst,"%s",$1); // Vérifier auquel indice l'instruction se rattache
        uneIstr->instr =maInst;  
        //À quelle position l'instruction apparaît ?
        int indice; 
        if(testt==1)
           indice= g_node_n_children(pere)-1;
        else
           indice= g_node_n_children(frere)-1;
        uneIstr->index =indice; 
        MesssInstr=g_slist_prepend(MesssInstr,uneIstr); 
      }
      | Accouv typeInstruction suiteInstructions Accferm { 
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
 // Vérifier auquel indice l'instruction se rattache
        sprintf(maInst,"%s",$2); // Vérifier auquel indice l'instruction se rattache
        uneIstr->instr =maInst;  
        //À quelle position l'instruction apparaît ?
        int indice;
        if(testt==1)
           indice= g_node_n_children(pere)-1;
        else
           indice= g_node_n_children(frere)-1;
        uneIstr->index =indice;
        MesssInstr=g_slist_prepend(MesssInstr,uneIstr);
      }
         ;

   suiteInstructions :   {
        MesssInstr=NULL;
       }
      | typeInstruction suiteInstructions  {
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
 // Vérifier auquel indice l'instruction se rattache
        sprintf(maInst,"%s",$1); // Vérifier auquel indice l'instruction se rattache
        uneIstr->instr =maInst;  
        //À quelle position l'instruction apparaît ?
        int indice;
        if(testt==1)
           indice= g_node_n_children(pere)-1;
        else
           indice= g_node_n_children(frere)-1;
        uneIstr->index =indice;
        MesssInstr=g_slist_prepend(MesssInstr,uneIstr);
      }
         ;

   inst   :  Entier Dpoint lesInstructions { 
      if(test==1)
      {  char* res="";  // Nombre d'éléments vérifié
         if( nbInit !=nbOffset)
         {  nbErr++;
            res="ERREUR : Les paramètres doivent avoir le même nombre d'éléments !";
            printf("\n  %s  \n",res);
         }
         test=2;
      }
      //Si l'indice est inexistant
      nbInit=lesFor->len;
      int etiq=atoi($1);
      if (etiq>=nbInit)
      {  printf("ERREUR : Entier hors limite %d ! le multifor contient seulement %d indice !\n",etiq,nbInit);
         nbErr++;
      }
      else 
      //Je dois rajouter cette instruction à la liste chainée de l'indice correspondant 
      {   InfoFor* aux2= g_ptr_array_index(lesFor,etiq);
          aux2->instr=g_slist_concat(aux2->instr,MesssInstr);
      } }
         ;

   OP_ADD   : Plus {$$="+";}
      |Moin {$$="-";}
         ;

   facteurBA        :    terme  {
      sprintf($$,"%s",$1);
      Element * opElement= NULL;
      opElement= malloc(sizeof(Element));
      if (opElement == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
        exit(0);
      }
      if(isInteger($$,strlen($$))==1)
         {opElement->inconnu="";
          opElement->coef=atoi($$);
         }else
         {opElement->inconnu=$$;
          opElement->coef=1;
         }
         operand = g_list_append(operand, opElement);
      }
      | Moin terme %prec MOINSU { 
      Element * opElement= NULL;
      opElement= malloc(sizeof(Element));
      if (opElement == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      if(isInteger($2,strlen($2))==1)
      {
       opElement->inconnu="";
       opElement->coef=atoi($2)*-1;
      }else
      {
       opElement->inconnu=$2;
       opElement->coef=-1;
      }
      operand = g_list_append(operand, opElement);
      char* chain= NULL;
      chain= malloc(50);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0);
      }
      sprintf(chain,"-%s",$2); 
      $$=chain;
       }
         ;

   termeBA        :  termeBA Mul facteurBA   { 
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
      sprintf(chain,"%s*%s",$1,$3); 
      $$=chain;
        }
      | facteurBA { 
      char* chain= NULL;
      chain= malloc(50);
      if (chain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      sprintf(chain,"%s",$1); 
      $$=chain;
        }
         ;

   bAffine    : bAffine OP_ADD termeBA   { 
      int longList =  g_list_length (operand) ;
      Element * op1=  g_list_nth_data (operand, longList-1);
      Element * op2= g_list_nth_data (operand, longList-2);
      if (strcmp($2,"-")==0)
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
      sprintf(chhain,"%s%s%s",$1,$2,$3); 
      $$=chhain;
        }
      | termeBA {  
      char* chhain= NULL;
      chhain= malloc(50);
      if (chhain == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
       exit(0);
      }
      sprintf(chhain,"%s",$1); 
      $$=chhain;
      }
         ;

   init    :   initSuite Var OpAff bAffine   { 
      nbInit++; 
      //Nouvel indice, alors créer une nouvelle structure
      InfoFor* pUnFor= NULL;
      pUnFor= malloc(sizeof(InfoFor));
      if (pUnFor == NULL) 
      {printf("L'allocation mémoire a échoué !\n");
      exit(0); 
      }
      pUnFor->indice=$2;
      pUnFor->type ="int";
      pUnFor->bInf =$4;
      pUnFor->instr=NULL;
      g_ptr_array_add (lesFor, pUnFor);
      // Rajouter les infos à pUnFor->bInfCloog
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
         ;

   initSuite  :  {  
      if(test==1)
      {  char* res="";  // Nombre d'éléments vérifié";
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
      |  init Virg  { operand=NULL;}
         ;

   comp    :  compSuite  Var OpRel bAffine  {
      if(nbComp<nbInit){
      nbComp++; 
      InfoFor* aux2= g_ptr_array_index(lesFor,nbComp-1);
      aux2->bSup=$4;
      aux2->opRel =$3;
      // Rajouter les infos à pUnFor->bInfCloog
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
         ;

   compSuite    :    {nbComp=0; }
      |  comp Virg
         ;

   incVar : Var suite  {$$=$2;}
      |Decr Var        {$$=-1;}
      | Incr Var       {$$=1;}
         ;

   inc    :   incSuite incVar   {
     if(nbInc<nbInit){
      nbInc++; 
      InfoFor* aux2= g_ptr_array_index(lesFor,nbInc-1);
      aux2->incr=$2;
      if(aux2->incr==0){  printf("L'incrément ne peut pas être nul !\n");
        nbErr++;}}
      else {
            nbErr++;
            printf("\n  ERREUR : Les paramètres doivent avoir le même nombre d'éléments !  \n");
            test=2;
       }
      }
         ;

   suite    :    Incr  {$$=1;}
      |Decr            {$$=-1;}
      |Ajout NegEntier {$$=$2;}
      |Sous NegEntier  {$$=$2*-1;}
         ;

   incSuite    :    {nbInc=0;}
      |  inc Virg
         ;

   grain    :  grainSuite  NegEntier  { 
      if(nbGrain<nbInit){
      nbGrain++; 
      if($2<1){printf("Le grain doit être supérieur ou égal à 1 !\n");
      nbErr++;}
      InfoFor* aux2= g_ptr_array_index(lesFor,nbGrain-1);
      aux2->grain =$2;
      }
      else {
            nbErr++;
            printf("\n  ERREUR : Les paramètres doivent avoir le même nombre d'éléments !  \n");
            test=2;
      }
}
         ;

   grainSuite    :    {nbGrain=0;}
      |  grain Virg
         ;

   offset    :    offsetSuite bAffine  {
      if(test==0)
      {  char* res=""; //  Nombre d'éléments vérifié";
         if(nbInit!=nbComp || nbInit!=nbInc || nbInit!=nbGrain)
         {  nbErr++;
            res="ERREUR : Les paramètres doivent avoir le même nombre d'éléments !";
            printf("\n  %s  \n",res);
         }
         test=1;
      }
      if(nbOffset<nbInit) {
         nbOffset++; 
         if (isInteger ($2,strlen($2)))
         {   if(atoi($2)<0) {
               printf("ERREUR : L'offset doit être supérieur ou égal à 0 !\n");
               nbErr++;}
         }
         else
            create_Max_Min=1;
         InfoFor* aux2= g_ptr_array_index(lesFor,nbOffset-1);
         aux2->offset =$2; 

     // Rajouter les infos à aux2->offsetCloog
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
               //Initialiser la liste des instructions
               aux2->instr=NULL;
            } 
            if(root==NULL)
            {  //C'est le premier Multifor=> Créer la racine de l'arbre
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
            {    //Inserts a new GNode as the last child of the given parent
               if(nested==1)
               {  pere=frere; // printf("\n(nested==1)   ★ Le frère devient père ★\n");
                  prem=0;
               }  
               g_node_append_data(pere, lesFor);
               frere=g_node_last_child(pere);  // printf("\n★ MAJ : frere=g_node_last_child(pere); ★\n");
               nested=1;
               testt=0;
               // Faire le test : le neud fils ne peut pas avoir plus d'indice que le père
               GPtrArray* auxTest=pere->data;
               if(nbIncices > auxTest->len)
               {  printf("ERREUR : Le Multifor interne ne peut pas avoir plus d'indices que le multifor englobant !\n");
                  nbErr++;
               }
               else
               { majInputClooG( auxTest, lesFor);}//fin else
            }
         }// fin if
      }
     else {  nbErr++;
             printf("\n  ERREUR : Les paramètres doivent avoir le même nombre d'éléments !  \n");
             test=2;
          }
      }
         ;

   offsetSuite    :    {nbOffset=0;}
      |  offset Virg 
         ;

// Ne pas oublier de rajouter des Productions d'erreurs, pour que les messages d'erreurs soient plus clairs

%%

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
