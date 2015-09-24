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
	fprintf(stream, "**************************************"
			"*********************************\n\n");
	fprintf(stream,"Usage: \t  %s "
	               "\t size "
	               "\t threads_no \n"
	               "\t filename \n",
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
	    n,
	    verbose = 0,
	    fd = -1,
	    no_threads;

	const char *filename = NULL;

	char buff[BUFF_SIZE];
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

	if (argc != 4 ) {
		print_usage(stdout,argv[0]);
		return EXIT_FAILURE;
	}

	filename = argv[3];

	if ( -1 == (fd = open(filename,O_RDWR|O_CREAT|O_APPEND,0644))) {
		perror("Open:");
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
		printf("Size x matrix is:\t%d\n",x);
		printf("Size y matrix is:\t%d\n",y);
		printf("The desired numbe  of threads is:\t%d\n",no_threads);
		printf("Filename is: \t%s\n",filename);
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

	matrix_multiply_jki(matrix_a, matrix_b, matrix_c,0);

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

