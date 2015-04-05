// $Id: eratosthenes.java,v 1.1 2009-02-26 18:01:41-08 - - $
//
// Threaded version of the Sieve of Eratosthenes.
//
class eratosthenes{
   final static int ENDSTREAM = -1;

   static class sieve{
      int value;
      boolean hasvalue = false;
      Thread filter;
      sieve(){
         filter = new sievethread( this );
         filter.start();
      };
      void waitcatch(){
         try{ wait(); }catch( InterruptedException e){};
      };
      synchronized void put( int newvalue ){
         while( hasvalue ) waitcatch();
         hasvalue = true;
         value = newvalue;
         notifyAll();
      };
      synchronized int get(){
         while( ! hasvalue ) waitcatch();
         hasvalue = false;
         notifyAll();
         return value;
      };
   };

   static class sievethread extends Thread{
      sieve caller;
      sievethread( sieve init ){ caller = init; };
      public void run(){
         int prime = caller.get();
         if( prime == ENDSTREAM ) return;
         System.out.println( prime );
         sieve callee = new sieve();
         for(;;){
            int value = caller.get();
            if( value == ENDSTREAM ){ callee.put( value ); return; };
            if( value % prime != 0 ){ callee.put( value ); };
         };
      };
   };

   static void main( String[] args ){
      int maxprime = Integer.parseInt( args[0] );
      sieve two = new sieve();
      for( int i = 2; i <= maxprime; i++ ) two.put( i );
      two.put( ENDSTREAM );
   };
};
