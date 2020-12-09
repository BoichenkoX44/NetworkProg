package Pract_7;
import java.io.*;
import java.net.*;

public class MultiTCPServer {
    public static void main(String[] args) {
        ServerSocket servSocket = null;
        PrintStream ps = null;
        int port = 8071;
        try {
            System.out.println("Initialize...");
            servSocket = new ServerSocket(port);
            System.out.println("Waiting incomming connections");
            while (true){
                Socket s = servSocket.accept();
                System.out.println("["+s.getInetAddress().getHostName()+"] connected");
                ServerThread srvThread = new ServerThread(s);
                srvThread.start();
            }
        } catch (Exception e) {
            System.err.println(e);
        }
        finally{
            try {
                servSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
