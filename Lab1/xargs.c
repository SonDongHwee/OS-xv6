#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAXARGLEN 1024

int readline(char *new_argv[32], int cur)
{
    char buf[MAXARGLEN];
    int n = 0;
    while (read(0, buf + n, 1))
    {
        if (n == MAXARGLEN - 1)
        {
            fprintf(2, "argument is too long\n");
            exit(1);
        }
        if (buf[n] == '\n')
            break;
        n++;
    }

    buf[n] = 0;
    if (n == 0)
        return 0;
    int offset = 0;
    while (offset < n)
    {
        new_argv[cur++] = buf + offset;
        while (buf[offset] != ' ' && offset < n)
        {
            offset++;
        }
        while (buf[offset] == ' ' && offset < n)
        {
            buf[offset++] = 0;
        }
    }
    return cur;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "Usage: xargs command (arg ...)\n");
        exit(1);
    }

    char *command = malloc(strlen(argv[1]) + 1);
    char *new_argv[MAXARG];
    strcpy(command, argv[1]);

    for (int i = 1; i < argc; i++)
    {
        new_argv[i - 1] = malloc(strlen(argv[i]) + 1);
        strcpy(new_argv[i - 1], argv[i]);
    }

    int cur;
    while ((cur = readline(new_argv, argc - 1)) != 0)
    {
        new_argv[cur] = 0;
        if (fork() == 0)
        {
            exec(command, new_argv);
            fprintf(2, "exec failed\n");
            exit(1);
        }
        else
        {
            wait((int *)0);
        }
    }
    exit(0);
}