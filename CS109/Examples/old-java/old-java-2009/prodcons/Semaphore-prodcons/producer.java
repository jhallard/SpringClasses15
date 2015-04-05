// $Id: producer.java,v 1.1 2009-02-26 20:48:49-08 - - $

import static java.lang.System.*;

class producer <item_t> implements Runnable {

   private buffer outbuf;
   private String name;
   private long delay_msec;
   private item_t[] data;

   producer (buffer outbuf, String name, long delay, item_t[] data) {
      this.outbuf = outbuf;
      this.name = name;
      this.delay_msec = delay;
      this.data = data;
   }

   public void run () {
      stamp.printf ("producer %s starting%n", name);
      for (item_t datum: data) {
         try {
            Thread.currentThread ().sleep (delay_msec);
         }catch (InterruptedException exn) {
            stamp.printf ("producer %s: %s%n", name, exn);
         }
         stamp.printf ("producer %s: put (\"%s\")%n", name, datum);
         outbuf.put (datum);
      }
      stamp.printf ("producer %s finished%n", name);
   }

}

