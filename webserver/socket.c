#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int creer_serveur(int port)
{
  int socketfd;
  struct sockaddr_in srv_addr;

  srv_addr.sin_family = AF_INET;
  srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  srv_addr.sin_port = htons(port);

  socketfd = socket(AF_INET, SOCK_STREAM, 0);

   if (socketfd == -1)
   {
     perror("socket error");
     return -1;
   }

   if(bind(socketfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == -1)
   {
     perror("bind socket error");
     return -1;
   }

   if(listen(socketfd, 10) == -1)
   {
     perror("bind socket error");
     return -1;
   }
   return socketfd;
}
