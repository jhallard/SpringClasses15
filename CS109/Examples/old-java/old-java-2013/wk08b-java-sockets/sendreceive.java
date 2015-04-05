// $Id: sendreceive.java,v 1.13 2013-08-12 11:23:55-07 - - $

//
// Simple send receive example.  Start up two processes,
// receiver (server) which accepts messages and prints them,
// and a sender (client) which send messages.  Both loop
// indefinitely until killed.  
//    Usage: sendreceive port
// If the port is positive, server receiver.
// If the port is negative, client sender.
//

import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;
import static java.lang.System.*;

class sendreceive {

   static void server_receiver (int port) {
      try {
         ServerSocket server = new ServerSocket (port);
         print_server_socket ("server: server socket", server);
         Socket client = server.accept();
         print_socket ("server: client socket", client);
         Scanner sockin = new Scanner (client.getInputStream());
         for (;;) {
            String line = sockin.nextLine();
            out.printf ("server: %s%n", line);
         }
      }catch (IOException exn) {
         out.printf ("server: %s%n", exn);
      }
   }

   static void client_sender (int port, String hostname) {
      try {
         Socket server = new Socket (hostname, port);
         print_socket ("client: server socket", server);
         PrintWriter sockout =
                     new PrintWriter (server.getOutputStream());
         for (int count = 0; ; ++count) {
            String line = "Message " + count;
            out.printf ("client: %s%n", line);
            sockout.printf ("%s%n", line);
            sockout.flush();
            if (sockout.checkError()) {
               out.printf ("sender: error: %s%n", server);
               break;
            }
            try {
               Thread.sleep (1000);
            }catch (InterruptedException exn) {
               out.printf ("client: %s%n", exn);
            }
         }
      }catch (IOException exn) {
         out.printf ("client: %s%n", exn);
      }
   }


   static void print_server_socket (String ident, ServerSocket socket) {
      out.printf ("%s: %s%n", ident, socket);
      out.printf ("%s: %s%n", "InetAddress", socket.getInetAddress());
      out.printf ("%s: %s%n", "LocalPort", socket.getLocalPort());
   }

   static void print_socket (String ident, Socket socket) {
      out.printf ("%s: %s%n", ident, socket);
      out.printf ("%s: %s%n", "InetAddress", socket.getInetAddress());
      out.printf ("%s: %s%n", "LocalAddress", socket.getLocalAddress());
      out.printf ("%s: %s%n", "LocalPort", socket.getLocalPort());
      out.printf ("%s: %s%n", "Port", socket.getPort());
   }

   public static void main (String[] args) {
      String hostname = args.length >= 2 ? args[1] : "localhost";
      if (args.length < 1) {
         out.printf ("Usage: sendreceive port [hostname]%n");
         exit (1);
      }
      int port = Integer.parseInt (args[0]);
      if (port > 0) server_receiver (port);
               else client_sender (- port, hostname);
   }
}

