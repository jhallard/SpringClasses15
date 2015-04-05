// $Id: files.java,v 1.1 2009-03-03 17:30:30-08 - - $

import java.io.*;
import java.util.*;
import static java.lang.System.*;

class files {

   static FilenameFilter filter = new FilenameFilter () {
      public boolean accept (File dir, String name) {
         return ! name.startsWith (".");
      }
   };

   static Comparator<File> filecmp = new Comparator<File> () {
      public int compare (File one, File two) {
         return one.getName().compareTo (two.getName ());
      }
   };

   public static void main (String[] args) {
      for (String filename: args) {
         File file = new File (filename);
         if (file.isFile ()) {
            out.printf ("%s is a file: %s%n", filename,
                        file.canRead () ? "readable" : "not readdable");
         }else if (file.isDirectory ()) {
            out.printf ("%s is a directory:%n", filename);
            File[] dirents = file.listFiles (filter);
            Arrays.sort (dirents, filecmp);
            for (File dirent: dirents) {
               out.printf ("   %s%n", dirent.getName ());
            }
         }else {
            out.printf ("%s is not a file or directory%n", filename);
         }
      }
   }
}
