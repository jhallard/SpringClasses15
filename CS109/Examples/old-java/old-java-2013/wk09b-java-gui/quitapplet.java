// $Id: quitapplet.java,v 1.5 2013-03-05 19:57:15-08 - - $

//
// Quit applet.  Click on quit to stop.
//

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import static java.lang.System.*;

public class quitapplet extends JApplet {
   public static final long serialVersionUID = 1;

   static void gui () {
      JFrame frame = new JFrame ("quitapplet");
      Container pane = frame.getContentPane ();
      Button quit = new Button ("Quit");
      quit.addActionListener (new ActionListener () {
         public void actionPerformed (ActionEvent event) {
            out.printf ("quitapplet: gui quitting.%n");
            exit (0);
         }
      });
      quit.setFont (new Font ("TimesRoman", Font.BOLD, 24));
      pane.add (quit);
      frame.pack (); 
      frame.setLocation (256, 256);
      frame.setSize (192, 64);
      frame.setVisible (true);
   }

   public static void main (String[] args) {
      out.printf ("quitapplet: main function starting.%n");
      gui ();
   }

   public void init () {
      out.printf ("quitapplet: init function starting.%n");
      gui ();
   }

}
