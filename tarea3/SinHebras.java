import java.util.Scanner;
import java.util.concurrent.TimeUnit;
import java.io.File;

public class SinHebras{

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

            for(int j = 0; j < n; j++)
                for(int i = 0; i < n; i++){
                    if(matriz[j][i] == 1){
                        System.out.printf("fila %d, columna [%d,%d]\n",j + 1,i + 1,i + m);
                        i += m - 1;
                    }
                }

            sc.close();
        
        }catch(Exception e){
            System.out.println("Error");
        }
        long endTime = System.nanoTime();
        long timeElapsed = (endTime - startTime);
        System.out.println("Execution time in nanoseconds: " + timeElapsed);
    }
}