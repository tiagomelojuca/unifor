import java.io.IOException;
import java.util.Scanner;
import java.util.Vector;
import java.util.Iterator;

class Moves {
    private int services;
    private int blocks;
    private int attacks;
    
    public Moves(int _services, int _blocks, int _attacks) {
        services = _services;
        blocks = _blocks;
        attacks = _attacks;
    }
    
    public void Add(Moves other) {
        services += other.services;
        blocks += other.blocks;
        attacks += other.attacks;
    }
    
    public int getServices() {
        return services;
    }
    
    public int getBlocks() {
        return blocks;
    }
    
    public int getAttacks() {
        return attacks;
    }
}

class Player {
    private String name;
    private Moves attempts;
    private Moves success;
    
    public Player(String _name, Moves _attempts, Moves _success) {
        name = _name;
        attempts = _attempts;
        success = _success;
    }
    
    public Moves getAttempts() {
        return attempts;
    }
    
    public Moves getSuccess() {
        return success;
    }
}

class Team {
    private Vector<Player> players = new Vector<Player>();
    private Moves attempts = new Moves(0, 0, 0);
    private Moves success = new Moves(0, 0, 0);;
    
    private double servicesPercent;
    private double blocksPercent;
    private double attacksPercent;
    
    public void pushPlayer(Player _player) {
        players.add(_player);
        
        attempts.Add(_player.getAttempts());
        success.Add(_player.getSuccess());
        
        servicesPercent = (100.0 * (double)success.getServices() / (double)attempts.getServices());
        blocksPercent   = (100.0 * (double)success.getBlocks() / (double)attempts.getBlocks());
        attacksPercent  = (100.0 * (double)success.getAttacks() / (double)attempts.getAttacks());
    }
    
    public double getServicesPercent() {
        return servicesPercent;
    }
    
    public double getBlocksPercent() {
        return blocksPercent;
    }
    
    public double getAttacksPercent() {
        return attacksPercent;
    }
}

class IO {
    Scanner scanner;
    
    public IO(Scanner _scanner) {
        scanner = _scanner;
    }
    
    public void handleInputs() {
        Team gameTeam = nextTeam();
        printTeamSummary(gameTeam);
    }
    
    private void printTeamSummary(Team team) {
        System.out.printf("Pontos de Saque: %.2f %%.\n", team.getServicesPercent());
        System.out.printf("Pontos de Bloqueio: %.2f %%.\n", team.getBlocksPercent());
        System.out.printf("Pontos de Ataque: %.2f %%.\n", team.getAttacksPercent());
    }
    
    private Moves nextMoves() {
        String moves = scanner.nextLine();
        String[] values = moves.split(" ");
        
        int services = Integer.parseInt(values[0]);
        int blocks = Integer.parseInt(values[1]);
        int attacks = Integer.parseInt(values[2]);
        
        return new Moves(services, blocks, attacks);
    }
    
    private Player nextPlayer() {
        String name = scanner.nextLine();
        Moves attempts = nextMoves();
        Moves success = nextMoves();
        
        return new Player(name, attempts, success);
    }
    
    private Team nextTeam() {
        int numberOfPlayersInTeam = scanner.nextInt();
        scanner.nextLine();
        
        Team currentTeam = new Team();
        for (int i = 0; i < numberOfPlayersInTeam; i++) {
            Player currentPlayer = nextPlayer();
            currentTeam.pushPlayer(currentPlayer);
        }
        
        return currentTeam;
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        IO io = new IO(new Scanner(System.in));
        io.handleInputs();
    }
 
}
