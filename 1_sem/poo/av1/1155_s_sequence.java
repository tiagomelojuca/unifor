import java.io.IOException;

public class Main {
 
    public static void main(String[] args) throws IOException {
        double sum = 0;
        for (int i = 1; i <= 100; i++) {
            sum += 1.0 / i;
        }
        
        System.out.printf("%.2f\n", sum);
    }
 
}
