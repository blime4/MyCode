import java.util.Scanner;
public class guess{
    static int count;
    public static void main(String args[]){
        int n = 0;
        Scanner s = new Scanner(System.in);
        // System.out.println(count);
        while(count >= 0){
            int number = (int)(Math.random()*99+1);
            for (count=0;n!=number;count++){
                n=s.nextInt();
                if(n>number) System.out.println("输入过大");
                else if(n<number) System.out.println("输入过小");
                else System.out.println("猜对了");
            }
            System.out.println("你猜了 ："+count+" 次");
            System.out.println("输入1重新开始，输入-1退出");
            count=s.nextInt();
        }
    }
}