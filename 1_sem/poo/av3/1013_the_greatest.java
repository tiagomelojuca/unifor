import java.io.*;
import java.util.*;

class GreaterVerifier {
    private Vector<Integer> numbers;
    
    public GreaterVerifier() {
        numbers = new Vector<Integer>();
    }
    
    public void PushNumber(int n) {
        numbers.add(n);
    }
    
    public int GetGreater() {
        Collections.sort(numbers);
        return numbers.get(numbers.size() - 1);
    }
}

class StreamReader {
    BufferedReader in;
    
    public StreamReader(BufferedReader _in) {
        in = _in;
    }
    
    public String Stringify() throws IOException {
        String line;
        StringBuilder content = new StringBuilder();
        
        while ((line = in.readLine()) != null) {
            content.append(line);
            content.append(" ");
        }
        
        return content.toString();
    }
}

class StdinParser {
    public String[] Parse() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StreamReader reader = new StreamReader(in);
        
        return reader.Stringify().split(" ");
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        StdinParser parser = new StdinParser();
        GreaterVerifier verifier = new GreaterVerifier();
        
        String[] tokens = parser.Parse();
        for (int i = 0; i < tokens.length; i++) {
            verifier.PushNumber(Integer.parseInt(tokens[i]));
        }
        
        System.out.print(verifier.GetGreater() + " eh o maior\n");
    }
 
}
