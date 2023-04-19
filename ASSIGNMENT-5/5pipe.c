#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

void read_input(int *x, int *y) {
    printf("Enter value of x : ");
    scanf("%d", x);
    if ((*x < 1.0) || (*x != (int)*x)) {
        printf("You entered wrong string instead of integer\n");
        exit(1);
    }
    printf("Enter value of y : ");
    scanf("%d", y);
    if ((*y < 1.0) || (*y != (int)*y)) {
        printf("You entered wrong string instead of integer\n");
        exit(1);
    }
}

void write_to_pipe(int *pipe, int *value) {
    if (write(pipe[1], value, sizeof(int)) == -1) {
        printf("Error in writing to pipe\n");
        exit(1);
    }
}

void read_from_pipe(int *pipe, int *value) {
    if (read(pipe[0], value, sizeof(int)) == -1) {
        printf("Error while reading from pipe\n");
        exit(1);
    }
}

void write_to_file(int fd, int *value) {
    if (write(fd, value, sizeof(int)) == -1) {
        printf("Error in writing to file\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    int pipe1[2];
    int pipe2[2];
    int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        printf("Error in opening txt file\n");
        exit(1);
    }
    int saved_stdout = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    if (pipe(pipe1) == -1) {
        printf("Error in creating a pipe\n");
        exit(1);
    }
    if (pipe(pipe2) == -1) {
        printf("Error in creating a pipe\n");
        exit(1);
    }
    int child = fork();
    if (child == -1) {
        printf("Error in creating a child process\n");
        exit(1);
    } else if (child == 0) {
        close(pipe1[1]); // Doesn't write to pipe 1's write
        close(pipe2[0]); // Doesn't read from pipe 2's read
        int a = 0, b = 0, c = 0;
        read_from_pipe(pipe1, &a);
        read_from_pipe(pipe1, &b);
        c = a + b;
        write_to_pipe(pipe2, &c);
        close(pipe1[0]);
        close(pipe2[1]);
    } else {
        close(pipe1[0]); // Doesn't read from pipe 1's read
        close(pipe2[1]); // Doesn't write to pipe 2's write
        int x = 0, y = 0, sum = 0;
        dup2(saved_stdout, STDOUT_FILENO);
        read_input(&x, &y);
        dup2(fd, STDOUT_FILENO);
        write_to_pipe(pipe1, &x);
        write_to_pipe(pipe1, &y);
        read_from_pipe(pipe2, &sum);
        printf("The sum returned from Child : %d\n", sum);
        close(pipe1[1]);
        close(pipe2[0]);
    }
    close(fd);
    close(saved_stdout);
    return 0;
}


// This is a C program that creates two pipes and a 
// child process. The parent process reads two integers 
// from the user, sends them to the child process via the 
// first pipe, and then waits for the child to send the sum
// of the two integers back via the second pipe. 
// The child process reads the two integers from the 
// first pipe, calculates their sum, and sends the sum 
// back to the parent process via the second pipe. 
// The parent process then prints the sum to the console.


// The dup() system call creates a copy of a file descriptor.

// It uses the lowest-numbered unused descriptor for the new descriptor.
// If the copy is successfully created, then the original and copy file 
// descriptors may be used interchangeably.
// They both refer to the same open file description and thus share file 
// offset and file status flags.

// The dup2() system call is similar to dup() but the basic
// difference between them is that instead of using the 
// lowest-numbered unused file descriptor, it uses the 
// descriptor number specified by the user.