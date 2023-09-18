import java.util.Scanner;

public class Shape3DApp {
    public static void main(String args[]) {
        Scanner scObject = new Scanner(System.in);
        int numShapes = 0;
        int userChoice = 0;
        double totalFigureArea = 0;
        Shapes[] shapesList = null;

        do {
            // User Menu
            System.out.println("######################### Shapes Menu #########################");
            System.out.println("(1) Provide the Dimensions for the 3D Figure.");
            System.out.println("(2) Calculate the Surface Area of the 3D Figure.");
            System.out.println("(3) Quit.");
            System.out.println("__________________________________________________________________________");
            System.out.println("Enter the number for your choice: ");
            userChoice = scObject.nextInt();

            switch(userChoice) {
                case 1:
                    // Create a List to store the Shapes of the Figure
                    System.out.println("Please provide the total number of shapes in your 3D figure: ");
                    numShapes = scObject.nextInt();
                    shapesList = new Shapes[numShapes];

                    int userChoice2 = 0;
                    int counter = 0;
                    while (counter != numShapes) {
                        System.out.println("######################### Dimensions Menu #########################");
                        System.out.println("(1) Sphere.");
                        System.out.println("(2) Cuboid.");
                        System.out.println("(3) Cone.");
                        System.out.println("(4) Pyramid.");
                        System.out.println("(5) Cylinder.");
                        System.out.println("__________________________________________________________________________");
                        System.out.println("Choose the Shape that you would like to provide the dimensions with: ");
                        userChoice2 = scObject.nextInt();

                        switch(userChoice2) {
                            case 1:
                                System.out.println("Radius of Sphere: ");
                                Double sphereRadius = scObject.nextDouble();

                                // Creating a Sphere and setting the Radius
                                shapesList[counter] = new Sphere(sphereRadius);
                                break;
                            
                            case 2:
                                System.out.println("Length of Cuboid: ");
                                Double cuboidLength = scObject.nextDouble();
                                System.out.println("Breadth of Cuboid: ");
                                Double cuboidBreadth = scObject.nextDouble();
                                System.out.println("Height of Cuboid: ");
                                Double cuboidHeight = scObject.nextDouble();

                                // Creating a new Cuboid Shape
                                shapesList[counter] = new Cuboid(cuboidBreadth, cuboidHeight, cuboidLength);
                                break;

                            case 3:
                                // Cone
                                System.out.println("Radius of Cone: ");
                                Double coneRadius = scObject.nextDouble();
                                System.out.println("Height of Cone: ");
                                Double coneHeight = scObject.nextDouble();

                                shapesList[counter] = new Cone(coneRadius, coneHeight);
                                break;

                            case 4:
                                System.out.println("Length of Pyramid: ");
                                double pyramidLength = scObject.nextDouble();
                                System.out.println("Height of Pyramid: ");
                                double pyramidHeight = scObject.nextDouble();

                                shapesList[counter] = new SquarePyramid(pyramidHeight, pyramidLength);
                                break;
                            
                            case 5:
                                // Cylinder
                                System.out.println("Radius of Cylinder: ");
                                Double cylinderRadius = scObject.nextDouble();
                                System.out.println("Height of Cylinder: ");
                                Double cylinderHeight = scObject.nextDouble();

                                shapesList[counter] = new Cylinder(cylinderHeight, cylinderRadius);
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

                    System.out.printf("Total Surface Area of 3D Figure: %.2f\n\n", totalFigureArea);
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
