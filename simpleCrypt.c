#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_BUFFER 10
static bool usage(int argc,char **argv)
{
  if(argc<4)
    {
      fprintf(stderr,"\n\nAttention !\nUsage : fichier1 fichier2 cle\n\n");
      return false;
    }
  return true;
}
static void erreurSi(int cond,char *msg)
{
  if(cond)
    {
      perror(msg);
      exit(1);
    }
}
int main(int argc,char **argv)
{
  if(!usage(argc,argv))
    {
      return EXIT_FAILURE;
    }
  int fdRead=open(argv[1],O_RDONLY);
  erreurSi(fdRead<0,"Erreur ouverture fichier read");
  int fdWrite=open(argv[2],O_CREAT|O_TRUNC|O_WRONLY,0666);
  erreurSi(fdWrite<0,"Erreur ouverture fichier write");

  char buffer[TAILLE_BUFFER];
  char *cle=argv[3];
  int tailleCle=strlen(cle);
  int nb;
  int i;
  while((nb=read(fdRead,buffer,sizeof(char)*TAILLE_BUFFER))>0)
    {
      for(i=0;i<nb;i++){
	buffer[i]^=cle[i%tailleCle];
      }
      write(fdWrite,buffer,sizeof(char)*nb);
    }
  
  
  close(fdRead);
  close(fdWrite);
  return EXIT_SUCCESS;

}
