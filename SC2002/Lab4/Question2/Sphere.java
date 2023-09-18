public class Sphere implements Shapes {
    private double sphereRadius;

    public Sphere(double sphereRadius) {
        this.sphereRadius = sphereRadius;
    }

    public double getRadius() {
        return sphereRadius;
    }

    public void setRadius(double sphereRadius) {
        this.sphereRadius = sphereRadius;
    }

    @Override
    public double calculateArea() {
        double area = 4 * Math.PI * sphereRadius * sphereRadius;
        return area;
    }
}