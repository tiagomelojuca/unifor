import java.io.IOException;
import java.util.Scanner;
 
public class Main {
    
    public static int factorial(int number) {
        if (number == 0) {
            return 1;
        }
        
        return number * factorial(number - 1);
    }
 
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        System.out.printf("%d\n", factorial(in.nextInt()));
    }
 
}
