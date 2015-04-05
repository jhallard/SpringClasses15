// $Id: eightthreads.java,v 1.14 2012-11-30 12:23:23-08 - - $

//
// Create 8 threads which loop continuously.
//

import static java.lang.System.*;

class eightthreads {

   static class printmsg implements Runnable {
      String threadname;
      long loops;
      long result = 0;
      printmsg (String threadname_, long loops_) {
         threadname = threadname_;
         loops = loops_;
      }
      public void run() {
         Thread self = Thread.currentThread();
         self.setName (threadname);
         out.printf ("%s: starting%n", threadname);
         for (long count = 0; count < loops; ++count) {
            ++result;
         }
         out.printf ("%s: finished: %d%n", threadname, result);
      }
   }

   static String[] names = {"Hello", "World", "Foo", "Bar", "Baz",
                            "Penguin", "Dæmon", "Racoon"};

   public static void main (String[] args) {
      Thread self = Thread.currentThread();
      out.printf ("%s: starting%n", self.getName());
      for (int index = 0; index < names.length; ++index) {
         Thread thread = new Thread (new printmsg (names[index],
                         index * 1L<<32));
         thread.start();
      }
      out.printf ("%s: finished%n", self.getName());
   }
}
