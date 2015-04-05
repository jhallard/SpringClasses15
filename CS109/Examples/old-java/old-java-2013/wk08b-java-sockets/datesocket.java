// $Id: datesocket.java,v 1.12 2013-03-19 15:23:29-07 - - $

//
// Date client/server application.
//
// Date server waits for client connection and responds with
// current date.
//
// Client connects to server and prints information received.
//

import java.io.*;
import java.net.*;
import java.util.*;
import static java.lang.System.*;

class datesocket {

   static void print_socket (String label, Socket socket) {
      out.printf ("%s: %s(%s) %s(%s)%n", label,
                  socket.getInetAddress(), socket.getLocalAddress(),
                  socket.getPort(), socket.getLocalPort());
   }

   static void client (int port) throws IOException {
      Socket socket = new Socket ("localhost", port);
      print_socket ("client", socket);
      InputStream instream = socket.getInputStream();
      byte[] buffer = new byte[4096];
      int bytes = instream.read (buffer);
      out.printf ("%s%n", new String (buffer, 0, bytes, "US-ASCII"));
   }

   static void server (int port) throws IOException {
      ServerSocket serversocket = new ServerSocket (port);
      out.printf ("server: %s %s%n", serversocket.getInetAddress(),
                  serversocket.getLocalPort());
      for (;;) {
         Socket client = serversocket.accept();
         print_socket ("server client", client);
         OutputStream outstream = client.getOutputStream();
         String date = new Date().toString() + "\n";
         out.printf ("date: %s%n", date);
         outstream.write (date.getBytes("US-ASCII"));
         outstream.flush();
         client.close();
      }
   }

   public static void main (String[] args) throws IOException {
      int port = Integer.parseInt (args[0]);
      if (port < 0) server (-port);
               else client (port);
   }

}
