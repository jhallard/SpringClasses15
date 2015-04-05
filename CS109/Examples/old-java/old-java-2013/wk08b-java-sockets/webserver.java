// $Id: webserver.java,v 1.27 2014-05-22 19:37:09-07 - - $

//
// Web server.  Responds with README.html when queried.
//

import java.io.*;
import java.net.*;
import java.util.*;
import static java.lang.String.*;
import static java.lang.System.*;

class webserver {
   static final String RCSID =
         "$Id: webserver.java,v 1.27 2014-05-22 19:37:09-07 - - $";
   static options opts = null;
   static String[] server_socket_info;

   static String ident() {
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

   static String timenow() {
      return format ("%1$tY %1$tb %1$td %1$ta %1$tT.%1$tL",
                     Calendar.getInstance());
   }


   static void sendline (PrintWriter writer, String line) {
      out.printf ("SENT: %s%n", line);
      writer.printf ("%s\n", line);
   }

   static void sendfile (Socket client, String filename)
                  throws IOException {
      if (filename.length() == 0) filename = "README";
      List<String> lines = new LinkedList<String>();
      PrintWriter writer = new PrintWriter (client.getOutputStream());
      lines.add ("<PRE>");
      lines.add ("Server RCS Id: " + RCSID);
      try {
         InetAddress addr = InetAddress.getLocalHost();
         lines.add ("From HostName: " + addr.getHostName());
         lines.add ("From HostAddress: " + addr.getHostAddress());
      }catch (UnknownHostException exn) {
         lines.add ("UnknownHostException: " + exn.getMessage());
      }
      for (String str: server_socket_info) lines.add (str);
      lines.add ("Client InetAddress: " + client.getInetAddress());
      lines.add ("Client LocalAddress: " + client.getLocalAddress());
      lines.add ("Client LocalPort: " + client.getLocalPort());
      lines.add ("Client Port: " + client.getPort());
      lines.add ("Page sent: " + timenow());
      lines.add ("");
      try {
         Scanner file = new Scanner (new File (filename));
         while (file.hasNextLine()) {
            String line = file.nextLine();
            lines.add (line);
         }
      }catch (IOException exn) {
         out.printf ("%s%n", exn);
         lines.add ("IOException: " + exn.getMessage());
      }
      int length = 0;
      for (String line: lines) length += line.length() + 1;
      sendline (writer, "HTTP/1.1 200 OK");
      sendline (writer, "Server: " + ident());
      sendline (writer, "Content-Type: text/html");
      sendline (writer, "Content-Length: " + length);
      sendline (writer, "");
      for (String line: lines) sendline (writer, line);
      writer.flush();
   }

   static List<String> getrequest (Socket client) throws IOException {
      List<String> lines = new LinkedList<String>();
      Scanner input = new Scanner (client.getInputStream());
      while (input.hasNextLine()) {
         String line = input.nextLine();
         out.printf ("RECD: %s%n", line);
         lines.add (line);
         if (line.length() == 0) break;
      }
      return lines;
   }


   static class worker implements Runnable {
      static int worker_count = 0;
      Socket client;
      int id = ++worker_count;
      worker (Socket client) {
         this.client = client;
      }
      public void run() {
         Thread.currentThread().setName ("Worker " + id);
         out.printf ("%s: worker %d: starting%n", ident(), id);
         try {
            List<String> request = getrequest (client);
            String filename = request.get(0).split("\\s+")[1];
            sendfile (client, filename.substring(1));
            client.close();
            out.printf ("%s: worker %d: finished%n", ident(), id);
         }catch (IOException exn) {
            quit ("%s: %s%n", ident(), exn);
         }
      }
   }

   static void quit (String format, Object... params) {
      err.printf (format, params);
      Set<Map.Entry<Thread, StackTraceElement[]>> entryset =
                  Thread.getAllStackTraces().entrySet();
      for (Map.Entry<Thread, StackTraceElement[]> entry: entryset) {
         Thread key = entry.getKey();
         StackTraceElement[] value = entry.getValue();
         err.printf ("Thread %d: %s%n", key.getId(), key.getName());
         for (StackTraceElement stack: value) {
            err.printf ("   %s%n", stack.toString());
         }
      }
      exit (1);
   }

   public static void main (String[] args) {
      opts = new options (args);
      try {
         ServerSocket socket = new ServerSocket (opts.portnumber);
         server_socket_info = new String[2];
         server_socket_info[0] = "Server InetAddress: "
                               + socket.getInetAddress();
         server_socket_info[1] = "Server LocalPort: "
                               + socket.getLocalPort();
         out.printf ("%s: waiting for client%n", ident());
         for (;;) {
            Socket client = socket.accept();
            out.printf ("%s: socket.accept OK%n", ident());
            Thread worker = new Thread (new worker (client));
            worker.start();
         }
      }catch (IOException exn) {
         quit ("%s: %s%n", ident(), exn);
      }catch (IllegalArgumentException exn) {
         quit ("%s: %s%n", ident(), exn);
      }
   }

}
