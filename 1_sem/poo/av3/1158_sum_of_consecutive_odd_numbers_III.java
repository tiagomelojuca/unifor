import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class StdinParser {
    private BufferedReader in;
    
    public StdinParser() {
        in = new BufferedReader(new InputStreamReader(System.in));
    }
    
    public Vector<Vector<Integer>> readLines() throws IOException {
        Vector<Vector<Integer>> lines = new Vector<Vector<Integer>>();
        
        int numberOfTestCases = Integer.parseInt(in.readLine());
        for (int i = 0; i < numberOfTestCases; i++) {
            lines.add(readIntegers());
        }
        
        return lines;
    }
    
    private Vector<Integer> readIntegers() throws IOException {
        Vector<Integer> integers = new Vector<Integer>();
        
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
        a = uriInput.get(0);
        n = uriInput.get(1);
    }
    
    public int Handle() {
        int offset = a % 2  == 0 ? a + 1 : a;
        
        int sum = 0;
        for(int i = 0; i < n; i++) {
            sum += offset + 2*i;
        }
        
        return sum;
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        StdinParser parser = new StdinParser();
        
        Vector<Vector<Integer>> readLines = parser.readLines();
        for (int i = 0; i < readLines.size(); i++) {
            InputHandler iHandler = new InputHandler(readLines.get(i));
            System.out.print(iHandler.Handle() + "\n");
        }
    }
 
}
