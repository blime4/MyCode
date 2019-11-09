
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import org.jb2011.lnf.beautyeye.BeautyEyeLNFHelper;

import java.awt.Color;
import java.awt.EventQueue;

import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.UIManager;
import javax.swing.JButton;
import java.awt.Font;
import java.awt.Toolkit;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

/**
 * 客户端界面类
 *
 * @author XerCis
 * @version 1.0
 */
public class ClinetFrame extends JFrame {

    private JTextArea input; //发送框
    private JTextArea output; //显示框
    private String name; //用户名
    private PrintStream ps; //输出流


    /**
     * 客户端线程类（内部类）
     *
     * @author XerCis
     * @version 1.0
     */
    class ClientThread implements Runnable {

        BufferedReader br = null;

        ClientThread(Socket s) throws IOException {
            br = new BufferedReader(new InputStreamReader(s.getInputStream()));
        }

        public void run() {
            try {
                String content = null;
                while((content = br.readLine())!=null) {
                    output.append(content+"\n");
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }





    /**
     * 发送信息
     *
     * @since 1.0
     */
    private void sendMessage(){
        Date now = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
        String time = sdf.format(now);//当前时间

        String message = input.getText();
        if(message.isEmpty())
            return;
        message = name+"("+time+")\n"+message;
        ps.println(message);
        input.setText("");//发送完清空
    }


    private ClinetFrame() throws UnknownHostException, IOException {
        Random rand = new Random();
        int randNum = rand.nextInt(17);
        name = "用户" + String.valueOf(randNum);
        this.setVisible(true);
        setTitle(name); //设置窗口名
        setResizable(false); //不可放大
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//关闭后退出
        setIconImage(Toolkit.getDefaultToolkit().getImage("img\\logo.png")); //设置图标

        Socket s = new Socket("127.0.0.1",6666); //获取套接字
        new Thread(new ClientThread(s)).start(); //启动客户端线程
        ps = new PrintStream(s.getOutputStream());
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        /* 容器  */
        setBounds(100, 100, 599, 629);
        //组件容器
        JPanel contentPaneeee = new JPanel();
        contentPaneeee.setBackground(new Color(0, 153, 204));
        contentPaneeee.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPaneeee);
        contentPaneeee.setLayout(null);

        /* 显示框的滚动条 */
        JScrollPane scrollPane = new JScrollPane();
        scrollPane.setBounds(23, 63, 422, 290);
        contentPaneeee.add(scrollPane);

        /* 显示框 */
        String text = "XerCis\nNorthwest A&F University\nShaanxi,Yangling,712100\nTel:13201405250\nE-mail:Jiankun_Luo@qq.com\n----------------------------------------\n";
        output = new JTextArea(text);
        scrollPane.setViewportView(output);//将滚动条附加到显示框中
        output.setFont(new Font("微软雅黑", Font.PLAIN, 18));
        output.setEditable(false);//不可编辑
        output.setLineWrap(true);//自动换行
        output.setWrapStyleWord(true);//断行不断字
        output.setCaretPosition(output.getText().length());//自动换行且滚动到最新
        output.getDocument().addDocumentListener(new DocumentListener(){
            public void changedUpdate(DocumentEvent e) {
                output.setCaretPosition(output.getText().length());//自动换行且滚动到最新
            }
            public void insertUpdate(DocumentEvent e) {
                output.setCaretPosition(output.getText().length());//自动换行且滚动到最新
            }
            public void removeUpdate(DocumentEvent e) {
                output.setCaretPosition(output.getText().length());//自动换行且滚动到最新
            }
        });

        /* 头像 */
        JLabel me = new JLabel("");
        me.setIcon(new ImageIcon("img\\head\\"+randNum+".png"));
        me.setBounds(450, 385, 100, 100);
        contentPaneeee.add(me);

        /* 发送按钮 */
        JButton send = new JButton("\u53D1\u9001(Enter)");
        send.setFont(new Font("微软雅黑", Font.PLAIN, 12));
        send.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent arg0) {
                sendMessage();
            }
        });
        send.setBounds(334, 506, 111, 23);
        contentPaneeee.add(send);

        /* 发送框的滚动条 */
        JScrollPane scrollPane_1 = new JScrollPane();
        scrollPane_1.setBounds(23, 385, 422, 100);
        contentPaneeee.add(scrollPane_1);

        /* 发送框 */
        input = new JTextArea();
        input.addKeyListener(new KeyAdapter() {
            public void keyReleased(KeyEvent arg0) {
                if(arg0.getKeyCode() == KeyEvent.VK_ENTER) {
                    if(input.getText().equals("\n")) {
                        input.setText("");
                        return;
                    }
                    sendMessage(); //按回车发送
                }
            }
        });
        scrollPane_1.setViewportView(input); //将滚动条附加到发送框中
        input.setFont(new Font("微软雅黑", Font.PLAIN, 18));
        input.setLineWrap(true);
        input.setWrapStyleWord(true);

        /* 背景 */
        JLabel background = new JLabel("");
        background.setBackground(new Color(214, 217, 223));
        background.setIcon(new ImageIcon("img\\background.png"));
        background.setBounds(0, 0, 550, 550);
        contentPaneeee.add(background);
    }








    /**
     * main方法，启动客户端
     *
     * @since 1.0
     */
    public static void main(String[] args) throws Exception {
        /*设置成BeautyEye风格*/
        try {
            System.setProperty("sun.java2d.noddraw", "true");//解决切换中文输入法导致白屏
            BeautyEyeLNFHelper.frameBorderStyle = BeautyEyeLNFHelper.FrameBorderStyle.translucencyAppleLike;//强立体透明
            org.jb2011.lnf.beautyeye.BeautyEyeLNFHelper.launchBeautyEyeLNF();//加载BeautyEye风格，需引入包beautyeye_lnf.jar
            UIManager.put("RootPane.setupButtonVisible", false);//隐藏“设置”按钮
            String[] DEFAULT_FONT  = new String[]{"Table.font","TableHeader.font","CheckBox.font","Tree.font","Viewport.font","ProgressBar.font","RadioButtonMenuItem.font","ToolBar.font","ColorChooser.font","ToggleButton.font","Panel.font","TextArea.font","Menu.font","TableHeader.font","TextField.font","OptionPane.font","MenuBar.font","Button.font","Label.font","PasswordField.font","ScrollPane.font","MenuItem.font","ToolTip.font","List.font","EditorPane.font","Table.font","TabbedPane.font","RadioButton.font","CheckBoxMenuItem.font","TextPane.font","PopupMenu.font","TitledBorder.font","ComboBox.font"};
            for (String s : DEFAULT_FONT) UIManager.put(s, new Font("微软雅黑", Font.PLAIN, 14));//设置默认字体解决组件发虚问题
        } catch (Exception e) {
            e.printStackTrace();
        }

        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    ClinetFrame client = new ClinetFrame();
                    client.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
}
