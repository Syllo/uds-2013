enum op_Arith { PLUS, MOIN, MUL,DIV };

typedef struct BlockFor BlockFor;
struct BlockFor
{   char *indiceRef;
    char *borneInf;
    char **offset;  // tableau des offsets pour voir si la compression est faisable ou non
    int nbOffset;
};

typedef struct InputClooG InputClooG;
struct InputClooG
{   GList * iterators;
    GList * parameters;
    int constante;
    int nbiterators;
    int nbParameters;
};


typedef struct InfoBlock InfoBlock;
struct InfoBlock
{   char *indiceRef;//exprimer l'ancien indice en fonction de l'indice de Reférence 
    char *garde;
    GSList * instr;//Une liste chainée
};


typedef struct InfoFor InfoFor;
struct InfoFor
{   char *indice;//Peut être je vais le modifier après. ça doit être un pointeur sur l'entrée correspondante dans la table de symboles
    char *type;
    char *opRel;
    char *bInf;
    char *bSup;
    int incr;
    int grain;
    char* offset;
    GSList * instr;//Une liste chainée
    InputClooG * bInfCloog;
    InputClooG * bSupCloog;
    InputClooG * offsetCloog;
};

// Pour chaque instruction je dois péciser à quelle position elle sera insérée (cas d'un nid de multifor imparfait)

typedef struct Instruc Instruc;
struct Instruc
{   char* instr;
    int index;
};

//Nom de l'inconnu et le coef correspondant

typedef struct Element Element;
struct Element
{   char * inconnu;
    int coef;
};
