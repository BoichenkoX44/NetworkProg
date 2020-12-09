package Pract_6;
import java.io.*;
import java.net.*;

public class SimpleClient {
    public static void main(String[] args) {
        Socket s = null;
        InputStreamReader isr = null;
        BufferedReader br = null;
        String serverAddr = "localhost";
        int port = 8030;
        try {
            s = new Socket(serverAddr,port);
            isr = new InputStreamReader(s.getInputStream());
            br = new BufferedReader(isr);
            String msg = br.readLine();
            System.out.println("Повідомлення: " + msg);
        } catch (IOException e) {
            e.printStackTrace();
        } finally{
            try {
                br.close();
                isr.close();
                s.close();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }
    }
}
