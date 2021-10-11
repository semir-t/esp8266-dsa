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
#define NUMBER_OF_CONNECTIONS 10
#define SERVER_PORT 8888 

void * serve_client(void * sock);

int main(int argc, char *argv[])
{
  int socket_desc , client_sock , c; 
  struct sockaddr_in server , client;
  pthread_t thread;

  //Create socket
  socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if (socket_desc == -1)
  {
    printf("Could not create socket");
    return 1;
  }
  puts("Socket created");

  //Prepare the sockaddr_in structure
  //INADDR_ANY is used when you don't need to bind a socket to a specific IP. When you use this value as the address when calling bind(), 
  //the socket accepts connections to all the IPs of the machine
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(SERVER_PORT);

  //Bind
  //If any error accures then function bind return -1
  if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
  {
    //print the error message
    perror("bind failed. Error"); return 1;
  }
  puts("bind done");

  //Listen
  listen(socket_desc, NUMBER_OF_CONNECTIONS);

  while(1) 
  {
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
      perror("accept failed");
      return 1;
    }
    int *safesock = malloc(sizeof(int));
    if (safesock) {
      *safesock = client_sock;
      if (pthread_create(&thread, NULL, serve_client,safesock) != 0) {
        fprintf(stderr, "Failed to create thread\n");

      }

    }
    else {
      perror("malloc");

    }

    puts("Connection accepted");

    //call thread function
    /* serve_client(client_sock); */
  }
  return 0;
}

void * serve_client(void * sock)/*{{{*/
{
  int client_sock = *(int *) sock;
  int read_size;
  char client_message[100];
  //Receive a message from client
  while( (read_size = recv(client_sock , client_message , 100 , 0)) > 0 )
  {
    //Send the message back to client
    client_message[read_size]='\0';
    puts(client_message);
    break;
  }
  if(read_size == 0)
  {
    puts("Client disconnected");
    fflush(stdout);
  }
  else if(read_size == -1)
  {
    perror("recv failed");
  }
}/*}}}*/
