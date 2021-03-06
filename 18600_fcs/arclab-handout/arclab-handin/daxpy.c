/*
 * daxpy.c - DAXPY for Arc Lab
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
#define N 2056
double X[N];
double Y[N];
double alpha = 0.5; 
static void usage(char *prog);

void run();
void randInit();
void init();
void verify();
float tdiff (struct timeval *, struct timeval *);

/* Multiply Y = a*X + Y*/
void run()
{
    int i; 
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Implment DAXPY here
    for(i = 0; i < N; i++)
    {   
        Y[i] = (alpha * X[i] + Y[i]);     
    }
    
    gettimeofday(&end, NULL);
    printf("Elapsed time %0.6f secs.\n", tdiff(&start, &end));
}


int main(int argc, char **argv)
{
    char c;
    bool unaryInit = false;
    while ((c = getopt(argc, argv, "urh")) != EOF) {
        switch (c) {
            case 'r': /* Generate random vectors */
                printf("init with random\n");
                randInit();
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

    if (argc > 1) 
        run();

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
    fprintf(stderr, "Usage %s [-uhr]\n", prog);
    fprintf(stderr, "Options\n");
    fprintf(stderr, "\t-r       Run with randomly generated vectors.\n");
    fprintf(stderr, "\t-h       Print this message.\n");
    fprintf(stderr, "\t-u       Run with unary vectors (all ones).\n");
}


float tdiff(struct timeval *start, struct timeval *end) 
{
    return (end->tv_sec-start->tv_sec)
        + 1e-6*(end->tv_usec-start->tv_usec);
}

void init()
{
    int i;
    for(i = 0; i < N; i++)
    {
        Y[i] = 1.0;
        X[i] = 1.0;
    }
}

void randInit()
{
    int i;
    for(i = 0; i < N; i++)
    {
        X[i] = (double)rand() / (double) RAND_MAX;
        Y[i] = (double)rand() / (double) RAND_MAX;
    }
}

/*
 * verify - Verify result matrix for unary inputs (all ones) 
 */
void verify() 
{
    int i;
    for(i = 0; i < N; i++)
    {
        if (Y[i] != 1.5) 
        {
            printf("error; Y[%d] = %f\n", i, Y[i]);
            exit(0);
        } 
    }
    printf("Verified!\n");
}
