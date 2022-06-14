import java.io.IOException;

public class Main {
 
    public static void main(String[] args) throws IOException {
        // I(i) = -1 + 2i => I(i) = 9 se, e somente se, i = 5
        for (int i = 1; i <= 5; i++) {
            for (int j = 0; j < 3; j++) {
                System.out.printf("I=%d J=%d\n", 2*i - 1, 7 - j);
            }
        }
    }
 
}
