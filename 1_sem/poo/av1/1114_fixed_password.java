import java.io.IOException;
import java.util.Scanner;
 
public class Main {
 
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        while (true) {
            int passwd = in.nextInt();
            if (passwd == 2002) {
                System.out.printf("Acesso Permitido\n");
                break;
            }
            
            System.out.printf("Senha Invalida\n");
        }
    }
 
}
