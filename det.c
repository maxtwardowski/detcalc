#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double det(double ** matrix, int n);

int main() {
    int matrix_dim = 3;
    double ** matrix = (double **) malloc(matrix_dim * sizeof(double *));
    for (int i = 0; i < matrix_dim; i++)
        matrix[i] = malloc(matrix_dim * sizeof(double));

    matrix[0][0] = 1.344000;
    matrix[0][1]= 45.555000;
    matrix[0][2]= 54.330000;
    matrix[1][0]= 23.560000;
    matrix[1][1]= 48.999900;
    matrix[1][2]= 43.455550;
    matrix[2][0]= 1.000000;
    matrix[2][1]= 0.555556;
    matrix[2][2]= 3.999600;

    printf("The result is: %lf \n", det(matrix, matrix_dim));

    for (int i = 0; i < matrix_dim; i++)
        free(matrix[i]);
    free(matrix);
    return 0;
}

double det(double ** matrix, int n) {
    int i,j,k,row,col;
    double determinant = 0;

    if (n == 1)
        return **matrix;
    else if(n == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else {
        double ** Minor = (double **) malloc((n - 1) * sizeof(double *));
        for (int i = 0; i < n - 1; i++) {
            Minor[i] = (double *) malloc((n - 1) * sizeof(double));
            if(!Minor[i]) abort();
        }

        for (i = 0; i < n; i++) {
            row = 0, col = 0;
            for (j = 1 ; j < n ; j++) {
                for (k = 0 ; k < n ; k++) {
                    if (k != i) {
                        Minor[row][col] = matrix[j][k];
                        col++;
                        if (col > n - 2) {
                            row++;
                            col = 0;
                        }
                    }
                }
            }
            determinant += pow(-1, i) * (matrix[0][i] * det(Minor, n - 1));
        }
        for (int i = 0; i < n - 1; i++)
            free(Minor[i]);
        free(Minor);
        return determinant;
    }
}
