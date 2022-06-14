// Broken on URI, dont know why

import java.io.*;
import java.util.*;

class DummyBrowser {
    public Vector<String> ParseDOM() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        
        while(!in.readLine().contains("<body>")) {}
        
        Vector<String> lines = new Vector<String>();
        
        String line = in.readLine();
        while(!line.contains("</body>")) {
            lines.add(line);
            line = in.readLine();
        }
        
        return lines;
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        Vector<String> lines = new DummyBrowser().ParseDOM();
        for (int i = 0; i < lines.size(); i++) {
            System.out.print(lines.get(i));
        }
        System.out.print("\n");
    }
 
}
