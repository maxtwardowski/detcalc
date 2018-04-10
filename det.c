#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

double determinant(double ** matrix, int matrix_dim);

int main() {

    double * rawinput = (double *) calloc(0, sizeof(double));
    double current;
    int itemcounter = 0;
    while (scanf("%lf", &current) != EOF) {
        itemcounter++;
        rawinput = (double *) realloc(rawinput, itemcounter * sizeof(double));
        rawinput[itemcounter - 1] = current;
    }

    //Renctangularity check
    int calculated_dim = sqrt(itemcounter - 1);
    if (pow(calculated_dim, 2) == itemcounter - 1)
        printf("The matrix is rectangular\n");
    else
        abort();

    int matrix_dim = rawinput[0];

    double ** matrix = (double **) malloc(matrix_dim * sizeof(double *));
    for (int i = 0; i < matrix_dim; i++)
        matrix[i] = malloc(matrix_dim * sizeof(double));
    for (int i = 0; i < matrix_dim; i++)
        for (int j = 0; j < matrix_dim; j++)
            matrix[i][j] = rawinput[j + matrix_dim * i + 1];

    printf("The result is: %lf \n", determinant(matrix, matrix_dim));

    for (int expansionrow = 0; expansionrow < matrix_dim; expansionrow++)
        free(matrix[expansionrow]);
    free(matrix);
    free(rawinput);
    return 0;
}

double determinant(double ** matrix, int matrix_dim) {
    int expansionrow, tocopyrow, tocopycol, minorrow, minorcol;
    double finalvalue = 0;

    if (matrix_dim == 1)
        return **matrix;
    else if(matrix_dim == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else {
        double ** expansion_matrix = (double **) malloc((matrix_dim - 1) * sizeof(double *));
        for (int expansionrow = 0; expansionrow < matrix_dim - 1; expansionrow++)
            expansion_matrix[expansionrow] = (double *) malloc((matrix_dim - 1) * sizeof(double));

        for (expansionrow = 0; expansionrow < matrix_dim; expansionrow++) {
            minorrow = 0, minorcol = 0;
            for (tocopyrow = 1; tocopyrow < matrix_dim; tocopyrow++) {
                for (tocopycol = 0; tocopycol < matrix_dim; tocopycol++) {
                    if (tocopycol != expansionrow) {
                        expansion_matrix[minorrow][minorcol] = matrix[tocopyrow][tocopycol];
                        minorcol++;
                        if (minorcol > matrix_dim - 2) {
                            minorrow++;
                            minorcol = 0;
                        }
                    }
                }
            }
            finalvalue += pow(-1, expansionrow) * (matrix[0][expansionrow] * determinant(expansion_matrix, matrix_dim - 1));
        }
        for (int expansionrow = 0; expansionrow < matrix_dim - 1; expansionrow++)
            free(expansion_matrix[expansionrow]);
        free(expansion_matrix);
        return finalvalue;
    }
}
