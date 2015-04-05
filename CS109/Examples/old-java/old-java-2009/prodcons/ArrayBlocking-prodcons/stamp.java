// $Id: stamp.java,v 1.1 2009-02-26 20:49:08-08 - - $

import static java.lang.System.*;

class stamp {

   private static long start_time = currentTimeMillis ();

   public static void printf (String format, Object... args) {
      long diff = currentTimeMillis () - start_time;
      long milliseconds = diff % 1000;
      diff /= 1000;
      long seconds = diff % 60;
      long minutes = diff / 60;
      out.printf ("%2d:%02d.%03d: ", minutes, seconds, milliseconds);
      out.printf (format, args);
   }

}

