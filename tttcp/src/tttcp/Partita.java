package tttcp;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Partita implements Runnable
{
    Socket socketG1, socketG2;
    PrintWriter stampaG1, stampaG2;
    BufferedReader inputG1, inputG2;
    
    public Partita(Socket g1, Socket g2) throws IOException
    {
        this.socketG1 = g1;
        this.socketG2 = g2;
        
        inputG1 =new BufferedReader(new InputStreamReader(socketG1.getInputStream()));
        stampaG1 =new PrintWriter(socketG1.getOutputStream(), true);
        
        inputG2 =new BufferedReader(new InputStreamReader(socketG2.getInputStream()));
        stampaG2 =new PrintWriter(socketG2.getOutputStream(), true);
    }
    
    @Override
    public void run()
    {
        try
        {
            stampaG1.println("X");
            stampaG2.println('O');
            
            String msg = "Partita iniziata!";
            stampaG1.println("Un giocatore si e' connesso. " + msg);
            stampaG2.println(msg);
            
            stampaG1.print("Inserisci il numero della casella: ");            
            System.out.println(inputG1.readLine());
        }
        catch(IOException e)
        {
            System.out.println("Oopsie " + e);
        }
    }
    
}
