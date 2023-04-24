/*
** EPITECH PROJECT, 2023
** Corewar bootstrap
** File description:
** P1/S1
*/

#include <stdio.h>

int main(void)
{
    FILE *stream = fopen("some-text.yolo", "w");
    if (stream == NULL)
        return (84);
    fprintf(stream, "Hello bambino\n");
    fclose(stream);
    return (0);
}
