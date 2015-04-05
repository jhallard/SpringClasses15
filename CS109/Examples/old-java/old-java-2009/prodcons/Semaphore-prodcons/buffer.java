// $Id: buffer.java,v 1.1 2009-02-26 20:47:05-08 - - $

interface buffer <item_t> {

   void put (item_t item);
   item_t get ();
   void producers_finished ();

}

