// $Id: poolserver.java,v 1.5 2009-02-27 18:25:51-08 - - $

//
// Pool server.  Usage:  java multiserver hostport.  Accept a
// connection from many client and echo back any input.  Each
// client is assigned a worker thread:w
//
// java.util.concurrent.Executors is used to keep cache old
// threads and reuse them so new threads don't need to be started.
//

import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;
import static java.lang.System.*;

class poolserver {

   public static void main (String[] args) {
      options opts = new options (args);
      Executor pool = Executors.newCachedThreadPool ();
      try {
         ServerSocket socket = new ServerSocket (opts.portnumber);
         out.printf ("%s: waiting for client%n", ident (opts));
         for (;;) {
            Socket client = socket.accept ();
            out.printf ("%s: socket.accept OK%n", ident (opts));
            pool.execute (new worker (opts, client));
         }
      }catch (IOException exn) {
         quit ("%s: %s%n", ident (opts), exn);
      }catch (IllegalArgumentException exn) {
         quit ("%s: %s%n", ident (opts), exn);
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
      public void run () {
         out.printf ("%s: worker %d: starting%n",
                     ident (opts), worker_id);
         try {
            Scanner client_in = new Scanner (client.getInputStream ());
            PrintWriter client_out =
                        new PrintWriter (client.getOutputStream ());
            for (int count = 1; client_in.hasNextLine (); ++count) {
               String line = client_in.nextLine ();
               client_out.printf ("%d[%d]%s%n", worker_id, count, line);
               client_out.flush ();
            }
            client.close ();
            out.printf ("%s: worker %d: finished%n",
                        ident (opts), worker_id);
         }catch (IOException exn) {
            quit ("%s: %s%n", ident (opts), exn);
         }
      }
   }

   static void quit (String format, Object... params) {
      err.printf (format, params);
      exit (1);
   }

   static String ident (options opts) {
      return String.format ("%s: port %d", opts.progname,
                            opts.portnumber);
   }

   static class options {
      final String progname = "miniclient";
      int portnumber;
      options (String[] args) {
         try {
            if (args.length != 1) throw new NumberFormatException ();
            portnumber = Integer.parseInt (args[0]);
         }catch (NumberFormatException exn) {
            quit ("Usage: %s hostname portnumber%n", progname);
         }
      }
   }

}
