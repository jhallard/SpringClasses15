// $Id: mouseevent.java,v 1.12 2012-05-31 22:09:32-07 - - $

//
// Shows how to handle mouse events.
// Mouse is clicked, which is pressed then released.
// Mouse enters or leaves on a mouseover.
//

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import static java.lang.System.*;

class mouseevent {

   static void log_event (String name, MouseEvent event) {
      out.printf ("Mouse %s:%n", name);
      Point relative = event.getPoint();
      Point absolute = event.getLocationOnScreen();
      out.printf ("   relative = (%s,%s), screen = (%s,%s)%n",
                  relative.getX(), relative.getY(),
                  absolute.getX(), absolute.getY());
      out.printf ("   button = %d, clicks = %d, when = %d%n",
                  event.getButton(), event.getClickCount(),
                  event.getWhen());
      out.printf ("   modifiers =");
      if (event.isAltDown()) out.printf (" Alt");
      if (event.isAltGraphDown()) out.printf (" AltGraph");
      if (event.isControlDown()) out.printf (" Control");
      if (event.isMetaDown()) out.printf (" Meta");
      if (event.isShiftDown()) out.printf (" Shift");
      out.printf ("%n");
   }

   static class mouse_listener implements MouseListener {
      public void mouseClicked (MouseEvent event) {
         log_event ("Clicked", event);
      }
      public void mouseEntered (MouseEvent event) {
         log_event ("Entered", event);
      }
      public void mouseExited (MouseEvent event) {
         log_event ("Exited", event);
      }
      public void mousePressed (MouseEvent event) {
         log_event ("Pressed", event);
      }
      public void mouseReleased (MouseEvent event) {
         log_event ("Released", event);
      }
   }


   public static void main (String[] args) {
      JFrame frame = new JFrame ("mouseevent");
      Container pane = frame.getContentPane ();
      JButton button = new JButton ("Click this");
      pane.add (button);
      button.setFont (new Font ("Helvetica", Font.BOLD, 36));
      button.addMouseListener (new mouse_listener ());
      frame.setLocation (256, 256);
      frame.pack ();
      frame.setVisible (true);
   }

}

