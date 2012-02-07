#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

// Useful constants (so we don't have to remember)
#define  STDIN_FD 0
#define STDOUT_FD 1
#define  READ_END 0
#define WRITE_END 1

char *message = ".egassem terces eht derevocsid tsuj ev'uoY .snoitalutargnoC";

int echo_child(int *);
int  rev_child(int *);

int main() {

    // Holds file descriptors for read and write ends of the pipe
    int pipefd[2];

    // Create the (unidirectional) pipe
    if (pipe(pipefd)) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork echo child
    pid_t echo_child_pid = fork();
    if (echo_child_pid < 0) {
        perror("Error birthing echo child");
        return EXIT_FAILURE;
    } else if (echo_child_pid == 0) {
        echo_child(pipefd);
    }

    // Fork rev child
    pid_t rev_child_pid = fork();
    if (rev_child_pid < 0) {
        perror("Error birthing rev child");
        return EXIT_FAILURE;
    } else if (rev_child_pid == 0) {
        rev_child(pipefd);
    }

    // The parent needs to close its
    // references to the pipes...
    // (Warning: this is lazy because it doesn't
    //           check return values of `close`!)
    close(pipefd[READ_END]);
    close(pipefd[WRITE_END]);

    // Wait for children
    int status1, status2;
    wait(&status1);
    wait(&status2);

    // If either status = 1 (FAILURE)
    // then the overall process failed
    return (status1 | status2);
}

int echo_child(int *pipefd) {
    // Close the end of the pipe this child
    // is not going to use...
    close(pipefd[READ_END]);

    // Close STDOUT so we can replace its file
    // descriptor with that of the pipe's
    // "write" end (TODO: error checking)
    close(STDOUT_FD);

    // Duplicates this file descriptor so that STDOUT
    // also points to the write end of the pipe
    dup2(pipefd[WRITE_END], STDOUT_FD);

    // This child becomes `echo $message`
    // with STDOUT redirected to the pipe
    execlp("echo", "echo", message, (char *) NULL);
    _exit(EXIT_FAILURE);
}

int rev_child(int *pipefd) {
    // Close the end of the pipe this child
    // is not going to use...
    close(pipefd[WRITE_END]);

    // Close STDIN so we can replace its file
    // descriptor with that of the pipe's
    // "read" end (TODO: error checking)
    close(STDIN_FD);

    // Duplicates this file descriptor so that STDIN
    // also points to the read end of the pipe
    dup(pipefd[READ_END]);

    // This child becomes `rev`
    // with STDIN redirected from the pipe
    execlp("rev", "rev", (char *) NULL);
    _exit(EXIT_FAILURE);
}
