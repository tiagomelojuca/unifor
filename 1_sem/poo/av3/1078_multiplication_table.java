import java.io.*;
import java.util.*;

class MultTable {
    private String table;
    
    public void CreateFromStdin() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        
        String line = in.readLine();
        int number = Integer.parseInt(line);
        
        table = "";
        for (int i = 1; i <= 10; i++) {
            table += i + " x " + number + " = " + i * number + "\n";
        }
    }
    
    public String Get() {
        return table;
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        MultTable table = new MultTable();
        table.CreateFromStdin();
        
        System.out.print(table.Get());
    }
 
}
