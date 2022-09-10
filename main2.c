#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct year{
    char year[4];
    int a;
    int b;
    int c;
}Year;

/*------------------------------------------------- countFiles -----
         |  Function countFiles
         |
         |  Purpose:  Entra al directorio del año y cuenta la cantidad de archivos que hay en cada subdirectorio
         |            de prioridades. Luego, guarda la cantidad de archivos en el struct Year.
         |
         |  Parameters:
         |      char carpeta[] (IN) -- directorio de un año en específico.
         |      Year *y (IN) -- estructura que contiene los 3 años.
         |
         |  Returns:  Cuántos archivos hay en todos los directorios de prioridad de un año en específico.
         |            no retorna nada.
         |     
         *-------------------------------------------------------------------*/
void countFiles(char carpeta[],Year *y){

    DIR* directory;
    char *temp , buffer[15];
    struct dirent* ent;

    strcpy(buffer,carpeta);
    strcat(buffer,"/");
    
    temp = &buffer[strlen(buffer)];

    //3000+
    strcpy(temp,"3000+");
    directory = opendir(buffer);
    if(directory == NULL){
        printf("No se pudo abrir la carpeta");
        return;
    }
    y->a=0;
    while ((ent=readdir(directory)) != NULL){
        if(strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name,"..") == 0)
            continue;
        y->a++;
    }
    
    //6000+
    strcpy(temp,"6000+");
    directory = opendir(buffer);
    if(directory == NULL){
        printf("No se pudo abrir la carpeta");
        return;
    }
    y->b=0;
    while ((ent=readdir(directory)) != NULL){
        if(strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name,"..") == 0)
            continue;
        y->b++;
    }

    //9000+
    strcpy(temp,"9000+");
    directory = opendir(buffer);
    if(directory == NULL){
        printf("No se pudo abrir la carpeta");
        return;
    }
    y->c=0;
    while ((ent=readdir(directory)) != NULL){
        if(strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name,"..") == 0)
            continue;
        y->c++;
    } 
    closedir (directory);
}

/*------------------------------------------------- main -----
         |  Function main
         |
         |  Purpose:  Crea el struct Year y llama a la función countFiles para cada año, luego imprime los resultados.
         |
         |  Parameters:
         |
         |  Returns:  Retorna 0 si todo sale bien.
         |     
         *-------------------------------------------------------------------*/
int main(){
    Year y[3];
    countFiles("2019", &y[0]);
    countFiles("2020", &y[1]);
    countFiles("2021", &y[2]);

    int sum2019 = y[0].a + y[0].b + y[0].c;
    int sum2020 = y[1].a + y[1].b + y[1].c;
    int sum2021 = y[2].a + y[2].b + y[2].c;

    printf("La cantidad de estudiantes de 2019 es: %d \n",sum2019);
    printf("\t La cantidad de estudiantes de 2019 con prioridad 3000-5999 es: %d \n",y[0].a);
    printf("\t La cantidad de estudiantes de 2019 con prioridad 6000-8999 es: %d \n",y[0].b);
    printf("\t La cantidad de estudiantes de 2019 con prioridad 9000+ es: %d \n",y[0].c);

    printf("La cantidad de estudiantes de 2020 es: %d \n",sum2020);
    printf("\t La cantidad de estudiantes de 2020 con prioridad 3000-5999 es: %d \n",y[1].a);
    printf("\t La cantidad de estudiantes de 2020 con prioridad 6000-8999 es: %d \n",y[1].b);
    printf("\t La cantidad de estudiantes de 2020 con prioridad 9000+ es: %d \n",y[1].c);

    printf("La cantidad de estudiantes de 2021 es: %d \n",sum2021);
    printf("\t La cantidad de estudiantes de 2021 con prioridad 3000-5999 es: %d \n",y[2].a);
    printf("\t La cantidad de estudiantes de 2021 con prioridad 6000-8999 es: %d \n",y[2].b);
    printf("\t La cantidad de estudiantes de 2021 con prioridad 9000+ es: %d \n",y[2].c);
    
    return 0;
}