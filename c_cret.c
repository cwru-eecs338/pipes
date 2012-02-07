#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

int echo_child(void);
int rev_child(void);

int main() {

    // Fork echo child
    pid_t echo_child_pid = fork();
    if (echo_child_pid < 0) {
        perror("Error birthing echo child");
        return EXIT_FAILURE;
    } else if (echo_child_pid == 0) {
        _exit(echo_child());
    }

    // Fork rev child
    pid_t rev_child_pid = fork();
    if (rev_child_pid < 0) {
        perror("Error birthing rev child");
        return EXIT_FAILURE;
    } else if (rev_child_pid == 0) {
        _exit(rev_child());
    }

    return EXIT_SUCCESS;
}

int echo_child() {
    return EXIT_SUCCESS;
}

int rev_child() {
    return EXIT_SUCCESS;
}
