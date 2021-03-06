/*
 * mm.c - Matrix Multiplication for Arc Lab
 * 
 * DO NOT EDIT THIS FILE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

/* do not change the following */
#define N 32
double A[N][N];
double B[N][N];
double C[N][N];
static void usage(char *prog);

void mmNaive();
void randInit();
void init();
void verify();
float tdiff (struct timeval *, struct timeval *);

/* Naive implementation of Matrix Multiplicaton. */
void mmNaive()
{
    // Declare variables here
    int i, j, k;
    
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Implment matrix multiplication in this space
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
                for(k=0; k<N; k++)
                {
                    C[i][j] += A[i][k]*B[k][j];
                }
        }
    }
    
    gettimeofday(&end, NULL);
    printf("Elapsed time %0.6f secs.\n", tdiff(&start, &end));
}

int main(int argc, char **argv)
{
    char c;
    bool runNaive = false;
    bool unaryInit = false;
    while ((c = getopt(argc, argv, "urhnl")) != EOF) {
        switch (c) {
            case 'r': /* Generate a random matrix */
                printf("init with random\n");
                randInit();
                break;
            case 'n': /* Naive matrix multiplication */
                printf("naive mm\n");
                runNaive = true;
                break;
            case 'h': 
                usage(argv[0]);
                exit(0);
            case 'u':
                printf("init with ones\n");
                unaryInit = true;
                init();
                break;
            default:
                usage(argv[0]);
                exit(1);
        }
    }

    if (runNaive) {
        mmNaive();
    }

    if (unaryInit) {
        verify();
    }

    return 0;
}

/*
 * usage - Describe the command line arguments 
 */
static void usage(char *prog)
{
    fprintf(stderr, "Usage %s [-rhnub]\n", prog);
    fprintf(stderr, "Options\n");
    fprintf(stderr, "\t-r       Run with randomly generated matrices.\n");
    fprintf(stderr, "\t-h       Print this message.\n");
    fprintf(stderr, "\t-n       Run naive matrix multiplication.\n");
    fprintf(stderr, "\t-u       Run with unary matrices (all ones).\n");
}

/*
 * tdiff - Print the cpu time 
 */
float tdiff (struct timeval *start, struct timeval *end) 
{
    return (end->tv_sec-start->tv_sec)
        + 1e-6*(end->tv_usec-start->tv_usec);
}

/*
 * init - Initialize both matrices A and B with ones
 */
void init()
{
    int i, j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            A[i][j] = 1.0;
            B[i][j] = 1.0;
            C[i][j] = 0;
        }
    }
}

/*
 * randInit - Initialize both matrices randomly
 */
void randInit()
{
    int i, j;
    srand(time(NULL));
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            A[i][j] = (double)rand() / (double) RAND_MAX;
            B[i][j] = (double)rand() / (double) RAND_MAX;
            C[i][j] = 0;
        }
    }
}

/*
 * verify - Verify result matrix for unary inputs (all ones) 
 */
void verify() 
{
    int i, j;
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++) {
           if (C[i][j] != N) {
               printf("error; C[%d][%d] = %f\n", i, j, C[i][j]);
               exit(0);
           } 
        }
    printf("Verified!\n");
}
