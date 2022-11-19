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

/*------------------------------------------------- alidacionAsignacion -----
         |  Function alidacionAsignacion
         |
         |  Purpose:  Esta funcion se encarga de validar si es que algun lado
		 |  de la pieza sea igual al lado libre de las piezas que estan en la
		 |  mesa. Si es asi, se asigna la pieza a la mesa y se cambia el estado
		 |  de la pieza a 1, indicando que ya no esta libre.
         |
         |  Parameters:
         |      MSG *m : mensaje entre procesos
		 |      Nodo *l: pieza de la izquierda
		 |		Modo *r: pieza de la derecha
         |
         |  Returns:  No retorna nada, ya que es void
         *-------------------------------------------------------------------*/
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


/*------------------------------------------------- sum -----
         |  Function sum
         |
         |  Purpose:  Esta funcion se encarga de sumar los puntos de los 2 lados de
		 |  las piezas de una mano.
         |
         |  Parameters:
         |      Pieza mano[MAZO] : arreglo (mano) de piezas
         |
         |  Returns:  int: retorna la suma de los lados de las piezas de la mano
         *-------------------------------------------------------------------*/
int sum(Pieza mano[MAZO]){
	int contador = 0;
	for(int i = 0; i < MAZO; i++)
		if(!mano[i].asignada){
			printf(" %d/%d",mano[i].p1,mano[i].p2);
			contador += mano[i].p1 + mano[i].p2;
		};

	if(!contador)
	 printf(" Vacio y suma 0.");
	else printf(" y suma %d.",contador);
	return contador;
}

/*------------------------------------------------- juez -----
         |  Function juez
         |
         |  Purpose:  Esta funcion se encarga de recibir la informacion de los mazos, elige 
		 |  que jugador empieza, muestra la informacion de la mesa y llama a la funcion validacionAsignacion.
		 |  Tambien muestra si es que un jugador jugó alguna pieza o pasó. Finalmente llama a la funcion sum
		 |  para mostrar la suma de los puntos de cada jugador y ver cual es el menor.
         |  Parameters:
         |      fd[PLAYERS][2] : arreglo de pipes
         |
         |  Returns:  No retorna nada, ya que es void
         *-------------------------------------------------------------------*/
void juez(int fd[PLAYERS][2]){
	MSG m;
	Nodo l,r;


	int jugador,piezas_jugadas = 0,saltos = 0;

	jugador = rand() % PLAYERS;

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
	printf("Inicia el jugador %d con la pieza %d/%d.\n",jugador + 1,m.p.p1,m.p.p2);

	int contador = 0;
	for(jugador = (jugador + 1) % PLAYERS;
			saltos < PLAYERS && m.cantidad_piezas > 0;
			jugador = (jugador + 1) % PLAYERS){

		printf("Libres: %d -- %d\n", l.libre,r.libre);

		m.l = l.libre;
		m.r = r.libre;

		do{
			write(fd[jugador][1],(char *) &m, sizeof(MSG));

			waitRead(fd[jugador][0],(char *) &m, sizeof(MSG));
			validacionAsignacion(&m,&l,&r);
			if(!m.piezaValida)
				printf("La pieza es invalida.\nElige otra o pasa.\n");
		}while(!m.piezaValida && !m.pasa);
		m.piezaValida = 1;
		write(fd[jugador][1],(char *) &m, sizeof(MSG));
		if(m.pasa){
			printf("El jugador %d paso.\n",jugador + 1);
			m.pasa = 0;
			saltos++;
		}else printf("El jugador %d jugó %d/%d\n",jugador + 1,m.p.p1,m.p.p2);

		contador++;
		if(contador == PLAYERS && saltos != PLAYERS){
			saltos = 0;
			contador = 0;
		}

	}

	int player,menor = 1000000;
	m.status = 2;
	printf("Fin de bucle\n");
	for(int i = 0; i < PLAYERS; i++){
		write(fd[i][1],(char *) &m, sizeof(MSG));
		waitRead(fd[i][0],(char *) &m, sizeof(MSG));
		printf("La mano del jugador %d es",i + 1);
		int temp = sum(m.mano);
		printf("\n");
		if(temp < menor){
			menor = temp;
			player = i;
		}
	}

	printf("El ganador es: %i\n",player + 1);

}
