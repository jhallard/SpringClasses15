// $Id: endian.c,v 1.4 2014-05-20 21:45:24-07 - - $

// Illustrate endianness.

#include <arpa/inet.h>
#include <stdio.h>

typedef union union32 { uint32_t num; char chr[4]; } union32;
typedef union union16 { uint16_t num; char chr[2]; } union16;

void print32 (const char *label, const union32 *val) {
   printf ("%-8s: 0x%08X =", label, val->num);
   for (int i = 0; i < 4; ++i) printf (" %02X", val->chr[i]);
   printf ("\n");
}

void print16 (const char *label, const union16 *val) {
   printf ("%-8s: 0x%04X =", label, val->num);
   for (int i = 0; i < 2; ++i) printf (" %02X", val->chr[i]);
   printf ("\n");
}

int main () {
   union union32 n32 = {0x12345678};
   print32 ("Original", &n32);
   n32.num = htonl (n32.num);
   print32 ("Network", &n32);
   n32.num = ntohl (n32.num);
   print32 ("Host", &n32);

   union union16 n16 = {0x1234};
   print16 ("Original", &n16);
   n16.num = htons (n16.num);
   print16 ("Network", &n16);
   n16.num = ntohs (n16.num);
   print16 ("Host", &n16);

   return 0;
}
