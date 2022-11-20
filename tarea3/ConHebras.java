import java.util.Scanner;
import java.lang.Thread;
import java.io.File;

public class ConHebras{

    
    
    /* 
     * Funcion: public static void main
     * Descripcion: La funcion principal de el porgrama el cual encuentra la embarcación de tamaño m en nu matriz de nxn
     * Parametros: 
     *      String[] args -> variable que guarda los argumentos al ejecutar un porgrama, en este caso no se usara.
    */
    public static void main(String[] args) {
        // Procesamiento de entradas
        long startTime = System.nanoTime();

        try{
            File filee = new File("./informe-nautico.txt");
            Scanner sc = new Scanner(filee);
        

            int n = sc.nextInt();
            int m = sc.nextInt();
            int[][] matriz = new int[n][n];

            sc.nextLine();
            String matrizSTR = sc.nextLine();
            sc.close();

            // Procesamineto de matriz
            for(int i = 0,level = -1,x = 0; i < matrizSTR.length(); i++){
                char temp = matrizSTR.charAt(i);
                if(temp == '[')
                    level++;
                else if(temp == ']')
                    x = 0;
                else if(temp == '1' || temp == '0')
                        matriz[level][x++] = temp == '1'? 1 : 0;
            }

            // Creación 4 hebras
            int x = n - 1, y = n - 1,i = 0,j = 0;
            if(x + 1 - i <= m){
                int saveJ = -1;
                for(int jj = j ; jj <= y; jj++)
                    if(matriz[jj][i] == 1)
                        saveJ = jj;
                if(saveJ >= 0)
                    System.out.printf("fila %d, columna [%d,%d]\n",saveJ + 1,i + 1,i + m);
            }else{
                int midX = (i + x)/2;
                int midY = (j + y)/2;
                Multithreading t1 = new Multithreading(matriz, i, j, midX, midY, m);
                Multithreading t2 = new Multithreading(matriz, midX + 1, j, x, midY, m);
                Multithreading t3 = new Multithreading(matriz, i, midY + 1, midX, y, m);
                Multithreading t4 = new Multithreading(matriz, midX + 1, midY + 1, x, y, m);
                t1.start();
                t2.start();
                t3.start();
                t4.start();
                try{
                    t1.join();
                    t2.join();
                    t3.join();
                    t4.join();
                }catch(Exception e){System.out.println("Error.");}
            }
        }catch(Exception e){
            System.out.println("Error");
        }
        long endTime = System.nanoTime();
        long timeElapsed = (endTime - startTime);
        System.out.println("Execution time in nanoseconds: " + timeElapsed);
    }
}


class Multithreading extends Thread{
    private int matriz[][];
    private int i,j,x,y,m;
    
    /* 
     * Funcion: Multithreading
     * Descripcion: Corresponde al constructor de la clase Multithreading la cual es extendida de Thread. Tambien guarda los valores correspondeintes en la clase.
     * Parametros: 
     *      int ma[][] -> Corresponse a la matriz
     *      int i -> Corresponse a donde inicia en el eje horizontal la subseccion
     *      int j -> Corresponde a donde inicia en el eje vertical la subseccion
     *      int x -> Corresponde a donde finaliza en el eje horizontal la subseccion
     *      int y -> Corresponde a donde fnializa en el eje vertical la subseccion
     *      int m -> Corresponde al largo de la embarcacion
    */
    public Multithreading(int ma[][],int i, int j, int x, int y, int m){
        super();
        this.matriz = ma;
        this.i = i;
        this.j = j;
        this.x = x;
        this.y = y;
        this.m = m;
    }

    /* 
     * Funcion: public void run
     * Descripcion: Corresponde a lo que se ejecutara en cada hilo al llamar el metodo start
     * Parametros: 
     *      sin parametors
    */
    public void run(){
        if(x + 1 - i <= m){
            int saveJ = -1;
            for(int jj = j ; jj <= y; jj++)
                if(matriz[jj][i] == 1)
                    saveJ = jj;
            if(saveJ >= 0)
                System.out.printf("fila %d, columna [%d,%d]\n",saveJ + 1,i + 1,i + m);
            return;
        }
        int midX = (i + x)/2;
        int midY = (j + y)/2;
        Multithreading t1 = new Multithreading(this.matriz, i, j, midX, midY, m);
        Multithreading t2 = new Multithreading(this.matriz, midX + 1, j, x, midY, m);
        Multithreading t3 = new Multithreading(this.matriz, i, midY + 1, midX, y, m);
        Multithreading t4 = new Multithreading(this.matriz, midX + 1, midY + 1, x, y, m);
        t1.start();
        t2.start();
        t3.start();
        t4.start();
        try{
            t1.join();
            t2.join();
            t3.join();
            t4.join();
        }catch(Exception e){System.out.println("Error.");}
    }
}