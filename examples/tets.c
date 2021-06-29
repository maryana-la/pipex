//
// Created by mlays on 24.06.2021.
//
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char ** argv)
{
    char *cmd = argv[1];
    char *in_name = argv[2];

    int in = open(in_name, O_RDONLY);
    dup2(in, 0);
    close(in);
    int fds_pair[2];
    pipe(fds_pair);

    pid_t pid = fork();
    if (pid == 0)
    {
        dup2(fds_pair[1], 1);
        close(fds_pair[1]);
        execlp(cmd, cmd, NULL);
    }
    else
    {
        close(fds_pair[1]);
        int total_count = 0;
        size_t count;
        char buffer[4096];
        while((count = read(fds_pair[0], buffer, sizeof(buffer))) > 0)
            total_count += count;
        waitpid(pid, 0, 0);
        printf("%d\n", total_count);
    }
    return (0);
}
