import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

class StringNode {
    private String data;
    private StringNode parent;
    private ArrayList<StringNode> children;
    
    StringNode(String _data) {
        data = _data;
        children = new ArrayList<StringNode>();
    }
    
    public String GetData() {
        return data;
    }
    
    public StringNode AppendChild(StringNode _child) {
        _child.parent = this;
        children.add(_child);
        return _child;
    }
    
    public StringNode SearchChild(String _data) {
        for (StringNode node : children) {
            if (node.data.equals(_data)) {
                return node;
            }
        }
        
        return this;
    }
    
    public StringNode GetLastChild() {
        return children.get(children.size() - 1);
    }
}

class StringTree {
    private StringNode root;
    
    StringTree() {
        root = new StringNode("root");
    }
    
    public StringNode GetRoot() {
        return root;
    }
}

class TokenTree {
    StringTree tree;
    
    TokenTree() {
        tree = new StringTree();
        StringNode nodeRoot = tree.GetRoot();
        
        StringNode nodeVertebrado           = nodeRoot.AppendChild(new StringNode("vertebrado"));
        StringNode nodeInvertebrado         = nodeRoot.AppendChild(new StringNode("invertebrado"));
        
        StringNode nodeVertebradoAve        = nodeVertebrado.AppendChild(new StringNode("ave"));
        StringNode nodeVertebradoMamifero   = nodeVertebrado.AppendChild(new StringNode("mamifero"));
        StringNode nodeInvertebradoInseto   = nodeInvertebrado.AppendChild(new StringNode("inseto"));
        StringNode nodeInvertebradoAnelideo = nodeInvertebrado.AppendChild(new StringNode("anelideo"));
        
        nodeVertebradoAve.AppendChild(new StringNode("carnivoro")).AppendChild(new StringNode("TAguia"));
        nodeVertebradoAve.AppendChild(new StringNode("onivoro")).AppendChild(new StringNode("TPomba"));
        nodeVertebradoMamifero.AppendChild(new StringNode("onivoro")).AppendChild(new StringNode("THomem"));
        nodeVertebradoMamifero.AppendChild(new StringNode("herbivoro")).AppendChild(new StringNode("TVaca"));
        nodeInvertebradoInseto.AppendChild(new StringNode("hematofago")).AppendChild(new StringNode("TPulga"));
        nodeInvertebradoInseto.AppendChild(new StringNode("herbivoro")).AppendChild(new StringNode("TLagarta"));
        nodeInvertebradoAnelideo.AppendChild(new StringNode("hematofago")).AppendChild(new StringNode("TSanguessuga"));
        nodeInvertebradoAnelideo.AppendChild(new StringNode("onivoro")).AppendChild(new StringNode("TMinhoca"));
    }
    
    public StringNode GetRoot() {
        return tree.GetRoot();
    }
}

interface IAnimal {
    public String GetToken();
}

class TAguia implements IAnimal
{ @Override public String GetToken() { return "aguia"; } }

class TPomba implements IAnimal
{ @Override public String GetToken() { return "pomba"; } }

class THomem implements IAnimal
{ @Override public String GetToken() { return "homem"; } }

class TVaca  implements IAnimal
{ @Override public String GetToken() { return "vaca"; } }

class TPulga implements IAnimal
{ @Override public String GetToken() { return "pulga"; } }

class TLagarta implements IAnimal
{ @Override public String GetToken() { return "lagarta"; } }

class TSanguessuga implements IAnimal
{ @Override public String GetToken() { return "sanguessuga"; } }

class TMinhoca implements IAnimal
{ @Override public String GetToken() { return "minhoca"; } }

class AnimalFactory {
    String className;
    
    AnimalFactory(String _className) {
        className = _className;
    }
    
    public IAnimal Create() {
        Object obj;
        try {
            obj = Class.forName(className).getDeclaredConstructor().newInstance();
        }
        catch (ClassNotFoundException | InstantiationException | IllegalAccessException | InvocationTargetException | NoSuchMethodException e) {
            obj = new THomem(); // Fallback para quando não encontrar nenhuma classe na árvore
        }
        
        return (IAnimal) obj;
    }
}

class TokenParser {
    Scanner scanner;
    TokenTree tokenTree;
    
    TokenParser(TokenTree _tokenTree) {
        scanner   = new Scanner(System.in);
        tokenTree = _tokenTree;
    }
    
    public String NextClassName() {
        String n1 = scanner.nextLine();
        String n2 = scanner.nextLine();
        String n3 = scanner.nextLine();
        
        return tokenTree.GetRoot().SearchChild(n1).SearchChild(n2).SearchChild(n3).GetLastChild().GetData();
    }
}

class IO {
    TokenParser tokenParser;
    
    IO () {
        tokenParser = new TokenParser(new TokenTree());
    }
    
    private IAnimal NextAnimal() {
        String className = tokenParser.NextClassName();
        return new AnimalFactory(className).Create();
    }
    
    public void handleNext() {
        IAnimal animal = NextAnimal();
        System.out.println(animal.GetToken());
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        IO io = new IO();
        io.handleNext();
    }
 
}
