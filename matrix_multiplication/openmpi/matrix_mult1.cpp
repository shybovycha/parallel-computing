#define N 512
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <sys/time.h>

void print_results(char *prompt, float a[N][N]);

int main(int argc, char *argv[]) {
  int size, rank, blksz, i, j, k;
  float a[N][N], b[N][N], c[N][N];
  char *usage = "Usage: %s file\n";
  float row[N][N], col[N][N];
  FILE *fd;
  int portion, lowerbound, upperbound;
  double elapsed_time, start_time, end_time;
  struct timeval tv1, tv2;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  blksz = (int) ceil((double) N / size);
  /*
  if (argc < 2) {
      fprintf (stderr, usage, argv[0]);
      return -1;
  }
  if ((fd = fopen(argv[1], "r")) == NULL) {
         fprintf(stderr, "%s: Cannot open file %s for reading.\n", argv[0],argv[1]);
         fprintf(stderr, usage, argv[0]);
         return -1;
 }
 */

//Read input from file for matrices a and b.
//The I/O is not timed because this I/O needs
//to be done regardless of whether this program
//is run sequentially on one processor or in
//parallel on many processors. Therefore, it is
//irrelevant when considering speedup.
if (rank == 0) {
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            a[i][j] = i + j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            b[i][j] = i + j;
    /*
    for (i = 0; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            int temp = b[i][j];
            b[i][j] = b[j][i];
            b[j][i] = temp;
        }
    }
    */
}

//TODO: Add a barrier prior to the time stamp.
MPI_Barrier(MPI_COMM_WORLD);
// Take a time stamp
gettimeofday(&tv1, NULL);
//TODO: Scatter the input matrices a and b.
    MPI_Scatter(a, blksz * N, MPI_FLOAT, row, blksz * N, MPI_FLOAT, 0,
        MPI_COMM_WORLD);
    MPI_Scatter(b, blksz * N, MPI_FLOAT, col, blksz * N, MPI_FLOAT, 0,
        MPI_COMM_WORLD);
//TODO: Add code to implement matrix multiplication (C=AxB) in parallel.
for (i = 0; i < blksz && rank * blksz + i < N; i++) {
    for (j = 0; j < N; j++) {
        c[i][j] = 0.0;
        for (k = 0; k < N; k++) {
            //c[i][j] += row[i][j] * col[j][k];
            c[i][j] += row[i][k] * col[j][k];
        }
    }
}
//TODO: Gather partial result back to the master process.
MPI_Gather(c, blksz * N, MPI_FLOAT, c, blksz * N, MPI_FLOAT, 0,
        MPI_COMM_WORLD);
// Take a time stamp. This won't happen until after the master
// process has gathered all the input from the other processes.
gettimeofday(&tv2, NULL);
elapsed_time = (tv2.tv_sec - tv1.tv_sec) + ((tv2.tv_usec - tv1.tv_usec)
        / 1000000.0);
printf("elapsed_time=\t%lf (seconds)\n", elapsed_time);
// print results
MPI_Barrier(MPI_COMM_WORLD);
print_results("C = ", c);
MPI_Finalize();

}

void print_results(char *prompt, float a[N][N]) {
int i, j;
printf("\n\n%s\n", prompt);
for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
        printf(" %.2f", a[i][j]);
    }
    printf("\n");
}
printf("\n\n");
}