/*
** EPITECH PROJECT, 2023
** Corewar bootstrap
** File description:
** P2/S2
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

static int8_t run_op(FILE *stream)
{
    uint8_t op;
    fread(&op, sizeof(uint8_t), 1, stream) != 1;
    if (ferror(stream) || feof(stream))
        return (feof(stream) ? 0 : -1);
    if (op == 0x04) {
        uint32_t len;
        fread(&len, sizeof(uint32_t), 1, stream);
        if (ferror(stream) || feof(stream))
            return (feof(stream) ? 0 : -1);
        char *str = malloc(sizeof(char[len + 1]));
        str[len] = '\0';
        fread(str, sizeof(char[len]), 1, stream);
        if (ferror(stream) || feof(stream))
            return (feof(stream) ? 0 : -1);
        if (printf("%s\n", str) < 0)
            return (-1);
    } else if (op == 0x01 || op == 0x02 || op == 0x03) {
        int32_t params[2];
        fread(params, sizeof(int32_t[2]), 1, stream);
        if (ferror(stream) || feof(stream))
            return (feof(stream) ? 0 : -1);
        switch (op) {
            case 0x01:
                params[0] += params[1];
                break;
            case 0x02:
                params[0] -= params[1];
                break;
            case 0x03:
                params[0] *= params[1];
                break;
        }
        if (printf("%d\n", params[0]) < 0)
            return (-1);
    } else
        return -1;
    return 1;
}

static _Bool execute(FILE *stream)
{
    int8_t ret;
    while ((ret = run_op(stream)) > 0);
    return (ret);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (84);
    FILE *stream = fopen(argv[1], "r");
    if (stream == NULL)
        return (84);
    if (execute(stream)) {
        fclose(stream);
        return (84);
    }
    fclose(stream);
    return (0);
}
