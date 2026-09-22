/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-22
 *
 * NAME
 *   connectivity.c
 *
 * DESCRIPTION
 *   Algorithms for solving the connectivity problem -  QF QU WQU CWQU
 *   For each method count number of entry pairs and the number of links
 *
 * COMMENTS
 *   Code for public distribution
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#include "connectivity.h"

#define DEBUG 0

/******************************************************************************
 * quick_find()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Find algorithm
 *****************************************************************************/

void quick_find(int *id, int N, FILE * fp, int quietOut)
{
   int i, p, q, t;
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   unsigned long int numOpsFind = 0;
   unsigned long int numOpsUnion = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      /* do search first */
      numOpsFind+=2;
      if (id[p] == id[q]) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      numOpsUnion++; //para encontrar o t
      for (t = id[p], i = 0; i < N; i++) {
         numOpsUnion++;
         if (id[i] == t) {
            numOpsUnion+=2;
            id[i] = id[q];
         }
      }
      links_cnt++;
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QF: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("QF: %ld(F)+%ld(U) relevant accesses were performed (total: %ld)\n",
          numOpsFind, numOpsUnion, numOpsFind+numOpsUnion);

   return;
}


/******************************************************************************
 * quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Union algorithm
 *****************************************************************************/

void quick_union(int *id, int N, FILE * fp, int quietOut)
{

   int i, j, p, q;
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   long int numOpsFind = 0;
   long int numOpsUnion = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      i = p;
      j = q;

      /* do search first */
      numOpsFind++;
      while (i != id[i]) {
         numOpsFind++;
         i = id[i];
         numOpsFind++;
      }
      while (j != id[j]) {
         numOpsFind++;
         j = id[j];
         numOpsFind++;
      }
      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      numOpsUnion++;
      id[i] = j;
      numOpsUnion++;
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("QU: %ld(F)+%ld(U) relevant accesses were performed (total: %ld)\n",
          numOpsFind, numOpsUnion, numOpsFind+numOpsUnion);
}


/******************************************************************************
 * weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Weighted Quick Union algorithm
 *****************************************************************************/

void weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{

   int i, j, p, q;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
  unsigned long int numOpsFind = 0;
  unsigned long int numOpsUnion = 0;
  unsigned long int numOpsUnionBalance = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;

      /* do search first */
      numOpsFind++;
      for (i = p; i != id[i]; i = id[i]){
         numOpsFind+=2;
      }
      
      for (j = q; j != id[j]; j = id[j]){
         numOpsFind+=2;
      }

      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
         numOpsUnionBalance+=2;
      if (sz[i] < sz[j]) {
         numOpsUnion++;
         id[i] = j;
         numOpsUnionBalance+=3;
         sz[j] += sz[i];
      }
      else {
         numOpsUnion++;
         id[j] = i;
         numOpsUnionBalance+=2;
         sz[i] += sz[j];
      }
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("WQU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("WQU: %ld(F)+%ld(U)+%ld(W) relevant accesses were performed (total: %ld)\n",
          numOpsFind, numOpsUnion, numOpsUnionBalance,
          numOpsFind+numOpsUnion+numOpsUnionBalance);

   free(sz);
   return;
}


/******************************************************************************
 * compressed_weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Compressed Weighted Quick Union algorithm
 *****************************************************************************/

void compressed_weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{
   int i, j, p, q, t, x;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
  unsigned long int numOpsFind = 0;
  unsigned long int numOpsUnion = 0;
  unsigned long int numOpsUnionBalance = 0;
  unsigned long int numOpsUnionCompress = 0;

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;

      /* do search first */
      numOpsFind++;
      for (i = p; i != id[i]; i = id[i]){
         numOpsFind+=2;
      }

      for (j = q; j != id[j]; j = id[j]){
         numOpsFind+=2;
      }

      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      numOpsUnionBalance+=2;
      if (sz[i] < sz[j]) {
         numOpsUnion++;
         id[i] = j;
         numOpsUnionBalance+=2;
         sz[j] += sz[i];
         t = j;
      }
      else {
         numOpsUnion++;
         id[j] = i;
         numOpsUnionBalance+=2;
         sz[i] += sz[j];
         t = i;
      }
      links_cnt++;

      /* retrace the path and compress to the top */
      numOpsUnionCompress++;
      for (i = p; i != id[i]; i = x) {
         numOpsUnionCompress++;
         x = id[i];
         numOpsUnionCompress++;
         id[i] = t;
         numOpsUnionCompress++;
      }
      numOpsUnionCompress++;
      for (j = q; j != id[j]; j = x) {
         numOpsUnionCompress++;
         x = id[j];
         numOpsUnionCompress++;
         id[j] = t;
         numOpsUnionCompress++;
      }
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("CWQU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   printf("CWQU: %ld(F)+%ld(U)+%ld(W)+%ld(C) relevant accesses were performed (total: %ld)\n",
          numOpsFind, numOpsUnion, numOpsUnionBalance, numOpsUnionCompress,
          numOpsFind+numOpsUnion+numOpsUnionBalance+numOpsUnionCompress);

   free(sz);
   return;
}
