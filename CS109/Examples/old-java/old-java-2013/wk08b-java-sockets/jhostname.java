// $Id: jhostname.java,v 1.2 2013-08-13 19:11:30-07 - - $

//
// Get IP address and hostname of localhost.
//

import java.net.*;
import static java.lang.System.*;

class jhostname {
   public static void main (String[] args) {
      try {
         InetAddress addr = InetAddress.getLocalHost ();
         String hostname = addr.getHostName ();
         String hostaddr = addr.getHostAddress ();
         out.printf ("hostname = %s, hostaddr = %s%n",
                     hostname, hostaddr);
      }catch (UnknownHostException exn) {
         err.printf ("hostname: %s%n", exn);
         exit (1);
      }
   }
}

