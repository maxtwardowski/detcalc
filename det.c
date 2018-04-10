#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double det(double ** matrix, int matrix_dim);

int main() {
    int matrix_dim;
    scanf("%d", &matrix_dim);

    double ** matrix = (double **) malloc(matrix_dim * sizeof(double *));
    for (int expansionrow = 0; expansionrow < matrix_dim; expansionrow++)
        matrix[expansionrow] = malloc(matrix_dim * sizeof(double));
    for (int expansionrow = 0; expansionrow < matrix_dim; expansionrow++)
        for (int j = 0; j < matrix_dim; j++)
            scanf("%lf", &matrix[expansionrow][j]);

    printf("The result is: %lf \n", det(matrix, matrix_dim));

    for (int expansionrow = 0; expansionrow < matrix_dim; expansionrow++)
        free(matrix[expansionrow]);
    free(matrix);
    return 0;
}

double det(double ** matrix, int matrix_dim) {
    int expansionrow, tocopyrow, tocopycol, minorrow, minorcol;
    double determinant = 0;

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
            determinant += pow(-1, expansionrow) * (matrix[0][expansionrow] * det(expansion_matrix, matrix_dim - 1));
        }
        for (int expansionrow = 0; expansionrow < matrix_dim - 1; expansionrow++)
            free(expansion_matrix[expansionrow]);
        free(expansion_matrix);
        return determinant;
    }
}
