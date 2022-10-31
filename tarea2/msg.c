#include "msg.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

//read(fd[jugador][0],(char *) &m, sizeof(MSG));
void waitRead(int fd, char *m, int size){
  int nread;
  while((nread = read(fd,m,size)) <= 0);
};
