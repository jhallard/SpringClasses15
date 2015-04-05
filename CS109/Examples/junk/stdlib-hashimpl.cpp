// $Id: stdlib-hashimpl.cpp,v 1.11 2013-08-12 18:44:03-07 - - $

#include <iomanip>
#include <iostream>
using namespace std;

// libsupc++/hash_bytes.h

size_t  _Hash_bytes(const void* __ptr, size_t __len, size_t __seed);

// include/bits/functional_hash.h

struct _Hash_impl { 
   static size_t hash(const void* __ptr, size_t __clength,
                      size_t __seed = static_cast<size_t>(0xC70F6907UL))
   { return _Hash_bytes(__ptr, __clength, __seed); }
    
   template<typename _Tp>
   static size_t hash(const _Tp& __val)
   { return hash(&__val, sizeof(__val)); }
    
   template<typename _Tp>
   static size_t __hash_combine(const _Tp& __val, size_t __hash) 
   { return hash(&__val, sizeof(__val), __hash); }
};

// libsupc++/hash_bytes.cc

inline std::size_t unaligned_load(const char* p) {
   std::size_t result;
   __builtin_memcpy(&result, p, sizeof(result));
   return result;
}

// Loads n bytes, where 1 <= n < 8.
inline std::size_t load_bytes(const char* p, int n) {
   std::size_t result = 0;
   --n;
   do
      result = (result << 8) + static_cast<unsigned char>(p[n]);
   while (--n >= 0);
   return result;
}

inline std::size_t shift_mix(std::size_t v) {
   return v ^ (v >> 47);
}


// Implementation of Murmur hash for 64-bit size_t. 
size_t _Hash_bytes(const void* ptr, size_t len, size_t seed) {
   static const size_t mul = (((size_t) 0xc6a4a793UL) << 32UL)
                             + (size_t) 0x5bd1e995UL;
   const char* const buf = static_cast<const char*>(ptr);
   
   // Remove the bytes not divisible by the sizeof(size_t).  This
   // allows the main loop to process the data as 64-bit integers.
   const int len_aligned = len & ~0x7; 
   const char* const end = buf + len_aligned;
   size_t hash = seed ^ (len * mul); 
   for (const char* p = buf; p != end; p += 8) {
      const size_t data = shift_mix(unaligned_load(p) * mul) * mul;
      hash ^= data;
      hash *= mul; 
   }
   if ((len & 0x7) != 0) {
      const size_t data = load_bytes(end, len & 0x7); 
      hash ^= data;
      hash *= mul; 
   }
   hash = shift_mix(hash) * mul;
   hash = shift_mix(hash);
   return hash;
} 

// TESTING.

size_t hash (const string &str) {
   return _Hash_impl::hash (str.c_str(), str.size());
}

int main (int argc, char **argv) {
   const size_t width = 20;
   for (char **argp = &argv[1]; argp != &argv[argc]; ++argp) {
      string str {*argp};
      size_t hashnr = hash (str);
      cout << setw(width) << hashnr << " = hash(\"" << str << "\")"
           << endl;
   }
   const size_t max = static_cast<size_t> (-1);
   cout << setw(width) << max << " = 0x" << hex << uppercase << max
        << " = " << static_cast<long double> (max) << endl;
}
