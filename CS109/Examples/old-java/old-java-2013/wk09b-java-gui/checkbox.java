// $Id: checkbox.java,v 1.2 2013-03-05 19:53:14-08 - - $

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import static java.lang.System.*;

class checkbox {

   public static class submit implements ActionListener {
      JCheckBox javabox;
      JCheckBox cbox;
      JCheckBox cxxbox;
      submit (JCheckBox _jbox, JCheckBox _cbox, JCheckBox _cxxbox) {
         javabox = _jbox;
         cbox = _cbox;
         cxxbox = _cxxbox;
      }
      public void actionPerformed (ActionEvent event) {
         out.printf ("Submitted: Java %b, C %b, C++ %b%n",
                     javabox.isSelected (), cbox.isSelected (),
                     cxxbox.isSelected ());
      }
   }

   public static void main (String[] args) {
      JFrame frame = new JFrame ("checkbox");
      Container display = frame.getContentPane ();
      FlowLayout layout = new FlowLayout (FlowLayout.CENTER);
      display.setLayout (layout);
      display.add (new JLabel (
                   "What programming languages do you know?"));
      display.add (new JLabel ("Check all that apply:"));
      JCheckBox javabox = new JCheckBox ("Java", true);
      JCheckBox cbox = new JCheckBox ("C", false);
      JCheckBox cxxbox = new JCheckBox ("C++", true);
      display.add (javabox);
      display.add (cbox);
      display.add (cxxbox);
      JButton submit = new JButton ("Submit");
      submit.addActionListener (new submit (javabox, cbox, cxxbox));
      display.add (submit);
      frame.pack ();
      Dimension dim = layout.minimumLayoutSize (frame);
      frame.setLocation (256, 256);
      frame.setSize (300, 100);
      frame.setVisible (true);
   }

}

