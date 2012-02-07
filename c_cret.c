#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

char *message = ".egassem terces eht derevocsid tsuj ev'uoY .snoitalutargnoC";
#define  STDIN_FD 0
#define STDOUT_FD 1
#define  READ_END 0
#define WRITE_END 1

int echo_child(void);
int  rev_child(void);

int main() {

    // Holds file descriptors
    // for read and write
    // ends of the pipe
    int pipefd[2];

    // Create the pipe
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
        close(pipefd[READ_END]);
        close(STDOUT_FD);
        dup(pipefd[WRITE_END]);
        _exit(echo_child());
    }

    // Fork rev child
    pid_t rev_child_pid = fork();
    if (rev_child_pid < 0) {
        perror("Error birthing rev child");
        return EXIT_FAILURE;
    } else if (rev_child_pid == 0) {
        close(pipefd[WRITE_END]);
        close(STDIN_FD);
        dup(pipefd[READ_END]);
        _exit(rev_child());
    }

    close(pipefd[READ_END]);
    close(pipefd[WRITE_END]);

    // The lazy way to wait...
    // (without checking return values)
    wait(NULL);
    wait(NULL);

    return EXIT_SUCCESS;
}

int echo_child() {
    // This child becomes `echo message`
    execlp("echo", "echo", message, (char *) NULL);
    return EXIT_FAILURE;
}

int rev_child() {
    // This child becomes `rev`
    execlp("rev", "rev", (char *) NULL);
    return EXIT_FAILURE;
}
