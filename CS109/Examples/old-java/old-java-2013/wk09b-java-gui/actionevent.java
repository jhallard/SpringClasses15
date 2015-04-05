// $Id: actionevent.java,v 1.3 2013-03-08 17:04:20-08 - - $

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import static java.lang.System.*;

//
// Shows ActionListener.
// Note: only reacts to mouse button1.
// If you need other buttons, use a MouseListener.
//

class actionevent {

   static int[] masks = {ActionEvent.ALT_MASK, ActionEvent.CTRL_MASK,
                         ActionEvent.META_MASK, ActionEvent.SHIFT_MASK};
   static String[] names = {"ALT", "CTRL", "META", "SHIFT"};
   static String parse (int modifiers) {
      String result = "";
      for (int index = 0; index < masks.length; ++index) {
         if ((modifiers & masks[index]) != 0) {
            result += " " + names[index]; 
            modifiers &= ~ masks[index];
         }
      }
      return String.format ("0x%X", modifiers) + result;
   }

   static class action_listener implements ActionListener {
      public void actionPerformed (ActionEvent event) {
         out.printf ("getActionCommand = \"%s\"%n",
                     event.getActionCommand ());
         out.printf ("getModifiers = %s%n",
                     parse (event.getModifiers ()));
         out.printf ("paramString = \"%s\"%n", event.paramString ());
      }
   }

   public static void main (String[] args) {
      JFrame frame = new JFrame ("checkbox");
      Container pane = frame.getContentPane ();
      JButton button = new JButton ("CLICK THIS");
      pane.add (button);
      button.addActionListener (new action_listener());
      button.setFont (new Font ("Courier", Font.BOLD, 43));
      frame.setLocation (256, 256);
      frame.pack ();
      frame.setVisible (true);
   }

}
