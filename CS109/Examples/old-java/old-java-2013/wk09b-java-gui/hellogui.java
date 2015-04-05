// $Id: hellogui.java,v 1.10 2012-05-30 19:55:40-07 - - $

//
// Display a hello button.
// Pressing it shows a slight change of appearance.
// Program only quits when killed externally.
//

import java.awt.*; 
import javax.swing.*;

class hellogui { 
   public static void main (String[] args) { 
      JFrame frame = new JFrame ("HelloButton");
      Container pane = frame.getContentPane ();
      JButton hello = new JButton ("« Hello, world! »");
      int fontsize = (int) Math.round (10 * Math.pow (1.2, 6));
      Font timesroman = new Font ("SansSerif", Font.BOLD, fontsize);
      hello.setFont (timesroman);
      pane.add (hello); 
      frame.pack (); 
      frame.setSize (512, 128);
      frame.setLocation (256, 256);
      frame.setVisible (true);
   }
}

