Nombres:
    Carlos Lagos, 202073571-9, 201
    José Pinto, 202073559-K, 201

juez.c juez.h -> Corresponde a las funcionalidades del padre
jugador.c jugador.h -> Corresponde a las funcionalidades del jugador (Usuario)
npc.c npc.h -> Corresponde a las funcionalidades de los otros jugadores
msg.c msg.h -> Corresponde a la convencion de los mensajes ente procesos
pieza.h -> Se definen constantentes correspondientes a las piezas
vars.h -> Se definen variables globales (Ej: maximo de jugadores, mazo, etc)


Makefile:
    Para compilar y ejecutar el programa usa:
        make RunAndCompile
    Para solo compilar usar:
        make compile
    Para solo ejecutar usar:
        make run
    En caso de no poder ejecutar con estos comandos usar:
        Para compilar:
            gcc main.c juez.c jugador.c npc.c msg.o -o main
        Para ejecutar:
            ./main
