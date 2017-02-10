#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socket.h"

void traitement_signal(int sig)
{
  printf("Signal %d reçu\n", sig);
}

void initialiser_signaux(void)
{
  struct sigaction sa;

  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask); sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD, &sa, NULL) == -1)
  {
    perror("sigaction(SIGCHLD)");
  }

  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
  {
    perror("signal");
  }
}

int main(void/*int argc, char **argv*/)
{
  int socket_srv4;
  int socket_srv6;
  int socket_client4;
  int socket_client6;
  char welcome[256] = "Ohayo\nTire au Lapin\nChasseur chassant chausette\nWill Crappy creep\nFreddy les griffe du night\ndeja a cours d'idee\nunicode plz (づ◔ ͜ʖ◔)づ\nsocketv6 marche steup ( ﾟロ ﾟ)\nla magie du gwak (∩ ͡°ᴥ ͡°)⊃━☆ﾟ.*\nNOTHING¯\\_ツ_/¯\n\0";
  pid_t pid4;
  pid_t pid6;
  int n;

  initialiser_signaux();

  n = 0;
  pid4 = fork();
  printf("fils4:%d\n", pid4);
  if (pid4 == 0)
  {
    char recvBuff[1024];
    socket_srv4 = create_socket4(8080);
    if (socket_srv4 == -1)
    {
      perror("create socket4 error");
      return -1;
    }

    while ((socket_client4 = accept(socket_srv4, NULL, NULL)))
    {
      if (socket_client4 == -1)
      {
        perror("accept4 error");
        return -1;
      }
      sleep(1);
      if(fork() == 0)
      {
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
          }
        }
        exit(0);
      }
    }
    exit(0);
  }


pid6 = fork();
printf("fils6:%d\n", pid6);
if (pid6 == 0)
{
  char recvBuff[1024];
  socket_srv6 = create_socket6(8080);
  if (socket_srv6 == -1)
  {
    perror("create socket6 error");
    return -1;
  }

  while ((socket_client6 = accept(socket_srv6, NULL, NULL)))
  {
    if (socket_client6 == -1)
    {
      perror("accept6 error");
      return -1;
    }
    sleep(1);
    if(fork() == 0)
    {
      if (write(socket_client6, welcome, strlen(welcome)) == -1)
      {
        perror("write6_welcome");
      }

      while ((n = read(socket_client6, recvBuff, sizeof(recvBuff)-1)) > 0)
      {
        recvBuff[n] = 0;
        if (write(socket_client6, recvBuff, strlen(recvBuff)) == -1)
        {
          perror("write6");
        }
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("nope6");
        }
      }
      exit(0);
    }
  }
  exit(0);
}

wait(NULL);
wait(NULL);

  return 0;
 }
