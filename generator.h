#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n3 0
#define n4 4


int rand_int(int min, int max){
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

float rand_float(int max){
    return ((float)rand()/(float)(RAND_MAX)) * max;
}

int** create_2Darray(int size){
    int **A = (int **)malloc(size * sizeof(int *));
    for(int i = 0; i < size; i++){
        A[i] = (int *)calloc(size, sizeof(int));
    }
    return A;
}

int** create_xy_array(int size1, int size2){
    int **A = (int **)malloc(size1 * sizeof(int *));
    for(int i = 0; i < size1; i++){
        A[i] = (int *)calloc(size2, sizeof(int));
    }
    return A;
}

void print_2Darray(int** A, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (A[i][j] > 9){
                printf("%d, ", A[i][j]);
            } else{
                printf("%d,  ", A[i][j]);
            }
        }
        printf("\n");
    }
}

int** get_matrix(int size, double k){
    int **A = create_2Darray(size);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            A[i][j] = k * rand_int(0, 2);
            if (A[i][j] < 1.0){
                A[i][j] = 0;
            } else {
                A[i][j] = 1;
            }
        }
    }
    return A;
}

int** get_Wt_matrix(int** A, int size){
    int **res = create_2Darray(size);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            res[i][j] = A[i][j] * roundf(10 * rand_float(2));
        }
    }
    return res;
}

