#include <stdio.h>
#include <unistd.h>
#include "npc.h"
#include "jugador.h"
#include "msg.h"

/*------------------------------------------------- simularOpcion -----
         |  Function simularOpcion
         |
         |  Purpose:  Esta funcion se encarga de simular la opcion del NPC.
         |
         |  Parameters:
		 |		MSG m : mensaje entre procesos
         |      Pieza mano[MAZO]: la mano del jugador.
         |
         |  Returns:  int : retorna la opcion que el NPC eligio o -1.
         *-------------------------------------------------------------------*/
int simularOpcion(MSG m,Pieza mano[MAZO]){
	for(int i = 0; i < MAZO; i++)
		if(!mano[i].asignada &&
			(mano[i].p1 == m.l || mano[i].p1 == m.r || mano[i].p2 == m.l || mano[i].p2 == m.r))
			return i;

	return -1;
};

/*------------------------------------------------- npc -----
         |  Function npc
         |
         |  Purpose:  Esta funcion se encarga de inicializar la mano del npc,
		 |  colocar la pieza mayor en la mesa si es que le toca iniciar. Luego simula
		 |  la opcion que el NPC eligio y finalmente cambia el estado de las piezas y envia
		 |  la info al juez.
		 |
         |  Parameters:
         |      fd[2] : arreglo de pipes
		 |      Pieza mano[MAZO]: la mano del NPC
         |
         |  Returns:  No retorna nada, ya que es void
         *-------------------------------------------------------------------*/
void npc(int fd[2],Pieza mano[MAZO]){
	MSG m;
	int cantidad_piezas = MAZO;

	for(int i = 0; i < MAZO; i++)
		mano[i].asignada = 0;

	do{
		waitRead(fd[0],(char *) &m, sizeof(MSG));
		if(m.status == 0){
			Pieza *mayor = obtenerMayor(mano);

			m.p = *mayor;
			m.cantidad_piezas = --cantidad_piezas;
			m.status = 1;
			m.piezaValida = 1;
			write(fd[1],(char *) &m, sizeof(MSG));
			continue;
		}else m.cantidad_piezas = cantidad_piezas;
		int opcion;
		if(m.status == 2)
			break;
		do{

			do{
				opcion = simularOpcion(m, mano);
				if(opcion == -1)
					break;
				if(opcion < 0 || opcion >= MAZO || mano[opcion].asignada)
					printf("Pieza incorrecta.\nIntenta nuevamente.\n");
			}while(opcion < 0 || opcion >= MAZO || mano[opcion].asignada);
			if(opcion != -1){
				m.p = mano[opcion];
				m.cantidad_piezas = --cantidad_piezas;
			}
			else m.pasa = 1;

			write(fd[1],(char *) &m, sizeof(MSG));
			waitRead(fd[0],(char *) &m, sizeof(MSG));
		}while(!m.piezaValida);
	if(opcion != -1) mano[opcion].asignada = 1;
	}while(m.status == 1);

	for(int i = 0; i < MAZO; i++)
		m.mano[i] = mano[i];
	write(fd[1],(char *) &m, sizeof(MSG));
}
