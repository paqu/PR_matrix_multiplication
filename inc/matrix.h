#ifndef MATRIX_H
#define MATRIX_H

struct matrix {
	float **matrix;
	int x;
	int y;
};

int matrix_init(struct matrix **m, int x, int y);
void matrix_populate_random(struct matrix *m);
void matrix_multiply_jki(struct matrix *m_in_a, struct matrix *m_in_b, struct matrix *m_result);
void matrix_print(struct matrix *m);

#endif

