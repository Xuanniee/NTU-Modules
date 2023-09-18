public class Circle implements Shapes{
    private double radius;
    
    public Circle(double radius) {
        this.radius = radius;
    }

    public double getRadius() {
        return radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }
    
    public double calculateArea() {
        double area = Math.PI * radius * radius;
        return area;
    }
}
