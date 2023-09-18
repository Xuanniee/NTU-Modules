public class SquarePyramid implements Shapes{
    private double pyramidLength;
    private double pyramidHeight;

    public SquarePyramid(double pyramidHeight, double pyramidLength) {
        this.pyramidLength = pyramidLength;
        this.pyramidHeight = pyramidHeight;
    }

    public double getHeight() {
        return pyramidHeight;
    }

    public double getBase() {
        return pyramidLength;
    }

    public void setHeight(double pyramidHeight) {
        this.pyramidHeight = pyramidHeight;
    }

    public void setBase(double pyramidLength) {
        this.pyramidLength = pyramidLength;
    }

    public double calculateArea() {
        double baseArea = pyramidLength * pyramidLength;
        // Get Lateral Height of Triangle Side
        double lateralHeight = Math.sqrt(Math.pow(pyramidLength / 2, 2) + Math.pow(pyramidHeight, 2));
        double triangleSideArea = 0.5 * pyramidLength * lateralHeight;
        double area = baseArea + (4 * triangleSideArea);
        return area;
    }
    
}
