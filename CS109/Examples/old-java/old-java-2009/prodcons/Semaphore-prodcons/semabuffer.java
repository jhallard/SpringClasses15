// $Id: semabuffer.java,v 1.1 2009-02-26 20:40:57-08 - - $

import java.util.concurrent.*;

class semabuffer <item_t> implements buffer <item_t> {

   private arrayqueue <item_t> queue;
   private boolean producers_done = false;
   private Semaphore emptyslot = new Semaphore (5);
   private Semaphore fullslot = new Semaphore (0);

   public semabuffer (int size) {
      queue = new arrayqueue <item_t> (size);
   }

   public void put (item_t item) {
      if (producers_done) throw new
                  IllegalStateException ("producers are done");
      try {
         emptyslot.acquire ();
      }catch (InterruptedException exn) {
         throw new Error ("fixedbuffer.put: %s%n", exn);
      }
      queue.push (item);
      fullslot.release ();
   }

   public item_t get () {
      if (producers_done) return null;
      try {
         fullslot.acquire ();
      }catch (InterruptedException exn) {
         throw new Error ("fixedbuffer.get: %s%n", exn);
      }
      item_t result = queue.shift ();
      emptyslot.release ();
      return result;
   }

   synchronized public void producers_finished () {
      producers_done = true;
   }

}

