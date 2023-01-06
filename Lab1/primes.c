#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RANGE 35
#define FIRSTPRIME 2

int first_proc();
int prime_filter(int in_fd, int prime);

int main(int argc, char **argv)
{
    int prime;
    int in_fd;

    in_fd = first_proc();

    while (read(in_fd, &prime, sizeof(int)))
    {
        printf("prime %d\n", prime);
        in_fd = prime_filter(in_fd, prime);
    }

    exit(0);
}

int first_proc()
{
    int p[2];
    pipe(p);

    if (fork() == 0)
    {
        /* first process sends nums */
        for (int i = FIRSTPRIME; i <= RANGE; i++)
        {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        exit(0);
    }
    close(p[1]);
    return p[0];
}

int prime_filter(int in_fd, int prime)
{
    int num;
    int p[2];

    pipe(p);

    if (!fork())
    {
        while (read(in_fd, &num, sizeof(int)))
        {
            if (num % prime)
            {
                write(p[1], &num, sizeof(int));
            }
        }
        close(in_fd);
        close(p[1]);

        exit(0);
    }

    close(in_fd);
    close(p[1]);

    return p[0];
}