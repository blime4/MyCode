
public class Station extends Thread {
    public Station(String name){
        super(name);
    }
    static int ticker=1;
    static Object ob="aa";
    
    @Override
    public void run() {
        super.run();
        while(ticker<=20){
            synchronized(ob){
                if(ticker<=20){
                    System.out.println(getName()+"：卖出了第"+ticker+"张票");
                    ticker++;
                }else{
                    System.out.println("票卖完了");
                }
            }
            try {
                sleep(10);
            }catch(InterruptedException e){
                e.printStackTrace();
            }
        }
    }
    
    public static void main(String args[]){
        Station station1=new Station("窗口一");
        Station station2=new Station("窗口二");
        Station station3=new Station("窗口三");
        station1.start();
        station2.start();
        station3.start();
    }
}