#define _GNU_SOURCE

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include "matrix.h"





struct timespec get_timespec_diff(struct timespec start, struct timespec end)
{
	struct timespec temp;

	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
		
void print_usage(FILE *stream, const char *program_name)
{
	fprintf(stream, "**************************************"
			"*********************************\n\n");
	fprintf(stream,"Usage: \t  %s "
	               "\t size "
	               "\t threads_no \n",
	               program_name);
	fprintf(stream, "\n**************************************"
			"*********************************\n");

}

int check_arg(int * param, char * arg)
{
	if ( 0 == (*param = atoi(arg))) 
		return -1;
	return 0;
}	

int main(int argc, char *argv[])
{

	int x,
	    y,
	    verbose = 0,
	    no_threads;
/*
	const struct option long_options[] = {
		{ "help",    0, NULL, 'h' },
		{ "threads", 1, NULL, 't' },
		{ "verbose", 0, NULL, 'v' ),
		{ "size",    1, NULL, 's' },
		{  NULL,     0, NULL,  0  }
	};

*/
	struct timespec ts_start, ts_end, ts_diff;

	struct matrix *matrix_a = NULL,
		      *matrix_b = NULL,
		      *matrix_c = NULL;

	if (argc != 3 ) {
		print_usage(stdout,argv[0]);
		return EXIT_FAILURE;
	}

	if ( -1 == check_arg(&x,argv[1])) {
		fprintf(stderr,"Size is not int or equal to 0\n");
		return EXIT_FAILURE;
	}

	if ( -1 == check_arg(&y,argv[1])) {
		fprintf(stderr,"Size is not int or equal to 0\n");
		return EXIT_FAILURE;
	}

	if ( -1 == check_arg(&no_threads,argv[2])) {
		fprintf(stderr,"Threads_no  is not int or equal to 0\n");
		return EXIT_FAILURE;
	}

	if (verbose == 1 ) {
		printf("Size x matrix is:%d\n",x);
		printf("Size y matrix is:%d\n",y);
		printf("The desired number of threads is:%d\n",no_threads);
	}

	srand(time(NULL));

	if(matrix_init(&matrix_a, x, y)) {
		return EXIT_FAILURE;
	}

	if(matrix_init(&matrix_b, x, y)) {
		return EXIT_FAILURE;
	}

	if(matrix_init(&matrix_c, x, y)) {
		return EXIT_FAILURE;
	}

	matrix_populate_random(matrix_a);
	matrix_populate_random(matrix_b);

	if(clock_gettime(CLOCK_REALTIME, &ts_start) == -1) {
		perror("clock gettime");
		exit(EXIT_FAILURE);
	}

	matrix_multiply_jki(matrix_a, matrix_b, matrix_c);

	if(clock_gettime(CLOCK_REALTIME, &ts_end) == -1) {
		perror("clock gettime");
		exit(EXIT_FAILURE);
	}

	ts_diff = get_timespec_diff(ts_start, ts_end);
	printf("computed in %ld.%09ld  seconds\n",
			ts_diff.tv_sec, ts_diff.tv_nsec);

	matrix_free(&matrix_a);
	matrix_free(&matrix_b);
	matrix_free(&matrix_c);
	return EXIT_SUCCESS;

}

