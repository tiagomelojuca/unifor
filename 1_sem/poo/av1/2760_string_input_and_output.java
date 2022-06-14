import java.io.IOException;
import java.util.Scanner;

public class Main {
 
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        String str1 = in.nextLine();
        String str2 = in.nextLine();
        String str3 = in.nextLine();
        
        System.out.printf("%s%s%s\n", str1, str2, str3);
        System.out.printf("%s%s%s\n", str2, str3, str1);
        System.out.printf("%s%s%s\n", str3, str1, str2);
        
        String rStr1 = str1.length() > 10 ? str1.substring(0, 10) : str1;
        String rStr2 = str2.length() > 10 ? str2.substring(0, 10) : str2;
        String rStr3 = str3.length() > 10 ? str3.substring(0, 10) : str3;
        System.out.printf("%s%s%s\n", rStr1, rStr2, rStr3);
    }
 
}
