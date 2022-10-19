#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "vars.h"
#include "pieza.h"
#include "juez.h"

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

int main(){
    init(Piezas);

    int pid,i,pipes[PLAYERS][2];

    pid = fork();
    if(pid == 0){
        // Player
        return 0;
    }

    for(i = 0; i < PLAYERS - 1; i++){
        pid = fork();
        if(pid == 0){
            // Maquinas
            return 0;
        }
    }

    juez(pipes);

    return 0;
}