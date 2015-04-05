// $Id: goodbyegui.java,v 1.6 2012-05-30 20:13:46-07 - - $

//
// Display a hello button.  Pressing it causes a dialog box to 
// pop up with a Yes/No/Cancel choice.  Debug output is printed.
// An ActionListener is used to make the response.
//

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import static java.lang.System.*;

class goodbyegui {

   static class confirm implements ActionListener { 
      public void actionPerformed (ActionEvent e) {
         // Confirm with Yes/No/Cancel (integers 0/1/2)
         int response = JOptionPane.showConfirmDialog (null,
                        "Goodbye, World!  Really?",
                        "Goodbye, World!",
                        JOptionPane.YES_NO_CANCEL_OPTION);
         out.printf ("response = %d%n", response);
         switch (response) {
            case JOptionPane.YES_OPTION:
               out.printf ("YES: Goodbye, World!%n"); 
               exit (0); 
               break;
            case JOptionPane.NO_OPTION:
               out.printf ("NO: Hello, World!%n");
               break;
            case JOptionPane.CANCEL_OPTION:
               out.printf ("CANCEL: Hello, World!%n");
               break;
            case JOptionPane.CLOSED_OPTION:
               out.printf ("CLOSED: Hello, World!%n");
               break;
            default:
               out.printf ("Default: Hello, World!%n");
         }
      }
   }

   public static void main (String[] args) {
      JFrame frame = new JFrame ("goodbye");
      Container pane = frame.getContentPane ();
      Button hello = new Button ("Hello, world!");
      Font timesroman = new Font ("Serif", Font.BOLD, 24);
      hello.setFont (timesroman);
      confirm listener = new confirm ();
      hello.addActionListener (listener);
      pane.add (hello);
      frame.pack (); 
      frame.setLocation (256, 256);
      frame.setSize (256, 64);
      frame.setVisible (true);
   }

}

