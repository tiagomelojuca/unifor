import java.io.IOException;
import java.util.Scanner;
import java.util.Vector;

class InvalidScore extends RuntimeException{
    public InvalidScore(String message) {
        super(message);
    }
}

class ScoreManager {
    private Vector<Float> scores = new Vector<Float>();
    
    public void PushScore(float score) {
        if (score < 0 || score > 10) {
            throw new InvalidScore("nota invalida");
        }
        
        scores.add(score);
    }
    
    public boolean IsFilled() {
        return scores.size() == 2;
    }
    
    public float GetAverage() {
        float sum = 0.0f;
        int count = 0;
        
        for (int i = 0; i < scores.size(); i++) {
            sum += scores.get(i);
            count++;
        }
        
        return sum / count;
    }
}

class InputLoop {
    private Scanner scanner;
    ScoreManager scores;
    
    InputLoop() {
        scanner = new Scanner(System.in);
        scores = new ScoreManager();
    }
    
    private void RunLoop() {
        while (!scores.IsFilled()) {
            try {
                scores.PushScore(scanner.nextFloat());
            } catch (InvalidScore e) {
                System.out.printf("%s\n", e.getMessage());
            }
        }
    }
    
    private void Finish() {
        System.out.printf("media = %.2f\n", scores.GetAverage());
    }
    
    public void Execute() {
        RunLoop();
        Finish();
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        InputLoop loop = new InputLoop();
        loop.Execute();
    }
 
}
