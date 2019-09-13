import java.io.*;
public class FindNum{
    public static void main(String args[]){
        String s;
        double d;
        int i;
        boolean b = false;
        do{
            try{
                System.out.println("请输入一个浮点数：");
                BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
                s = br.readLine();
                i = s.indexOf('.');
                d = Double.parseDouble(s);
                System.out.println(d + "小数部分为："+(long)d);
                if(i==-1)
                System.out.println(d + "小数部分为：0.0");
                else
                System.out.println(d + "小数部分为："+Double.parseDouble(((s.charAt(0)=='-')?"-":"")+s.substring(i+1,s.length())));
                b = false;
            }
            catch(NumberFormatException nfe) {
                System.out.println("输入浮点数格式有误.\n");
                b = true;
            }
            catch(IOException ioe) {
                b = false;
            }
        }
        while(b);
    }
}