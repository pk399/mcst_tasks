// Prints error information by
// different methods

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
    open("hello, \t\n", O_WRONLY | O_NONBLOCK | 15);
    perror("Perror");
    printf("Errno: %d\n", errno);
    // Deprecated
    //printf("sys_errlist[]: %s\n", sys_errlist[errno]);
    printf("strerror: %s\n", strerror(errno));
}
