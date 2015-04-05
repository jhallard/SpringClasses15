// $Id: echotext.java,v 1.2 2012-05-31 22:16:50-07 - - $

//
// Text input field.  Brings up a text field with some initializtion.
// Edit the field.  At CR, a debug message is printed to stdout.
// The program is killed with ^C in the xterm or a kill command.
//

import java.awt.*; 
import java.awt.event.*;
import javax.swing.*;
import static java.lang.System.*;

class echotext { 

   static class echo implements ActionListener {
      public void actionPerformed (ActionEvent event) {
         JTextField source = (JTextField)event.getSource ();
         String text = source.getText ();
         try {
            double number = Double.parseDouble (text);
            out.printf ("number = %g%n", number);
         }catch (NumberFormatException exn) {
            out.printf ("text = \"%s\"\n", text);
            if (text.length () == 0) exit (0);
         }
      }
   }

   public static void main (String[] args) { 
      JFrame frame = new JFrame ("TextInput"); 
      Container pane = frame.getContentPane ();
      JTextField input = new JTextField ("Edit this text then <CR>");
      echo listener = new echo ();
      input.addActionListener (listener); 
      pane.add (input); 
      frame.pack ();
      frame.setLocation (256, 256);
      frame.setSize (256, 64);
      frame.setVisible (true);
   }

}

