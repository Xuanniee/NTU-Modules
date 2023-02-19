import java.util.Scanner;

public class CircleApp {
    public static void main (String[] args) {
        try (Scanner scObject = new Scanner(System.in)) {
            // Displays a Menu for Users to select Options
            System.out.println("===== Circle Computation =====");
            System.out.println("|1. Create a new circle      |");
            System.out.println("|2. Print Area               |");
            System.out.println("|3. Print Circumference      |");
            System.out.println("|4. Quit                     |");
            
            // Initialisation
            Circle cir = new Circle(0);
            Boolean userMenu = true;

            do {
                System.out.println("Choose Options (1-3): ");
                int userChoice = scObject.nextInt();

                switch(userChoice) {
                    case 1:
                        System.out.println("Enter the radius to compute the area and circumference: ");
                        int userRadius = scObject.nextInt();
                        cir.setRadius(userRadius);
                        System.out.println("A new circle is created: ");
                        break;

                    case 2:
                        if (cir != null) {
                            cir.printArea();
                        }
                        else {
                            System.out.println("Circle's Radius is not provided yet!!");
                        }
                        break;

                    case 3:
                        if (cir != null) {
                            cir.printCircumference();
                        }
                        else {
                            System.out.println("Circle's Radius is not provided yet!!");
                        }
                        break;

                    default:
                        // For Choice 4
                        userMenu = false;
                        System.out.println("Thank you!!");
                }
            } while (userMenu);
        }
        
    }
}

public class Circle {
    // Attributes / Instance Variables
    private double radius;        // radius of circle
    private static final double PI = 3.14159;
    
    // Constructor; No Retur Type and Name must follow the Class Names
    public Circle(double rad) {
        setRadius(rad);
    }

    // Abstract Methods & Behaviours
    // mutator method – set radius
    // Concrete Methods
    public void setRadius(double rad) {
        this.radius = rad;
    } // accessor method – get radius
    
    public double getRadius() {
        return radius;
    }

    // calculate area
    public double area() {
        return PI * radius * radius;
    }

    // calculate circumference
    public double circumference() {
        return 2 * PI * radius;
    }

    // print area
    public void printArea() {
        System.out.println("Area of Circle:");
        System.out.printf("Radius: %.1f\n", radius);
        System.out.printf("Area: %.5f\n\n", area());
    }

    // print circumference
    public void printCircumference() {
        System.out.println("Circumference of Circle:");
        System.out.printf("Radius: %.1f\n", radius);
        System.out.printf("Circumference: %.5f\n\n", circumference());
    }
}
