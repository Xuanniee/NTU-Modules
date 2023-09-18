public class Cuboid implements Shapes{
    private double cuboidLength;
    private double cuboidBreadth;
    private double cuboidHeight;

    public Cuboid(double cuboidBreadth, double cuboidHeight, double cuboidLength) {
        this.cuboidBreadth = cuboidBreadth;
        this.cuboidHeight = cuboidHeight;
        this.cuboidLength = cuboidLength;
    }

    // Setters & Getters
    public double getHeight() {
        return cuboidHeight;
    }

    public double getBreadth() {
        return cuboidBreadth;
    }

    public double getLength() {
        return cuboidLength;
    }

    public void setHeight(double cuboidHeight) {
        this.cuboidHeight = cuboidHeight;
    }

    public void setBreadth(double cuboidBreadth) {
        this.cuboidBreadth = cuboidBreadth;
    }

    public void setLength(double cuboidLength) {
        this.cuboidLength = cuboidLength;
    }

    public double calculateArea() {
        double set1 = 2 * (cuboidBreadth * cuboidHeight);
        double set2 = 2 * (cuboidBreadth * cuboidLength);
        double set3 = 2 * (cuboidHeight * cuboidLength);
        double area = set1 + set2 + set3;

        return area;
    }
    
}
