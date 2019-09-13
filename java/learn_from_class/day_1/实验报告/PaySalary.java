package learn_from_class.day_1.实验报告;

abstract class Employee {
    String name;
    float total;
    abstract void get_total();
    void setName(String name){
    this.name = name;
    }
    void Display(){
    get_total();
    System.out.println("姓名:"+name+"\n"+"应付工资:"+total);
    }
    };
    class Manager extends Employee{
    float base;
    void setBase(float base){
    this.base = base;
    }
    void get_total(){
    total = base;}
    };
    class Salesman extends Employee{
    float base;
    float extra;
    void setBase(float base){
    this.base = base;
    }
    void setExtra(float extra){
    this.extra = extra;
    }
    void get_total(){
    total = base + extra;
    }
    };
    class Worker extends Employee{
    float day_base;
    int time;
    void setDay_base(float day_base){
    this.day_base = day_base ;
    }
    void setTime(int time){
    this.time = time ;
    }
    void get_total(){
    total = day_base * time;
    }
    };
    public class PaySalary
    {
    public static void main(String args[]){
    Manager em1 = new Manager();
    em1.setName("经理");
    em1.setBase(2000);
    em1.Display();
    Salesman em2 = new Salesman();
    em2.setName("销售人员");
    em2.setBase(1000);
    em2.setExtra(500);
    em2.Display();
    Worker em3 = new Worker();em3.setName("一般工人");
    em3.setDay_base(50);
    em3.setTime(25);
    em3.Display();
    }
    };



