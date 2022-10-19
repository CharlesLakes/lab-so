juez.o: juez.c
	gcc juez.c -c
jugador.o: jugador.c
	gcc jugador.c -c
npc.o: npc.c
	gcc npc.c -c
main.o: main.c
	gcc main.c -c
compile: main.o juez.o jugador.o npc.o
	gcc main.o juez.o jugador.o npc.o -o main
delete: 
	rm *.o main