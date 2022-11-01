juez.o: juez.c
	gcc juez.c -c
jugador.o: jugador.c
	gcc jugador.c -c
npc.o: npc.c
	gcc npc.c -c
main.o: main.c
	gcc main.c -c
msg.o: msg.c
	gcc msg.c -c
compile: main.o juez.o jugador.o npc.o msg.o
	gcc main.o juez.o jugador.o npc.o msg.o -o main
run:
	./main
CANDR: compile run
delete:
	rm *.o main
