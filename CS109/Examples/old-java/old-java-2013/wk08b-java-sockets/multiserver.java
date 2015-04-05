// $Id: multiserver.java,v 1.4 2012-05-29 20:54:57-07 - - $

//
// Multi server.  Usage:  java multiserver hostport.  Accept a
// connection from many client and echo back any input.  Each
// client is assigned a worker thread.

//

import java.io.*;
import java.net.*;
import java.util.*;
import static java.lang.System.*;

class multiserver {

   static void quit (String format, Object... params) {
      err.printf (format, params);
      exit (1);
   }

   static String ident (options opts) {
      return String.format ("%s: port %d", opts.progname,
                            opts.portnumber);
   }

   static String get_jarname() {
      String jarpath = getProperty ("java.class.path");
      int lastslash = jarpath.lastIndexOf ('/');
      if (lastslash < 0) return jarpath;
      return jarpath.substring (lastslash + 1);
   }

   static class options {
      final String progname = get_jarname();
      int portnumber;
      options (String[] args) {
         try {
            if (args.length != 1) throw new NumberFormatException();
            portnumber = Integer.parseInt (args[0]);
         }catch (NumberFormatException exn) {
            quit ("Usage: %s portnumber%n", progname);
         }
      }
   }


   static class worker implements Runnable {
      static int worker_count = 0;
      options opts;
      Socket client;
      int worker_id = ++worker_count;
      worker (options opts, Socket client) {
         this.opts = opts;
         this.client = client;
      }
      public void run() {
         out.printf ("%s: worker %d: starting%n",
                     ident (opts), worker_id);
         try {
            Scanner client_in = new Scanner (client.getInputStream());
            PrintWriter client_out =
                        new PrintWriter (client.getOutputStream());
            for (int count = 1; client_in.hasNextLine(); ++count) {
               if (client.isInputShutdown()
                || client.isOutputShutdown()) break;
               String line = client_in.nextLine();
               out.printf ("%d[%d]%s%n", worker_id, count, line);
               client_out.printf ("%d[%d]%s%n", worker_id, count, line);
               client_out.flush();
            }
            client.close();
            out.printf ("%s: worker %d: finished%n",
                        ident (opts), worker_id);
         }catch (IOException exn) {
            quit ("%s: %s%n", ident (opts), exn);
         }
      }
   }

   public static void main (String[] args) {
      options opts = new options (args);
      try {
         ServerSocket socket = new ServerSocket (opts.portnumber);
         out.printf ("%s: waiting for client%n", ident (opts));
         for (;;) {
            Socket client = socket.accept();
            out.printf ("%s: socket.accept OK%n", ident (opts));
            Thread worker = new Thread (new worker (opts, client));
            worker.start();
         }
      }catch (IOException exn) {
         quit ("%s: %s%n", ident (opts), exn);
      }catch (IllegalArgumentException exn) {
         quit ("%s: %s%n", ident (opts), exn);
      }
   }

}
