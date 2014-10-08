#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_SIZE  256

int main(void)
{
    char buf[BUF_SIZE];
    int pipefd[2];  // two file descriptors:
    int pid2, pid3;
    int bytes_read;

    // open the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe creation error");
        exit(1);
    }

    // initialize the buffer
    memset(buf,0,BUF_SIZE);

    printf("ppid == %d\n",getpid());

    switch(pid2 = fork()) {
        case -1:
            perror("pid2 fork error");
            exit(1);
        case 0:
            close(1);
            dup(pipefd[1]);   // redirect stdout to the pipe
            close(pipefd[0]); // close the read end
            printf("pid2 executing command\n");
            if (execl("/usr/pkg/bin/pkgin", "pkgin", "ls", 0) == -1) {
                perror("execl call failed");
            }
            exit(1);    /* should never reach here */
        default:
            printf("%d created pid2 == %d\n",getpid(),pid2);
    }

    // fork a child process
    switch(pid3 = fork()) {
        case -1:
            perror("pid3 fork error");
            exit(1);
        case 0:
            close(pipefd[1]);  // close the write end of the pipe
            /* read from the pipe until it is closed on the other
               end (indicated by read returned zero)  */
            do {
                bytes_read = read(pipefd[0],buf,BUF_SIZE);
                if (bytes_read == -1)
                    perror("pid3: read pipe error");
                else
                    write(1,buf,bytes_read);  // echo data to stdout
            } while (bytes_read > 0);  // ie, for as long as something is read
            exit(0);
        default:
            printf("%d created pid3 == %d\n",getpid(),pid3);
    }

    return 0;
}
