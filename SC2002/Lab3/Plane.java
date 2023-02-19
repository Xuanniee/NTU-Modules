import java.util.Comparator;
import java.util.Arrays;


// B. Implementing aa Plane Class
public class Plane {
    private PlaneSeat[] planeSeats;
    private int numEmptySeat;
    private int numSeats = 12;
    private int BIG_VALUE = 99999999;

    // Constructor
    public Plane(int numEmptySeat) {
        this.numEmptySeat = numEmptySeat;
        planeSeats = new PlaneSeat[12];

        for (int i = 0; i < 12; i += 1){
            // -1 to represent no Customer ID yet
            planeSeats[i] = new PlaneSeat((i+1), false, BIG_VALUE);
        }
    }

    // Plane Methods    
    private PlaneSeat[] sortSeats() {
        // Create a Deep Copy of Seats to sort
        PlaneSeat[] copy = new PlaneSeat[12];
        System.arraycopy(planeSeats, 0, copy, 0, 12);

        // Sort by Customer ID
        // Arrays.sort(copy, Comparator.comparing(PlaneSeat.getCustomerID));
        Arrays.sort(copy, new Comparator<PlaneSeat>() {
            public int compare(PlaneSeat s1, PlaneSeat s2) {
                return Integer.compare(s1.getCustomerID(), s2.getCustomerID());
            }
        });

        return copy;
    }

    public void showNumEmptySeats() {
        // Display the Number of Empty Seats
        System.out.println("Number of Empty Seats: " + numEmptySeat);
    }

    public void showEmptySeats() {
        // Display the List of Empty Seats
        for (int i = 0; i < numSeats; i += 1) {
            if (planeSeats[i].isOccupied() == false) {
                System.out.println("SeatID " + planeSeats[i].getSeatID());
            }
        }
    }

    public void showAssignedSeats(boolean bySeatId) {
        // If bySeatId == true, order will be via Seat ID, else is Customer ID
        PlaneSeat[] temp = new PlaneSeat[12];
        System.arraycopy(planeSeats, 0, temp, 0, 12);
        System.out.println("The seat assignments are as follow: ");

        if (!bySeatId) {
            // Sort By Customer ID
            temp = sortSeats();
        }
        for (int i  = 0; i < numSeats; i += 1) {
            if (temp[i].isOccupied()) {
                // System.out.print(temp[i].isOccupied() + " ");
                System.out.println("SeatID " + temp[i].getSeatID() + " assigned to CustomerID " + temp[i].getCustomerID() + ".");
            }
        }
    }

    public void assignSeat(int seatId, int cust_id) {
        // Assigns a Customer ID to an Empty Seat
        for (int i = 0; i < numSeats; i += 1) {
            // Ensure unoccupied and is the seat we want
            if (planeSeats[i].isOccupied() == false && planeSeats[i].getSeatID() == seatId) {
                planeSeats[i].assign(cust_id);
                numEmptySeat -= 1;
                System.out.println("Seat Assigned!!!");
                return;
            }
        }
        System.out.println("Seat already assigned to a customer.");
    }

    public void unAssignSeat(int seatId) {
        // Unassigns a Customer ID to a Seat
        for (int i = 0; i < numSeats; i += 1) {
            // Ensure occupied and is the seat we want
            if (planeSeats[i].isOccupied() == true && planeSeats[i].getSeatID() == seatId) {
                planeSeats[i].unAssign();
                numEmptySeat += 1;
                System.out.println("Seat Unassigned!!");
            }
        }
    }
}