import java.awt.*;
import javax.swing.*;

public class login extends JFrame{

    private static final long serialVersionUID = 1L;
    JPanel loginPanel, passwordPanel, buttonPanel;
    JButton loginButton,cancelButton;
    JLabel loginLabel,passwordLabel;
    JTextField loginTextField;
    JPasswordField passwordField;

    public static void main(String args[]){
        login log = new login();
    }
    public login() {
        loginPanel = new JPanel();
        passwordPanel = new JPanel();
        buttonPanel = new JPanel();

        loginLabel = new JLabel("Username:");
        passwordLabel = new JLabel("Password:");

        loginButton = new JButton("Login");
        cancelButton = new JButton("Cancel");

        loginTextField = new JTextField(10);
        passwordField = new JPasswordField(10);

        this.setLayout(new GridLayout(3,1));

        loginPanel.add(loginLabel);
        loginPanel.add(loginTextField);

        passwordPanel.add(passwordLabel);
        passwordPanel.add(passwordField);

        buttonPanel.add(loginButton);
        buttonPanel.add(cancelButton);

        this.add(loginPanel);
        this.add(passwordPanel);
        this.add(buttonPanel);

        this.setSize(300,200);
        this.setTitle("Login");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
    }
}