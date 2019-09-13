import java.io.*;
public class ReadFile{
    public static void main(String[] args)throws IOException{
        BufferedReader br = new BufferedReader(new FileReader("ReadFile.java"));
        String s = br.readLine();
        while (s!=null){
            System.out.println(s);
            s = br.readLine();
        }
        br.close();
    }
}