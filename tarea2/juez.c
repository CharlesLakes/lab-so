#include "juez.h"
#include "pieza.h"
#include "msg.h"
#include "vars.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct nodo{
	Pieza c;
	Pieza* p1;
	Pieza* p2;
}Nodo;

Pieza temp[SIZE];



void juez(int fd[PLAYERS][2]){
	int turno;
	MSG m;

	
	turno = 0;//rand() % PLAYERS;

	m.status = 0;


	write(fd[turno][1],(char *) &m, sizeof(MSG));

	read(fd[turno][0],(char *) &m, sizeof(MSG));

	printf("%d/%d\n",m.p.p1,m.p.p2);
	

}