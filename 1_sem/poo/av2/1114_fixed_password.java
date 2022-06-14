import java.io.IOException;
import java.util.Scanner;
import java.util.Vector;

class GlobalDefs {
    public static final int PASSWD = 2002;
}

class UnauthorizedAccess extends RuntimeException{
    public UnauthorizedAccess(String message) {
        super(message);
    }
}

class ConnectionClosed extends RuntimeException{
    public ConnectionClosed(String message) {
        super(message);
    }
}

class DBController {
    Vector<Integer> usersPasswords = new Vector<Integer>();
    
    public int SelectPasswordFromUsersWhereIdIs(int id) {
        return usersPasswords.get(id - 1);
    }
    
    public int InsertIntoUsersPasswordValue(int passwd) {
        usersPasswords.add(passwd);
        return usersPasswords.size();
    }
}

class AuthService {
    private boolean isConnected = false;
    private DBController dbController;
    
    private int GetUniquePassword() {
        if (!isConnected) {
            throw new ConnectionClosed("couldn't establish connection to the database");
        }
        
        return dbController.SelectPasswordFromUsersWhereIdIs(1);
    }
    
    private boolean IsPasswordValid(int clientPasswd) {
        return clientPasswd == GetUniquePassword();
    }
    
    public void Connect(DBController _dbController) {
        dbController = _dbController;
        isConnected = true;
    }
    
    public void Disconnect() {
        dbController = null;
        isConnected = false;
    }
    
    public void Auth(int passwd) {
        if (!IsPasswordValid(passwd)) {
            throw new UnauthorizedAccess("invalid password");
        }
    }
}

class TestSuit {
    private DBController dbController;
    private AuthService authService;
    
    private void SetUp() {
        dbController = new DBController();
        dbController.InsertIntoUsersPasswordValue(GlobalDefs.PASSWD);
        
        authService = new AuthService();
        authService.Connect(dbController);
    }
    
    private void TearDown() {
        authService.Disconnect();
    }
    
    private boolean TestPassword(int passwd) {
        try {
            authService.Auth(passwd);
            System.out.printf("Acesso Permitido\n");
            return true;
        } catch (UnauthorizedAccess e) {
            System.out.printf("Senha Invalida\n");
            return false;
        }
    }
    
    public void Run() {
        SetUp();
        
        Scanner in = new Scanner(System.in);
        while (!TestPassword(in.nextInt()));
        
        TearDown();
    }
}

public class Main {
    
    public static void main(String[] args) throws IOException {
        new TestSuit().Run();
    }
 
}
