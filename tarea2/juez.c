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
	int libre
}Nodo;


void juez(int fd[PLAYERS][2]){
	MSG m;
	Nodo l,r;


	int jugador,piezas_jugadas = 0,saltos = 0;
	
	jugador = 0;//rand() % PLAYERS;

	m.status = 0;


	write(fd[jugador][1],(char *) &m, sizeof(MSG));

	read(fd[jugador][0],(char *) &m, sizeof(MSG));

	l.c = r.c = m;
	l.libre = l.c.p1;
	r.libre = r.c.p2;
	
	piezas_jugadas++;

	jugador = (jugador + 1) % PLAYERS;

	for(jugador = (jugador + 1) % PLAYERS;
		saltos < PLAYERS && m.cantidad_piezas == 0;
		jugador = (jugador + 1) % PLAYERS){

		write(fd[jugador][1],(char *) &m, sizeof(MSG));
		read(fd[jugador][0],(char *) &m, sizeof(MSG));

		if()

	}


}