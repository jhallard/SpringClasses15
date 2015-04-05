// $Id: miniserver.java,v 1.5 2013-08-13 20:18:57-07 - - $

//
// Mini server.
//    Usage:  miniserver hostport
// Accept a connection from a client and echo back any input.
//

import java.io.*;
import java.net.*;
import java.util.*;
import static java.lang.System.*;

class miniserver {

   static void quit (String format, Object... params) {
      err.printf (format, params);
      exit (1);
   }

   static String ident (options opts) {
      return String.format ("%s: port %d", opts.jarname,
                            opts.portnumber);
   }

   static String get_jarname() {
      String jarpath = getProperty ("java.class.path");
      int lastslash = jarpath.lastIndexOf ('/');
      if (lastslash < 0) return jarpath;
      return jarpath.substring (lastslash + 1);
   }

   static class options {
      final String jarname = get_jarname();
      int portnumber;
      options (String[] args) {
         try {
            if (args.length != 1) throw new NumberFormatException();
            portnumber = Integer.parseInt (args[0]);
         }catch (NumberFormatException exn) {
            quit ("Usage: %s portnumber%n", jarname);
         }
      }
   }



   public static void main (String[] args) {
      options opts = new options (args);
      try {
         ServerSocket socket = new ServerSocket (opts.portnumber);
         out.printf ("%s: waiting for client%n", ident (opts));
         Socket client = socket.accept();
         out.printf ("%s: socket.accept OK%n", ident (opts));
         Scanner client_in = new Scanner (client.getInputStream());
         PrintWriter client_out =
                     new PrintWriter (client.getOutputStream());
         for (int count = 1; client_in.hasNextLine(); ++count) {
            String line = client_in.nextLine();
                   out.printf ("Client sent: [%d]%s%n", count, line);
            client_out.printf ("Client sent: [%d]%s%n", count, line);
            client_out.flush();
         }
         socket.close();
         client.close();
         out.printf ("%s: finished%n", ident (opts));
      }catch (IOException exn) {
         quit ("%s: %s%n", ident (opts), exn);
      }catch (IllegalArgumentException exn) {
         quit ("%s: %s%n", ident (opts), exn);
      }
   }

}
