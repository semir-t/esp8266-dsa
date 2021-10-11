/*
    C ECHO client example using sockets
*/
//Kompajlirajte sa: gcc  echoclient.c  -o  echoclient i startajte sa ./echoclient u terminal prozoru

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <stdlib.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Server Cofigure
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SERVER_PORT 8888

//nc -lkv -p 8888

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[100];
    /* int read_size; */

    // specify server
    // server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_addr.s_addr = inet_addr("192.168.0.108");
    /* server.sin_addr.s_addr = INADDR_ANY; */
    server.sin_family = AF_INET;
    server.sin_port = htons( SERVER_PORT );

    //keep the program running until user terminates the program
    //Create socket
    //0 indicates that the caller does not want to specify the protocol and will leave it up to the service provider.
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
        return -1;
    }
    puts("Socket created");

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return -1;
    }
    puts("Connected\n");
    while(1)
    {
        printf("Enter text to send: ");
        fgets(message,100,stdin);
        if(send(sock ,message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
        }
    }
    return 0;
}
