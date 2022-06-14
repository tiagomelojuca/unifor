import java.io.IOException;
import java.util.Scanner;
 
public class Main {
 
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int a = in.nextInt();
        int b = in.nextInt();
        int c = in.nextInt();
        int d = in.nextInt();
        
        boolean isAcceptedValue = b > c &&
                                  d > a &&
                                  (c+d) > (a+b) &&
                                  c > 0 &&
                                  d > 0 &&
                                  a % 2 == 0;
                                  
        if (isAcceptedValue) {
            System.out.printf("Valores aceitos\n");
        }
        else {
            System.out.printf("Valores nao aceitos\n");
        }
    }
 
}
