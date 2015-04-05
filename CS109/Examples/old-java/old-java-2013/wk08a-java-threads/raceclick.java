// $Id: raceclick.java,v 1.2 2012-05-23 21:31:15-07 - - $

//
// Show race conditions between two threads that click an int.
// Unsynchronized clicking the counter 1000000 times each.
//

import static java.lang.System.*;

class raceclick {

   static class counter {
      int count = 0;
   }

   static class racer implements Runnable {
      int ident;
      counter counted;
      racer (int idinit, counter countinit) {
         ident = idinit;
         counted = countinit;
      }
      public void run () {
         out.printf ("racer %d starting%n", ident);
         out.flush();
         for (int itor = 0; itor < 1000000; ++itor) ++counted.count;
         out.printf ("racer %d finished, count = %d%n",
                     ident, counted.count);
         out.flush();
      }
   }

   public static void main (String[] args) {
      out.printf ("main starting%n");
      out.flush();
      counter counted = new counter ();
      Thread racer1 = new Thread (new racer (1, counted));
      Thread racer2 = new Thread (new racer (2, counted));
      racer1.start ();
      racer2.start ();
      out.printf ("main finished, count = %d%n", counted.count);
      out.flush();
   }

}

//TEST// runprog -x raceclick.lis raceclick
//TEST// mkpspdf raceclick.ps raceclick.java* raceclick.lis

