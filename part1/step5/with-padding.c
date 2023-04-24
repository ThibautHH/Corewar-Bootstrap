/*
** EPITECH PROJECT, 2023
** Corewar bootstrap
** File description:
** P1/S1
*/

#include <stdio.h>

typedef struct {
    unsigned int number;
    char c;
    char str[40];
} yolo_t;

int main(void)
{
    FILE *stream = fopen("one-structure.yolo", "w");
    if (stream == NULL)
        return (84);
    yolo_t yolo = {192837u, 'k', "Corewar is swag!!"};
    fwrite(&yolo, sizeof(yolo_t), 1, stream);
    fclose(stream);
    return (0);
}
