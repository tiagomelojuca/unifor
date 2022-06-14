import java.io.IOException;
import java.util.Scanner;

class Time {
    int h; int m;
    
    Time(int _h, int _m) { h = _h; m = _m; }
    int GetHours()   { return h; }
    int GetMinutes() { return m; }
}

interface IGame {
    public Time CalcDuration();
    public void DisplayResult();
}

class Game implements IGame {
    Time initialTime;
    Time finalTime;
    
    Game(Time i, Time f) {
        initialTime = i;
        finalTime = f;
    }
    
    @Override
    public Time CalcDuration() {
        int initialTimeInMinutes = initialTime.GetHours() * 60 + initialTime.GetMinutes();
        int finalTimeInMinutes = finalTime.GetHours() * 60 + finalTime.GetMinutes();
        
        if (finalTimeInMinutes <= initialTimeInMinutes) {
            finalTimeInMinutes += 24 * 60;
        }
        
        int durationInMinutes = finalTimeInMinutes - initialTimeInMinutes;
        int durationHours     = durationInMinutes / 60;
        int durationMinutes   = durationInMinutes - durationHours * 60;
        
        return new Time(durationHours, durationMinutes);
    }
    
    @Override
    public void DisplayResult() {
        Time d = CalcDuration();
        System.out.printf("O JOGO DUROU %d HORA(S) E %d MINUTO(S)\n", d.GetHours(), d.GetMinutes());
    }
}

class Parser {
    Scanner scanner;
    
    Parser() {
        scanner = new Scanner(System.in);
    }
    
    IGame parseLine() {
        int hI = scanner.nextInt();
        int mI = scanner.nextInt();
        int hF = scanner.nextInt();
        int mF = scanner.nextInt();
        
        return new Game(new Time(hI, mI), new Time(hF, mF));
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        IGame game = new Parser().parseLine();
        game.DisplayResult();
    }
 
}
