// $Id: javatime.java,v 1.4 2013-08-12 20:23:18-07 - - $

import java.util.Calendar;
import static java.lang.System.*;

class javatime {
   public static void main (String[] args) {
      Calendar now = Calendar.getInstance();
      out.printf ("%1$tY %1$tb %1$td %1$ta %1$tT.%1$tL %1$tZ %1$tz%n",
                  now);
   }
}
