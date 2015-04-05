// $Id: mapentry.java,v 1.2 2009-03-13 12:48:23-07 - - $

//
// Example of how to iterate over a HashMap and access Map.Entry
// elements via an iterator.  The example uses the strings in 
// argv as keys and the indices as values.
//
// http://java.sun.com/j2se/1.5.0/docs/api/java/util/HashMap.html
// http://java.sun.com/j2se/1.5.0/docs/api/java/util/Set.html
// http://java.sun.com/j2se/1.5.0/docs/api/java/util/Map.Entry.html
//

import java.util.*;
import static java.lang.System.*;

class mapentry {
   public static void main (String[] args) {

      // Make the map.
      HashMap <String, Integer> map = new HashMap <String, Integer> ();

      // Insert keys and values into the map.
      for (int argi = 0; argi < args.length; ++argi) {
         map.put (args[argi], argi);
      }

      // Extract a collection view of the map.
      Set <Map.Entry <String, Integer>> set = map.entrySet ();

      // Get an iterator over the set.
      Iterator <Map.Entry <String, Integer>> itor = set.iterator ();

      // Print out the keys and values in whatever hash map order.
      while (itor.hasNext ()) {
         Map.Entry <String, Integer> entry = itor.next ();
         out.printf ("%s => %s%n", entry.getKey (), entry.getValue ());
      }
     
   }
}
