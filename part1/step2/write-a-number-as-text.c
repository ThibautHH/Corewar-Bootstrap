/*
** EPITECH PROJECT, 2023
** Corewar bootstrap
** File description:
** P1/S2
*/

#include <stdio.h>

int main(void)
{
    FILE *stream = fopen("number-as-text.yolo", "w");
    if (stream == NULL)
        return (84);
    fprintf(stream, "12345678");
    fclose(stream);
    return (0);
}
