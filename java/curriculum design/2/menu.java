import java.awt.*;
public class menu{
    public static void main(String args[]){
        Frame f = new Frame("Menu");
        MenuBar m = new MenuBar();
        f.setMenuBar(m);
        Menu m1 = new Menu("File");
        Menu m2 = new Menu("Format");
        Menu m3 = new Menu("help");
        m.add(m1);
        m.add(m2);
        m.setHelpMenu(m3);
        MenuItem m21 = new MenuItem("中文");
        Menu m22 = new Menu("进制");
        m2.add(m21);
        m2.add(m22);
        MenuItem m221 = new MenuItem("二进制");
        MenuItem m222 = new MenuItem("八进制");
        MenuItem m223 = new MenuItem("十进制");
        m22.add(m221);
        m22.add(m222);
        m22.add(m223);

        f.pack();
        f.setVisible(true);
    }
}