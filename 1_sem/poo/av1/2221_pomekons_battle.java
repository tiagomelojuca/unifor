import java.io.IOException;
import java.util.Scanner;

class Pomekon {
    private int atk;
    private int def;
    
    public Pomekon(int _atk, int _def) {
        atk = _atk;
        def = _def;
    }
    
    public int GetAttack() {
        return atk;
    }
    
    public int GetDefense() {
        return def;
    }
}

class Master {
    private String name;
    private boolean hasBonus;
    
    public Master(String _name, int _lvl) {
        name = _name;
        hasBonus = _lvl % 2 == 0;
    }
    
    public String GetName() {
        return name;
    }
    
    public boolean HasBonus() {
        return hasBonus;
    }
}

class Team {
    private Pomekon pomekon;
    private Master master;
    
    public Team(Pomekon _pomekon, Master _master) {
        pomekon = _pomekon;
        master = _master;
    }
    
    public Pomekon GetPomekon() {
        return pomekon;
    }
    
    public Master GetMaster() {
        return master;
    }
}

class Battle {
    private Team t1;
    private Team t2;
    
    private double value1;
    private double value2;
    
    private boolean hasWinner;
    private Team winner;
    
    public Battle(int _bonus, Team _t1, Team _t2) {
        t1 = _t1;
        t2 = _t2;
        
        int bonusAppliedT1 = t1.GetMaster().HasBonus() ? _bonus : 0;
        value1 = ((t1.GetPomekon().GetAttack() + t1.GetPomekon().GetDefense()) / 2.0) + bonusAppliedT1;
        
        int bonusAppliedT2 = t2.GetMaster().HasBonus() ? _bonus : 0;
        value2 = ((t2.GetPomekon().GetAttack() + t2.GetPomekon().GetDefense()) / 2.0) + bonusAppliedT2;
        
        if (value1 != value2) {
            hasWinner = true;
            winner = value1 > value2 ? t1 : t2;
        }
    }
    
    public boolean HasWinner() {
        return hasWinner;
    }
    
    public Team GetWinner() {
        return winner;
    }
}

class BattleIO {
    private Scanner scanner;
    
    public BattleIO(Scanner _scanner) {
        scanner = _scanner;
    }
    
    public Battle nextBattle() {
        int bonus = scanner.nextInt();
        
        int atkPomekonDabriel = scanner.nextInt();
        int defPomekonDabriel = scanner.nextInt();
        int lvlDabriel = scanner.nextInt();
        
        int atkPomekonGuarte = scanner.nextInt();
        int defPomekonGuarte = scanner.nextInt();
        int lvlGuarte = scanner.nextInt();
        
        Master dabriel = new Master("Dabriel", lvlDabriel);
        Pomekon pomekonDabriel = new Pomekon(atkPomekonDabriel, defPomekonDabriel);
        Team teamDabriel = new Team(pomekonDabriel, dabriel);
        
        Master guarte = new Master("Guarte", lvlGuarte);
        Pomekon pomekonGuarte = new Pomekon(atkPomekonGuarte, defPomekonGuarte);
        Team teamGuarte = new Team(pomekonGuarte, guarte);
        
        return new Battle(bonus, teamDabriel, teamGuarte);
    }
}

class DataIO {
    private void PrintResult(Battle battle) {
        String res = battle.HasWinner() ? battle.GetWinner().GetMaster().GetName() : "Empate";
        System.out.printf("%s\n", res);
    }
    
    public void handleNextInput() {
        Scanner in = new Scanner(System.in);
        BattleIO reader = new BattleIO(in);
        
        int numberOfBattles = in.nextInt();
        for (int i = 0; i < numberOfBattles; i++) {
            Battle currentBattle = reader.nextBattle();
            PrintResult(currentBattle);
        }
        
        in.close();
    }
}
 
public class Main {
 
    public static void main(String[] args) throws IOException {
        DataIO io = new DataIO();
        io.handleNextInput();
    }
 
}
