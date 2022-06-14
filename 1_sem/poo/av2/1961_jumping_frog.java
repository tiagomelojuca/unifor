import java.io.IOException;
import java.util.Scanner;
import java.util.Vector;
import java.util.Iterator;

enum GameResults { WON_MATCH, LOST_MATCH };

interface Game {
    public String GetMessageVictory();
    public String GetMessageGameOver();
    
    public void EvUserKbInput();
    public void HandleGameBusinessLogic();
    
    public void Play();
    public GameResults GetResult();
}

class ScrController {
    Game game;
    
    ScrController(Game _game) {
        game = _game;
    }
    
    public void DisplayGameResult() {
        String msg = game.GetResult() == GameResults.WON_MATCH ? game.GetMessageVictory() : game.GetMessageGameOver();
        System.out.printf("%s\n", msg);
    }
}

abstract class KbController {
    Scanner scanner;
    
    KbController() {
        scanner = new Scanner(System.in);
    }
    
    public abstract void HandleNext();
}

class PulaSapoInput {
    private int frogJumpHeight;
    private int numberOfPipes;
    private Vector<Integer> pipesHeight;
    
    PulaSapoInput(int _frogJumpHeight, int _numberOfPipes, Vector<Integer> _pipesHeight) {
        frogJumpHeight = _frogJumpHeight;
        numberOfPipes = _numberOfPipes;
        pipesHeight = _pipesHeight;
    }
    
    public int GetFrogJumpHeight() {
        return frogJumpHeight;
    }
    public int GetNumberOfPipes() {
        return numberOfPipes;
    }
    public Vector<Integer> GetPipesHeights() {
        return pipesHeight;
    }
}

class PulaSapoKbController extends KbController {
    PulaSapoInput input;
    
    public PulaSapoInput GetInput() {
        return input;
    }
    
    @Override
    public void HandleNext() {
        int frogJumpHeight = scanner.nextInt();
        int numberOfPipes  = scanner.nextInt();
        
        Vector<Integer> pipesHeight = new Vector<Integer>();
        for (int i = 1; i <= numberOfPipes; i++) {
            pipesHeight.add(scanner.nextInt());
        }
        
        input = new PulaSapoInput(frogJumpHeight, numberOfPipes, pipesHeight);
    }
}

class PulaSapo implements Game {
    PulaSapoKbController kbController;
    
    // Game State (received from the user)
    private PulaSapoInput matchInput;
    // Game State (depends on game business logic)
    private GameResults matchResult;
    
    PulaSapo() {
        kbController = new PulaSapoKbController();
    }
    
    @Override
    public String GetMessageVictory() {
        return "YOU WIN";
    }
    
    @Override
    public String GetMessageGameOver() {
        return "GAME OVER";
    }
    
    @Override
    public void EvUserKbInput() {
        kbController.HandleNext();
        matchInput = kbController.GetInput();
    }
    
    @Override
    public void HandleGameBusinessLogic() {
        Vector<Integer> pipesHeight = matchInput.GetPipesHeights();
        int numberOfPipes = matchInput.GetNumberOfPipes();
        int frogJumpHeight = matchInput.GetFrogJumpHeight();
        
        for (int i = 0; i < numberOfPipes - 1; i++) {
            int heightCurrentPipe = pipesHeight.get(i);
            int heightNextPipe = pipesHeight.get(i + 1);
            int diff = Math.abs(heightNextPipe - heightCurrentPipe);
            
            if (diff > frogJumpHeight) {
                matchResult = GameResults.LOST_MATCH;
                return;
            }
        }
		
        matchResult = GameResults.WON_MATCH;
    }
    
    @Override
    public void Play() {
        EvUserKbInput();
        HandleGameBusinessLogic();
    }
    
    @Override
    public GameResults GetResult() {
        return matchResult;
    }
}

class VirtualConsole {
    ScrController currentScreen;
    Game currentGame;
    
    VirtualConsole(Game _game) {
        currentGame = _game;
        currentScreen = new ScrController(currentGame);
    }
    
    public void PlayGameMatch() {
        currentGame.Play();
        currentScreen.DisplayGameResult();
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        VirtualConsole console = new VirtualConsole(new PulaSapo());
        console.PlayGameMatch();
    }
 
}
