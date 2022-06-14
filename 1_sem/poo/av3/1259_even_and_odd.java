// Time limit exceeds on URI, dont know why

import java.io.IOException;
import java.util.List;
import java.util.Vector;
import java.util.Collections;
import java.util.Scanner;

class Storage
{
    private List<Integer> numbers;
    
    Storage()
    {
        numbers = new Vector<Integer>();
    }
    
    public List<Integer> GetNumbers()
    {
        return numbers;
    }
    
    public String Stringify()
    {
        String res = "";
        for(int i = 0; i < numbers.size(); i++) {
            res += numbers.get(i).toString() + "\n";
        }
        
        return res;
    }
}

abstract class StorageFilter
{
    protected Storage s;
    
    StorageFilter(Storage _s)
    {
        s = _s;
    }
    
    public abstract Storage Execute();
}

abstract class StorageSorter
{
    protected Storage s;
    
    StorageSorter(Storage _s)
    {
        s = _s;
    }
    
    public abstract void Execute();
}


class StorageFilterEven extends StorageFilter
{
    StorageFilterEven(Storage _s)
    {
        super(_s);
    }
    
    @Override
    public Storage Execute()
    {
        Storage filteredStorage = new Storage();
        for (int i = 0; i < s.GetNumbers().size(); i++) {
            Integer current = s.GetNumbers().get(i);
            if ((current % 2) == 0) {
                filteredStorage.GetNumbers().add(current);
            }
        }
        
        return filteredStorage;
    }
}

class StorageFilterOdd extends StorageFilter
{
    StorageFilterOdd(Storage _s)
    {
        super(_s);
    }
    
    @Override
    public Storage Execute()
    {
        Storage filteredStorage = new Storage();
        for (int i = 0; i < s.GetNumbers().size(); i++) {
            Integer current = s.GetNumbers().get(i);
            if ((current % 2) != 0) {
                filteredStorage.GetNumbers().add(current);
            }
        }
        
        return filteredStorage;
    }
}

class StorageSorterStupidRule extends StorageSorter
{
    StorageSorterStupidRule(Storage _s)
    {
        super(_s);
    }
    
    @Override
    public void Execute()
    {
        StorageFilterEven filterEven = new StorageFilterEven(s);
        StorageFilterOdd  filterOdd  = new StorageFilterOdd(s);
        
        Storage storageEven = filterEven.Execute();
        Storage storageOdd  = filterOdd.Execute();
        
        Collections.sort(storageEven.GetNumbers());
        Collections.sort(storageOdd.GetNumbers(), Collections.reverseOrder());
        
        s.GetNumbers().clear();
        for (int i = 0; i < storageEven.GetNumbers().size(); i++) {
            s.GetNumbers().add(storageEven.GetNumbers().get(i));
        }
        for (int i = 0; i < storageOdd.GetNumbers().size(); i++) {
            s.GetNumbers().add(storageOdd.GetNumbers().get(i));
        }
    }
}

class Parser
{
    public Storage Execute()
    {
        Scanner in = new Scanner(System.in);
        
        Storage s = new Storage();
        int numberOfNumbers = in.nextInt();
        for (int i = 0; i < numberOfNumbers; i++) {
            s.GetNumbers().add(in.nextInt());
        }
        
        return s;
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        Storage storage = new Parser().Execute();
        
        StorageSorterStupidRule sorter = new StorageSorterStupidRule(storage);
        sorter.Execute();
        
        System.out.printf("%s", storage.Stringify());
    }
}
