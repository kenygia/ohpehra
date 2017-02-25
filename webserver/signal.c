#include <stdio.h>
#include <sys/wait.h>


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
