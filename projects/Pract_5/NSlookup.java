package Pract_5;
import java.net.*;
import java.util.Scanner;

public class NSlookup {
    public static void main(String[] args) {
        String hostName = null;
        System.out.println("Уведіть ім’я хосту");
        Scanner s = new Scanner(System.in);
        host = s.nextLine();
        try {
            InetAddress[] inetAddress = InetAddress.getAllByName(hostName);
            for (InetAddress ip : inetAddress){
                System.out.println(ip.getHostAddress());
            }
        } catch (UnknownHostException ex) {
            System.out.println(ex.getMessage());
        }
    }
}