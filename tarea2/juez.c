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
	int libre;
}Nodo;

void validacionAsignacion(MSG *m,Nodo *l,Nodo *r){
	if(m->pasa)
		return;
	m->piezaValida = 1;

	if(m->p.p1 == l->libre){
		l->c = m->p;
		l->libre = m->p.p2;
		return;
	}

	if(m->p.p1 == r->libre){
		r->c = m->p;
		r->libre = m->p.p2;
		return;
	}

	if(m->p.p2 == l->libre){
		l->c = m->p;
		l->libre = m->p.p1;
		return;
	}

	if(m->p.p2 == r->libre){
		r->c = m->p;
		r->libre = m->p.p1;
		return;
	}

	m->piezaValida = 0;
};

int sum(Pieza mano[MAZO]){
	int contador = 0;
	for(int i = 0; i < MAZO; i++)
		if(!mano[i].asignada)
			contador += mano[i].p1 + mano[i].p2;

	return contador;
}

void juez(int fd[PLAYERS][2]){
	MSG m;
	Nodo l,r;


	int jugador,piezas_jugadas = 0,saltos = 0;

	jugador = 0;//rand() % PLAYERS;

	m.status = 0;
	m.pasa = 0;
	m.piezaValida = 1;

	write(fd[jugador][1],(char *) &m, sizeof(MSG));

	waitRead(fd[jugador][0],(char *) &m, sizeof(MSG));

	l.c = r.c = m.p;
	l.libre = l.c.p1;
	r.libre = r.c.p2;
	m.status = 1;

	piezas_jugadas++;


	for(jugador = 0;//(jugador + 1) % PLAYERS;
			saltos < PLAYERS && m.cantidad_piezas > 0;
			jugador = 0/*(jugador + 1) % PLAYERS*/){

		printf("Libres: %d -- %d\n", l.libre,r.libre);

		m.l = l.libre;
		m.r = r.libre;

		do{
			write(fd[jugador][1],(char *) &m, sizeof(MSG));

			waitRead(fd[jugador][0],(char *) &m, sizeof(MSG));
			validacionAsignacion(&m,&l,&r);
			if(!m.piezaValida)
				printf("La pieza es invalida.\nElige otra o pasa.\n");
			printf("%d\n",m.pasa);
		}while(!m.piezaValida && !m.pasa);
		m.piezaValida = 1;
		write(fd[jugador][1],(char *) &m, sizeof(MSG));
		if(m.pasa){
			printf("El jugador %d paso.\n",jugador + 1);
			m.pasa = 0;
			saltos++;
		}
	}

	int player,menor = 1000000;
	m.status = 2;
	for(int i = 0; i < PLAYERS; i++){
		write(fd[i][1],(char *) &m, sizeof(MSG));
		waitRead(fd[i][0],(char *) &m, sizeof(MSG));
		int temp = sum(m.mano);
		if(temp < menor){
			menor = temp;
			player = i;
		}
	}

	printf("El ganador es: %i\n",player + 1);

}
