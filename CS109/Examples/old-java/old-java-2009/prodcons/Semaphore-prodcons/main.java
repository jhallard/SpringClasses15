// $Id: main.java,v 1.3 2009-02-27 17:46:18-08 - - $

import static java.lang.System.*;

class main {

   public static void main (String[] args) {
      stamp.printf ("main starting%n");
      String[] latin = {
         "prîmus", "secundus,", "tertius", "quârtus", "quîntus",
         "sextus", "septimus", "octâvus", "nônus", "decimus"
      };
      String[] greek = {
         "prôtos", "deuteros", "tritos", "tetartos", "pentos",
         "hektos", "hebdomos", "ogdoos", "enatos", "dekatos"
      };
      buffer <String> buf = new semabuffer (5);
      Thread[] producers = {
         new Thread (new producer <String> (buf, "Latin", 100, latin)),
         new Thread (new producer <String> (buf, "Greek", 300, greek))
      };
      Thread[] consumers = {
         new Thread (new consumer (buf, "Foo", 200)),
         new Thread (new consumer (buf, "Bar", 500))
      };
      for (Thread thread: producers) thread.start ();
      for (Thread thread: consumers) thread.start ();
      for (int itor = 0; itor < producers.length; ++itor) {
         try {
            producers[itor].join ();
         }catch (InterruptedException exn) {
            stamp.printf ("main join: %s%n", exn);
         }
      }
      buf.producers_finished ();
      stamp.printf ("main finished%n");
   }

}
