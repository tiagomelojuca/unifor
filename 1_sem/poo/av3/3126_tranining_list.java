import java.io.IOException;
import java.util.*;

class InputReader {
    private Scanner in;
    
    public InputReader() {
        in = new Scanner(System.in);
    }
    
    public Vector<Byte> read() {
        Vector<Byte> candidatesChoices = new Vector<Byte>();
        
        int numberOfCandidates = in.nextInt(); in.nextLine();
        String candidates = in.nextLine();
        
        String[] tokens = candidates.split(" ");
        for (int i = 0; i < numberOfCandidates; i++) {
            candidatesChoices.add(tokens[i].equals("1") ? (byte) 0x01 : (byte) 0x00);
        }
        
        return candidatesChoices;
    }
}

class CandidateStorage {
    Vector<Byte> candidatesChoices;
    
    public CandidateStorage(Vector<Byte> candidates) {
        candidatesChoices = candidates;
    }
    
    public int getCandidates() {
        int nCandidates = 0;
        
        for (int i = 0; i < candidatesChoices.size(); i++) {
            if (candidatesChoices.get(i) != 0x00) {
                nCandidates++;
            }
        }
        
        return nCandidates;
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        InputReader io = new InputReader();
        CandidateStorage storage = new CandidateStorage(io.read());
        System.out.print(storage.getCandidates() + "\n");
    }
 
}
