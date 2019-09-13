package learn_from_class.day_1.临时作业;

class circle {
    private double r;
    public circle(double r) {
        this.r = r;
    }
    public double getr(){
        return r;
    }
    public double area(){
        return 0.5*3.14159*r*r;
    }
    public double circlelength(){
        return 2*3.14159*r;
    }
}

public class CircleDemo {
    public static void main(String args[]){
        circle m1 = new circle(5.3);
        System.out.println("半径为"+m1.getr());
        System.out.println("面积为"+m1.area());
        System.out.println("周长为"+m1.circlelength());
    }
}