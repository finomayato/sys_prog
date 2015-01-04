// http://www.gnu.org/software/libc/manual/html_node/Process-Creation-Example.html
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Execute the command using this shell program
#define SHELL "/bin/sh"

int main (int args, char *const argv[])
{
    int status;
    char * wait_str = (char*)malloc(80);
    pid_t pid;

    if (args < 2) {
        fprintf(stderr, "Not enough arguments\n");
        return 1;
    }

    pid = fork ();
    if (pid == 0) {
        // This is the child process. Execute the shell command
        execl (SHELL, SHELL, "-c", argv[1], NULL);
        _exit (EXIT_FAILURE);
    }
    else if (pid < 0) {
        // The fork failed.  Report failure.
        status = -1;
    }
    else {
        // This is the parent process. Wait for the child to complete
        kill(pid,SIGTSTP);
        printf("Process `%s' stopped! Do you want to go further?\n", argv[1]);
        scanf("%s", wait_str);
        kill(pid,SIGCONT);
        printf("Anyway, process `%s' resumed!\n", argv[1]);
        if (waitpid (pid, &status, 0) != pid) status = -1;
    }

    return status;
}
