// $Id: getopts.java,v 1.1 2009-03-13 12:28:16-07 - - $

//
// NAME
//    getopts - similar to the C library function getopt(3c)
//
// SYNOPSIS
//    public getopts (String[] args, String optstring)
//    public int getopt ()
//    public String getoptarg ()
//    public int geterror ()
//    public String[] getoperands ()
//
// DESCRIPTION
//    Knowledge of the C function getopt(3c) is assumed.  Read that
//    man page first.  An options and operands array args is scanned
//    for option flags, options with arguments, and operands.
//
//    public getopts (String[] args, String optstring)
//       Constructs a new getopts from an args array and an option
//       string.  The option strings is as per getopt(3c) and consists
//       of a sequence of letters.  If an argument is required, a
//       colon must follow the letter.  The argument is either the
//       rest of the word, if such exists, or the next word, if it 
//       does not.
//
//    public int getopt ()
//       Returns the next option char as an int if a valid option 
//       char is found.  If not, returns END to indicate that there
//       are no more options or ERROR if an invalid option char was
//       found.
//       Throws: IllegalStateException if END has been returned.
//
//    public String getoptarg ()
//       Returns the argument associated with the last option letter.
//       Throws: IllegalStateException if END has been returned or
//       if the last option letter did not need an argument.
//
//    public int geterrchar ()
//       Returns the option letter that most recently caused ERROR to
//       be returned.
//       Throws: IllegalStateException if END has been returned or
//       if the last option letter was not in error.
//
//    public String[] getoperands ()
//       Returns a subarray of args that is left after all options
//       have been scanned.  This array may have length 0.
//       Throws: IllegalStateException if END has not been returned.
//

class getopts {
   public static final int END = -1;
   public static final int ERROR = -2;
   private int optindex = 0;
   private char optchar = 0;
   private String optarg = null;
   private String[] args;
   private String optstring;
   private int strpos = 0;
   private boolean gotend = false;
   private boolean goterror = false;

   private int setgotend () {
      gotend = true;
      return END;
   }

   private int setgoterror () {
      goterror = true;
      return ERROR;
   }

   public getopts (String[] args, String optstring) {
      this.args = args;
      this.optstring = optstring;
   }

   public int getopt () {
      if (gotend) throw new IllegalStateException ();
      goterror = false;
      String arg = null;
      optarg = null;
      for (;;) {
         if (optindex >= args.length) return setgotend ();
         arg = args[optindex];
         if (strpos == 0) {
            if (! arg.startsWith ("-")) return setgotend ();
            if (arg.equals ("-")) return setgotend ();
            if (arg.equals ("--")) {++optindex; return setgotend (); }
            ++strpos;
         }
         if (strpos < arg.length ()) break;
         strpos = 0;
         ++optindex;
      }
      optchar = arg.charAt (strpos);
      ++strpos;
      int optpos = optstring.indexOf (optchar);
      if (optpos < 0) return setgoterror ();
      if (optpos == optstring.length () - 1) return optchar;
      if (optstring.charAt (optpos + 1) != ':') return optchar;
      if (strpos < arg.length ()) {
         optarg = arg.substring (strpos);
         ++optindex;
         strpos = 0;
         return optchar;
      }
      if (optindex == args.length - 1) return setgoterror ();
      optarg = args[++optindex];
      strpos = 0;
      ++optindex;
      return optchar;
   }

   public String getoptarg () {
      if (gotend || optarg == null) throw new IllegalStateException ();
      return optarg;
   }

   public char geterrchar () {
      if (! goterror) throw new IllegalStateException ();
      return optchar;
   }

   public String[] getoperands () {
      if (! gotend) throw new IllegalStateException ();
      String[] operands = new String [args.length - optindex];
      System.arraycopy (args, optindex, operands, 0, operands.length);
      return operands;
   }
   
}
