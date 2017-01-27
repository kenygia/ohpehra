#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include "socket.h"

int main(void/*int argc, char **argv*/)
{
  int socket_srv;
  int socket_client;
  char recvBuff[1024];
  int n;

  n = 0;
  socket_srv = creer_serveur(8080);
  socket_client = accept(socket_srv, NULL, NULL);

  if (socket_client == -1)
  {
    perror("accept error");
   }
  while ((n = read(socket_client, recvBuff, sizeof(recvBuff)-1)) > 0)
  {
    recvBuff[n] = 0;
    if(fputs(recvBuff, stdout) == EOF)
    {
        printf("nope");
    }
  }

  return 0;
 }
