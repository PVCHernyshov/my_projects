#include <stdio.h>

void input_static(int matrix[][100], int* rows, int* cols);
void output_static(int matrix[][100], int rows, int cols);
void transpose_static(int matrix[][100], int* rows, int cols);
void find_max_static(int matrix[][100], int rows, int cols, int* max_val, int* max_r, int* max_c);

int main(void) {
    int rows, cols;
    int max_val, max_r = 0, max_c = 0;

    int matrix[100][100];

    input_static(matrix, &rows, &cols);
    if (rows == -1) {
        printf("n/a");
        return 0;
    }
    printf("\n");
    output_static(matrix, rows, cols);
    printf("\n\n");
    transpose_static(matrix, &rows, cols);
    if (rows == -1) {
        printf("n/a");
        return 0;
    }
    output_static(matrix, rows, cols);
    printf("\n");
    find_max_static(matrix, rows, cols, &max_val, &max_r, &max_c);
    printf("\n\n");
    printf("Val = %d\nr = %d c = %d\n", max_val, max_r, max_c);
    return 0;
}

void input_static(int matrix[][100], int* rows, int* cols) {
    if ((scanf("%d %d", rows, cols) != 2) || ((*rows <= 0 || *rows > 100) || (*cols <= 0 || *cols > 100))) {
        *rows = -1;
        return;
    }

    for (int r = 0; r < *rows; r++) {
        for (int c = 0; c < *cols; c++) {
            if (scanf("%d", &matrix[r][c]) != 1) {
                *rows = -1;
                return;
            }
        }
    }
}

void output_static(int matrix[][100], int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("%2d", matrix[r][c]);
            if (c < cols - 1) {
                printf(" ");
            }
        }
        if (r < rows - 1) {
            printf("\n");
        }
    }
}

void transpose_static(int matrix[][100], int* rows, int cols) {
    if (*rows != cols) {
        *rows = -1;
        return;
    }
    int sm = 0;
    for (int r = 0; r < *rows; r++) {
        for (int c = 0; c < r; c++) {
            sm = matrix[r][c];
            matrix[r][c] = matrix[c][r];
            matrix[c][r] = sm;
        }
    }
}

void find_max_static(int matrix[][100], int rows, int cols, int* max_val, int* max_r, int* max_c) {
    *max_val = matrix[0][0];
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (*max_val < matrix[r][c]) {
                *max_val = matrix[r][c];
                *max_r = r;
                *max_c = c;
            }
        }
    }
}