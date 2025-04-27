// //#include "ibitvector.h"
// #include "error.c"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "bitmatrice.h"


// void initattrmatr(FILE *f, bitvector ***matr, int **row_lengths, int n, int k) {
//     char *row, *tmp;
//     char *endp;
//     int i, j, count;
//     bitvector v;

//     /* Allocate memory for the array of pointers to rows */
//     if ((*matr = (bitvector **)malloc(n * sizeof(bitvector *))) == NULL)
//       error(6);
//       //printf("%s","m");
    
//     /* Allocate memory for the array of row lengths */
//     if ((*row_lengths = (int *)malloc(n * sizeof(int))) == NULL)
//         error(6);

//     if ((row = (char *)malloc(6000)) == NULL)
//       error(6);

//     /* Read data */
//     i = 0;
//     while (i < n) {
//         if (fgets(row, 6000, f) == NULL) {
//             printf("Cannot read row %d\n", i + 1);
//             error(5);
//         }

//         /* Count the number of attributes in the row */
//         count = 0;
//         tmp = row;
//         while (*tmp != '\0' && *tmp != '\n') {
//             strtoull(tmp, &endp, 10); // Use strtoull for unsigned long long int
//             if (endp == tmp) {
//                 break; // or handle the error as you see fit
//             }
//             count++;
//             tmp = endp;
//             while ((*tmp == ',') || (*tmp == ' '))
//                 tmp++;
//         }

//         /* Allocate memory for the row (add 1 for null-terminator) */
//         if (((*matr)[i] = (bitvector *)malloc((count + 1) * sizeof(bitvector))) == NULL)
//            error(6);

//         /* Parse the row and store the attributes */
//         j = 0;
//         tmp = row;
//         while (j < count) {
//             v = strtoull(tmp, &endp, 10); // Use strtoull for unsigned long long int

//             if (endp == tmp) {
//                 printf("Non-integer at row %d\n", i + 1);
//                 free((*matr)[i]);
//                 error(5);
//             }

//             if (v >= (bitvector)k) { // Cast k to bitvector for comparison
//                 printf("Too large attr. value %llu at row %d\n", v, i + 1);
//                 free((*matr)[i]);
//                 error(5);
//             }

//             (*matr)[i][j] = v;
//             tmp = endp;
//             while ((*tmp == ',') || (*tmp == ' '))
//                 tmp++;
//             j++;
//         }

//         /* Null-terminate the row */
//         (*matr)[i][j] = '\0';

//         /* Store the length of the current row */
//         (*row_lengths)[i] = count;

//         i++;
//     }
//     free(row);
// }

// #include <stdbool.h>

// int binary_search(bitvector *row, int len, bitvector target) {
//     int left = 0, right = len - 1;
//     while (left <= right) {
//         int mid = left + (right - left) / 2;
//         if (row[mid] == target) {
//             return 1; // Found the target
//         } else if (row[mid] < target) {
//             left = mid + 1;
//         } else {
//             right = mid - 1;
//         }
//     }
//     return 0; // Target not found
// }

// int frset(int *set, int len, bitvector **amatr, int *row_lengths, int n) {
//     int i, fr = 0;

//     if (len < 1) return 0;

//     /* Iterate through each data row in amatr */
//     for (i = 0; i < n; i++) {
//         int start = 0; // index of row from which to start searching
//         int match = 1; // Assume all attributes in the set are present in the current row

//         /* Check if all attributes in the set are present in the current row */
//         for (int j = 0; j < len; j++) {
//             /* Use binary search to check for the presence of set[j] in the current row */
//             if (!binary_search(amatr[i], row_lengths[i], set[j])) {
//                 match = 0; // If any attribute is missing, set match to 0
//                 break;
//             }
//         }

//         if (match) {
//             fr++; // Increment frequency if all attributes in the set are found in the row
//         }
//     }

//     return fr;
// }


// int generate1sets(bitvector** amatr, Node *t, int **fr, int **oldaddr, int **order, int *special) {
//     int i, j, min, position;
//     Node* p;
//     int ok, next;
//     int* tmp;
//     int nol = 0; // Number of attributes to be removed

//     (*special) = 0; // Number of special attributes
//     if ((specialattr = (int*)malloc(k * sizeof(int))) == NULL)
//         error(6);

//     if ((tmp = (int*)malloc(k * sizeof(int))) == NULL)
//         error(6);

//     for (i = 0; i < k; i++) {
//         tmp[i] = 0;
//         specialattr[i] = 0;
//     }

//     if (((*fr) = (int*)malloc(k * sizeof(int))) == NULL)
//         error(6);

//     for (i = 0; i < k; i++)
//         (*fr)[i] = 0;

//     // Count frequencies of single attributes
//     for (i = 0; i < n; i++) { // Iterate over transactions
//         for (j = 0; amatr[i][j] != '\0'; j++) { // Iterate over attributes in the transaction
//             (*fr)[amatr[i][j]]++;
//         }
//     }

//     // Prune attributes if their frequency is below the threshold or if they appear in all transactions
//     for (i = 0; i < k; i++) {
//         if (((*fr)[i] < absminfr) || ((*fr)[i] == n)) {
//             nol++;
//             (*fr)[i] = 0;
//         } else if (n - (*fr)[i] < absminfr) {
//             (*special)++;
//             specialattr[i] = 1;
//         }
//         tmp[i] = (*fr)[i];
//     }

//     tim2=clock();
//     tottim+=(double)(tim2-tim1);

//     printf("Removing %d attributes (P(A)<%.6f=minfr or P(A)=1), left %d attributes\n",nol,minfr,k-nol);

//     printf("Data matrix takes %d bits (%.1f MB) space; freed %d bits (%.1f MB)\n",n*(k-nol),n*(((float)k)-nol)/(8.0*1024.0*1024.0),n*nol,n*((float)nol)/(8.0*1024.0*1024.0));


//     tim1=clock();

//     // Allocate and initialize oldaddr and order arrays
//     if (((*oldaddr) = (int*)malloc((k - nol) * sizeof(int))) == NULL)
//         error(6);
//     if (((*order) = (int*)malloc(k * sizeof(int))) == NULL)
//         error(6);

//     for (i = 0; i < (k - nol); i++) {
//         (*oldaddr)[i] = -1;
//     }

//     for (i = 0; i < k; i++) {
//         (*order)[i] = -1;
//     }

//     // Add attributes in the order of their frequency
//     ok = 0;
//     next = 0;
//     while (!ok) {
//         min = n;
//         position = -1;
//         for (i = k - 1; i >= 0; i--) { // Find the next smallest attribute
//             if ((tmp[i] > 0) && (tmp[i] < min)) {
//                 min = tmp[i];
//                 position = i;
//             }
//         }
//         if (position == -1) {
//             break; // All attributes added
//         }

//         (*oldaddr)[next] = position;
//         (*order)[position] = next;
//         next++;
//         tmp[position] = 0; // Remove attribute
//     }

//     // Add attributes to the tree in ascending order
//     for (i = 0; i < k - nol; i++) {
//         p = addChild(t, (*oldaddr)[i], *order);
//         p->data->fr = (*fr)[(*oldaddr)[i]];
//         initbestandpossible(p, (*fr), (*oldaddr), (*order), k - nol);
//     }

//     free(tmp);

//     return k - nol;
// }


// int main() {
//     FILE *f = fopen("mushroom.dat", "r"); // Replace "mushroom.dat" with your file
//     if (f == NULL) {
//         printf("Error opening file\n");
//         return 1;
//     }

//     bitvector **data_matrix;
//     int *row_lengths;
//     int num_rows = 8124; // Replace with the actual number of rows in your data
//     int max_attributes = 124; // Replace with a reasonable estimate of the maximum attribute value

//     // Initialize the attribute matrix and row lengths
//     initattrmatr(f, &data_matrix, &row_lengths, num_rows, max_attributes);

//     // // Print the data matrix for debugging
//     // for (int i = 0; i < num_rows; i++) {
//     //     for (int j = 0; j < row_lengths[i]; j++) {
//     //         printf("%llu ", data_matrix[i][j]);
//     //     }
//     //     printf("\n");
//     // }
//     // printf("\n");

//     // Example usage: calculate the frequency of a set of attributes
//     int set[] = {48}; // Example set of attributes
//     int len = sizeof(set) / sizeof(set[0]);
//     int frequency = frset(set, len, data_matrix, row_lengths, num_rows);
//     printf("Frequency of the set: %d\n", frequency);

//     fclose(f);

//     // Free the allocated memory
//     for (int i = 0; i < num_rows; i++) {
//         free(data_matrix[i]);
//     }
//     free(data_matrix);
//     free(row_lengths);

//     return 0;
// }
