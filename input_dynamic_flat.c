#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int* input_dynamic_flat(int* rows, int* cols);
void set_error(int* rows) { *rows = -1; }
void matrix_filling(int* matrix, int* rows, int cols);
void error_check(int* matrix, int rows);
void print_matrix(int* matrix, int rows, int cols, int size);
int find_max(int* matrix, int rows, int cols);
int find_min(int* matrix, int rows, int cols);

int main(void) {
    int rows = 0;
    int cols = 0;
    int max = 0;
    int size = 0;
    int* matrix = NULL;

    matrix = input_dynamic_flat(&rows, &cols);
    error_check(matrix, rows);

    matrix_filling(matrix, &rows, cols);
    error_check(matrix, rows);

    max = find_max(matrix, rows, cols);
    size = find_min(matrix, rows, cols);

    if (size < 0) {
        size = abs(size) * 10;
    }
    if (size < max) {
        size = max;
    }

    print_matrix(matrix, rows, cols, size);

    free(matrix);
    return 0;
}

int* input_dynamic_flat(int* rows, int* cols) {
    char sbr = 0;
    char sbc = 0;
    if ((scanf("%d%c%d%c", rows, &sbr, cols, &sbc) != 4) ||
        ((*rows <= 0 || *rows > 100) || (*cols <= 0 || *cols > 100) ||
         (sbr != ' ' && sbr != '\n' && sbr != '\t') || (sbc != ' ' && sbc != '\n' && sbc != '\t'))) {
        set_error(rows);
        return 0;
    }

    int* m = malloc(((*rows) * (*cols)) * sizeof(int));
    if (m == NULL) {
        set_error(rows);
        return 0;
    }

    return m;
}

void matrix_filling(int* matrix, int* rows, int cols) {
    char sb = 0;
    for (int r = 0; r < *rows; r++) {
        for (int c = 0; c < cols; c++) {
            if ((scanf("%d%c", &matrix[r * cols + c], &sb) != 2) || (sb != ' ' && sb != '\n' && sb != '\t')) {
                set_error(rows);
                return;
            }
        }
    }
}

void error_check(int* matrix, int rows) {
    if (rows == -1) {
        printf("n/a");
        free(matrix);
        exit(0);
    }
}

void print_matrix(int* matrix, int rows, int cols, int size) {
    int width = 0;
    if (size == 0) {
        width = 1;
    } else {
        width = floor(log10(size)) + 1;
    }
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("%*d", width, matrix[r * cols + c]);
            if (c < cols - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int find_max(int* matrix, int rows, int cols) {
    int max = matrix[0];
    for (int i = 1; i < rows * cols; i++) {
        if (max < matrix[i]) {
            max = matrix[i];
        }
    }
    return max;
}

int find_min(int* matrix, int rows, int cols) {
    int min = matrix[0];
    for (int i = 1; i < (rows * cols); i++) {
        if (min > matrix[i]) {
            min = matrix[i];
        }
    }
    return min;
}