import java.io.IOException;
import java.util.Scanner;
import java.util.Vector;
import java.util.Iterator;

class EnergyCable {
    int radius;
    EnergyCable(int _radius) { radius = _radius; }
    public int GetRadius() { return radius; }
}

class Conduit {
    Vector<EnergyCable> cables = new Vector<EnergyCable>();
    public void PushCable(EnergyCable e) {
        cables.add(e);
    }
    
    public int CalcRadius() {
        int sum = 0;
        Iterator<EnergyCable> it = cables.iterator();
        while (it.hasNext()) { sum += it.next().GetRadius(); }
        
        return sum;
    }
}

class ConduitReader {
    private Scanner scanner;
    
    ConduitReader(Scanner _scanner) {
        scanner = _scanner;
    }
    
    public Conduit readConduit() {
        int r1 = scanner.nextInt();
        int r2 = scanner.nextInt();
        
        Conduit c = new Conduit();
        c.PushCable(new EnergyCable(r1));
        c.PushCable(new EnergyCable(r2));
        
        return c;
    }
}

class AppIO {
    private ConduitReader reader;
    
    private void printConduitOutput(Conduit c) {
        System.out.printf("%d\n", c.CalcRadius());
    }
    
    public void handleInput() {
        Scanner scanner = new Scanner(System.in);
        ConduitReader in = new ConduitReader(scanner);
        
        int numberOfTestCases = scanner.nextInt();
        for (int i = 0; i < numberOfTestCases; i++) {
            Conduit c = in.readConduit();
            printConduitOutput(c);
        }
        
        scanner.close();
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        AppIO in = new AppIO();
        in.handleInput();
    }
 
}
