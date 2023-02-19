import java.lang.constant.DirectMethodHandleDesc.Kind;

// public class staticBinding {
//     public static void main (String args[]) {
//         /** 
//          * Demonstrate Static Binding of all printArea Methods for each Polygon Subclass
//          *  */ 
//         // Static Binding is to look at Reference Type (Left Hand Side)
//         Rectangle rectObject = new Rectangle("Rectangle Object", 10, 20);
//         Triangle triObject = new Triangle("Triangle Object", 20, 15);

//         TestPolygon testPolygon = new TestPolygon("Test Polygon", 1, 1);
//         System.out.println("This is printArea for Rectangle: ");
//         testPolygon.printArea(rectObject);
//         System.out.println("This is printArea for Triangle: ");
//         testPolygon.printArea(triObject);
//     }
// }

public class dynamicBinding {
    public static void main(String args[]) {
        /** 
         * Demonstrate Dynamic Binding of all printArea Methods for each Polygon Subclass
         *  */ 
        // Static Binding is to look at Reference Type (Left Hand Side)
        Rectangle rectObject = new Rectangle("Rectangle Object", 10, 20);
        Triangle triObject = new Triangle("Triangle Object", 20, 15);

        rectObject.printArea(rectObject);
        triObject.printArea(triObject);
    }
}

abstract class Polygon {
    // Polygon Attributes
    public enum KindofPolygon { POLY_PLAIN, POLY_RECT, POLY_TRIANG };
    protected String name;
    protected float width;
    protected float height;
    protected KindofPolygon polytype;
    
    // Constructor
    public Polygon(String theName, float theWidth, float theHeight) {
        name = theName;
        width = theWidth;
        height = theHeight;
        polytype = KindofPolygon.POLY_PLAIN;
    }

    // Methods / Behaviours
    public KindofPolygon getPolytype() {
        return polytype;
    }

    public void setPolytype(KindofPolygon value) { 
        polytype = value;
    }

    public String getName()  { 
        return name; 
    }
    
    abstract float calArea();

    public void printWidthHeight( ) {
        System.out.println("Width = " + width + " Height = " + height); 
    }

    public void printArea(Polygon polygon) {
        float area = polygon.calArea();
        System.out.printf("The Area of the Polygon is %.2f .\n", area);
    }
}

// Subclasses derived from Polygon Class
public class Rectangle extends Polygon {
    // Constructor
    public Rectangle(String name, float width, float height) {
        // Initialise the Polygon
        super(name, width, height);
        // Set to a Rectangle; Inherited the Enum
        super.setPolytype(KindofPolygon.POLY_RECT);
    }

    // Methods
    @Override
    public float calArea() {
        return (super.width * super.height);
    }

}

public class Triangle extends Polygon {
    // Constructor
    public Triangle(String name, float width, float height) {
        super(name, width, height);
        super.setPolytype(KindofPolygon.POLY_TRIANG);
    }

    // Methods
    @Override
    public float calArea() {
        // Inherited the Attributes as well
        float area = (float) 0.5 * width * height;
        return area;
    }

}

public class TestPolygon extends Polygon{
    public TestPolygon(String name, float width, float height) {
        super(name, width, height);
    }
    // Method Overloading for PrintArea()
    public void printArea(Rectangle rectangle) {
        // Calculate and Print out the Area of the Polygon
        float rectArea = rectangle.calArea();
        System.out.printf("The Area of the Rectangle is %.2f .\n", rectArea);
    }

    public void printArea(Triangle triangle) {
        float triArea = triangle.calArea();
        System.out.printf("The Area of the Triangle is %.2f .\n", triArea);
    }
    @Override
    public float calArea() {
        return 0;
    }
    
}