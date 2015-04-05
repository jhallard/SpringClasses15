// $RCSfile: httpget.c,v $$Revision: 1.1 $

//
// httpget - get a web page from some host
//
// usage:
//    httpget [-port] http_host pathname
//
// Default port is 80.  Gets the given page from the given host.
//

#define DEFAULT_PORT 80

#include <errno.h>
#include <libgen.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

char *exec_name = NULL;

void usage() {
   fprintf (stderr, "Usage: %s [-port] [host [path]]\n", exec_name);
   exit (EXIT_FAILURE);
}

void print_command (char **argv) {
   printf ("\nCommand:");
   while (*argv) printf (" %s", *argv++);
   printf ("\n");
}

void crash (const char *object, const char *message) {
   fflush (stdout);
   fprintf (stderr, "%s: %s: %s\n", exec_name, object, message);
   fflush (stderr);
   exit (EXIT_FAILURE);
}

void print_host_port (char *http_host, struct hostent *hostp,
                      int http_port) {
   printf ("host = %s = %s =", http_host, hostp->h_name);
   for (int i = 0; i < 4; i++) {
      printf ("%c%d", i == 0 ? ' ' : '.',
              (unsigned char) hostp->h_addr[i]);
   }
   printf ("\nport = %d\n", http_port);
}


int main (int argc, char *argv[]) {
   print_command (argv);
   exec_name = basename ((argc--, *argv++));
   int http_port = DEFAULT_PORT;
   if (argc > 0 && **argv == '-') http_port = atoi ((argc--, *argv++));
   char *http_host = argc > 0 ? (argc--, *argv++) : "localhost";
   char *http_path = argc > 0 ? (argc--, *argv++) : "/";
   if (argc != 0) usage();

   // get inet address of host and print it
   struct hostent *hostp = gethostbyname (http_host);
   if (hostp == 0) crash (http_host, hstrerror (h_errno));
   print_host_port (http_host, hostp, http_port);

   // create a socket to connect to other machine
   int sockfd = socket (AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) crash ("socket()", strerror (errno));

   // create a struct sockaddr and connect it to the socket
   struct sockaddr_in sock;
   sock.sin_family = AF_INET; 
   sock.sin_port = htons (http_port);
   sock.sin_addr = *(struct in_addr *) hostp->h_addr;
   int rc = connect (sockfd, (struct sockaddr *) &sock, sizeof sock);
   if (rc < 0) crash ("connect()", strerror (errno));

   // read info from the remote and convert to host format
   char buffer[4096];
   int nbytes = sprintf (buffer, "GET %s\n", http_path);
   printf ("request: %s", buffer);
   write (sockfd, buffer, nbytes);
   for(;;){
      int nbytes = read (sockfd, &buffer, sizeof buffer - 1);
      if (nbytes == 0) break;
      buffer[nbytes] = '\0';
      printf ("%s", buffer);
   }

   // all done
   close (sockfd);
   return EXIT_SUCCESS;
}

//TEST// echo $0: Running httpget tests: >httpget.out
//TEST// ./httpget >>httpget.out 2>&1
//TEST// ./httpget Unknown.Host >>httpget.out 2>&1
//TEST// ./httpget soe.ucsc.edu >>httpget.out 2>&1
//TEST// ./httpget www2.ucsc.edu /courses/cmps109-wm/ >>httpget.out 2>&1
//TEST// mkpspdf httpget.ps httpget.c* httpget.out

