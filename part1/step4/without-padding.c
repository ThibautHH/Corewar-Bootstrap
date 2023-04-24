/*
** EPITECH PROJECT, 2023
** Corewar bootstrap
** File description:
** P1/S5
*/

#include <stdio.h>

int main(void)
{
    FILE *stream = fopen("several-variables.yolo", "w");
    if (stream == NULL)
        return (84);
    unsigned int number = 192837;
    fwrite(&number, sizeof(unsigned int), 1, stream);
    fwrite("k", sizeof(char), 1, stream);
    char str[40] = "Corewar is swag!!";
    fwrite(str, sizeof(char[40]), 1, stream);
    fclose(stream);
    return (0);
}
