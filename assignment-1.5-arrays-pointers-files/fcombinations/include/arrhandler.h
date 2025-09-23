#ifndef ARRHANDLER_H
#define ARRHANDLER_H

#include "fcombinations.h"

int *fill_array(int, FILE *);
bool exists_in_array(int *, int, int);

void quicksort(int *, int, int);
int partition(int *, int, int);
void swap(int *, int *);

int find_pos(int *, int, int);

#endif