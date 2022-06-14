import java.io.IOException;
import java.util.Scanner;

public class Main {
    
    public static int ParseBase(String token) {
        if (token.equals("hex"))      { return 16; }
        else if (token.equals("dec")) { return 10; }
        else if (token.equals("bin")) { return  2; }
        else                          { return -1; }
    }
    public static String StringifyBase(int base) {
        if (base == 16)      { return "hex"; }
        else if (base == 10) { return "dec"; }
        else if (base == 2)  { return "bin"; }
        else                 { return "err"; }
    }
    
    public static String StringifyNumber(String srcNumber, int srcBase, int dstBase) {
        String dstNumber = Integer.toString(Integer.parseInt(srcNumber, srcBase), dstBase);
        return dstNumber + " " + StringifyBase(dstBase);
    }
 
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int numberOfTestCases = in.nextInt();
        
        for (int i = 1; i <= numberOfTestCases; i++) {
            String num = in.next();
            String inputToken  = in.next();
            int base = ParseBase(inputToken);
            
            System.out.printf("Case %d:\n", i);
            if (base == 16) {
                System.out.printf("%s\n%s\n\n", StringifyNumber(num, base, 10), StringifyNumber(num, base, 2));
            } else if (base == 10) {
                System.out.printf("%s\n%s\n\n", StringifyNumber(num, base, 16), StringifyNumber(num, base, 2));
            } else if (base == 2) {
                System.out.printf("%s\n%s\n\n", StringifyNumber(num, base, 10), StringifyNumber(num, base, 16));
            } else {
                System.out.printf("Invalid Input");
            }
        }
    }
 
}
