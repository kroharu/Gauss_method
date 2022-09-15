#include <stdio.h>
#include <math.h>

// void    matrix_multiplication(float matrix[3][4], float X[3])
// {
//     int     i = -1, j = -1;

//     while ((++i < 3) && (++j < 4))
//     {
//         X[i] += matrix[i][j] * 
//     }
// }

float     matrix[3][4] = 
{
    {1,-2,3,-6},
    {-2,-3,-1,-14},
    {3,-1,-3,9}
};

void    print_matrix(float matrix[3][4])
{
    int i = -1;
    int j = -1;

    while (++i < 3)
    {
        while (++j < 4)
        {
            if (j == 3)
                printf("|\t"); 
            printf("%.4f\t", matrix[i][j]);
        }
        j = -1;
        printf("\n");
    }
}

int find_max(float matrix[3][4], int i, int j)
{
    int max;

    while (++i < 2)
        if (fabs(matrix[i + 1][j]) > fabs(matrix[i][j]))
            max = i + 1;
    return (max);
}

int     main()
{
    int     i = -1, j = -1;
    int     str = -1, col = 0; //для нахождения max в каждом из столбцов
    int     max;
    float   tmp;
    float   x1, x2, x3, X[3];

    //Вывод первоначальной матрицы
    printf("\nИзначальный вид матрицы:\n\n");
    print_matrix(matrix);

    //Основной цикл Гаусса
    while ((str < 2) && (col < 3))
    {
        //Поиск максимального по модулю значения в столбце
        max = find_max(matrix, str, col);
        str++;

        //Перестановка строк, чтобы максимальное значение было в первой строке
        if (max > 0)
        {
            while (++j < 4)
            {
                tmp = matrix[str][j];
                matrix[str][j] = matrix[max][j];
                matrix[max][j] = tmp;
            }
        //Вывод получившейся матрицы
        printf("\nВ результате перестановки строк:\n\n");
        print_matrix(matrix);
        }
    
        //Деление str строки на col элемент строки
        j = -1;
        tmp = matrix[str][col];
        while (++j < 4)
            matrix[str][j] /= tmp;

        //Вывод получившейся матрицы
        printf("\nПосле деления на %.4f:\n\n", tmp);
        print_matrix(matrix);

        //Вычитание из последующих строк первой строки умноженной на их первые элементы строк
        i = str;
        j = col - 1;
        while (++i < 3)
        {
            max = matrix[i][col];
            while (++j < 4)
                matrix[i][j] -= matrix[str][j] * max;
            j = col - 1;
        }

        //Вывод получившейся матрицы
        printf("\nПосле вычитания преобразованной строки %d из всех последующих:\n\n", str + 1);
        print_matrix(matrix);

        col++;
    }

    //Вывод итоговой матрицы
    printf("\nИтоговый вид матрицы:\n\n");
    print_matrix(matrix);




    printf("\nОбратный ход:\n\n");
    x3 = matrix[str][col];
    x2 = matrix[str - 1][col] - x3 * matrix[str - 1][col - 1];
    x1 = matrix[str - 2][col] - x3 * matrix[str - 2][col - 1] - x2 * matrix[str - 2][col - 2];
    printf("x3 = (%.4f)\n", matrix[str][col]);
    printf("x2 = (%.4f) - %.4f * (%.4f)\n", matrix[str - 1][col], x3, matrix[str - 1][col - 1]);
    printf("x1 = (%.4f) - %.4f * (%.4f) - (%.4f) * (%.4f)\n\n", matrix[str - 2][col], x3, matrix[str - 2][col - 1], x2, matrix[str - 2][col - 2]);
    printf("x3 = %.4f\n", x3);
    printf("x2 = %.4f\n", x2);
    printf("x1 = %.4f\n", x1);

    return (0);
}
