/* bitmatrice.c                                                         */
/* Read the graph from file to bit matrix                               */
/* muutettu 6.10.08; lis�tty initattrmatr */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmatrice.h"
/*#include "kasvit.h"*/

/*extern char* kasvit[];*/

/* vertailu bsearchille 
static int vertaa(const void *m1,const void *m2){
  return strcmp(*(char **)m1,*(char **)m2);
  }*/


void initmatr(FILE *f, bitvector ***matr, int n, int k) {

  char *row, *tmp;
  char *endp;
  int i, v;


  /* create matrix */

    if ((*matr=(bitvector**)malloc(n*sizeof(bitvector*)))==NULL)
      error(6);

  for (i=0; i<n; i++) {
    (*matr)[i]=bv_alloc(k);
    bv_clr((*matr)[i],k);
  }


  if ((row=(char*)malloc(6000))==NULL) error(6);

  /* read data */
  i=0;
  while (i<n) { 
    if (fgets(row, 6000, f)==NULL){
      printf("Cannot read row %d\n",i+1);
      error(5);
    }

    /* read first attr */
    v=strtol(row, &endp, 10);
   
    if (endp==row){
      printf("Non-integer value at row %d\n",i+1);
      error(5);
    }

    /*    printf("%d eka\n",v);*/
    tmp=endp;
    /* insert to matr */
    bv_setbit((*matr)[i],v); /* ol. ett� attr. numerointi alkaa 0:sta */

   while ((*tmp==',') || (*tmp==' '))
      tmp++; /* luetaan viela v�limerkit pois */

    /* luetaan loput */
    while (*tmp!='\n') {
      v=strtol(tmp, &endp, 10);

      if (endp==tmp){
	printf("Non-integer value at row %d\n",i+1);
	/*printf("rivi %d\n",i);*/
	error(5);
      }

      tmp=endp;
      while ((*tmp==',')||(*tmp==' ')) 
	tmp++; /* v�limerkit */
          /* insert to matr */
      bv_setbit((*matr)[i],v);
    }
    i++; /* next row */
  }
  free(row);

}

// ADDED
/* an array of pointers is created where each pointer points to an array- 
each row corresponds to a transaction and each transaction contains only the
attributes corresponding to it in the file */

void initattrmatr(FILE *f, bitvector ***matr, int **row_lengths, int n, int k) {
  char *row, *tmp;
  char *endp;
  int i, j, count;
  bitvector v;

  /* allocate memory for the array of pointers to rows */
  if ((*matr = (bitvector **)malloc(n * sizeof(bitvector *))) == NULL)
    error(6);
  
  /* allocate memory for the array of row lengths */
  if ((*row_lengths = (int *)malloc(n * sizeof(int))) == NULL)
      error(6);

  if ((row = (char *)malloc(6000)) == NULL)
    error(6);

  /* read data */
  i = 0;
  while (i < n) {
      if (fgets(row, 6000, f) == NULL) {
          printf("Cannot read row %d\n", i + 1);
          error(5);
      }

      /* count number of attributes in the row */
      count = 0;
      tmp = row;
      while (*tmp != '\0' && *tmp != '\n') {
          strtoull(tmp, &endp, 10); //  strtoull for unsigned long long int
          if (endp == tmp) {
              break;
          }
          count++;
          tmp = endp;
          while ((*tmp == ',') || (*tmp == ' '))
              tmp++;
      }

      /* allocate memory for the row (add 1 for null-terminator) */
      if (((*matr)[i] = (bitvector *)malloc((count + 1) * sizeof(bitvector))) == NULL)
         error(6);

      /* parse the row and store the attributes */
      j = 0;
      tmp = row;
      while (j < count) {
          v = strtoull(tmp, &endp, 10); // strtoull for unsigned long long int

          if (endp == tmp) {
              printf("Non-integer at row %d\n", i + 1);
              free((*matr)[i]);
              error(5);
          }

          if (v >= (bitvector)k) { 
              printf("Too large attr. value %llu at row %d\n", v, i + 1);
              free((*matr)[i]);
              error(5);
          }

          (*matr)[i][j] = v;
          tmp = endp;
          while ((*tmp == ',') || (*tmp == ' '))
              tmp++;
          j++;
      }

      (*matr)[i][j] = '\0'; // null-terminate the row 

  
      (*row_lengths)[i] = count; // store length of current row

      i++;
  }
  free(row);
}


void printdata(bitvector **matr, int row, int col){
  int i,j;

  printf("Data:\n");

  for (i=0; i<row; i++){
    for (j=0; j<col; j++)
      if (bv_tstbit(matr[i],j))
	  printf("%d ",j+1);
    printf("\n");
  }
}


/* print only attributes whose frequency is >=absminfr */
/* In matr, attributes are on rows, data rows on columns */
void printdata2(bitvector **matr, int *fr, int row, int col, int absminfr){
  int i,j;


  for (i=0; i<row; i++){
    for (j=0; j<col; j++)
      if ((fr[j]>=absminfr)&&(bv_tstbit(matr[j],i)))
	  printf("%d ",j+1);
    printf("\n");
  }
}


/* kun rivien ja sarakkeiden lkm parametreina */
void initmatr2(FILE *f, bitvector ***matr, int n1, int k1) {

  char *row, *tmp;
  char *endp;
  int i, v;


  /* create matrix */

    if ((*matr=(bitvector**)malloc(n1*sizeof(bitvector*)))==NULL)
      error(6);

  for (i=0; i<n1; i++) {
    (*matr)[i]=bv_alloc(k1);
    bv_clr((*matr)[i],k1);
  }


  if ((row=(char*)malloc(6000))==NULL) error(6);

  /* read data */
  i=0;
  while (i<n1) { 
    if (fgets(row, 6000, f)==NULL)
      error(5);
    /* read first attr */
    v=strtol(row, &endp, 10);
    if (endp==row)
      error(5);
    tmp=endp;
    /* insert to matr */
    bv_setbit((*matr)[i],v-1); /* ol. ett� attr. numerointi alkaa 1:st� */
    while ((*tmp==',') || (*tmp==' '))
      tmp++; /* luetaan viela v�limerkit pois */

    /* luetaan loput */
    while (*tmp!='\n') {
      v=strtol(tmp, &endp, 10);
      if (endp==tmp)
	error(5);
      tmp=endp;
      while ((*tmp==',')||(*tmp==' ')) 
	tmp++; /* v�limerkit */
          /* insert to matr */
      bv_setbit((*matr)[i],v-1);
    }
    i++; /* next row */
  }
  free(row);
}


void freematr(bitvector **matr,int n1){
  int i;

  if (matr!=NULL){
    for (i=0; i<n1; i++)
      if (matr[i]!=NULL)
	bv_free(matr[i]);
    free(matr);
  }

}

/* average transaction length */
float avgtlen(bitvector **matr,int n1, int k1){
  int i,j;
  int len=0;
  int sum=0;

  for (i=0;i<n1;i++){
    len=0;
    for (j=0;j<k1;j++){
      if (bv_tstbit(matr[j],i))
	len++;
    }
  sum+=len;
  }
  return ((float)sum)/n1;
}

/* Data luku, kun nimi�, jotka l�ytyv�t taulukosta kasvit.h 
void readnames(FILE *f,bitvector ***matr,int n,int k){

  char *row; 
  char *tmp;
  int i;
  char **v; 
  int posit;
  char *kasvi;

    if ((*matr=(bitvector**)malloc(n*sizeof(bitvector*)))==NULL)
      error(6);

  for (i=0; i<n; i++) {
    (*matr)[i]=bv_alloc(k);
    bv_clr((*matr)[i],k);
  }


  if ((row=(char*)malloc(6000))==NULL) error(6);

  i=0;
  while (i<n) { 
    if (fgets(row, 6000, f)==NULL)
      error(5);

    kasvi=strtok_r(row,",\n",&tmp);
    if ((v=bsearch(&kasvi,kasvit,k,sizeof(char*),vertaa))==NULL){
      printf("Unknown item: %s\n",kasvi);
      error(5);
    }
    posit=v-kasvit;


    bv_setbit((*matr)[i],posit); 

    while ((kasvi=strtok_r(NULL,",\n",&tmp))!=NULL){
      if ((v=bsearch(&kasvi,kasvit,k,sizeof(char*),vertaa))==NULL){
	printf("Unknown item: %s\n",kasvi);
	error(5);
      }
      posit=v-kasvit;

      bv_setbit((*matr)[i],posit);
    }
    i++; 
  }
  free(row);
  }*/



