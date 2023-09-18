public class Cone implements Shapes{
    private double coneRadius;
    private double coneHeight;

    public Cone(double coneRadius, double coneHeight) {
        this.coneHeight = coneHeight;
        this.coneRadius = coneRadius;
    }

    // Setters and Getters
    public double getConeHeight() {
        return coneHeight;
    }

    public double getConeRadius() {
        return coneRadius;
    }

    public void setConeHeight(double coneHeight) {
        this.coneHeight = coneHeight;
    }

    public void setConeRadius(double coneRadius) {
        this.coneRadius = coneRadius;
    }

    public double calculateArea() {
        double baseArea = Math.PI * coneRadius * coneRadius;
        double lateralHeight = Math.sqrt(Math.pow(coneRadius, 2) + Math.pow(coneHeight, 2));
        double area = baseArea + (Math.PI * coneRadius * lateralHeight);
        return area;
    }
    
}
