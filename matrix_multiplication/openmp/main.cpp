#include <QElapsedTimer>

#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int **a, **b, **c;

    int a_cols = qrand() % 1000, a_rows = qrand() % 1000;
    int b_cols = qrand() % 1000, b_rows = a_cols;

    int i, j, t;

    a = new int*[a_rows];
    b = new int*[b_rows];
    c = new int*[a_rows];

    for (i = 0; i < a_rows; i++)
    {
        a[i] = new int[a_cols];

        for (t = 0; t < a_cols; t++)
            a[i][t] = (qrand() % 500) - 250;
    }

    for (i = 0; i < b_rows; i++)
    {
        b[i] = new int[b_cols];

        for (t = 0; t < b_cols; t++)
            b[i][t] = (qrand() % 500) - 250;
    }

    for (i = 0; i < a_rows; i++)
        c[i] = new int[a_cols];

    printf("Matrices generated. Starting multiplication!\n");

    omp_set_dynamic(0);      // запретить библиотеке openmp менять число потоков во время исполнения
    omp_set_num_threads(10); // установить число потоков в 10

    QElapsedTimer timer;
    qint64 nsecs = 0;

    timer.start();

    printf("Serial calculation:");
    timer.restart();

    for (i = 0; i < a_rows; i++)
        for (t = 0; t < b_cols; t++)
            for (j = 0; j < b_rows; j++)
                c[i][t] += (a[i][j] * b[j][t]);

    nsecs = timer.nsecsElapsed();

    printf("%lld nsecs elapsed\n", nsecs);

    printf("OpenMP calculation:");
    timer.restart();

    // добуток матриць
    #pragma omp parallel shared(a, b, c) private(i, t, j)
    {
        #pragma omp for
        for (i = 0; i < a_rows; i++)
            for (t = 0; t < b_cols; t++)
                for (j = 0; j < b_rows; j++)
                    c[i][t] += (a[i][j] * b[j][t]);
    }

    nsecs = timer.nsecsElapsed();

    printf("%lld nsecs elapsed\n", nsecs);

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
