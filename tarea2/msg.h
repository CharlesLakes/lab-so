#ifndef MSG_H_
#define MSG_H_
#include "vars.h"
#include "pieza.h"

typedef struct msg{
	int status;
	int piezaValida;
	int cantidad_piezas;
	int suma;
	int pasa;
	int l;
	int r;
	Pieza p;
	Pieza mano[MAZO];

}MSG;

void waitRead(int fd, char *m, int size);

#endif
