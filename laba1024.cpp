#include <stdio.h>
#include <iostream> 
#include <ctime> 
#include <stdlib.h>

// float    *matrix_multiplication(float matrix[1024][1025], float X[1024])
// {
//     int     i = -1, j = -1;
//     float   rez[1024];

//     while (++i < 1024)
//     {
//         while (++j < 1024)
//             rez[i] += matrix[i][j] * X[j];
//         j = -1;
//     }
//     i = -1;
// }

int find_max(double **matrix, int i, int j)
{
    int max;

    while (++i < 99)
        if (matrix[i + 1][j] > matrix[i][j])
            max = i + 1;
    return (max);
}

int     main()
{
    int     i = -1, j = -1;
    int     str = -1, col = 0;  //для контроля диагонали матрицы
    int     max;                //для обозначения строки с max элеменнтом для перестановки
    double   tmp, multiply;      //tmp для замены элементов строк, multiply для умножения вычитаемой строки на нужную цифру
    double   X[100], x1024, rez[100];

    srand(time(NULL));

    //Инициализируем матрицу 1024х1025
    double **matrix;
    matrix = new double*[100];
    while (++i < 100)
        matrix[i] = new double[101];
    printf("\nМатрица инициализирована\n");
    
    //Заполняем матрицу случайными числами
    while (++i < 100)
        while (++j < 101)
            matrix[i][j] = rand() % 100;
    printf("\nРандомная матрица заполнена\n");

    i = -1;
    j = -1;
    while (++i < 100)
    {
        while (++j < 101)
            printf("%.4f ", matrix[i][j]);
        printf("\n");
    }
    
    //Заполняем матрицу решений от 1 до 1024
    i = -1;
    while (++i < 100)
        X[i] = i + 1;
    printf("\nМатрица решений заполнена\n");

    //Заполняем последний столбец рандомной матрицы
    i = -1;
    while (++i < 100)
    {
        while (++j < 100)
            rez[i] += matrix[i][j] * X[j];
        printf("rez[%d] = %.4f\n", i, rez[i]);
        j = -1;
    }
    while (++j < 100)
        matrix[j][100] = rez[j];
    printf("\nРандомная матрица заполнена ответами\n\n");
    
    //Прямой ход Гаусса
    while ((str < 99) && (col < 100))
    {
        //Поиск максимального по модулю значения в столбце
        max = find_max(matrix, str, col);
        str++;

        //Перестановка строк, чтобы максимальное значение было в нужной строке
        if (max > 0 && max < 100)
        {
            while (++j < 101)
            {
                tmp = matrix[str][j];
                matrix[str][j] = matrix[max][j];
                matrix[max][j] = tmp;
            }
        }
    
        //Деление str строки на col элемент строки
        j = -1;
        tmp = matrix[str][col];
        while (++j < 101)
            matrix[str][j] /= tmp;

        //Вычитание из последующих строк первой строки умноженной на их первые элементы строк
        i = str;
        j = col - 1;
        while (++i < 100)
        {
            multiply = matrix[i][col];
            while (++j < 101)
                matrix[i][j] -= matrix[str][j] * multiply;
            j = col - 1;
        }

        col++;
    }

    x1024 = matrix[str][col];
    printf("Ответ: x1024 = %.4f\n", x1024);
}