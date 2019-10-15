abstract class Employee{
    private String name;
    public Employee(String name){
        this.name = name;
    }
    public String getName() {
        return name;
    }
    public abstract double computeSalary();
}

class Manager extends Employee{
    double monthSalary;
    public Manager(String name,double monthSalary){
        super(name);
        this.monthSalary = monthSalary;
    }
    public double computeSalary() {
        return monthSalary;
    }
}

class Salesman extends Employee{
    double baseSalary;
    int quantity;
    double commission;
    public Salesman(String name,double baseSalary,int quantity,double commission){
        super(name);
        this.baseSalary = baseSalary;
        this.quantity = quantity;
        this.commission = commission;
    }
    public double computeSalary() {
        return baseSalary+quantity*commission;
    }
}

class Worker extends Employee{
    int days;
    double dailySalary;
    public Worker(String name,int days,double dailySalary){
        super(name);
        this.days = days;
        this.dailySalary = dailySalary;
    }
    public double computeSalary() {
        return dailySalary*days;
    }
}

public class pay_salary{
    public static void main(String args[]){
        Manager m = new Manager("小明",19876);
        Salesman s = new Salesman("小红",5432,10,12);
        Worker w = new Worker("小兰",30,123);
        System.out.println("Manager:    "+m.getName()+" "+m.computeSalary()+"$");
        System.out.println("Salesman:   "+s.getName()+" "+s.computeSalary()+"$");
        System.out.println("Worker:     "+w.getName()+" "+w.computeSalary()+"$");
    }
}