// """Example Usage of generate1sets"""

// #include <stdio.h>
// #include <stdlib.h>

// // Assuming the necessary headers and global variables (e.g., `absminfr`, `minfr`, etc.) are defined

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

//     // Define the tree root node
//     Node *root = createNode(); // Assuming `createNode` is a function that initializes a tree node

//     // Define variables for generate1sets
//     int *frequencies;   // Array to store frequencies of attributes
//     int *oldaddr;       // Array to map pruned attributes to their original indices
//     int *order;         // Array to map original indices to pruned indices
//     int special;        // Number of special attributes

//     // Set global parameters
//     absminfr = 10; // Example: Minimum frequency threshold
//     minfr = 0.01;  // Example: Minimum frequency as a fraction of total rows

//     // Call generate1sets
//     int num_frequent_attributes = generate1sets(data_matrix, root, &frequencies, &oldaddr, &order, &special);

//     // Print results
//     printf("Number of frequent attributes: %d\n", num_frequent_attributes);
//     printf("Number of special attributes: %d\n", special);

//     // Print frequencies of attributes
//     printf("Frequencies of attributes:\n");
//     for (int i = 0; i < max_attributes; i++) {
//         if (frequencies[i] > 0) {
//             printf("Attribute %d: %d\n", i, frequencies[i]);
//         }
//     }

//     // Free allocated memory
//     fclose(f);
//     for (int i = 0; i < num_rows; i++) {
//         free(data_matrix[i]);
//     }
//     free(data_matrix);
//     free(row_lengths);
//     free(frequencies);
//     free(oldaddr);
//     free(order);

//     return 0;
// }