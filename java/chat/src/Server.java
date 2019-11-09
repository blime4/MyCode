

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * 服务器线程类，实现Runnable接口
 *
 * @author XerCis
 * @version 1.0
 */
class ServerThread implements Runnable {

    private Socket s; //套接字
    private BufferedReader br; //字符输入流






    /**
     * 构造函数
     *
     * @param s Socket
     * @throws IOException
     * @since 1.0
     */
    public ServerThread(Socket s) throws IOException {
        this.s = s;
        br = new BufferedReader(new InputStreamReader(s.getInputStream()));
    }





    /**
     * 从客户端接收信息
     *
     * @return 从客户端接收到的信息
     * @since 1.0
     */
    private String readFromClient() {
        try {
            return br.readLine();
        } catch (IOException e) {
            Server.socketList.remove(s);
        }
        return null;
    }




    /**
     * 线程不断从客户端接收信息并转发
     *
     * @since 1.0
     */
    public void run() {
        String content = null; //从客户端接收信息
        while((content = readFromClient()) != null) //不为空的时候转发给所有客户端
        {
            for(Socket s:Server.socketList) {
                try {
                    PrintStream ps; //打印流（字节输出流）
                    ps = new PrintStream(s.getOutputStream()); //用服务器Socket的OutputStream封装
                    ps.println(content);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}


/**
 * 服务器类
 *
 * @author XerCis
 * @version 1.0
 */
public class Server {

    public static List<Socket> socketList = Collections.synchronizedList(new ArrayList<>());//保存所有Socket，线程安全





    /**
     * main方法，启动服务器
     *
     * @author XerCis
     * @version 1.0
     */
    @SuppressWarnings("resource")
    public static void main(String[] args) {
        try {
            ServerSocket serversocket = new ServerSocket(6666);//指定端口为6666
            System.out.println("服务器启动");
            while(true) {
                Socket socket = serversocket.accept();//接受客户端
                socketList.add(socket);//添加进客户端List中
                new Thread(new ServerThread(socket)).start();//启动服务器线程
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}