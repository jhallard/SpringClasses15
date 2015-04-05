// $Id: miniclient.java,v 1.8 2013-08-13 20:22:20-07 - - $

//
// Mini client.
//    Usage:  miniclient hostname hostport
// Reads stdin and copies to the port.  Then copies the answer
// back from the port to stdout.  Runs only in lock step with
// strict alternation for the server.
//

import java.io.*;
import java.net.*;
import java.util.*;
import static java.lang.System.*;

class miniclient {

   static void quit (String format, Object... params) {
      err.printf (format, params);
      exit (1);
   }

   static String ident (options opts) {
      return String.format ("%s: %s %d", opts.jarname,
                            opts.hostname, opts.portnumber);
   }

   static String get_jarname() {
      String jarpath = getProperty ("java.class.path");
      int lastslash = jarpath.lastIndexOf ('/');
      if (lastslash < 0) return jarpath;
      return jarpath.substring (lastslash + 1);
   }

   static class options {
      final String jarname = get_jarname();
      String hostname = "localhost";
      int portnumber;
      options (String[] args) {
         try {
            if (args.length < 1) throw new NumberFormatException ();
            portnumber = Integer.parseInt (args[0]);
            if (args.length > 1) hostname = args[1];
         }catch (NumberFormatException exn) {
            quit ("Usage: %s hostname portnumber%n", jarname);
         }
      }
   }


   public static void main (String[] args) {
      Scanner stdin = new Scanner (System.in);
      options opts = new options (args);
      try {
         Socket socket = new Socket (opts.hostname, opts.portnumber);
         out.printf ("%s: socket OK%n", ident (opts));
         Scanner serve_in = new Scanner (socket.getInputStream ());
         PrintWriter serve_out =
                     new PrintWriter (socket.getOutputStream ());
         for(;;) {
            out.printf ("%s: ", opts.jarname);
            if (! stdin.hasNextLine ()) break;
            String line = stdin.nextLine();
                  out.printf ("Stdin read: %s%n", line);
            serve_out.printf ("Stdin read: %s%n", line);
            serve_out.flush ();
            if (serve_in.hasNextLine ()) {
               out.printf ("Server said: %s%n", serve_in.nextLine ());
            }else {
               quit ("%s: no reply%n", ident (opts));
            }
         }
         socket.close ();
         out.printf ("%s: finished%n", ident (opts));
      }catch (IOException exn) {
         quit ("%s: %s%n", ident (opts), exn.getMessage());
      }catch (IllegalArgumentException exn) {
         quit ("%s: %s%n", ident (opts), exn.getMessage());
      }
   }

}

