Nombres:
    Carlos Lagos, 202073571-9, 201
    José Pinto, 202073559-K, 201

Archivos:
    ConHebras.java -> Archivo que contiene el algoritmo con ConHebras
    SinHebras.java -> Archivo que contiene el algoritmo sin ConHebras

Comentarios:
    * Se imprime el tiempo de ejecución de cada algoritmo junto con la solución final.
    * Se toma el archivo "informe-nautico.txt" como entrada de datos, no por consola.

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
