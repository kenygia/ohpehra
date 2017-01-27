#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
  int socket_serveur;
  socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
   if (socket_serveur == -1)
   {
     /* traitement de l’erreur */
     perror("socket_serveur");
   } /* Utilisation de la socket serveur */
   
   return 0;
 }
