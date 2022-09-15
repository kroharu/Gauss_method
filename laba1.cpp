#include <stdio.h>
#include <math.h>

// void    matrix_multiplication(float matrix[3][4], float X[3])
// {
//     int     i = -1, j = -1;
//     float   rez[3] = {0,0,0};

//     while (++i < 3)
//     {
//         while (++j < 3)
//             rez[i] += matrix[i][j] * X[j];
//         j = -1;
//     }
//     i = -1;
//     while (++i < 3)
//         printf("rez = %.4f ", rez[i]);
//     printf("\n");
// }

float   matrix[3][4] = 
{
    {-2,2,-3,-14},
    {2,-1,3,12},
    {-3,3,2,-8}
};

// float   matrix_first[3][4] = 
// {
//     {1,-2,3,-6},
//     {-2,-3,-1,-14},
//     {3,-1,-3,9}
// };

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
    int     str = -1, col = 0;  //для контроля диагонали матрицы
    int     max;                //для обозначения строки с max элеменнтом для перестановки
    float   tmp, multiply;        //tmp для замены элементов строк, multiply для умножения вычитаемой строки на нужную цифру
    float   x1, x2, x3, X[3];

    //Вывод первоначальной матрицы
    printf("\nИзначальный вид матрицы:\n\n");
    print_matrix(matrix);

    //Прямой ход Гаусса
    while ((str < 2) && (col < 3))
    {
        //Поиск максимального по модулю значения в столбце
        max = find_max(matrix, str, col);
        str++;

        //Перестановка строк, чтобы максимальное значение было в нужной строке
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
        else
            printf("\nПерестановка строк не требуется\n");
    
        //Деление str строки на col элемент строки
        j = -1;
        tmp = matrix[str][col];
        while (++j < 4)
            matrix[str][j] /= tmp;

        //Вывод получившейся матрицы
        printf("\nПосле деления строки %d на %.4f:\n\n", str + 1, tmp);
        print_matrix(matrix);

        //Вычитание из последующих строк первой строки умноженной на их первые элементы строк
        i = str;
        j = col - 1;
        while (++i < 3)
        {
            multiply = matrix[i][col];
            while (++j < 4)
                matrix[i][j] -= matrix[str][j] * multiply;
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
    X[2] = matrix[str][col];
    X[1] = matrix[str - 1][col] - X[2] * matrix[str - 1][col - 1];
    X[0] = matrix[str - 2][col] - X[2] * matrix[str - 2][col - 1] - X[1] * matrix[str - 2][col - 2];
    printf("x3 = (%.4f)\n", matrix[str][col]);
    printf("x2 = (%.4f) - %.4f * (%.4f)\n", matrix[str - 1][col], X[2], matrix[str - 1][col - 1]);
    printf("x1 = (%.4f) - %.4f * (%.4f) - (%.4f) * (%.4f)\n\n", matrix[str - 2][col], X[2], matrix[str - 2][col - 1], X[1], matrix[str - 2][col - 2]);
    printf("\nОтвет:\n\n");
    printf("x1 = %.4f\n", X[0]);
    printf("x2 = %.4f\n", X[1]);
    printf("x3 = %.4f\n", X[2]);

    // matrix_multiplication(matrix_first, X);

    return (0);
}
