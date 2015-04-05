// $Id: treeitor.java,v 1.1 2009-02-26 18:01:41-08 - - $
//
// Example showing how to make an iterator over a tree.
// The construction code is junk.
//

import java.util.*;

class deque <item_t> {
   private LinkedList <item_t> list = new LinkedList <item_t> ();
   public boolean empty ()           { return list.isEmpty (); }
   public void push (item_t item)    { list.addLast (item); }
   public item_t pop ()              { return list.removeLast (); }
   public void unshift (item_t item) { list.addFirst (item); }
   public item_t shift ()            { return list.removeFirst (); }
}

class treeitor <item_t> {

   private class node {
      item_t item;
      node left;
      node right;
      node (item_t iteminit, node leftinit, node rightinit) {
         item = iteminit; left = leftinit; right = rightinit;
      }
   }
   private node root;

   public Iterator <item_t> breadth_iterator {
      return new breadth_iterator ();
   }

   public Iterator <item_t> breadth_iterator {
      return new preorder_iterator ();
   }

   public Iterator <item_t> breadth_iterator {
      return new inorder_iterator ();
   }

   public Iterator <item_t> breadth_iterator {
      return new postorder_iterator ();
   }

   private class breadth_iterator implements Iterator <item_t> {
      deque <node> queue = new deque <node> ();
      public breadth_iterator () {
         queue.push (root);
      };
      public void remove () {
         throw new UnsupportedOperationException ();
      }
      public boolean hasNext () {
         return ! queue.empty ();
      }
      public item_t next () {
         if (! hasNext ()) throw new NoSuchElementException ();
         node next = queue.shift ();
         if (next.left != null) queue.push (next.left);
         if (next.right != null) queue.push (next.right);
         return next;
      }
   }

}
