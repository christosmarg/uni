#ifndef ARRHANDLER_H
#define ARRHANDLER_H

#include <stdbool.h>

int *fill_array(int);
bool exists_in_array(int *, int, int);

void quicksort(int *, int, int);
int partition(int *, int, int);
void swap(int *, int *);
void printarray(int *, int);

void combinations(int *, int, int, int, int);
int even_calc(int *);
bool belongs_x(int, int, int);
int sum_calc(int *);
bool belongs_y(int, int, int);
int sum_comb_calc();

void print();
int not_printed();
int not_first_condition();
int not_second_condition_only();
int frequency();

#endif