#include "jugador.h"
#include "msg.h"
#include <stdio.h>
#include <unistd.h>

/*------------------------------------------------- obtenerMayor -----
         |  Function obtenerMayor
         |
         |  Purpose:  Esta funcion se encarga de buscar la pieza que 
		 |  al sumar sus caras sea la mayor.
         |
         |  Parameters:
         |      Pieza *mano : arreglo (mano) de piezas.
         |
         |  Returns:  Pieza *pieza : retorna la pieza mayor.
         *-------------------------------------------------------------------*/
Pieza* obtenerMayor(Pieza *mano){
	Pieza *temp;
	int mayor = -1;

	for(int i = 0; i < MAZO; i++)
		if(mayor < mano[i].p1 + mano[i].p2 && !mano[i].asignada){
			mayor = mano[i].p1 + mano[i].p2;
			temp = &mano[i];
		};
	temp->asignada = 1;

	return temp;
};

/*------------------------------------------------- printMazo -----
         |  Function printMazo
         |
         |  Purpose:  Esta funcion se encarga de imprimir el mazo, mostrando
		 |  las piezas que no han sido asignadas.
         |
         |  Parameters:
         |      Pieza mano[MAZO]: la mano del jugador.
         |
         |  Returns:  No retorna nada, ya que es void.
         *-------------------------------------------------------------------*/
void printMazo(Pieza mano[MAZO]){
	for(int i = 0; i < MAZO; i++)
		if(!mano[i].asignada)
			printf("%d) %d/%d\n", i,mano[i].p1,mano[i].p2);
}

/*------------------------------------------------- jugador -----
         |  Function jugador
         |
         |  Purpose:  Esta funcion se encarga de inicializar la mano del jugador,
		 |  colocar la pieza mayor en la mesa si es que le toca iniciar. Luego muestra 
		 |  el mazo y espera a que el usuario ingrese la pieza que desea colocar en la mesa.
		 |  Y finalmente cambia el estado de las piezas y envia la info al juez.
		 |
         |  Parameters:
         |      fd[PLAYERS][2] : arreglo de pipes
         |
         |  Returns:  No retorna nada, ya que es void
         *-------------------------------------------------------------------*/
void jugador(int fd[2],Pieza mano[MAZO]){
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
				printf("Elige la pieza.\n");
				printMazo(mano);
				printf("Si quieres pasar ingresa -1.\n");
				scanf("%i",&opcion);
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

};
