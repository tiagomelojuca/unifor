import java.io.IOException;
import java.util.Scanner;
import java.util.HashMap;
import java.util.Map;

class Snack {
    String spec;
    int price;
    
    Snack(String _spec, int _price) {
        spec  = _spec;
        price = _price;
    }
    
    public String GetSpecification() { return spec; }
    public int GetPrice() { return price; }
}

class SnacksMenu {
    Map<Integer, Snack> snacks = new HashMap<Integer, Snack>();
    
    SnacksMenu() {
        snacks.put(1, new Snack("Cachorro Quente", 400));
        snacks.put(2, new Snack("X-Salada", 450));
        snacks.put(3, new Snack("X-Bacon", 500));
        snacks.put(4, new Snack("Torrada Simples", 200));
        snacks.put(5, new Snack("Refrigerante", 150));
    }
    
    public Snack GetSnack(int code) { return snacks.get(code); }
}

class Request {
    private SnacksMenu menu;
    private int total;
    
    Request (SnacksMenu _menu) {
        menu = _menu;
    }
    
    public void readRequest() {
        Scanner in = new Scanner(System.in);
        
        int x = in.nextInt();
        int y = in.nextInt();
        
        total = menu.GetSnack(x).GetPrice() * y;
        
        in.close();
    }
    
    public void printTotal() {
        System.out.printf("Total: R$ %.2f\n", (float) total / 100);
    }
}
 
public class Main {
 
    public static void main(String[] args) throws IOException {
        Request request = new Request(new SnacksMenu());
        
        request.readRequest();
        request.printTotal();
    }
 
}
