import java.io.IOException;
import java.util.Scanner;

public class Main {
 
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int numberOfTestCases = in.nextInt();
        
        for (int i = 0; i < numberOfTestCases; i++) {
          float a = in.nextFloat();
          float b = in.nextFloat();
          float c = in.nextFloat();
          
          float avg = (a * 2 + b * 3 + c * 5) / (2 + 3 + 5);
          System.out.printf("%.1f\n", avg);
        }
    }
 
}
