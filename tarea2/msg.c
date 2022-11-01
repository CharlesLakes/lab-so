#include "msg.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

//read(fd[jugador][0],(char *) &m, sizeof(MSG));


/*------------------------------------------------- waitRead -----
         |  Function waitRead
         |
         |  Purpose:  Esta funcion se encarga de leer un mensaje del pipe.
         |  Parameters:
         |      int fd: Es el file descriptor del pipe que se va a leer
         |      char *m: Es el mensaje que se va a leer
         |      int size: Es el tamaño del mensaje
         |
         |  Returns:  No retorna nada, ya que es void
         *-------------------------------------------------------------------*/
void waitRead(int fd, char *m, int size){
  int nread;
  while((nread = read(fd,m,size)) <= 0);
};
