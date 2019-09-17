import java.io.*;


public class Test{
    public static void main(String args[]){
        File files = new File("new22.txt");
        
        if(!files.exists()){
            try {
                if(files.createNewFile()){
                    System.out.println("created new file!");
                    System.out.println(files.canRead());
                    System.out.println(files.getAbsolutePath());
                }else{
                    System.out.println("create file failed!");
                }
            } catch (IOException e) {
                //TODO: handle exception
                e.printStackTrace();
            }
        }
        System.out.println("");
    }
}
