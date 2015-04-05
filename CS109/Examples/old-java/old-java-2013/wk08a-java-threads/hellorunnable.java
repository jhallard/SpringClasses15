// $Id: hellorunnable.java,v 1.11 2013-08-12 19:24:37-07 - - $

//
// Hello World example using two threads.
// class greeter implements Runnable.
//

import static java.lang.System.*;
import static java.lang.String.*;

class hellorunnable {
   static long nanostart = nanoTime();

   static void print (String fmt, Object... args) { 
      Thread self = Thread.currentThread();
      double millisec = (nanoTime() - nanostart) / 1e6;
      String ident = format ("%10.3f: %s(%d): ",
                             millisec, self.getName(), self.getId());
      String message = format (fmt, args);
      out.println (ident + message);
      out.flush();
   }

   static class greeter implements Runnable {
      String threadname;
      long delay_msec;
      greeter (String _threadname, int _delay_msec) {
         threadname = _threadname;
         delay_msec = _delay_msec;
      }
      public void run() {
         Thread self = Thread.currentThread();
         self.setName (threadname);
         print ("starting");
         for (int count = 0; count < 10; ++count) {
            try {
               Thread.sleep (delay_msec);
            }catch (InterruptedException exn) {
               print ("interrupted: %s", exn.getMessage());
            }
            print ("slept %d msec, %dth time", delay_msec, count);
         }
         print ("finished");
      }
   }

   public static void main (String[] args) {
      print ("starting");
      Thread hello = new Thread (new greeter ("Hello", 500));
      Thread world = new Thread (new greeter ("World", 800));
      hello.start();
      world.start();
      print ("finished");
   }

}

//TEST// runprog -x hellorunnable.lis hellorunnable
//TEST// mkpspdf hellorunnable.ps hellorunnable.java* hellorunnable.lis

