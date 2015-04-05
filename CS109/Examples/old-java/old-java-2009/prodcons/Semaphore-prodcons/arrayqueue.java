// $Id: arrayqueue.java,v 1.1 2009-02-26 20:47:04-08 - - $

class arrayqueue <item_t> {

   private static final int EMPTY = -1;
   private int front = EMPTY;
   private int rear = EMPTY;
   item_t[] items;

   public arrayqueue (int size) {
      items = (item_t[]) new Object[size];
   }

   public boolean empty () {
      return front == EMPTY;
   }

   public boolean full () {
      return (rear + 1) % items.length == front;
   }

   public void push (item_t item) {
      if (full ()) throw new IllegalStateException ("queue is full");
      if (empty ()) front = rear = 0;
               else rear = (rear + 1) % items.length;
      items[rear] = item;
   }

   item_t shift () {
      if (empty ()) throw new IllegalStateException ("queue is empty");
      item_t result = items[front];
      if (front == rear) front = rear = EMPTY;
                    else front = (front + 1) % items.length;
      return result;
   }

}

