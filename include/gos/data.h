#ifndef GOS_DATA_H_
#define GOS_DATA_H_

#include <stdbool.h>

#include <gos/types.h>

#ifdef __cplusplus
extern "C" {
#endif

bool gos_data_initialize_vector(gos_vector* vector, int size);
bool gos_data_initialize_matrix(gos_matrix* matrix, int sd1, int sd2);

void gos_data_set_vector_d1(gos_matrix* matrix, gos_vector* vector, int index);
void gos_data_set_vector_d2(gos_matrix* matrix, gos_vector* vector, int index);

void gos_data_set_matrix(gos_matrix* matrix, int id1, int id2, double value);
double gos_data_get_matrix(gos_matrix* matrix, int id1, int id2);

void gos_data_shift_matrix_d1d1(gos_matrix* matrix);
void gos_data_shift_matrix_d1d2(gos_matrix* matrix);
void gos_data_shift_matrix_d2d1(gos_matrix* matrix);
void gos_data_shift_matrix_d2d2(gos_matrix* matrix);

void gos_data_free_vector(gos_vector* vector);
void gos_data_free_matrix(gos_matrix* matrix);

#ifdef __cplusplus
}
#endif

#endif
