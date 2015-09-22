#define _GNU_SOURCE

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"


#define THREADS_NO 4

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

int main()
{

	srand(time(NULL));

	int x = 100, y = 100;

	struct timespec ts_start, ts_end, ts_diff;

	struct matrix *matrix_a = NULL,
		      *matrix_b = NULL,
		      *matrix_c = NULL;

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

	return EXIT_SUCCESS;

}

