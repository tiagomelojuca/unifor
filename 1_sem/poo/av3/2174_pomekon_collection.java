import java.io.IOException;
import java.util.Scanner;
import java.util.Set;
import java.util.HashSet;
import java.util.Iterator;

class Parser {
    private Scanner in;
    
    public Parser() {
        in = new Scanner(System.in);
    }
    
    public Set<String> parsePomekons() {
        Set<String> pomekonsNames = new HashSet<String>();
        
        int setSize = in.nextInt(); in.nextLine();
        for (int i = 0; i < setSize; i++) {
            pomekonsNames.add(in.nextLine());
        }
        
        return pomekonsNames;
    }
}

class Pomedex {
    private static final int TOTAL_POMEKONS = 151;
    public Set<String> knownPomekons;
    
    public Pomedex()
    {
        knownPomekons = new HashSet<String>();
    }
    
    public void Register(Set<String> _knownPomekons)
    {
        knownPomekons.addAll(_knownPomekons);
    }
    
    public int GetUnknownPomekons()
    {
        return TOTAL_POMEKONS - knownPomekons.size();
    }
}

class ResultBuilder {
    private Pomedex pomedex;
    String res;
    
    public ResultBuilder(Pomedex _pomedex) {
        pomedex = _pomedex;
    }
    
    public void Build() {
        res = "Falta(m) " + pomedex.GetUnknownPomekons() + " pomekon(s).";
    }
    
    public String GetResult() {
        return res;
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        Pomedex pomedex = new Pomedex();
        
        Parser p = new Parser();
        pomedex.Register(p.parsePomekons());
        ResultBuilder resBuilder = new ResultBuilder(pomedex);
        resBuilder.Build();
        
        System.out.print(resBuilder.GetResult() + "\n");
    }
 
}
