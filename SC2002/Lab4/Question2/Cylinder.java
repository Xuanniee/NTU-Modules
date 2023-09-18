public class Cylinder implements Shapes{
    private double cylinderRadius;
    private double cylinderLength;

    public Cylinder(double cylinderLength, double cylinderRadius) {
        this.cylinderLength = cylinderLength;
        this.cylinderRadius = cylinderRadius;
    }

    // Setters & Getters
    public double getCylinderLength() {
        return cylinderLength;
    }

    public double getCylinderRadius() {
        return cylinderRadius;
    }

    public void setCylinderLength(double cylinderLength) {
        this.cylinderLength = cylinderLength;
    }

    public void setCylinderRadius(double cylinderRadius) {
        this.cylinderRadius = cylinderRadius;
    }

    public double calculateArea() {
        double cirArea = Math.PI * cylinderRadius * cylinderRadius * 2;
        double curvedArea = 2 * Math.PI * cylinderRadius * cylinderLength;
        double area = cirArea + curvedArea;
        return area;
    }
    
}
