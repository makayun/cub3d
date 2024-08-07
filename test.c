#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "cub3d.h"



int main()
{
    printf("t_pos %lu\n", sizeof(t_position)); // 8
    printf("t_coord %lu\n", sizeof(t_coord)); // 8
    printf("float[2] %lu\n", sizeof(float[2])); // 8
    printf("pointer %lu\n", sizeof(void *)); // 8
    printf("float %lu\n", sizeof(float)); // 4
    printf("bool %lu\n", sizeof(bool)); // 1
}
