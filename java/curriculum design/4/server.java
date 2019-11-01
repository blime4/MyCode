
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.ServerSocket;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class server implements Runnable {
    static List<Socket> socketList = new ArrayList<Socket>();
    static ServerSocket serverSocket = null;
    public server() {
        try {
            serverSocket = new ServerSocket(8888);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void main(String args[]){
        Scanner input = new Scanner(System.in);
        System.out.println("-------服务器-------");
        server t = new server();
        int count = 0;
        while(true){
            try {
                System.out.println("端口8888等待被连接....");
                socket = serverSocket.accept();
                count++;
                System.out.println("第"+count+"个用户已连接");
                socketList.add(socket);
            } catch (IOException e) {
                e.printStackTrace();
            }
            Print p = new Print(socket);
            Thread read = new Thread(t);
            Thread print = new Thread(p);
            read.start();
            print.start();
        }
    }
    @Override
    public void run(){
        try {
            Thread.sleep(1000);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            while(true){
                String receive = in.readLine();
                System.out.println(receive);
                for (int i = 0; i < socketList.size(); i++) {
                    Socket socket = socketList.get(i);
                    PrintWriter out = new PrintWriter(socket.getOutputStream());
                    if (socket!=this.socket) {
                        out.println(receive);
                    }else {
                        out.println("(你)"+receive);
                    }
                    out.flush();
                }
            }
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}

class Print implements Runnable{
    static List<Socket> socketList= new ArrayList<Socket>();
    Scanner input = new Scanner(System.in);
    public Print(Socket s){
        try {
            socketList.add(s);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    @Override
    public void run() {
        try {
            Thread.sleep(1000);
            while(true){
                String message = input.next();
                for (int i = 0; i < socketList.size(); i++) {
                    Socket socket = socketList.get(i);
                    PrintWriter out = new PrintWriter(socket.getOutputStream());
                    out.println("服务端说："+message);
                    out.flush();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}