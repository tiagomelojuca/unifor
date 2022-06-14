import java.io.IOException;
import java.util.Scanner;
 
public class Main {
    
    public static boolean isPrime(int number) {
        for (int i = number - 1; i > 1; i--) {
            if (number % i == 0) {
                return false;
            }
        }
        
        return true;
    }
 
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int numberOfTestCases = in.nextInt();
        for (int i = 1; i <= numberOfTestCases; i++) {
            int cNum = in.nextInt();
            System.out.printf("%d %s\n", cNum, isPrime(cNum) ? "eh primo" : "nao eh primo");
        }
    }
 
}
