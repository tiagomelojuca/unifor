import java.io.IOException;

public class Main {
 
    public static void main(String[] args) throws IOException {
        // I(i) = -2 + 3i
        // J(i) = 65 - 5i => J(i) = 0 se, e somente se, i = 13
        for(int i = 1; i <= 13; i++) {
            System.out.printf("I=%d J=%d\n", 3*i - 2, 65 - 5*i);
        }
    }
 
}
