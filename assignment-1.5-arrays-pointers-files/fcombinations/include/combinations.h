#ifndef COMBINATIONS_H
#define COMBINATIONS_H

#include <stdbool.h>

void read_file();

int get_n();
int get_k();
int *fill_array(int);
bool exists_in_array(int *, int, int);
int *sort(int *);

void x_pair(int *, int *);
void y_pair(int *, int *);

void combinations(int *, int, int, int, int);
int even_calc(int *);
bool belongs_x(int, int, int);
int sum_calc(int *);
bool belongs_y(int, int, int);
void print_combs(int *);
int combinations_count(int);
int factorial(int);
int sum_comb_calc();

void print();
int not_printed();
int not_first_condition();
int not_second_condition_only();
int frequency();

#endif
