// $Id: pipelinesort.java,v 1.1 2009-02-26 18:02:03-08 - - $
//
// Pipeline sorting example: O(n) time * O(n) processors.
//
import java.io.*;
class pipelinesort{

   static class latch{
      Comparable value;
      boolean hasvalue = false;
      void waitcatch(){
         try{ wait(); }catch( InterruptedException e){};
      };
      synchronized void put( Comparable newvalue ){
         while( hasvalue ) waitcatch();
         hasvalue = true;
         value = newvalue;
         notifyAll();
      };
      synchronized Comparable get(){
         while( ! hasvalue ) waitcatch();
         hasvalue = false;
         notifyAll();
         return value;
      };
   };

   static class pipeline extends Thread{
      latch read_up;
      latch write_up;
      pipeline( latch rinit, latch winit ){
         read_up = rinit; write_up = winit;
      };
      public void run(){
         Comparable thisvalue = write_up.get();
         if( thisvalue == null ){ read_up.put( null ); return; };
         latch read_down = new latch();
         latch write_down = new latch();
         pipeline sorter = new pipeline( read_down, write_down );
         sorter.start();
         for(;;){
            Comparable value = write_up.get();
            write_down.put( value );
            if( value == null ) break;
         };
         for(;;){
            Comparable value = read_down.get();
            if( value == null ) break;
            if( value.compareTo( thisvalue ) > 0 ){
               read_up.put( thisvalue );
               thisvalue = value;
            }else{
               read_up.put( value );
            };
         };
         read_up.put( thisvalue );
         read_up.put( null );
      };
   };

   static void main( String[] args ){
      latch read_ = new latch();
      latch write_ = new latch();
      pipeline sorter = new pipeline( read_, write_ );
      sorter.start();
      for( int i = 0; i < args.length; i++ ){
         write_.put( args[i] + " [" + i + "]" );
      };
      write_.put( null );
      for(;;){
         Comparable value = read_.get();
         if( value == null ) break;
         System.out.println( value );
      };
   };
};
