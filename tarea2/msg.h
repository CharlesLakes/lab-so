#ifndef MSG_H_
#define MSG_H_
#include "pieza.h"

typedef struct msg{
	int status;
	int l;
	int r;
	int cantidad_piezas;
	Pieza p;

}MSG;


#endif