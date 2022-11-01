#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "vars.h"
#include "pieza.h"
#include "juez.h"
#include "jugador.h"
#include "npc.h"

Pieza Piezas[SIZE];

void init(Pieza P[]){
    // Definiciones
    int i,j,temp,count = 0;
    Pieza clon[SIZE];
    srand(time(NULL));

    // Se genera el mazo
    for(i = 0; i <= MAX; i++){
        for(j = 0; j <= i; j++){
            P[count + j].p1 = i;
            P[count + j].p2 = j;
            P[count + j].asignada = 0;
        }
        count += i + 1;
    }


    // Se revuelve el mazo
    count = 0;
    for(i = 0; i < SIZE; i++){
        temp = rand() % (SIZE - 1);
        for(j = 0; j < SIZE && temp > -1; j = (j + 1) % SIZE)
            if(!P[j].asignada){
                temp--;
                if(temp < 0)
                    j--;
            }

        P[j].asignada = 1;
        clon[count++] = P[j];
    }

    for(i = 0; i < SIZE; i++)
        P[i] = clon[i];


}

void initDoublePipe(int *fd1, int *fd2){
    pipe(fd1);
    pipe(fd2);
};

void configDoublePipe(int pid,int *fd1, int *fd2, int *final){
    if(pid == 0){
        close(fd1[0]);
        close(fd2[1]);

        final[0] = fd2[0];
        final[1] = fd1[1];

        return;
    }

    close(fd1[1]);
    close(fd2[0]);

    final[0] = fd1[0];
    final[1] = fd2[1];
};

int main(){
    init(Piezas);

    int pid,i,pipes[PLAYERS][2],fd1[2],fd2[2];

    initDoublePipe(fd1,fd2);
    pid = fork();
    configDoublePipe(pid,fd1,fd2,pipes[0]);

    if(pid == 0){
        jugador(pipes[0],&Piezas[0]);
        close(pipes[0][0]);
        close(pipes[0][1]);
        return 0;
    }
    for(i = 0; i < PLAYERS - 1; i++){
        initDoublePipe(fd1,fd2);
        pid = fork();
        configDoublePipe(pid,fd1,fd2,pipes[i + 1]);
        if(pid == 0){
            npc(pipes[i + 1],&Piezas[MAZO*(i + 1)]);
            close(pipes[i + 1][0]);
            close(pipes[i + 1][1]);
            return 0;
        }
    }


    juez(pipes);
    for(int i = 0; i < PLAYERS; i++){
      close(pipes[i][0]);
      close(pipes[i][1]);
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
