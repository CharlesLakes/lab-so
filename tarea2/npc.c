#include <unistd.h>
#include "npc.h"
#include "jugador.h"
#include "msg.h"

void npc(int fd[2],Pieza mano[MAZO]){
	MSG m;

	for(int i = 0; i < MAZO; i++)
		mano[i].asignada = 0;


	read(fd[0],(char *) &m, sizeof(MSG));



	if(m.status == 0){
		Pieza *mayor = obtenerMayor(mano);

		m.p = *mayor;
		m.cantidad_piezas = MAZO - 1;

		write(fd[1],(char *) &m, sizeof(MSG));
	}else m.cantidad_piezas = MAZO;
}
