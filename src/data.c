#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <gos/data.h>

bool gos_data_initialize_vector(gos_vector* vector, int size) {
  bool funres;
  assert(vector != NULL);
  vector->data = (double*)malloc(size * sizeof(double));
  funres = vector->data != NULL;
  vector->count = funres ? size : 0;
  return funres;
}
bool gos_data_initialize_matrix(gos_matrix* matrix, int sd1, int sd2) {
  int i;
  assert(matrix != NULL);
  matrix->data = (double**)calloc(sd1, sizeof(double*));
  if (matrix->data != NULL) {
    matrix->countd1 = sd1;
    matrix->countd2 = 0;
    for (i = 0; i < sd1; i++) {
      matrix->data[i] = (double*)calloc(sd2, sizeof(double));
      if (matrix->data[i] == NULL) {
        gos_data_free_matrix(matrix);
        return false;
      }
    }
    matrix->countd2 = sd2;
    return true;
  }
  return false;
}

void gos_data_set_vector_d1(gos_matrix* matrix, gos_vector* vector, int index) {
  assert(matrix != NULL);
  assert(matrix->data != NULL);
  assert(vector != NULL);
  assert(vector->data != NULL);
  assert(matrix->countd2 == vector->count);
  assert(index < matrix->countd1);
  memcpy(matrix->data[index], vector->data, vector->count * sizeof(double));
}
void gos_data_set_vector_d2(gos_matrix* matrix, gos_vector* vector, int index) {
  int i;
  double* d;
  assert(matrix != NULL);
  assert(matrix->data != NULL);
  assert(vector != NULL);
  assert(vector->data != NULL);
  assert(matrix->countd1 == vector->count);
  assert(index < matrix->countd2);
  for (i = 0; i < matrix->countd1; i++) {
    d = matrix->data[i];
    d[index] = vector->data[i];
  }
}


void gos_data_set_matrix(gos_matrix* matrix, int id1, int id2, double value) {
  double* d;
  assert(matrix != NULL);
  assert(matrix->data != NULL);
  assert(id1 < matrix->countd1);
  assert(id2 < matrix->countd2);
  d = matrix->data[id1];
  d[id2] = value;
}
double gos_data_get_matrix(gos_matrix* matrix, int id1, int id2) {
  double* d;
  assert(matrix != NULL);
  assert(matrix->data != NULL);
  assert(id1 < matrix->countd1);
  assert(id2 < matrix->countd2);
  d = matrix->data[id1];
  return(d[id2]);
}

void gos_data_shift_matrix_d1d1(gos_matrix* matrix) {
  int i;
  assert(matrix != NULL);
  assert(matrix->data != NULL);
  for (i = 0; i < matrix->countd1 - 2; i++) {
    memcpy(
      matrix->data[i],
      matrix->data[i + 1],
      matrix->countd2 * sizeof(double));
  }
}
void gos_data_shift_matrix_d1d2(gos_matrix* matrix) {
  int i;
  assert(matrix != NULL);
  assert(matrix->data != NULL);
  for (i = 0; i < matrix->countd1; i++) {
    memmove(
      matrix->data[i] + 1,
      matrix->data[i],
      (((size_t)matrix->countd2) - 1) * sizeof(double));
  }
}
void gos_data_shift_matrix_d2d1(gos_matrix* matrix) {
  int i;
  assert(matrix != NULL);
  assert(matrix->data != NULL);
  for (i = matrix->countd1 - 2; i >= 0; i--) {
    memcpy(
      matrix->data[i + 1],
      matrix->data[i],
      matrix->countd2 * sizeof(double));
  }
}
void gos_data_shift_matrix_d2d2(gos_matrix* matrix) {
  int i;
  assert(matrix != NULL);
  assert(matrix->data != NULL);
  for (i = 0; i < matrix->countd1; i++) {
    memmove(
      matrix->data[i],
      matrix->data[i] + 1,
      (((size_t)matrix->countd2) - 1) * sizeof(double));
  }
}

void gos_data_free_vector(gos_vector* vector) {
  if (vector != NULL && vector->data != NULL) {
    free(vector->data);
    vector->data = NULL;
    vector->count = 0;
  }
}
void gos_data_free_matrix(gos_matrix* matrix) {
  int i;
  if (matrix != NULL && matrix->data != NULL) {
    for (i = 0; i < matrix->countd1; i++) {
      if (matrix->data[i] != NULL) {
        free(matrix->data[i]);
        matrix->data[i] = NULL;
      }
    }
    free(matrix->data);
    matrix->data = NULL;
    matrix->countd1 = 0;
    matrix->countd2 = 0;
  }
}
