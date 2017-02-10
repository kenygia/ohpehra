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
  int sockfd;
  struct sockaddr_in srv_addr;
  int mode;
  int opt_reuseadddr;

  mode = 1;
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  srv_addr.sin_port = htons(port);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd == -1)
  {
    perror("socket4 error");
    return -1;
  }

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(char *)&mode,sizeof(mode)) < 0)
  {
    perror("set socket4 failed");
    return -1;
  }

  if(bind(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == -1)
  {
    perror("bind socket4 error");
    return -1;
  }

  if(listen(sockfd, 10) == -1)
  {
    perror("listen socket4 error");
    return -1;
  }

  opt_reuseadddr = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_reuseadddr, sizeof(int)) == -1)
  {
    perror("Can not set SO_REUSEADDR option4");
    return -1;
  }

  return sockfd;
}

int create_socket6(int port)
{
  int sockfd;
  struct sockaddr_in6 srv_addr;
  int opt_reuseadddr;

  srv_addr.sin6_family = AF_INET6;
  srv_addr.sin6_addr = in6addr_any;
  srv_addr.sin6_port = htons(port);

  sockfd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

   if (sockfd == -1)
  {
    perror("socket6 error");
    return -1;
  }

  opt_reuseadddr = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_reuseadddr, sizeof(int)) == -1)
  {
    perror("Can not set SO_REUSEADDR option6");
    return -1;
  }

  if(bind(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == -1)
  {
    perror("bind socket6 error");
    return -1;
  }

   if(listen(sockfd, 10) == -1)
  {
    perror("listen socket6 error");
    return -1;
  }

   return sockfd;
}

int creer_serveur(int port)
{
  int sockfd;
  struct sockaddr_in srv_addr;

  srv_addr.sin_family = AF_INET;
  srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  srv_addr.sin_port = htons(port);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

   if (sockfd == -1)
   {
     perror("socket error");
   }

   if(bind(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == -1)
   {
     perror("bind socket error");
   }

   if(listen(sockfd, 10) == -1)
   {
     perror("bind socket error");
   }
   return sockfd;
}
