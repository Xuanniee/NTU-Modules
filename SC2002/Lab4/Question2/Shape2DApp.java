import java.util.Scanner;

public class Shape2DApp {
    
    public static void main(String args[]) {
        Scanner scObject = new Scanner(System.in);
        int numShapes = 0;
        int userChoice = 0;
        double totalFigureArea = 0;
        Shapes[] shapesList = null;

        do {
            // User Menu
            System.out.println("######################### Shapes Menu #########################");
            System.out.println("(1) Provide the Dimensions for the 2D Figure.");
            System.out.println("(2) Calculate the Area of the 2D Figure.");
            System.out.println("(3) Quit.");
            System.out.println("__________________________________________________________________________");
            System.out.println("Enter the number for your choice: ");
            userChoice = scObject.nextInt();

            switch(userChoice) {
                case 1:
                    // Create a List to store the Shapes of the Figure
                    System.out.println("Please provide the total number of shapes in your 2D figure: ");
                    numShapes = scObject.nextInt();
                    shapesList = new Shapes[numShapes];

                    int userChoice2 = 0;
                    int counter = 0;
                    while (counter != numShapes) {
                        System.out.println("######################### Dimensions Menu #########################");
                        System.out.println("(1) Circle.");
                        System.out.println("(2) Rectangle.");
                        System.out.println("(3) Square.");
                        System.out.println("(4) Triangle.");
                        System.out.println("__________________________________________________________________________");
                        System.out.println("Choose the Shape that you would like to provide the dimensions with: ");
                        userChoice2 = scObject.nextInt();

                        switch(userChoice2) {
                            case 1:
                                // Circle
                                System.out.println("Radius of Circle: ");
                                Double circleRadius = scObject.nextDouble();

                                // Creating a Circle and setting the Radius
                                shapesList[counter] = new Circle(circleRadius);
                                break;
                            
                            case 2:
                                // Rectangle
                                System.out.println("Length of Rectangle: ");
                                Double rectLength = scObject.nextDouble();
                                System.out.println("Height of Rectangle: ");
                                Double rectHeight = scObject.nextDouble();

                                // Creating a new Rectangle Shape
                                shapesList[counter] = new Rectangle(rectLength, rectHeight);
                                break;

                            case 3:
                                // Square
                                System.out.println("Length of Square: ");
                                Double squareLength = scObject.nextDouble();

                                // Creating new Square
                                shapesList[counter] = new Square(squareLength);
                                break;

                            case 4:
                                // Triangle
                                System.out.println("Base of Triangle: ");
                                double triangleBase = scObject.nextDouble();
                                System.out.println("Height of Triangle: ");
                                double triangleHeight = scObject.nextDouble();

                                shapesList[counter] = new Triangle(triangleBase, triangleHeight);
                                break;
                            
                            default:
                                System.out.println("UNKNOWN SHAPE!!");
                                break;
                        }
                        counter += 1;
                    }

                    break;

                case 2:
                    if (shapesList == null) {
                        System.out.println("Invalid Choice!! Please set up the dimensions of the figure first.");
                        break;
                    }
                    for (int i = 0; i < numShapes; i += 1) {
                        totalFigureArea += shapesList[i].calculateArea();
                    }

                    System.out.printf("Total Area of 2D Figure: %.2f\n\n", totalFigureArea);
                    break;
                
                case 3:
                    break;

                default:
                    System.out.println("Invalid Choice!! Please provide another value.");
            }

        } while(userChoice != 3);

        scObject.close();
    }
}
