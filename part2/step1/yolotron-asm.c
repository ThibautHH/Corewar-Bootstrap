/*
** EPITECH PROJECT, 2023
** Corewar bootstrap
** File description:
** P2/S1
*/

#include <sys/types.h>

#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define OP_COUNT 4
#define IS_SPC(c) ((c) == ' ' || (c) == '\t')

_Bool encode_arithm(const char *line, FILE *out);
_Bool encode_put(const char *line, FILE *out);

static const struct {
    char *name;
    uint8_t code;
    _Bool (*encode_op)(const char *line, FILE *out);
} ops[OP_COUNT] = {
    {"add", 0x01, encode_arithm},
    {"sub", 0x02, encode_arithm},
    {"mul", 0x03, encode_arithm},
    {"put", 0x04, encode_put}
};

_Bool encode_put(const char *line, FILE *out)
{
    if (!IS_SPC(*line))
        return 1;
    while (IS_SPC(*line))
        line++;
    uint32_t len = strlen(line);
    fwrite(&len, sizeof(uint32_t), 1, out);
    if (ferror(out))
        return 1;
    fwrite(line, sizeof(char), len, out);
    return ferror(out);
}

_Bool encode_arithm(const char *line, FILE *out)
{
    if (!IS_SPC(*line))
        return 1;
    char *end;
    int32_t params[2];
    for (size_t i = 0; i < 2; i++) {
        params[i] = strtol(line, &end, 10);
        if (line == end)
            return 1;
        line = end;
    }
    while (IS_SPC(*line))
        line++;
    if (*line != '\n')
        return 1;
    fwrite(params, sizeof(int32_t), 2, out);
    return ferror(out);
}

static int compile(const char *file, const char *output)
{
    FILE *in = fopen(file, "r"), *out = fopen(output, "w");
    if (!in || !out || setvbuf(out, NULL, _IONBF, 0))
        return (84);
    char *line = NULL;
    size_t size = 0;
    _Bool has_failed = 0, is_op = 0;
    errno = 0;
    for (ssize_t len; ((len = getline(&line, &size, in)) != -1) || has_failed; errno = 0, is_op = 0) {
        if (len == 1)
            continue;
        for (size_t i = 0; i < OP_COUNT; i++)
            if (!strncmp(line, ops[i].name, strlen(ops[i].name))) {
                is_op = 1;
                fwrite(&ops[i].code, sizeof(uint8_t), 1, out);
                if (ferror(out))
                    return 1;
                has_failed = ops[i].encode_op(line + strlen(ops[i].name), out);
                break;
            }
        if (!is_op)
            has_failed = 1;
    }
    if (errno)
        has_failed = 1;
    fclose(in); fclose(out);
    return (has_failed) ? 84 : 0;
}

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <file> [output]\n", argv[0]);
        return (84);
    }
    if (!strcmp(argv[1], "-h")) {
        printf("Usage: %s <file> [output]\n", argv[0]);
        return (0);
    }
    char outf[256];
    if (argc == 2) {
        char *last_dot = strrchr(argv[1], '.');
        size_t stem_len = (last_dot) ? last_dot - argv[1] : strlen(argv[1]);
        sprintf(outf, "%.*s%s", (int)(stem_len), argv[1], ".bytecode");
    }
    return compile(argv[1], (argc == 3) ? argv[2] : outf);
}
