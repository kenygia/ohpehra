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
  printf("child_sig:%d \n", sig);
  while(waitpid(-1, NULL, WNOHANG));
}

void initialiser_signaux(void)
{
  struct sigaction sa;

  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
  {
    perror("signal");
  }

  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask); sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD, &sa, NULL) == -1)
  {
    perror("sigaction(SIGCHLD)");
  }
}

int socket_field(int version)
{
  pid_t pid;
  int socket_srv;
  int socket_cli;
  FILE *sockfd;
  char welcome[256] = "Ohayo\nTire au Lapin\nChasseur chassant chausette\nWill Crappy creep\nFreddy les griffe du night\ndeja a cours d'idee\nunicode plz (づ◔ ͜ʖ◔)づ\nsocketv6 marche steup ( ﾟロ ﾟ)\nla magie du gwak (∩ ͡°ᴥ ͡°)⊃━☆ﾟ.*\nNOTHING¯\\_ツ_/¯\n\0";

  char buff[1024];
  if (version == 4)
    socket_srv = create_socket4(8080);
  else if (version == 6)
    socket_srv = create_socket6(8080);
  else
    socket_srv = -1;

  if (socket_srv == -1)
  {
    perror("create socket4 error");
    return -1;
  }

  while ((socket_cli = accept(socket_srv, NULL, NULL)))
  {
    if (socket_cli == -1)
    {
      if(errno == EINTR)
        continue;
      perror("accept error");
      return -1;
    }

    sockfd = fdopen(socket_cli,"w+");

    sleep(1);

    pid = fork();
    printf("child:%d\n", pid);
    if(pid == 0)
    {
      if (fprintf(sockfd, "%s",welcome) < 0)
      {
        perror("fprintf_welcome");
        return -1;
      }


      while (fgets(buff, sizeof(buff)-1, sockfd) != NULL)
      {
        if (fprintf(sockfd, "<Light House> ") < 0 )
        {
          perror("fprintf_prefix");
          return -1;
        }

        if (fprintf(sockfd, "%s",buff) < 0 )
        {
          perror("fprintf");
          return -1;
        }

      }
      exit(0);
    }
  }
  close(socket_cli);

  return 0;
}

int main(void/*int argc, char **argv*/)
{

  initialiser_signaux();

  int sock4 = socket_field(4);
  printf("%d\n", sock4);

//  int sock6 = socket_field(6);
//  printf("%d\n", sock6);

  return 0;
 }
