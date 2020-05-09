/* 
 * asst2 problem2
 * maxZhong
 * 8/5/2020
 * 
 * 0. no overflow (0 <= num <= 1000)
 * 
 * 1. no right dimension to multiple -> set to all zero
 *    then output should be ( 0 0 )
 * 
 * 2. input format and output format
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

# define MAXN 300

typedef struct Matrix_s {
  size_t R, C;
  int index[MAXN][MAXN];
} Matrix;

int readMatrix(FILE *f, Matrix *A) {
    // error handle
    if (f == NULL || A == NULL) {
        return -1;
    }

    if (fscanf(f, "%zu %zu", &A->R, &A->C) != 2) {
        return -1;
    }

    if (A->R >= MAXN && A->C >= MAXN) {
        return -1;
    }

    for (size_t i = 0; i < A->R; i++) {
        for (size_t j = 0; j < A->C; j++) {
            if (fscanf(f, "%d", &A->index[i][j]) != 1) {
                return -1;
            }
        }
    }

    // func ends in normal
    return 0;
}

void matrixMultiple(Matrix *A, Matrix *B, Matrix *C) {
    if (A == NULL || B == NULL || C == NULL)
        return;

    // multipled matrix need to column1 == row2
    if (A->C != B->R)
        return;

    C->R = A->R;
    C->C = B->C;

    for (size_t i = 0; i < C->R; ++i) {
        for (size_t j = 0; j < C->C; ++j) {
            for (size_t k = 0; k < A->C; ++k) {
                C->index[i][j] += A->index[i][k] * B->index[k][j];
            }
        }
    }
}

void printMatrix(Matrix *C) {
    if (C == NULL) {
        return;
    }

    printf("%zu %zu\n", C->R, C->C);

    for (size_t i = 0; i < C->R; i++) {
        for (size_t j = 0; j < C->C; j++) {
            // if (j == C->C - 1) {
            //     printf("%d\n", C->index[i][j]);
            //     break;
            // }
            printf("%d ", C->index[i][j]);
        }
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    // ./pro2 input_data
    if (argc != 2) {
        fprintf(stderr, "usage: ./pro2 testData\n");
        exit(EXIT_FAILURE);
    }
    
    // handle fopen error case
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    
    //init
    Matrix A, B, C;
    C.R = C.C = 0;
    if (readMatrix(f, &A) != 0) {
        fprintf(stderr, "errors: readMatrix\n");
        exit(EXIT_FAILURE);
    }
    if (readMatrix(f, &B) != 0) {
        fprintf(stderr, "errors: readMatrix\n");
        exit(EXIT_FAILURE);
    }

    matrixMultiple(&A, &B, &C);

    printMatrix(&C);

    // handle fclose error case
    if (fclose(f) != 0) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    return 0;
}
