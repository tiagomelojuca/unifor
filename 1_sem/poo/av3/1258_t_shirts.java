import java.io.IOException;
import java.util.*;

enum Colors     { WHITE, RED; }
enum ShirtSizes { P, M, G; }

class StringTable {
    private static StringTable uniqueInstance = new StringTable();
    
    private Map<Colors, String> colorsNames;
    private Map<ShirtSizes, String> sizesNames;
    
    private StringTable() {
        colorsNames = new HashMap<Colors, String>();
        colorsNames.put(Colors.WHITE, "branco");
        colorsNames.put(Colors.RED,   "vermelho");
        
        sizesNames = new HashMap<ShirtSizes, String>();
        sizesNames.put(ShirtSizes.P, "P");
        sizesNames.put(ShirtSizes.M, "M");
        sizesNames.put(ShirtSizes.G, "G");
    }
    
    public static StringTable GetInstance() {
        return uniqueInstance;
    }
    
    public String GetString(Colors color) {
        return colorsNames.get(color);
    }
    
    public Colors GetColor(String value) {
        for (Map.Entry<Colors, String> set : colorsNames.entrySet()) {
            if (set.getValue().equals(value)) {
                return set.getKey();
            }
        }
        
        return null;
    }
    
    public String GetString(ShirtSizes size) {
        return sizesNames.get(size);
    }
    
    public ShirtSizes GetSize(String value) {
        for (Map.Entry<ShirtSizes, String> set : sizesNames.entrySet()) {
            if (set.getValue().equals(value)) {
                return set.getKey();
            }
        }
        
        return null;
    }
}

class TShirt implements Comparable<TShirt> {
    private Colors detailColor;
    private ShirtSizes size;
    private String studentName;
    
    public TShirt(Colors _detailColor, ShirtSizes _size, String _studentName) {
        detailColor = _detailColor;
        size = _size;
        studentName = _studentName;
    }
    
    public String Stringify() {
        String strDetailColor = StringTable.GetInstance().GetString(detailColor);
        String strShirtSize   = StringTable.GetInstance().GetString(size);
        return strDetailColor + " " + strShirtSize + " " + studentName;
    }
    
    @Override
    public int compareTo(TShirt other) {
        int colorCompare = detailColor.compareTo(other.detailColor);
        if (colorCompare != 0) {
            return colorCompare;
        }
        
        int sizeCompare = size.compareTo(other.size);
        if (sizeCompare != 0) {
            return sizeCompare;
        }
        
        return studentName.compareTo(other.studentName);
    }
}

class CollegeClass {
    private List<TShirt> shirts;
    
    public CollegeClass() {
        shirts = new Vector<TShirt>();
    }
    
    public void PushShirt(TShirt shirt) {
        shirts.add(shirt);
    }
    
    public void Sort() {
        Collections.sort(shirts);
    }
    
    public String Stringify() {
        String str = "";
        for (int i = 0; i < shirts.size() - 1; i++) {
            str += shirts.get(i).Stringify() + "\n";
        }
        str += shirts.get(shirts.size() - 1).Stringify();
        
        return str;
    }
}

class InputHandler {
    private Scanner scanner;
    
    public InputHandler() {
        scanner = new Scanner(System.in);
    }
    
    public CollegeClass readClass() {
        int numberOfShirts = scanner.nextInt();
        if (numberOfShirts == 0) {
            return null;
        }
        scanner.nextLine();
        
        CollegeClass currentClass = new CollegeClass();
        for (int i = 0; i < numberOfShirts; i++) {
            currentClass.PushShirt(readShirt());
        }
        currentClass.Sort();
        
        return currentClass;
    }
    
    private TShirt readShirt() {
        List<String> tokens = new Vector<String>();
        tokens.add(scanner.nextLine());
        Collections.addAll(tokens, scanner.nextLine().split(" "));
        
        String inputName     = tokens.get(0);
        Colors inputColor    = StringTable.GetInstance().GetColor(tokens.get(1));
        ShirtSizes inputSize = StringTable.GetInstance().GetSize(tokens.get(2));
        
        return new TShirt(inputColor, inputSize, inputName);
    }
}

class EventLoop {
    private InputHandler iHandler;
    
    public EventLoop(InputHandler _iHandler) {
        iHandler = _iHandler;
    }
    
    public void Begin() {
        boolean isFirstPrint = true;
        for (CollegeClass currentClass = iHandler.readClass();
             currentClass != null;
             currentClass = iHandler.readClass()) {
            String classStr = currentClass.Stringify();
            
            System.out.printf("%s", isFirstPrint ? classStr : "\n\n" + classStr);
            if (isFirstPrint) {
                isFirstPrint = false;
            }
        }
        System.out.printf("\n");
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        EventLoop evLoop = new EventLoop(new InputHandler());
        evLoop.Begin();
    }
}
