// Send a message from one programm to another
// Two programms must be open at the same time
// When you enter a name for the sending FIFO
// It must already created by another programm

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

const size_t MAX_BUF = 1024;

int main()
{
    printf("Enter FIFO name to receive: ");
    char myname[MAX_BUF] = {};
    if ( fgets(myname, MAX_BUF, stdin) == NULL )
    {
        printf("Failed to read the name\n");
        return 1;
    }
    myname[strlen(myname) - 1] = '\0';

    if ( mkfifo(myname, 0666) )
    {
        printf("Failed to create FIFO\n");
        return 1;
    }
    else printf("Created FIFO\n");

    int my = 0;
    if ( -1 == (my = open(myname, O_RDONLY | O_NONBLOCK)) )
    {
        printf("Failed to open receiving FIFO\n");
        return 1;
    }

    printf("Enter FIFO name to send: ");
    char othername[MAX_BUF] = {};
    if ( fgets(othername, MAX_BUF, stdin) == NULL )
    {
        printf("Failed to read the name\n");
        return 1;
    }
    othername[strlen(othername) - 1] = '\0';


    if ( !strncmp(myname, othername, MAX_BUF) )
    {
        printf("FIFO names must be different\n");
        return 1;
    }

    int other = 0;
    if ( -1 == (other = open(othername, O_WRONLY | O_NONBLOCK)) )
    {
        printf("Failed to open sending FIFO\n");
        return 1;
    }

    printf("Enter message to send: ");
    char msg[MAX_BUF] = {};
    if ( fgets(msg, MAX_BUF, stdin) == NULL )
    {
        printf("Failed to read the message\n");
        return 1;
    }

    if ( -1 == write(other, msg, strlen(msg) + 1) )
    {
        printf("Failed to send the message\n");
        return 1;
    } else printf("Message sent\n");

    printf("Waiting for a message....\n");
 
    // Turn off nonblocking
    int old_flags = fcntl(my, F_GETFL);
    fcntl(my, F_SETFL, old_flags & ~O_NONBLOCK);

    char msgbuf[MAX_BUF] = {};
    if ( -1 == read(my, msgbuf, MAX_BUF) )
    {
        printf("Failed to receive a message\n");
        return 1;
    }

    printf("Received: %s\n", msgbuf);

    close(other);
    close(my);

    printf("Removing FIFO\n");
    remove(myname);
}
