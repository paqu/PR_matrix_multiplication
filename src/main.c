#define _GNU_SOURCE

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "matrix.h"

#define BUFF_SIZE 128



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
	fprintf(stream,"Usage: %s size threads_no filename func_name radius\n",
			program_name);
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
	    n,
	    radius   =  0,
	    func_idx =  0,
	    verbose  =  0,
	    fd       = -1,
	    no_threads;

	const char *filename = NULL;

	char buff[BUFF_SIZE];

	void (*func[3])(struct matrix *,struct matrix *, struct matrix *,int) = {
		matrix_multiply_ijk,
		matrix_multiply_jki,
		matrix_multiply_6jki
	};

	void (*matrix_multiply)(struct matrix *a, struct matrix *b, struct matrix *c,int r);
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

	if (argc != 6 ) {
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

	if ( -1 == check_arg(&radius,argv[5])) {
		fprintf(stderr,"Radius is not int or equal to 0\n");
		return EXIT_FAILURE;
	}

	filename = argv[3];

	if ( -1 == (fd = open(filename,O_RDWR|O_CREAT|O_APPEND,0644))) {
		perror("Open:");
		return EXIT_FAILURE;
	}
	
	if ( 0 == strncmp(argv[4],"ijk",3)) 
		func_idx = 0;

	if ( 0 == strncmp(argv[4],"jki",3)) 
		func_idx = 1;

	if ( 0 == strncmp(argv[4],"6jki",4)) 
		func_idx = 2;

	if (verbose == 0 ) {
		printf("Size x matrix: %d\n",x);
		printf("Size y matrix: %d\n",y);
		printf("Threads no: %d\n",no_threads);
		printf("Output file: %s\n",filename);
		printf("Function id: %d\n",func_idx);
	}

	matrix_multiply = func[func_idx];

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

	matrix_multiply(matrix_a, matrix_b, matrix_c,radius);

	if(clock_gettime(CLOCK_REALTIME, &ts_end) == -1) {
		perror("clock gettime");
		exit(EXIT_FAILURE);
	}

	ts_diff = get_timespec_diff(ts_start, ts_end);
	printf("computed in %ld.%09ld  seconds\n",
			ts_diff.tv_sec, ts_diff.tv_nsec);

	memset(buff,0,BUFF_SIZE);
	sprintf(buff,"%d\t%ld.%09ld\n",x,ts_diff.tv_sec,ts_diff.tv_nsec);

	n = write(fd,buff,BUFF_SIZE);
	if ( n != BUFF_SIZE) {
		perror("write:");
		return EXIT_FAILURE;
	}

	matrix_free(&matrix_a);
	matrix_free(&matrix_b);
	matrix_free(&matrix_c);
	close(fd);

	return EXIT_SUCCESS;

}

