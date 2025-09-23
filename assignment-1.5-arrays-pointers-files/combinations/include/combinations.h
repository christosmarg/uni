#ifndef COMBINATIONS_H
#define COMBINATIONS_H

#include <stdbool.h>

int get_val(const char *);
int *fill_array(int);
bool exists_in_array(int *, int, int);

void x_pair(int *, int *);
void y_pair(int *, int *);

void combinations(int *);
int even_calc();
int sum_calc();
void print_combs();
int combinations_count(int);
int factorial(int);
int sum_comb_calc();
int not_printed();
float frequency();

char *get_filename();
bool is_subset();
void read_file();

#endif
