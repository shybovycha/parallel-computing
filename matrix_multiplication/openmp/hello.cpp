#include <stdio.h>
#include <omp.h>

#define N 100

int main(int argc, char *argv[])
{
    int a[2][3] = {{1, 2, 3}, {2, -1, 2}},
            b[3][3] = {{3, 2, 1}, {1, 3, -2}, {2, 4, 2}},
            **c = new int*[2];

    c[0] = new int[3];
    c[1] = new int[3];

    omp_set_dynamic(0);      // запретить библиотеке openmp менять число потоков во время исполнения
    omp_set_num_threads(2); // установить число потоков в 10

    int i, j, t;

    // добуток матриць
    #pragma omp parallel shared(a, b, c) private(i, t, j)
    {
        #pragma omp for
        for (i = 0; i < 2; i++)
            for (t = 0; t < 3; t++)
                for (j = 0; j < 3; j++)
                    c[i][j] += (a[i][j] * b[t][j]);
    }

    for (i = 0; i < 2; i++)
    {
        for (t = 0; t < 3; t++)
        {
            printf("%d\t", c[i][t]);
        }

        printf("\n");
    }

    return 0;
}

