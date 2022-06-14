import java.io.IOException;
import java.util.Scanner;

interface Snack { public float GetPrice(); }
class CachorroQuente implements Snack { public float GetPrice() { return 4.00f; } }
class XSalada        implements Snack { public float GetPrice() { return 4.50f; } }
class XBacon         implements Snack { public float GetPrice() { return 5.00f; } }
class TorradaSimples implements Snack { public float GetPrice() { return 2.00f; } }
class Refrigerante   implements Snack { public float GetPrice() { return 1.50f; } }

class SnackFactory {
    int code;
    
    SnackFactory(int _code) {
        code = _code;
    }
    
    public Snack Create() {
        switch (code) {
            case 1:  return new CachorroQuente();
            case 2:  return new XSalada();
            case 3:  return new XBacon();
            case 4:  return new TorradaSimples();
            case 5:  return new Refrigerante();
            default: return null;
        }
    }
}

class Pair {
    int elem1; int elem2;
    Pair(int _elem1, int _elem2) { elem1 = _elem1; elem2 = _elem2; }
    public int getKey()          { return elem1; }
    public int getValue()        { return elem2; }
}

class Calculator {
    private Pair ReadFromKeyboard() {
        Scanner in = new Scanner(System.in);
        int cod = in.nextInt();
        int qtd = in.nextInt();
        return new Pair(cod, qtd);
    }
    
    float CalcPrice(int cod, int qtd) {
        SnackFactory factory = new SnackFactory(cod);
        Snack snack = factory.Create();
        
        if (snack == null) {
            return -1.0f;
        }
        
        return snack.GetPrice() * qtd;
    }
    
    float CalcPrice(Pair codQtd) {
        return CalcPrice(codQtd.getKey(), codQtd.getValue());
    }
    
    public void PrintToScreen() {
        System.out.printf("Total: R$ %.2f\n", CalcPrice(ReadFromKeyboard()));
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        Calculator c = new Calculator();
        c.PrintToScreen();
    }
 
}
