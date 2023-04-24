/*
** EPITECH PROJECT, 2023
** Corewar bootstrap
** File description:
** P1/S3
*/

#include <stdio.h>

int main(void)
{
    FILE *stream = fopen("number-as-int.yolo", "w");
    if (stream == NULL)
        return (84);
    unsigned int number = 12345678;
    fwrite(&number, sizeof(unsigned int), 1, stream);
    fclose(stream);
    return (0);
}
