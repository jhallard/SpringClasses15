// $Id: consumer.java,v 1.1 2009-02-26 20:47:05-08 - - $

import static java.lang.System.*;

class consumer <item_t> implements Runnable {

   private buffer <item_t> inbuf;
   private String name;
   long delay_msec;

   consumer (buffer inbuf, String name, long delay_msec) {
      this.inbuf = inbuf;
      this.name = name;
      this.delay_msec = delay_msec;
   }

   public void run () {
      stamp.printf ("consumer %s starting%n", name);
      for (;;) {
         item_t item = inbuf.get ();
         if (item == null) break;
         try {
            Thread.currentThread ().sleep (delay_msec);
         }catch (InterruptedException exn) {
            stamp.printf ("consumer %s: %s%n", name, exn);
         }
         stamp.printf ("consumer %s: get() = \"%s\"%n", name, item);
      }
      stamp.printf ("consumer %s finished%n", name);
   }
   
}

