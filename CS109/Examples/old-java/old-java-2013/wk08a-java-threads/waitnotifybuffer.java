// $Id: waitnotifybuffer.java,v 1.16 2013-08-12 19:35:19-07 - - $

//
// Producer-consumer example using wait and notify on a
// bounded buffer.  Producer blocks when queue is full, and
// consumer blocks when queue is empty.  All classes are
// static inner classes to make the example fit in one file.
// Usually, each class would be in a separate file.
//

import java.io.*;
import java.util.*;
import static java.lang.String.*;
import static java.lang.System.*;

class waitnotifybuffer {

static class arrayqueue<item_t> {
   private static final int EMPTY = -1;
   private int front = EMPTY;
   private int rear = EMPTY;
   private item_t[] items;

   @SuppressWarnings ("unchecked")
   public arrayqueue (int size) {
      items = (item_t[]) new Object[size];
   }

   public boolean is_empty() {
      return front == EMPTY;
   }

   public boolean is_full() {
      return (rear + 1) % items.length == front;
   }

   public void push_rear (item_t item) {
      if (is_full()) throw new
            IllegalStateException ("arrayqueue.push_rear");
      if (is_empty()) front = rear = 0;
                 else rear = (rear + 1) % items.length;
      items[rear] = item;
   }

   item_t pop_front() {
      if (is_empty()) throw new
            IllegalStateException ("arrayqueue.pop_front");
      item_t result = items[front];
      if (front == rear) front = rear = EMPTY;
                    else front = (front + 1) % items.length;
      return result;
   }
}


interface buffer<item_t> {
   void put (item_t item);
   item_t get();
   void set_eof();
}

static class arraybuffer<item_t> implements buffer<item_t> {
   private arrayqueue<item_t> queue;
   private boolean eof = false;

   public arraybuffer (int size) {
      queue = new arrayqueue<item_t> (size);
   }

   synchronized public void set_eof() {
      eof = true;
   }

   synchronized public void put (item_t item) {
      if (eof) throw new IllegalStateException ("put");
      while (queue.is_full()) {
         try {
            wait();
         }catch (InterruptedException exn) {
            display ("arraybuffer.put: %s", exn.getMessage());
         }
      }
      queue.push_rear (item);
      notifyAll();
   }

   synchronized public item_t get() {
      while (queue.is_empty()) {
         if (eof) return null;
         try {
            wait();
         }catch (InterruptedException exn) {
            display ("arraybuffer.get: %s", exn.getMessage());
         }
      }
      item_t result = queue.pop_front();
      notifyAll();
      return result;
   }
}


static class producer<item_t> implements Runnable {
   private buffer<item_t> buf;
   private String name;
   private long delay_msec;
   private item_t[] data;

   producer (buffer<item_t> _buf, String _name, long _delay,
             item_t[] _data) {
      buf = _buf;
      name = _name;
      delay_msec = _delay;
      data = _data;
   }

   public void run() {
      Thread self = Thread.currentThread();
      self.setName ("producer " + name);
      display ("starting");
      int count = 0;
      for (item_t datum: data) {
         try {
            Thread.sleep (delay_msec);
         }catch (InterruptedException exn) {
            display ("%s", exn.getMessage());
         }
         display ("put (\"%s\")", datum);
         buf.put (datum);
      }
      display ("finished");
   }
}


static class consumer<item_t> implements Runnable {
   private buffer<item_t> buf;
   private String name;
   long delay_msec;

   consumer (buffer<item_t> _buf, String _name, long _delay) {
      buf = _buf;
      name = _name;
      delay_msec = _delay;
   }

   public void run() {
      Thread self = Thread.currentThread();
      self.setName ("consumer " + name);
      display ("starting");
      for (;;) {
         item_t item = buf.get();
         if (item == null) break;
         try {
            Thread.sleep (delay_msec);
         }catch (InterruptedException exn) {
            display ("%s", exn.getMessage());
         }
         display ("get() = \"%s\"", item);
      }
      display ("finished");
   }
}


   static long nanostart = nanoTime();

   synchronized static void display (String fmt, Object... args) {
      Thread self = Thread.currentThread();
      double millisec = (nanoTime() - nanostart) / 1e6;
      out.printf ("%10.3f: %s(%d): ",
                  millisec, self.getName(), self.getId());
      out.printf (fmt + "%n", args);
      out.flush();
   }

   public static void main (String[] args) {
      display ("starting");
      String[] latin = {
         "prîmus", "secundus,", "tertius", "quârtus", "quîntus",
         "sextus", "septimus", "octâvus", "nônus", "decimus"
      };
      String[] greek = { // Transliterated, of course.
         "prôtos", "deuteros", "tritos", "tetartos", "pentos",
         "hektos", "hebdomos", "ogdoos", "enatos", "dekatos"
      };
      buffer<String> buf = new arraybuffer<String> (5);
      Thread[] producers = {
         new Thread (new producer<String> (buf, "Romans", 100, latin)),
         new Thread (new producer<String> (buf, "Greeks", 300, greek))
      };
      Thread[] consumers = {
         new Thread (new consumer<String> (buf, "Gauls", 200)),
         new Thread (new consumer<String> (buf, "Picts", 500))
      };
      for (Thread thread: producers) thread.start();
      for (Thread thread: consumers) thread.start();
      for (int itor = 0; itor < producers.length; ++itor) {
         try {
            producers[itor].join();
         }catch (InterruptedException exn) {
            display ("join: %s", exn.getMessage());
         }
      }
      buf.set_eof();
      display ("finished");
   }
}

//TEST// ./waitnotifybuffer >waitnotifybuffer.lis 2>&1
//TEST// mkpspdf waitnotifybuffer.ps \
//TEST//         waitnotifybuffer.java* waitnotifybuffer.lis

