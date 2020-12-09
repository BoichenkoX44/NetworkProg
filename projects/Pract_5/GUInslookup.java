package Pract_5;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.InetAddress;
import java.net.UnknownHostException;

public class GUInslookup {
    private static String host;
    public static void main(String[] args) {
        JFrame frame = new JFrame("NSlookup");
        frame.setSize(300, 400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JPanel panel = new JPanel();
        frame.add(panel);
        JLabel websiteLabel = new JLabel("Website");
        JTextField hostField = new JTextField(20);
        JButton button = new JButton("Enter");
        JTextArea textArea = new JTextArea();
        panel.setLayout(null);
        websiteLabel.setBounds(10, 20, 50, 25);
        panel.add(websiteLabel);
        hostField.setBounds(60, 20, 165, 25);
        panel.add(hostField);
        button.setBounds(10, 60, 80, 25);
        panel.add(button);
        textArea.setBounds(0, 110, 500, 390);
        textArea.setEditable(false);
        panel.add(textArea);
        frame.setVisible(true);
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                host = hostField.getText();
                textArea.append("Scanning host: " + host + "\n");
                try {
                    InetAddress[] inetAddress = InetAddress.getAllByName(host);
                    for (InetAddress ip : inetAddress) {
                        textArea.append(IP.getHostAddress() + "\n");
                    }
                } catch (UnknownHostException ex) {
                    textArea.append(ex.getMessage() + "\n");
                }
            }
        });
    }
}
