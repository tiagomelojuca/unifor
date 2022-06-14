import java.io.IOException;
import java.util.Scanner;
import java.util.Vector;
import java.util.Iterator;
import java.util.Collections;

class ScoreList {
    private Vector<Float> scores;
    float sum;
    
    public ScoreList(float s1, float s2, float s3, float s4, float s5, float s6, float s7) {
        scores = new Vector<>();
        scores.add(s1);
        scores.add(s2);
        scores.add(s3);
        scores.add(s4);
        scores.add(s5);
        scores.add(s6);
        scores.add(s7);
        
        Collections.sort(scores);
        
        scores.remove(0);
        scores.remove(scores.size() - 1);
        
        Iterator<Float> it = scores.iterator();
        while (it.hasNext()) {
            sum += it.next();
        }
    }
    
    public float GetSum() {
        return sum;
    }
}

class Dive {
    private String competitorName;
    private float difficulty;
    private ScoreList scores;
    
    private float result;
    
    public Dive(String _competitorName, float _difficulty, ScoreList _scores) {
        competitorName = _competitorName;
        difficulty = _difficulty;
        scores = _scores;
        result = scores.GetSum() * difficulty;
    }
    
    public String GetCompetitorName() {
        return competitorName;
    }
    
    public float GetResult() {
        return result;
    }
}

class DiveInput {
    Scanner scanner;
    
    public DiveInput(Scanner _scanner) {
        scanner = _scanner;
    }
    
    public Dive ReadNextDiveInput() {
        String competitorName = scanner.next();
        float difficulty = scanner.nextFloat();
        
        float s1 = scanner.nextFloat();
        float s2 = scanner.nextFloat();
        float s3 = scanner.nextFloat();
        float s4 = scanner.nextFloat();
        float s5 = scanner.nextFloat();
        float s6 = scanner.nextFloat();
        float s7 = scanner.nextFloat();
        
        ScoreList scores = new ScoreList(s1, s2, s3, s4, s5, s6, s7);
        return new Dive(competitorName, difficulty, scores);
    }
}

class DivesInput {
    private void PrintDive(Dive d) {
        System.out.printf("%s %.2f\n", d.GetCompetitorName(), d.GetResult());
    }
    
    public void handleNextInput() {
        Scanner in = new Scanner(System.in);
        DiveInput diveScanner = new DiveInput(in);
        
        int numberOfCompetitions = in.nextInt();
        for (int i = 0; i < numberOfCompetitions; i++) {
            Dive currentDive = diveScanner.ReadNextDiveInput();
            PrintDive(currentDive);
        }
        
        in.close();
    }
}
 
public class Main {
 
    public static void main(String[] args) throws IOException {
        DivesInput io = new DivesInput();
        io.handleNextInput();
    }
 
}
