#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


#define THREADS_NO 4

int main()
{

	int i;

	omp_set_num_threads(THREADS_NO);

	printf("Hello travis \n");
#pragma omp parallel
	{
		for(i = 0; i <= 5; i++)
			printf("[%d] Hello World, i = %d\n", omp_get_thread_num(), i);
	}

	return EXIT_SUCCESS;

}

