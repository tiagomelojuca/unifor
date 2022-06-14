import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class StdinParser {
    public Vector<Integer> readIntegers() throws IOException {
        Vector<Integer> integers = new Vector<Integer>();
        
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line = in.readLine();
        String[] integersAsStrings = line.split(" ");
        
        for (int i = 0; i < integersAsStrings.length; i++) {
            integers.add(Integer.parseInt(integersAsStrings[i]));
        }
        
        return integers;
    }
}

class InputHandler {
    int a;
    int n;
    
    public InputHandler(List<Integer> uriInput) {
        Vector<Integer> filteredInput = uriInput.stream()
            .filter(p -> p > 0)
            .collect(Collectors.toCollection(Vector::new));
        a = filteredInput.get(0);
        n = filteredInput.get(1);
    }
    
    public int Handle() {
        int sum = 0;
        for(int i = 0; i < n; i++) {
            sum += a + i;
        }
        
        return sum;
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        StdinParser parser = new StdinParser();
        Vector<Integer> integers = parser.readIntegers();
        
        InputHandler iHandler = new InputHandler(integers);
        int res = iHandler.Handle();
        
        System.out.print(res + "\n");
    }
 
}
