import java.util.Arrays;
import java.util.Scanner;
import java.util.Collections;
import java.io.*;
import java.util.Comparator;

public class PlaneApp {
    public static void main(String args[]) {
        // Menu for Seating Reservation Programme
        Scanner scObject = new Scanner(System.in);
        Plane airplane = new Plane(12);
        int userChoice = 0;

        try {
            do {
                System.out.println("######################### Colossus Airlines Menu #########################");
                System.out.println("(1) Show the number of empty seats.");
                System.out.println("(2) Show the list of empty seats.");
                System.out.println("(3) Show the list of seat assignments by seat ID.");
                System.out.println("(4) Show the list of seat assignments by customer ID.");
                System.out.println("(5) Assign a customer to a seat.");
                System.out.println("(6) Remove a seat assignment.");
                System.out.println("(7) Exit");
                System.out.println("__________________________________________________________________________");
                System.out.println("Enter the number for your choice: ");

                userChoice = scObject.nextInt();
                switch(userChoice) {
                    case 1:
                        airplane.showNumEmptySeats();
                        break;

                    case 2:
                        airplane.showEmptySeats();
                        break;

                    case 3:
                        airplane.showAssignedSeats(true);
                        break;

                    case 4:
                        airplane.showAssignedSeats(false);
                        break;

                    case 5:
                        System.out.println("Assigning Seat...");
                        System.out.println("Please enter your SeatID: ");
                        int seatID = scObject.nextInt();
                        System.out.println("Please enter your CustomerID: ");
                        int customerID = scObject.nextInt();

                        airplane.assignSeat(seatID, customerID);
                        break;

                    case 6:
                        System.out.println("Enter the SeatID to unassign customer from: ");
                        int unassignSet = scObject.nextInt();
                        airplane.unAssignSeat(unassignSet);
                        break;

                    case 7:
                        continue;


                    default:
                        System.out.println("Invalid Option!! Program is terminating......");
                        userChoice = 8;
                        continue;
                }
            } while (userChoice < 7);
        }
        finally {
            // Close the Scanner Object to prevent memory leaks
            scObject.close();
        }

        return;
    }
    
}
