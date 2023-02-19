import java.util.Comparator;

// A. Implementing a Plane Seat Class
public class PlaneSeat {
    // Seat Attributes
    private int seatId;
    private boolean assigned = false;
    private int customerId;

    // Constructor 
    public PlaneSeat(int seatId, boolean assigned, int customerId) {
        this.seatId = seatId;
        this.assigned = assigned;
        this.customerId = customerId;
    }

    // Seat Methods
    public int getSeatID() {
        return seatId;
    }

    public int getCustomerID() {
        return customerId;
    }

    public boolean isOccupied() {
        return assigned;
    }

    public void assign(int cust_id) {
        // Assign this seat to the customer with this ID
        customerId = cust_id;
        assigned = true;
    }

    public void unAssign() {
        assigned = false;
    }
}
