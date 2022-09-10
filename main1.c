#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct data{
    char anno[10];
    int prioridad;
}Data;

/*------------------------------------------------- getDate -----
         |  Function getDate
         |
         |  Purpose:  Abre un archivo en modo lectura y obtiene la info del alumno.
         |
         |  Parameters:
         |      char filename (IN) -- nombre del archivo a abrir.
         |
         |  Returns:  Retorna el Struct Data con la info del alumno.
         *-------------------------------------------------------------------*/
Data getData(char filename[]){
    FILE *file;
    Data alumno;
    file = fopen(filename,"r");
    fscanf(file, "%s\n%d", alumno.anno,&(alumno.prioridad));
    fclose(file);

    return alumno;    
}

/*------------------------------------------------- inDir -----
         |  Function inDir
         |
         |  Purpose:  Verifica si un alumno se encuentra en un directorio.
         |
         |  Parameters:
         |      char base (IN) -- directorio a verificar.
         |      char element (IN) -- alumno a verificar.
         |
         |  Returns:  Retorna 1 si el alumno se encuentra en el directorio, 0 en caso contrario.
         *-------------------------------------------------------------------*/
int inDir(char base[], char elemento[]){
    DIR* directory = opendir(base);

    struct dirent* ent;
    while((ent = readdir(directory)))
        if(strcmp(ent->d_name, elemento) == 0){
            closedir(directory);
            return 1;
        };

    closedir(directory);
    return 0;
}

/*------------------------------------------------- isFormat -----
         |  Function isFormat
         |
         |  Purpose:  Verifica si un archivo tiene el formato correcto.
         |
         |  Parameters:
         |      char name (IN) -- nombre del archivo a verificar.
         |
         |  Returns:  Retorna 1 si el archivo tiene el formato correcto, 0 en caso contrario.
         *-------------------------------------------------------------------*/
int isFormat(char name[]){
    int size = strlen(name);
    int count = 0;

    if(size < 4)
        return 0;
    
    if(strcmp(&name[size - 4],".txt") != 0)
        return 0;

    while(count < size && name[count] != '_')
        count++;
    
    if(count == size)
        return 0;

    return 1;
}

/*------------------------------------------------- createYearDir -----
         |  Function createYearDir
         |
         |  Purpose:  Crea un directorio con el nombre del año con los directorios de las prioridades.
         |
         |  Parameters:
         |      char base (IN) -- directorio base.
         |      char anno (IN) -- año a crear.
         |
         |  Returns:  Crea el directorio con el año y con subdirectorios de prioridad.
         |            no retorna nada.
         *-------------------------------------------------------------------*/
void createYearDir(char base[], char anno[]){
    int size_base = strlen(base);
    int size_anno = strlen(anno);
    char *aux_ruta = (char *) malloc(sizeof(char) * (size_base + size_anno + 8));

    strcpy(aux_ruta, base);
    strcat(aux_ruta, "/"); 
    strcat(aux_ruta, anno); 

    mkdir(aux_ruta, (S_IRWXU | S_IRWXG | S_IRWXO));

    aux_ruta[size_base + size_anno + 1] = '/';

    char *temp_dir = &aux_ruta[size_base + size_anno + 2];

    strcpy(temp_dir,"3000+");
    mkdir(aux_ruta, (S_IRWXU | S_IRWXG | S_IRWXO));

    strcpy(temp_dir,"6000+");
    mkdir(aux_ruta, (S_IRWXU | S_IRWXG | S_IRWXO));

    strcpy(temp_dir,"9000+");
    mkdir(aux_ruta, (S_IRWXU | S_IRWXG | S_IRWXO));


    free(aux_ruta);
}

/*------------------------------------------------- moveOneFile -----
         |  Function moveOneFile
         |
         |  Purpose:  Mueve un archivo determinado a un directorio de prioridad determinado.
         |
         |  Parameters:
         |      char srcFilename(IN) -- nombre del archivo a mover.
         |      char destino(IN) -- directorio destino.
         |      char filename(IN) -- nombre del archivo destino.
         |      Data alumno(IN) -- info del alumno.
         |
         |  Returns:  Mueve el archivo a un directorio y no retorna nada.
         |     
         *-------------------------------------------------------------------*/
void moveOneFile(char srcFilename[], char destino[], char filename[], Data alumno){
    int size_destino, size_filename, size_anno;
    size_destino = strlen(destino);
    size_filename = strlen(filename);
    size_anno = strlen(alumno.anno);

    char *aux_ruta = (char *) malloc(sizeof(char) * (size_destino + size_filename + size_anno + 9));
    char *temp_dir;

    strcpy(aux_ruta, destino);
    strcat(aux_ruta,"/");
    strcat(aux_ruta,alumno.anno);
    strcat(aux_ruta,"/");

    if(alumno.prioridad >= 9000)
        strcpy(&aux_ruta[size_destino + size_anno + 2], "9000+/");
    else if(alumno.prioridad >= 6000)
        strcpy(&aux_ruta[size_destino + size_anno + 2], "6000+/");
    else strcpy(&aux_ruta[size_destino + size_anno + 2], "3000+/");

    strcat(aux_ruta,filename);


    rename(srcFilename, aux_ruta);

    free(aux_ruta);
}

/*------------------------------------------------- moveFiles -----
         |  Function moveFiles
         |
         |  Purpose:  Mueve todos los archivos de un directorio a sus respectivos directorios de prioridad.
         |
         |  Parameters:
         |      char ruta(IN) -- directorio actual.
         |      char destino(IN) -- directorio destino.
         |
         |  Returns:  Mueve todos los archivos a sus respectivos directorios de prioridad y no retorna nada.
         |     
         *-------------------------------------------------------------------*/
void moveFiles(char ruta[], char destino[]){
    DIR* directory = opendir(ruta);
    if(directory == NULL)
        return;
    
    struct dirent* ent;
    int aux_size,ruta_size = strlen(ruta); 
    char *aux_ruta;

    while((ent = readdir(directory))){
        if(strcmp(ent->d_name, "..") == 0 
            || strcmp(ent->d_name,".") == 0 
            || !isFormat(ent->d_name))
            continue;
        
        aux_size = ruta_size + strlen(ent->d_name) + 2;
        aux_ruta = (char *) malloc(sizeof(char) * aux_size);
        
        strcpy(aux_ruta, ruta);
        strcat(aux_ruta,"/");
        strcat(aux_ruta, ent->d_name);


        Data alumno = getData(aux_ruta);
        if(!inDir(destino, alumno.anno))
            createYearDir(destino, alumno.anno);

        moveOneFile(aux_ruta, destino, ent->d_name, alumno);

        printf("%s movido.\n",ent->d_name);

        free(aux_ruta);
    }


    closedir(directory);
}

/*------------------------------------------------- main -----
         |  Function main
         |
         |  Purpose:  Crea los directorios de las prioridades y mueve los archivos a sus respectivos directorios.
         |
         |  Parameters:
         |
         |  Returns:  Retorna 0 si todo sale bien.
         |     
         *-------------------------------------------------------------------*/
int main(){
    createYearDir(".", "2019");
    createYearDir(".", "2020");
    createYearDir(".", "2021");
    
    moveFiles(".",".");

    return 0;
}