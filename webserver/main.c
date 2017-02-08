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
  int socket_srv4;
  //int socket_srv6;
  int socket_client4;
  //int socket_client6;
  char recvBuff[1024];
  char welcome[256] = "Ohayo\nTire au Lapin\nChasseur chassant chausette\nWill Crappy creep\nFreddy les griffe du night\ndeja a cours d'idee\nunicode plz (づ◔ ͜ʖ◔)づ\nsocketv6 marche steup ( ﾟロ ﾟ)\nla magie du gwak (∩ ͡°ᴥ ͡°)⊃━☆ﾟ.*\nNOTHING¯\\_ツ_/¯\n\0";

  int pid4;
  //int pid6;
  int n;
  n = 0;
  pid4 = fork();
  printf("fils4:%d\n", pid4);
  if (pid4 == 0)
  {
    socket_srv4 = create_socket4(8080);
    if (socket_srv4 == -1)
    {
      perror("create socket4 error");
      return -1;
    }
    socket_client4 = accept(socket_srv4, NULL, NULL);
    if (socket_client4 == -1)
    {
      perror("accept4 error");
      return -1;
    }

    sleep(1);
    
    if (write(socket_client4, welcome, strlen(welcome)) == -1)
    {
      perror("write4_welcome");
    }

    while ((n = read(socket_client4, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
      recvBuff[n] = 0;
      if (write(socket_client4, recvBuff, strlen(recvBuff)) == -1)
      {
        perror("write4");
      }
      if(fputs(recvBuff, stdout) == EOF)
      {
          printf("nope4");
          //exit(0);
      }
    }
  }

/*
  pid6 = fork();
  printf("fils6:%d\n", pid6);
  if (pid6 == 0)
  {
    socket_srv6 = create_socket6(8081);
    if (socket_srv6 == -1)
    {
      perror("create socket6 error");
      return -1;
    }
    socket_client6 = accept(socket_srv6, NULL, NULL);
    if (socket_client6 == -1)
    {
      perror("accept6 error");
      return -1;
    }
    while ((n = read(socket_client6, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
    if (write(socket_client6, recvBuff, strlen(recvBuff)) == -1)
    {
      perror("write6");
    }
      recvBuff[n] = 0;
      if(fputs(recvBuff, stdout) == EOF)
      {
          printf("nope6");
          exit(0);
      }
    }
  }
*/



  return 0;
 }
