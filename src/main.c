#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"


#define THREADS_NO 4

int main()
{

	srand(time(NULL));

	int x = 10, y = 10;

	int i;
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

	matrix_multiply_jki(matrix_a, matrix_b, matrix_c);

	matrix_print(matrix_c);

	return EXIT_SUCCESS;

}

