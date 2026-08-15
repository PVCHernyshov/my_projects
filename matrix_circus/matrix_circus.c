#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input_number(int* num, const char* rowcol);
int safe_fgets(char* buf, int sibu);
int input_size_matrix(int* rows, int* cols, const char* row, const char* col);
int** create_matrix(int rows, int cols);
void free_matrix(int** matrix, int size);
int input_element(int* result, int sum, int count);
void buffer_clearing(char* buff);
int matrix_filling(int** matrix, int rows, int cols, int* err);
void print_matrix(int** matrix, int rows, int cols, int size);
int find_min(int** matrix, int rows, int cols);
int find_max(int** matrix, int rows, int cols);
int dinamic_size(int min, int max);

int main(void) {
    int rows = 0;
    int cols = 0;
    const char* row = "строк";
    const char* col = "столбцов";

    int err = input_size_matrix(&rows, &cols, row, col);
    if (err == -1) {
        printf("Операция ввода прервана.\n");
        return 1;
    }
    if (err == -2) {
        printf("Операция ввода отменена.\n");
        return 0;
    }

    int** matrix = create_matrix(rows, cols);

    if (matrix == NULL) return 1;

    int erro = 0;
    int erro2 = matrix_filling(matrix, rows, cols, &erro);
    if (erro == -1 || erro2 == -1) {
        printf("Операция ввода прервана.\n");
        free_matrix(matrix, rows);
        return 1;
    }
    if (erro == -2) {
        printf("Операция ввода отменена.\n");
        free_matrix(matrix, rows);
        return 0;
    }

    int min = find_min(matrix, rows, cols);
    int max = find_max(matrix, rows, cols);

    int size = dinamic_size(min, max);

    print_matrix(matrix, rows, cols, size);

    free_matrix(matrix, rows);
    return 0;
}

int input_size_matrix(int* rows, int* cols, const char* row, const char* col) {
    int err = input_number(rows, row);
    if (err != 0) {
        return err;
    }
    int err2 = input_number(cols, col);
    if (err2 != 0) {
        return err2;
    }
    return 0;
}

int input_number(int* num, const char* rowcol) {
    char buffer[64];
    while (1) {
        printf("Введите количество %s (от 1 до 100): ", rowcol);
        char sbr = 0;
        int err = safe_fgets(buffer, sizeof(buffer));
        if (err == -1) {
            return err;
        }
        int res = sscanf(buffer, "%d%c", num, &sbr);  // в первой версии был scanf
        if ((res == 2) && (*num > 0 && *num <= 100) && sbr == '\n') return 0;
        char input = 0;
        while (1) {
            printf("Введены не корректные данные. Хотите повторить ввод? (y/n): ");
            int err2 = safe_fgets(buffer, sizeof(buffer));
            if (err2 == -1) {
                return err2;
            }
            int res_in = sscanf(buffer, "%c", &input);
            if (res_in == 1 && (input == 'y' || input == 'Y')) break;
            if (res_in == 1 && (input == 'n' || input == 'N')) {
                return -2;
            }
        }
    }
    return 0;
}

int** create_matrix(int rows, int cols) {
    if ((rows <= 0 || rows > 100) || (cols <= 0 || cols > 100)) return NULL;
    int** m = NULL;
    m = malloc(rows * sizeof(int*));
    if (m == NULL) {
        return NULL;
    }
    for (int r = 0; r < rows; r++) {
        m[r] = calloc(cols, sizeof(int));
        if (m[r] == NULL) {
            free_matrix(m, r);
            return NULL;
        }
    }
    return m;
}

void free_matrix(int** matrix, int size) {
    for (int f = 0; f < size; f++) {
        free(matrix[f]);
    }
    free(matrix);
}

int safe_fgets(char* buf, int sibu) {
    if (fgets(buf, sibu, stdin) == NULL) {
        return -1;
    }
    buffer_clearing(buf);
    return 0;
}

int input_element(int* result, int sum, int count) {
    printf("Всего элементов: %d\n", sum);
    while (1) {
        printf("Введите элемент %d: ", count);
        char element[64];
        int err = safe_fgets(element, sizeof(element));
        if (err == -1) {
            return err;
        }
        char* endptr = NULL;
        errno = 0;
        long num = strtol(element, &endptr, 10);
        if ((endptr != element) && (*endptr == '\n') && (errno != ERANGE) &&
            (num >= INT_MIN && num <= INT_MAX)) {
            *result = num;
            return 0;
        }
        buffer_clearing(element);

        while (1) {
            printf("Введены некорректные данные, хотите повторить ввод? y/n: ");
            char answer[64];
            int err = safe_fgets(answer, sizeof(answer));
            if (err == -1) {
                return err;
            }
            char ans = 0;
            if (sscanf(answer, "%c", &ans) == 1 && (ans == 'N' || ans == 'n')) {
                return -2;
            } else if (ans == 'y' || ans == 'Y') {
                break;
            }
        }
    }
}

void buffer_clearing(char* buff) {
    size_t len = strlen(buff);
    if (len > 0 && buff[len - 1] != '\n') {
        int ch = 0;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}

int matrix_filling(int** matrix, int rows, int cols, int* err) {
    int sum_elem = rows * cols;
    int count = 1;
    if (err == NULL) {
        return -1;
    }
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            *err = input_element(&matrix[r][c], sum_elem, count);
            if (*err != 0) {
                return *err;
            }
            count++;
        }
    }
    return 0;
}

void print_matrix(int** matrix, int rows, int cols, int size) {
    int width = size;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("%*d", width, matrix[r][c]);
            if (c < cols - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int find_min(int** matrix, int rows, int cols) {
    int min = matrix[0][0];
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (min > matrix[r][c]) {
                min = matrix[r][c];
            }
        }
    }
    return min;
}
int find_max(int** matrix, int rows, int cols) {
    int max = matrix[0][0];
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (max < matrix[r][c]) {
                max = matrix[r][c];
            }
        }
    }
    return max;
}

int dinamic_size(int min, int max) {
    int size = 1;
    if (min == 0 && max == 0) {
        return size;
    }
    if (max < 0) {
        size = (int)floor(log10(abs(min))) + 2;
        return size;
    }
    if (min > 0) {
        size = (int)floor(log10(max)) + 1;
        return size;
    }
    min = abs(min);
    if (max > min) {
        size = (int)floor(log10(max)) + 1;
        return size;
    }
    size = (int)floor(log10(min)) + 2;
    return size;
}