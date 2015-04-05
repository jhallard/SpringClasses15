// $Id: stacktrace.java,v 1.29 2009-03-03 17:10:50-08 - - $

//
// Prints a stack trace for a particular thread.
//

import java.io.*;
import java.util.*;
import static java.lang.System.*;

class stacktrace {

   synchronized static void printthread () {
      Thread current = Thread.currentThread ();
      err.printf ("\tin thread %s, id %d, priority %d, state %s%n",
                  current.getName (), current.getId (),
                  current.getPriority (), current.getState ());
      err.printf ("\tin threadgroup %s%n", current.getThreadGroup ());
   }

   synchronized static void printthreadstack () {
      Thread current = Thread.currentThread ();
      for (StackTraceElement trace: current.getStackTrace ()) {
         err.printf ("\tat %s%n", trace);
      }
   }

   synchronized static void printtrace (String format, Object... args) {
      err.printf (format, args);
      printthreadstack ();
      printthread ();
      err.flush ();
   }

   synchronized static void printtrace (Throwable error) {
      error.printStackTrace ();
      err.flush ();
   }

   static void badfile () throws IOException {
      Scanner scan = new Scanner (new File ("/no/such/file"));
   }

   static class crash implements Runnable {
      public void run () {
         try {
            badfile ();
         }catch (IOException error) {
            printtrace (error);
         }
      }
   }

   public static void main (String[] args) {
      new Thread (new crash (), "Crash.1").start ();
      new Thread (new crash (), "Crash.2").start ();
      try {
         badfile ();
      }catch (IOException error) {
         printtrace (error);
      }
      printtrace ("FOOBAR ******** %g ********%n", 3.14);
   }

}
