import java.io.IOException;
import java.util.Scanner;
import java.util.Vector;
import java.util.Iterator;

class InvalidPitch extends Exception {
    public InvalidPitch(String message) {
        super(message);
    }
}

interface Game {
    public void Play();
    public String GetResult();
}

interface Match {
    public void Play();
    public String GetWinner();
}

class Pitch {
    private int scores;
    
    Pitch(int score, int distance) {
        scores = score * distance;
    }
    
    public int GetScores() {
        return scores;
    }
}

class GameProcess {
    public void Run() {
        InputHandler in = new InputHandler();
        Game game = in.parseGame();
        game.Play();
        
        System.out.printf("%s", game.GetResult());
    }
}

class DartGame implements Game {
    String result = "";
    private Vector<Match> matches = new Vector<Match>();
    
    @Override
    public void Play() {
        Iterator<Match> it = matches.iterator();
        while (it.hasNext()) {
            Match current = it.next();
            current.Play();
            result += current.GetWinner();
            result += "\n";
        }
    }
    
    @Override
    public String GetResult() {
        return result;
    }
    
    public void pushMatch(Match match) {
        matches.add(match);
    }
}

class DartMatch implements Match {
    private String namePlayer1;
    private String namePlayer2;
    private String winner;
    
    private Vector<Pitch> pitchesPlayer1 = new Vector<Pitch>();
    private Vector<Pitch> pitchesPlayer2 = new Vector<Pitch>();
    
    DartMatch(String _namePlayer1, String _namePlayer2) {
        namePlayer1 = _namePlayer1;
        namePlayer2 = _namePlayer2;
    }
    
    @Override
    public void Play() {
        int totalScorePlayer1 = CalcTotal(pitchesPlayer1);
        int totalScorePlayer2 = CalcTotal(pitchesPlayer2);
        
        if (totalScorePlayer1 > totalScorePlayer2) {
            winner = namePlayer1;
        } else if (totalScorePlayer2 > totalScorePlayer1) {
            winner = namePlayer2;
        } else {
            winner = "DRAW";
        }
    }
    
    @Override
    public String GetWinner() {
        return winner;
    }
    
    public void pushPitchPlayer1(Pitch pitch) {
        pitchesPlayer1.add(pitch);
    }
    
    public void pushPitchPlayer2(Pitch pitch) {
        pitchesPlayer2.add(pitch);
    }
    
    public int CalcTotal(Vector<Pitch> pitches) {
        int total = 0;
        Iterator<Pitch> it = pitches.iterator();
        while (it.hasNext()) {
            total += it.next().GetScores();
        }
        
        return total;
    }
}

class InputHandler {
    Scanner scanner;
    
    InputHandler() {
        scanner = new Scanner(System.in);
    }
    
    public Game parseGame() {
        int numberOfMatches = scanner.nextInt();
        scanner.nextLine();
        
        DartGame game = new DartGame();
        
        for (int i = 0; i < numberOfMatches; i++) {
            Match current = parseMatch();
            game.pushMatch(current);
        }
        
        return game;
    }
    
    private Match parseMatch() {
        DartMatch match = new DartMatch(Utils.NAME_PLAYER1, Utils.NAME_PLAYER2);
        
        for (int i = 0; i < Utils.PITCHES_PLAYER_PER_MATCH; i++) {
            try {
                Pitch current = nextPitch();
                match.pushPitchPlayer1(current);
            } catch (InvalidPitch e) {
                Utils.handleBadInput(e.getMessage());
            }
        }
        
        for (int i = 0; i < Utils.PITCHES_PLAYER_PER_MATCH; i++) {
            try {
                Pitch current = nextPitch();
                match.pushPitchPlayer2(current);
            } catch (InvalidPitch e) {
                Utils.handleBadInput(e.getMessage());
            }
        }
        
        return match;
    }
    
    private Pitch nextPitch() throws InvalidPitch {
        String line = scanner.nextLine();
        String[] tokens = line.split(" ");
        
        int score = Utils.tryParse(tokens[0]);
        int distance = Utils.tryParse(tokens[1]);
        
        if (score < 0 || distance < 0) {
            throw new InvalidPitch("pitch must contain only positive numbers");
        }
        
        return new Pitch(score, distance);
    }
}

class Utils {
    public static final String NAME_PLAYER1 = "JOAO";
    public static final String NAME_PLAYER2 = "MARIA";
    public static final int PITCHES_PLAYER_PER_MATCH = 3;
    
    public static int tryParse(String num) {
        try {
            return Integer.parseInt(num);
        } catch (NumberFormatException e) {
            return -1; // valor sentinela
        }
    }
    
    public static void handleBadInput(String msg) {
        System.out.printf("%s", msg);
        System.exit(1);
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        GameProcess proc = new GameProcess();
        proc.Run();
    }
 
}
