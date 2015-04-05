// $Id: blockingbuffer.java,v 1.2 2009-02-26 20:45:21-08 - - $

import java.util.concurrent.*;

class blockingbuffer <item_t> implements buffer <item_t> {

   private ArrayBlockingQueue <item_t> queue;
   private boolean producers_done = false;
   private Semaphore emptyslot = new Semaphore (5);
   private Semaphore fullslot = new Semaphore (0);

   public blockingbuffer (int size) {
      queue = new ArrayBlockingQueue <item_t> (size);
   }

   public void put (item_t item) {
      if (producers_done) throw new
                  IllegalStateException ("producers are done");
      try {
         queue.put (item);
      }catch (InterruptedException exn) {
         throw new Error ("blockingbuffer.put: %s%n", exn);
      }
   }

   public item_t get () {
      if (producers_done) return null;
      item_t result = null;
      try {
         result = queue.take ();
      }catch (InterruptedException exn) {
         throw new Error ("blockingbuffer.get: %s%n", exn);
      }
      return result;
   }

   synchronized public void producers_finished () {
      producers_done = true;
   }

}

