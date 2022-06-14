import java.io.IOException;
import java.util.Scanner;

class Point3D {
    private int x; private int y; private int z;
    
    public Point3D(int _x, int _y, int _z) {
        x = _x;
        y = _y;
        z = _z;
    }
    
    public int GetX() { return x; }
    public int GetY() { return y; }
    public int GetZ() { return z; }
}

class Point2D extends Point3D {
    public Point2D(int _x, int _y) {
        super(_x, _y, 0);
    }
}

interface Quadrant {
    public String Name();
    public boolean Contains(Point2D p);
}
class PrimeiroQuadrante implements Quadrant {
    @Override public String Name() { return "primeiro"; }
    @Override public boolean Contains(Point2D p) { return p.GetX() > 0 && p.GetY() > 0; }
}
class SegundoQuadrante implements Quadrant {
    @Override public String Name() { return "segundo"; }
    @Override public boolean Contains(Point2D p) { return p.GetX() < 0 && p.GetY() > 0; }
}
class TerceiroQuadrante implements Quadrant {
    @Override public String Name() { return "terceiro"; }
    @Override public boolean Contains(Point2D p) { return p.GetX() < 0 && p.GetY() < 0; }
}
class QuartoQuadrante implements Quadrant {
    @Override public String Name() { return "quarto"; }
    @Override public boolean Contains(Point2D p) { return p.GetX() > 0 && p.GetY() < 0; }
}
class QuadrantFactory {
    private int quadrantNumber;
    
    QuadrantFactory(int _quadrantNumber) { quadrantNumber = _quadrantNumber; }
    
    public Quadrant Create() {
        switch (quadrantNumber) {
            case 1:  return new PrimeiroQuadrante();
            case 2:  return new SegundoQuadrante();
            case 3:  return new TerceiroQuadrante();
            case 4:  return new QuartoQuadrante();
            default: return null;
        }
    }
}

class PointQuadrantVerifier {
    private Point2D p;
    
    PointQuadrantVerifier(Point2D _p) { p = _p; }
    
    public Quadrant Verify() {
        for (int i = 1; i <= 4; i++) {
            QuadrantFactory factory = new QuadrantFactory(i);
            Quadrant q = factory.Create();
            
            if (q.Contains(p)) {
                return q;
            }
        }
        
        return null;
    }
}

class Point2DReader {
    private Scanner scanner;
    
    Point2DReader() {
        scanner = new Scanner(System.in);
    }
    
    public Point2D nextPoint2D() {
        int x = scanner.nextInt();
        int y = scanner.nextInt();
        
        return new Point2D(x, y);
    }
}

class InputLoop {
    private Point2DReader pReader;
    
    InputLoop() {
        pReader = new Point2DReader();
    }
    
    private Quadrant nextQuadrant() {
        Point2D p = pReader.nextPoint2D();
        PointQuadrantVerifier v = new PointQuadrantVerifier(p);
        
        return v.Verify();
    }
    
    private void printQuadrantName(Quadrant q) {
        System.out.printf("%s\n", q.Name());
    }
    
    public void Exec() {
        for (;;) {
            Quadrant q = nextQuadrant();
            
            if (q == null) {
                break;
            }
            
            printQuadrantName(q);
        }
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        InputLoop loop = new InputLoop();
        loop.Exec();
    }
 
}
