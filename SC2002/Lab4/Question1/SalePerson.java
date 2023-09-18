// SalePerson must be a Comparable so that we can make comparisons in the first place
public class SalePerson implements Comparable {
    // Attributes
    private String firstName;
    private String lastName;
    private int totalSales;

    // Constructor
    public SalePerson(String firstName, String lastName, int totalSales) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.totalSales = totalSales;
    }

    // Methods
    public String toString() {
        // Create a String to express the number of sales made
        return String.format("%s, %s : %d", lastName, firstName, totalSales);
    }

    /**
     * Check if first and last name of Object is the same as Current Sales Person
     */
    public boolean equals(SalePerson person) {
        // Object Names
        String personFirst = person.getFirstName();
        String personLast = person.getLastName();
        if ((personFirst.compareToIgnoreCase(this.firstName) == 0) && (personLast.compareToIgnoreCase(this.lastName) == 0)) {
            return true;
        }
        
        // Not the same person
        return false;
    }

    /**
     * Makes Comparisons based on total sales. Negative number if executing object has less total sales and vice versa.
     * @param object
     * @return
     */
    @Override
    public int compareTo(Object object) {
        if (this.totalSales > ((SalePerson) object).getTotalSales()) {
            return 1;
        }
        else if (this.totalSales < ((SalePerson) object).getTotalSales()) {
            return -1;
        }
        else {
            // Same Amount of Total Sales; use Last Name to break Tie
            if (lastName.compareToIgnoreCase(((SalePerson) object).getLastName()) > 0)
                return -1;
            else
                return 1;

        }


    }

    // Accessor Methods
    public String getFirstName(){
        return this.firstName;
    }

    public String getLastName(){
        return this.lastName;
    }

    public int getTotalSales() {
        return this.totalSales;
    }

}
