import java.io.IOException;
import java.util.Scanner;
 
public class Main {
 
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int x = in.nextInt();
        int y = in.nextInt();
        
        int itemsLine = 1;
        for(int i = 1; i <= y; i++) {
            System.out.printf("%d", i);
            if (itemsLine == x) {
                System.out.printf("\n");
                itemsLine = 1;
            }
            else {
                System.out.printf(" ");
                itemsLine++;
            }
        }
    }
 
}
