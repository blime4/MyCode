import java.io.*;
import java.sql.BatchUpdateException;


public class copyFile{
    public static void main(String[] args){
        String src="D:\\mine\\Mycode\\java\\class_work4\\src\\copyFile.java";
        String dst="D:\\mine\\Mycode\\java\\class_work4\\src\\copy_copy.java";
        long startTime = System.currentTimeMillis();
        copy(src,dst);
        long endTime = System.currentTimeMillis();
        System.out.println("Spend time:"+(endTime-startTime));
    }
}

