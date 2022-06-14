import java.io.IOException;
import java.util.Scanner;
 
public class Main {
 
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        if (n >= 1) { System.out.printf("0"); }
        if (n >= 2) { System.out.printf(" 1"); }
        if (n >= 3) {
            int prevPrevNumber = 0;
            int prevNumber = 1;
            for (int i = 3; i <= n; i++) {
                int currentNumber = prevPrevNumber + prevNumber;
                System.out.printf(" %d", currentNumber);
                prevPrevNumber = prevNumber;
                prevNumber = currentNumber;
            }
        }
        System.out.printf("\n");
    }
 
}
