import java.io.IOException;
import java.util.*;

class TokenParser {
    private Scanner in;
    List<List<String>> lists;
    
    public TokenParser() {
        in = new Scanner(System.in);
        lists = new Vector<List<String>>();
    }
    
    public void parse() {
        int numberOfLists = in.nextInt(); in.nextLine();
        for (int i = 0; i < numberOfLists; i++) {
            String currentLine = in.nextLine();
            String[] tokens = currentLine.split(" ");
            
            List<String> currentList = new Vector<String>();
            for (int j = 0; j < tokens.length; j++) {
                currentList.add(tokens[j]);
            }
            
            lists.add(currentList);
        }
    }
    
    public List<String> GetList(int idx) {
        if (idx > lists.size()) {
            return null;
        }
        
        return lists.get(idx - 1);
    }
}

class ListConverter {
    private List<String> list;
    
    public void Attach(List<String> _list) {
        list = _list;
    }
    
    public Set<String> ToSet() {
        Set<String> set = new HashSet<String>();
        for (int i = 0; i < list.size(); i++) {
            set.add(list.get(i));
        }
        
        return set;
    }
    
    public String ToString() {
        String res = "";
        for (int i = 0; i < list.size(); i++) {
            res += list.get(i) + " ";
        }
        
        return res.substring(0, res.length() - 1);
    }
}

class SetConverter {
    private Set<String> set;
    
    public void Attach(Set<String> _set) {
        set = _set;
    }
    
    public List<String> ToList() {
        List<String> list = new Vector<String>();
        
        Iterator<String> value = set.iterator();
        while (value.hasNext()) {
            String str = value.next();
            list.add(str);
        }
        
        Collections.sort(list);
        
        return list;
    }
}

class ListHandler {
    private List<String> list;
    
    public void Attach(List<String> _list) {
        list = _list;
    }
    
    public String Handle() {
        ListConverter listConverter = new ListConverter();
        SetConverter setConverter = new SetConverter();
        
        listConverter.Attach(list);
        setConverter.Attach(listConverter.ToSet());
        listConverter.Attach(setConverter.ToList());
        
        return listConverter.ToString();
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        
        ListHandler listHandler = new ListHandler();
        TokenParser parser = new TokenParser();
        parser.parse();
        
        int i = 1;
        List<String> it = parser.GetList(i);
        while(it != null) {
            listHandler.Attach(it);
            System.out.print(listHandler.Handle() + "\n");
            
            i++;
            it = parser.GetList(i);
        }
        
    }
 
}
