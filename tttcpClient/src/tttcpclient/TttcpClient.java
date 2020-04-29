package tttcpclient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class TttcpClient
{
    private static String indirizzo = "localhost";
    private static int porta = 2001;
    private static char[][] campo =new char[3][3];
    private static char segno;
    
    public static void stampaCampo()
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                System.out.print(" " + campo[i][j]);
                if(j != 2)
                    System.out.print(" |");
            }
            System.out.println();
        }
    }
    
    public static void inserisci(int cas)
    {
        switch(cas) {
            case 1:
                campo[0][0] = segno;
                break;
            case 2:
                campo[0][1] = segno;
                break;
            case 3:
                campo[0][2] = segno;
                break;
            case 4:
                campo[1][0] = segno;
                break;
            case 5:
                campo[1][1] = segno;
                break;
            case 6:
                campo[1][2] = segno;
                break;
            case 7:
                campo[2][0] = segno;
                break;
            case 8:
                campo[2][1] = segno;
                break;
            case 9:
                campo[2][2] = segno;
                break;
            default:
                break;
        }
    }
    
    public static void main(String[] args)
    {
        // Se c'è un indirizzo o una porta come argomento li uso
        if(args.length > 0)
        {
            indirizzo = args[0];
            if(args[1] != null && !args[1].equals(""))
                porta = Integer.parseInt(args[1]);
        }
        
        Scanner in =new Scanner(System.in);
        int casella;
        
        // Inizializzo il campo
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                campo[i][j] = ' ';
            }
        }
        
        try
        {
            Socket socket =new Socket(indirizzo, porta);
            BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter output =new PrintWriter(socket.getOutputStream(), true);
            
            segno = input.readLine().charAt(0);
            
            System.out.println(input.readLine());
//            System.out.println(input.readLine());
            do
            {
                casella = in.nextInt();
                if(casella > 9 || casella < 1)
                    System.out.println("Devi inserire un numero da 1 a 9");
            }
            while(casella > 9 || casella < 1);
            inserisci(casella);
            stampaCampo();
            
            socket.close();
        }
        catch(IOException e)
        {
            System.out.println("Oopsie " + e);
        }
    }
}
