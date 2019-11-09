import java.net.*;
import java.io.*;

public class TCPSingleUserClient {
    public static void main(String args[]) throws IOException{
        InetAddress addr = InetAddress.getByName("localhost:8080");
        System.out.println("addr: " + addr);
        Socket socket = new Socket(addr,TCPSingleUserServer.PORT);
        try {
            System.out.println("socket: " + socket);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())),true);
            for (int i = 0; i <10;i++){
                out.println("Sending line: " + i + "...");
                String str  = in.readLine();
                System.out.println(str);
            }
            out.println("END");
        }
        finally {
            System.out.println("closing...");
            socket.close();
        }
    }
}