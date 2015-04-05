// $Id: fontfamilies.java,v 1.1 2012-05-30 19:47:17-07 - - $

//
// Print all Java font names.
//

import java.awt.*;
import java.util.*;
import static java.lang.System.*;
import static java.util.Collections.*;

class fontfamilies {
   public static void main (String[] args) {
      GraphicsEnvironment grenv =
      GraphicsEnvironment.getLocalGraphicsEnvironment();
      for (String fontname: grenv.getAvailableFontFamilyNames()) {
         out.printf ("%s%n", fontname);
      }
   }
}

//TEST// fontfamilies >fontfamilies.log
//TEST// mkpspdf fontfamilies.ps fontfamilies.java fontfamilies.log
