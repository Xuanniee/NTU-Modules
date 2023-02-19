import java.util.Scanner;

public class Tut3q2 {
    public static void main(String args[]) {
        Scanner scObject = new Scanner(System.in);

        System.out.println("Provide the X Coordinate of the Circle/Cylinder: ");
        int x = scObject.nextInt();
        System.out.println("Provide the Y Coordinate of the Circle/Cylinder: ");
        int y = scObject.nextInt();

        Circle circleInstance = new Circle(x, y);
        Cylinder cylinderInstance = new Cylinder(x, y);
        System.out.println("Provide the Radius of the Circle/Cylinder: ");
        double radius = scObject.nextDouble();
        // Different Instances so need to set twice
        circleInstance.setRadius(radius);
        cylinderInstance.setRadius(radius);

        System.out.println("Indicate 1 for Circle, 2 for Cylinder");
        int userInput = scObject.nextInt();
        if (userInput == 1) {
            // Circle
            double area = circleInstance.area();
            System.out.printf("Area: %.2f\n", area);
        } 
        else if (userInput == 2) {
            // Cylinder
            System.out.println("Provide the Height of the Cylinder: ");
            cylinderInstance.setHeight(scObject.nextDouble());
            System.out.println("Indicate 1 for Area, 2 for Volume");
            switch(scObject.nextInt()) {
                case 1:
                    double area = cylinderInstance.area();
                    System.out.printf("Area: %.2f\n", area);
                    break;
                case 2:
                    double volume = cylinderInstance.volume();
                    System.out.printf("Volume: %.2f\n", volume);
            }
        }
        

    }
}

// Parent Class
public class Point {
    // Attributes
    protected int x;
    protected int y;

    // Constructor
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    // Methods
    public String toString() {
        String result = "[ " + this.x + ", " + this.y + " ]";
        return result;
    }
    public void setPoint(int x, int y) {
        this.x = x;
        this.y = y;
    }
    public int getX() {
        return this.x;
    }
    public int getY() {
        return this.y;
    }
}

// Subclasses
public class Circle extends Point {
    // Attributes
    private double radius;
    public static final double PI = Math.PI;
    
    // Constructor
    public Circle(int x, int y) {
        super(x, y);
        radius = 0;
    }

    // Methods
    public void setRadius(double radius) {
        this.radius = radius;
    }
    public double getRadius() {
        return this.radius;
    }
    public double area() {
        return (PI * radius * radius);
    }
    public String toString() {
        return super.toString();
    }
}

public class Cylinder extends Circle {
    // Attributes
    private double height;
    
    // Constructor
    public Cylinder(int x, int y) {
        super(x, y);
        height = 0;
    }

    // Methods
    public void setHeight(double height) {
        this.height = height;
    }
    public double getHeight() {
        return this.height;
    }
    public double volume() {
        double radius = super.getRadius();
        return (PI * radius * radius * height);
    }
    public double area() {
        double radius = super.getRadius();
        double curvedSurfaceArea = 2 * PI * radius * height;
        double circleArea = 2 * PI * radius * radius;

        return (curvedSurfaceArea + circleArea);
    }
    public String toString() {
        return super.toString();
    }
}