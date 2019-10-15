
// import java.swing.*;
import java.awt.*;
// import java.swing.Frame;
// import java.awt.Frame;
// import java.awt.envent.ActionEvent;
// import java.awt.event.ActionListener;
// import java.util.Stack;

// class MYException extends Exception {
//     public MYException(){
//         super();
//     }
//     public MYException(String message){
//         super(message);
//     }
// }

public class jisuanqi extends Frame {
    private TextField textField;
    private String input;
    private String operator;

    public jisuanqi(){
        input = "";
        operator = "";

        Panel panel = new Panel();
        textField = new TextField(30);
        textField.setEditable(false);
        // textField.setHorizontalAlignment(TextField.LEFT);
        // textField.setPerferredSize(new Dimension(200,30));

        this.add(textField,BorderLayout.NORTH);

        String[] name={"7","8","9","+","4","5","6","-","1","2","3","*","0","C","=","/"};
        panel.setLayout(new GridLayout(4,4,1,1));

        for (int i=0; i<name.length; i++){
            Button button = new Button(name[i]);
            // button.addActionListener(new MyActionListener());
            panel.add(button);

        }
        this.add(panel,BorderLayout.CENTER);

    }
    public static void main(String[] args){
        Frame f = new jisuanqi();
        f.setTitle(f.getClass().getSimpleName());
        // f.setDefaultCloseOperation(Frame.EXIT_ON_CLOSE);
        f.setBounds(400,200,500,300);
        f.setVisible(true);
    }
}

// public String jisuanqi(String input){

// }