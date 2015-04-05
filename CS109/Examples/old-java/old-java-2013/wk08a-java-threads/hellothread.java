// $Id: hellothread.java,v 1.14 2012-05-24 15:36:26-07 - - $

//
// Hello World example using two threads.
// class greeter extends Thread.
//

import static java.lang.System.*;
import static java.lang.String.*;

class hellothread {
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

   static class greeter extends Thread {
      long delay_msec;
      greeter (String threadname, int delay) {
         super (threadname);
         delay_msec = delay;
      }
      public void run() {
         print ("starting");
         for (int count = 0; count < 10; ++count) {
            try {
               sleep (delay_msec);
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
      greeter hello = new greeter ("Hello", 500);
      greeter world = new greeter ("World", 800);
      hello.start();
      world.start();
      print ("finished");
   }

}

//TEST// runprog -x hellothread.lis hellothread
//TEST// mkpspdf hellothread.ps hellothread.java* hellothread.lis

