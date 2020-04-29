package tttcp;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Tttcp
{
    private static int porta = 2001;
    
    public static void main(String[] args) throws IOException
    {
        if(args.length > 0)
        {
            porta = Integer.parseInt(args[0]);
        }
        
        ServerSocket SocketServer =new ServerSocket(porta);
        Socket socketG1, socketG2;
        
        System.out.println("Server avviato\nIn attesa di collegamento");
        socketG1 = SocketServer.accept();        
        socketG2 = SocketServer.accept();
        
        new Thread(new Partita(socketG1, socketG2)).start();
        System.out.println("Partita iniziata");
        
        SocketServer.close();
    }
    
}