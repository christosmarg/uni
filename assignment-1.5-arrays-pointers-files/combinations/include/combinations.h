#ifndef COMBINATIONS_H
#define COMBINATIONS_H

#include <stdbool.h>

int get_n(const char *);
int combinations_count(int);
int factorial(int);
int sum_calc();
int sum_comb_calc();
int even_calc();
int not_printed();

int *fill_array(int);

float frequency();

char *get_filename();

bool exists_in_array(int *, int, int);
bool is_subset();

void x_pair(int *, int *);
void y_pair(int *, int *);
void combinations(int *);
void print_combs();
void read_file();

#endif
