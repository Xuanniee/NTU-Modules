public class Rectangle implements Shapes{
    // Attributes
    private double length;
    private double height;

    // Constructor
    public Rectangle(double length, double height){
        this.length = length;
        this.height = height;
    }

    // Methods
    @Override
    public double calculateArea() {
        double area = length * height;
        return area;
    }

    // Setter and Getter
    public double getLength() {
        return length;
    }

    public double getHeight() {
        return height;
    }

    public void setLength(double length) {
        this.length = length;
    }

    public void setHeight(double height) {
        this.height = height;
    }
    
}
