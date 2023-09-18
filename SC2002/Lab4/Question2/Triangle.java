public class Triangle implements Shapes{
    private double height;
    private double base;

    public Triangle(double base, double height) {
        this.base = base;
        this.height = height;
    }

    public double getHeight() {
        return height;
    }

    public double getBase() {
        return base;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public void setBase(double base) {
        this.base = base;
    }

    public double calculateArea() {
        double area = 0.5 * base * height;
        return area;
    }
    
}
