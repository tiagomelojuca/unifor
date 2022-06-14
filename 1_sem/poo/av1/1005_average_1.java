import java.io.IOException;
import java.util.Scanner;
 
public class Main {
 
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        float a = in.nextFloat();
        float b = in.nextFloat();
        
        double average = (a * 3.5 + b * 7.5) / 11;
        
        System.out.printf("MEDIA = %.5f\n", average);
    }
 
}
