import java.io.IOException;
import java.util.Scanner;

enum Operation { ABORTING, LEAVING, COMING_BACK; }

class Command {
    private Operation operation;
    private int amountTourists;
    
    public Command(Operation _operation, int _amountTourists) {
        operation = _operation;
        amountTourists = _amountTourists;
    }
    
    public Operation GetOperation() {
        return operation;
    }
    
    public int GetAmountTourists() {
        return amountTourists;
    }
    
    public boolean IsAbort() {
        return operation == Operation.ABORTING;
    }
}

class CommandParser {
    private Scanner scanner;
    
    public CommandParser(Scanner _scanner) {
        scanner = _scanner;
    }
    
    public Command Next() {
        String currentCommand = scanner.nextLine();
        
        if (currentCommand.equals("ABEND")) {
            return new Command(Operation.ABORTING, -1);
        }
        
        String[] tokens = currentCommand.split(" ");
        Operation parsedOperation = tokens[0].equals("SALIDA") ? Operation.LEAVING : Operation.COMING_BACK;
        int parsedAmountTourists = Integer.parseInt(tokens[1]);
        
        return new Command(parsedOperation, parsedAmountTourists);
    }
}

class TransportController {
    int countTourists;
    int countJeeps;
    
    private void ProcessCommand(Command command) {
        if (command.GetOperation() == Operation.LEAVING) {
            countTourists += command.GetAmountTourists();
            countJeeps++;
        } else if (command.GetOperation() == Operation.COMING_BACK) {
            countTourists -= command.GetAmountTourists();
            countJeeps--;
        }
    }
    
    public void ReadFromStdin(CommandParser in) {
        for (Command currentCommand = in.Next(); !currentCommand.IsAbort(); currentCommand = in.Next()) {
            ProcessCommand(currentCommand);
        }
    }
    
    public void PrintToStdout() {
        System.out.printf("%d\n%d\n", countTourists, countJeeps);
    }
}

class IO {
    private Scanner scanner;
    private TransportController storage;
    private CommandParser cmdParser;
    
    IO () {
        scanner = new Scanner(System.in);
        storage = new TransportController();
        cmdParser = new CommandParser(scanner);
    }
    
    public void handleNextInput() {
        storage.ReadFromStdin(cmdParser);
        storage.PrintToStdout();
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        IO io = new IO();
        io.handleNextInput();
    }
 
}
