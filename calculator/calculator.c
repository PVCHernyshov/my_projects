#include <stdio.h>

void input_number(double* num, char op);
void calculation(double num_x, double num_y, char oper, double* res);

int main(void) {
    double x = 0;
    double y = 0;
    double res = 0;
    char oper = 0;

    do {
        oper = 0;

        input_number(&x, oper);

        while (oper == 0) {
            printf("Введите действие (+, -, *, /): ");
            if ((scanf(" %c", &oper) != 1) || (oper != '+' && oper != '-' && oper != '*' && oper != '/')) {
                printf("Вы ввели не допустимое значение, повторите ввод.\n");
                oper = 0;
            }
        }

        input_number(&y, oper);

        calculation(x, y, oper, &res);

        printf("Результат = %.2lf\n", res);
        printf("Хотите продолжить? (y/n)");
        scanf(" %c", &oper);
    } while (oper == 'y' || oper == 'Y');

    return 0;
}
void input_number(double* num, char op) {
    while (1) {
        printf("Введите число: ");
        if (scanf("%lf", num) == 1) {
            if (*num == 0 && op == '/'){printf("Деление на ноль!\n");continue;}
            break;
        } else {
            printf("Вы ввели не допустимое значение, повторите ввод.\n");
            while (getchar() != '\n');
        }
    }
}

void calculation(double num_x, double num_y, char oper, double* res) {
    switch (oper) {
        case '+':
            *res = num_x + num_y;
            break;
        case '-':
            *res = num_x - num_y;
            break;
        case '*':
            *res = num_x * num_y;
            break;
        case '/':
            *res = num_x / num_y;
            break;
    }
}