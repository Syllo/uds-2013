#include <stdio.h>
#include <stdlib.h>

#define DIMENSION 2
#define SUB_CLUST(a) printf("  subgraph cluster_%d {\n  style=filled;\n  fillcolor=lightgrey;\n  label = \"nest %d\";\n",a,a);
#define DDV_ADD(i,j,x,y,s,t,e) indices[0]=i;\
                               indices[1]=j;\
                               memref[0]=x;\
                               memref[1]=y;\
                               ddv_table = append_table(ddv_table, s, indices, t, memref, e);
#define DDV_FUSE(i,j,x,y,s,t,e) indices[0]=i;\
                               indices[1]=j;\
                               memref[0]=x;\
                               memref[1]=y;\
                               ddv_table = DDV(ddv_table, s, indices, t, memref, e);

struct table
{
  char loop;
  int indices[DIMENSION];
  char name;
  int memref[DIMENSION];
  int ioflag;
  struct table *next;
};

void print_DDV(struct table *ddv_table)
{
  int i;
  while(ddv_table!=NULL)
  {
     printf("%c | ",(*ddv_table).loop);
     for(i=0;i<DIMENSION;i++) printf("%d | ",(*ddv_table).indices[i]);
     printf("%c | ",(*ddv_table).name);
     for(i=0;i<DIMENSION;i++) printf("%d | ",(*ddv_table).memref[i]);
     printf("%d\n",(*ddv_table).ioflag);
     ddv_table=(*ddv_table).next;
  }
scanf("%d\n",&i);
}

struct table * append_table(struct table *ddv_table, char dest, int *indices, char name, int *memref, int ioflag)
{
      int i;
      struct table *base;

      base = malloc(sizeof(struct table));
      (*base).next = ddv_table;
      (*base).ioflag = ioflag;
      (*base).loop = dest;
      (*base).name = name;
      for (i=0;i<DIMENSION;i++) {(*base).indices[i]=indices[i]; (*base).memref[i]=memref[i];}
      return(base);
}


int egal(int *memref1, int *memref2)
{
  int i;

  for (i=0;i<DIMENSION;i++)
    if (memref1[i]!=memref2[i]) return(0);
  return(1);
}


struct table * DDV(struct table *ddv_table, char dest, int *indices, char name, int *memref, int ioflag)
{
  int i;

  struct table *base;
  struct table *prev;

  prev = NULL;

  //printf("ENTREE DDV\n");

  // on ajoute dans la table
  base = malloc(sizeof(struct table));
  (*base).next = ddv_table;
  (*base).ioflag = ioflag;
  (*base).loop = dest;
  (*base).name = name;
  for (i=0;i<DIMENSION;i++) {(*base).indices[i]=indices[i]; (*base).memref[i]=memref[i];}
  
  if (ioflag==0) // read
  {
    //printf("ICI1\n");
    while (ddv_table!=NULL)
    {
      //printf("ICI2\n");

      if ( ((*ddv_table).name==name) && egal((*ddv_table).memref, memref)) // même ref ((*ddv_table).loop!=dest) &&
      {
        //printf("ICI1\n");
        if ((*ddv_table).ioflag==1) // write trouvé, flow-dep et fin
        {
          for (i=0;i<DIMENSION;i++) printf("%c%d",(*ddv_table).loop,(*ddv_table).indices[i]);
          printf(" -> ");
          for (i=0;i<DIMENSION;i++) printf("%c%d",dest,indices[i]);
          printf("\n");
          return(base); // fin fonction
        }
        /* else // on efface le read trouvé qui est inutile, rechainage
        {
          if (prev==NULL) {(*base).next=(*ddv_table).next,prev=base;}
          else (*prev).next=(*ddv_table).next;
          free(ddv_table);
          ddv_table = prev;
        }*/
      }
      prev = ddv_table;
      ddv_table = (*ddv_table).next;
    } // fin while
  }
  else // ioflag=1, write
  {
    //printf("ICI2\n");
    while (ddv_table!=NULL)
    {

      if ((*ddv_table).name==name && egal((*ddv_table).memref, memref)) // même ref ((*ddv_table).loop!=dest) && 
      {
        if ((*ddv_table).ioflag==1) // write trouvé, output-dep et fin
        {
          for (i=0;i<DIMENSION;i++) printf("%c%d",(*ddv_table).loop,(*ddv_table).indices[i]);
          printf(" -> ");
          for (i=0;i<DIMENSION;i++) printf("%c%d",dest,indices[i]);
          printf("\n");
          // on efface le write, rechainage
          if (prev==NULL) {(*base).next=(*ddv_table).next,prev=base;}
          else (*prev).next=(*ddv_table).next;
          free(ddv_table);
          return(base); // fin fonction
        }
        else // read trouvé, anti-dep
        {
          for (i=0;i<DIMENSION;i++) printf("%c%d",(*ddv_table).loop,(*ddv_table).indices[i]);
          printf(" -> ");
          for (i=0;i<DIMENSION;i++) printf("%c%d",dest,indices[i]);
          printf("\n");
          //on efface le read trouvé qui est devenu inutile, rechainage
          if (prev==NULL) {(*base).next=(*ddv_table).next,prev=base;}
          else (*prev).next=(*ddv_table).next;
          free(ddv_table);
          ddv_table = prev;
        }
      }
      prev = ddv_table;
      ddv_table = (*ddv_table).next;
    } // fin while
  } // fin if-else
  return(base);
}


