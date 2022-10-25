#include "jugador.h"
#include "msg.h"
#include <stdio.h>
#include <unistd.h>

void jugador(int fd[2],Pieza mano[MAZO]){
	MSG m;

	for(int i = 0; i < MAZO; i++)
		mano[i].asignada = 0;

	
	read(fd[0],(char *) &m, sizeof(MSG));



	if(m.status == 0){
		Pieza temp;
		int mayor = -1;
		for(int i = 0; i < MAZO; i++)
			if(mayor < mano[i].p1 + mano[i].p2){
				mayor = mano[i].p1 + mano[i].p2;
				temp = mano[i];
			};
		temp.asignada = 1;

		m.p = temp;

		write(fd[1],(char *) &m, sizeof(MSG));
	};




	
};