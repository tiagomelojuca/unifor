import java.io.IOException;
import java.util.*;

class Raindeer implements Comparable<Raindeer>
{
    private String name;
    private int weight;
    private int age;
    private float height;
    
    public Raindeer(String _name, int _weight, int _age, float _height)
    {
        name = _name;
        weight = _weight;
        age = _age;
        height = _height;
    }
    
    public String GetName()
    {
        return name;
    }
    public int GetWeight()
    {
        return weight;
    }
    public int GetAge()
    {
        return age;
    }
    public float GetHeight()
    {
        return height;
    }
    
    @Override
    public int compareTo(Raindeer other)
    {
        if (GetWeight() != other.GetWeight()) {
            return GetWeight() > other.GetWeight() ? -1 : 1;
        } else if (GetAge() != other.GetAge()) {
            return GetAge() < other.GetAge() ? -1 : 1;
        } else if (GetHeight() != other.GetHeight()) {
            return GetHeight() < other.GetHeight() ? -1 : 1;
        } else {
            return GetName().compareTo(other.GetName());
        }
    }
}

class TestCase
{
    private int n;
    private int m;
    List<Raindeer> raindeers;
    
    TestCase(int _n, int _m)
    {
        n = _n;
        m = _m;
        raindeers = new Vector<Raindeer>();
    }
    
    public int GetTotalNumberOfRaindeers()
    {
        return n;
    }
    
    public void PushRaindeer(Raindeer raindeer)
    {
        raindeers.add(raindeer);
    }
    
    public void Sort()
    {
        Collections.sort(raindeers);
    }
    
    public String StringifyResult()
    {
        String res = "";
        for(int i = 1; i <= m; i++) {
            res += new Integer(i).toString() + " - " + raindeers.get(i - 1).GetName() + (i != m ? "\n" : "");
        }
        
        return res;
    }
}

class StdinParser
{
    Scanner scanner;
    
    StdinParser()
    {
        scanner = new Scanner(System.in);
    }
    
    public List<TestCase> Parse()
    {
        List<TestCase> testCases = new Vector<TestCase>();
        
        int numberOfTestCases = Integer.parseInt(scanner.nextLine());
        for (int i = 0; i < numberOfTestCases; i++) {
            testCases.add(nextTestCase());
        }
        
        return testCases;
    }
    
    private TestCase nextTestCase()
    {
        String   lineNM = scanner.nextLine();
        String[] tokens = lineNM.split(" ");
        int n = Integer.parseInt(tokens[0]);
        int m = Integer.parseInt(tokens[1]);
        
        TestCase testCase = new TestCase(n, m);
        for(int i = 0; i < testCase.GetTotalNumberOfRaindeers(); i++) {
            testCase.PushRaindeer(nextRaindeer());
        }
        testCase.Sort();
        
        return testCase;
    }
    
    private Raindeer nextRaindeer()
    {
        String   lineRaindeer = scanner.nextLine();
        String[] tokens = lineRaindeer.split(" ");
        
        String name = tokens[0];
        int w = Integer.parseInt(tokens[1]);
        int a = Integer.parseInt(tokens[2]);
        float h = Float.parseFloat(tokens[3]);
        
        return new Raindeer(name, w, a, h);
    }
}

class Utils
{
    public static void Print(List<TestCase> tests)
    {
        for (int i = 1; i <= tests.size(); i++) {
            System.out.printf("CENARIO {%d}\n%s\n", i, tests.get(i - 1).StringifyResult());
        }
    }
}

public class Main
{
    public static void main(String[] args) throws IOException {
        Utils.Print(new StdinParser().Parse());
    }
}
