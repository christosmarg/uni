#ifndef C_COLORS_H
#define C_COLORS_H

#include <stdio.h>

enum options {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, BOLD_RED, BOLD_GREEN, BOLD_YELLOW, BOLD_BLUE, BOLD_MAGENTA, BOLD_CYAN, STANDARD};
enum options color;

void set_color(enum options color)
{
    switch (color)
    {
        case RED:           printf("\033[0;31m"); break;
        case GREEN:         printf("\033[0;32m"); break;
        case YELLOW:        printf("\033[0;33m"); break;
        case BLUE:          printf("\033[0;34m"); break;
        case MAGENTA:       printf("\033[0;35m"); break;
        case CYAN:          printf("\033[0;36m"); break;

        case BOLD_RED:      printf("\033[1;31m"); break;
        case BOLD_GREEN:    printf("\033[1;32m"); break;
        case BOLD_YELLOW:   printf("\033[1;33m"); break;
        case BOLD_BLUE:     printf("\033[1;34m"); break;
        case BOLD_MAGENTA:  printf("\033[1;35m"); break;
        case BOLD_CYAN:     printf("\033[1;36m"); break;

        case STANDARD:      printf("\033[0m");    break;
    }
}

#endif