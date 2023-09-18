public class Square implements Shapes{
    private double sideLength;

    public Square(double sideLength){
        this.sideLength = sideLength;
    }

    @Override
    public double calculateArea() {
        double area = sideLength * sideLength;
        return area;
    }

    // Setter & Getter
    public double getSideLength() {
        return sideLength;
    }

    public void setSideLength(double sideLength) {
        this.sideLength = sideLength;
    }
}