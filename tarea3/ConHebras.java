import java.util.Scanner;
import java.lang.Thread;

public class ConHebras{
    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        // Procesamiento de entradas
        int n = sc.nextInt();
        int m = sc.nextInt();
        int[][] matriz = new int[n][n];

        sc.nextLine();
        String matrizSTR = sc.nextLine();
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
        Multithreading t = new Multithreading(matriz, 0, 0, n - 1, n - 1,m);
        t.start();

       

    }
}


class Multithreading extends Thread{
    private int matriz[][];
    private int i,j,x,y,m;
    
    public Multithreading(int ma[][],int i, int j, int x, int y, int m){
        super();
        this.matriz = ma;
        this.i = i;
        this.j = j;
        this.x = x;
        this.y = y;
        this.m = m;
    }

    public void run(){
        if(x + 1 - i <= m){
            int saveJ = -1;
            for(int jj = j ; jj <= y; jj++)
                if(matriz[jj][i] == 1)
                    saveJ = jj;
            if(saveJ > 0)
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

    }
}