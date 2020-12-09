package Pract_6;
import java.io.*;
import java.net.*;

public class SimpleServer {
    public static void main(String[] args) {
        Socket s = null;
        ServerSocket servSocket = null;
        PrintStream ps = null;
        int port = 8030;
        try {
            servSocket = new ServerSocket(port);
            s = servSocket.accept();
            System.out.print("Підключився клієнт [");
            System.out.println(s.getInetAddress()+"]");
            ps = new PrintStream(s.getOutputStream());
            ps.println("Привіт");
            ps.flush();
        } catch (IOException e) {
            e.printStackTrace();
        } finally{
            ps.close();
            try {
                s.close();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
            try {
                servSocket.close();
            } catch (IOException e2) {
                e2.printStackTrace();
            }
        }
    }
}
