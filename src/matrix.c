#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>


int matrix_init(struct matrix **m, int x, int y)
{
	int i;

	if((*m = malloc(sizeof(struct matrix))) == NULL)
		return -1;

	(*m)->x = x;
	(*m)->y = y;


	if(((*m)->matrix = malloc((*m)->x * sizeof(int *))) == NULL)
		return -1;

	for (i = 0; i < (*m)->x; i++) {

		if(((*m)->matrix[i] = malloc((*m)->y * sizeof(int))) == NULL)
			return -1;
	}

	return 0;

}
void matrix_free(struct matrix **m)
{
	int i;

	for (i = 0; i < (*m)->x; ++i) {
		free((*m)->matrix[i]);		
		(*m)->matrix[i] = NULL;
	}

	free((*m)->matrix);
	(*m)->matrix = NULL;

	free(*m);
	*m = NULL;
}

void matrix_populate_random(struct matrix *m)
{
	int i,j;
	for(i = 0; i < m->x; i++)
		for(j = 0; j < m->y; j++) {
			m->matrix[i][j] = (float) rand() / RAND_MAX;
		}
}
void matrix_multiply_jki(struct matrix *m_in_a, struct matrix *m_in_b, struct matrix *m_result,int radius);
{
	int i, j, k,r;

	for (j = 0; j < m_result->y; j++)
		for (k = 0; k < m_result->y; k++)
			for (i = 0; i < m_result->x; i++)
				m_result->matrix[i][j] += m_in_a->matrix[i][k] * m_in_b->matrix[k][j];
}

void matrix_multiply_ijk(struct matrix *m_in_a, struct matrix *m_in_b, struct matrix *m_result,int radius)
{
	int i,j,k,r;
}

void matrix_multiply_6jki(struct matrix *m_in_a, struct matrix *m_in_b, struct matrix *m_result,int radius)
{
	int i,j,k,r;


}
void matrix_print(struct matrix *m)
{
	int i,j;

	for(i = 0; i < m->x; i++) {
		for(j = 0; j < m->y; j++) {
			printf("%.5f ", m->matrix[i][j]);
		}
		printf("\n");
	}
}

