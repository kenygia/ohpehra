#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int create_socket4(int port)
{
  int socketfd;
  struct sockaddr_in srv_addr;
  int mode;

  mode = 1;
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  srv_addr.sin_port = htons(port);

  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  if (socketfd == -1)
  {
    perror("socket4 error");
  }
  if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR,(char *)&mode,sizeof(mode)) < 0)
  {
    perror("set socket4 failed");
  }
  if(bind(socketfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == -1)
  {
    perror("bind socket4 error");
  }

  if(listen(socketfd, 10) == -1)
  {
    perror("listen socket4 error");
  }
  return socketfd;
}

int create_socket6(int port)
{
  int socketfd;
  struct sockaddr_in6 srv_addr;
  int mode;

  mode = 1;
  srv_addr.sin6_family = AF_INET6;
  srv_addr.sin6_addr = in6addr_any;
  srv_addr.sin6_port = htons(port);

  socketfd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

   if (socketfd == -1)
  {
    perror("socket6 error");
    return -1;
  }
  if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR,(char *)&mode,sizeof(mode)) < 0)
  {
    perror("set socket6 failed");
    return -1;
  }
  if(bind(socketfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == -1)
  {
    perror("bind socket6 error");
    return -1;
  }

   if(listen(socketfd, 10) == -1)
  {
    perror("listen socket6 error");
    return -1;
  }
   return socketfd;
}

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
   }

   if(bind(socketfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == -1)
   {
     perror("bind socket error");
   }

   if(listen(socketfd, 10) == -1)
   {
     perror("bind socket error");
   }
   return socketfd;
}
