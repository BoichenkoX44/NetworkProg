package Pract_7;
import java.io.*;
import java.net.*;

public class ServerThread extends Thread {
    private PrintStream psr = null;
    private BufferedReader isr = null;
    private InetAddress inetAddr = null;
    public ServerThread(Socket s) throws IOException {
        psr = new PrintStream(s.getOutputStream());
        isr = new BufferedReader(
                new InputStreamReader(s.getInputStream()));
        inetAddr = s.getInetAddress();
    }
    public void disconnect() {
        try {
            System.out.println(inetAddr.getHostName()+" disconnected");
            psr.close();
            isr.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        finally{
            this.interrupt();
        }
    }
    public void run (){
        int i=0;
        String str=null;
        try {
            while ((isr.readLine())!=null){
                if ("PING".equalsIgnoreCase(str))
                    psr.println("PONG "+ ++i);
                System.out.println("PING-PONG"+i+
                        " with"+inetAddr.getHostName());
            }
        } catch (IOException e) {
            System.out.println("Disconnect");
        }
        finally{
            disconnect();
        }
    }
}
