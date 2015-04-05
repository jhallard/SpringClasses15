// $Id: virtual.cpp,v 1.14 2015-02-10 17:54:20-08 - - $

#include <iostream>
#include <typeinfo>

using namespace std;
#define TRACE(STMT) cout << "TRACE (" << #STMT << ")" << endl; STMT

class nonbase {
   public:
      nonbase() { cout << "nonbase()" << endl; }
      ~nonbase() { cout << "~nonbase()" << endl; }
      void show () { cout << typeid (*this).name() << endl; }
};

class nonderived: public nonbase {
   public:
      nonderived() { cout << "nonderived()" << endl; }
      ~nonderived() { cout << "~nonderived()" << endl; }
      void show () { cout << typeid (*this).name() << endl; }
};

class virtbase {
   public:
      // Inheritance classes must have virtual destructors.
      virtbase() { cout << "virtbase()" << endl; }
      virtual ~virtbase() { cout << "~virtbase()" << endl; }
      virtual void show () { cout << typeid (*this).name() << endl; }
};

class virtderived: public virtbase {
   public:
      virtderived() { cout << "virtderived()" << endl; }
      virtual ~virtderived() { cout << "~virtderived()" << endl; }
      virtual void show () { cout << typeid (*this).name() << endl; }
};

int main () {
   TRACE (nonbase *nb = new nonbase();)
   TRACE (nb->show();)
   TRACE (nonderived *nd = new nonderived ();)
   TRACE (nd->show();)
   TRACE (delete nb;)
   TRACE (nb = nd;)
   TRACE (nb->show();)
   TRACE (nd = static_cast<nonderived*> (nb);)
   TRACE (nd->show();)
   TRACE (delete nd;)

   TRACE (virtbase *vb = new virtbase();)
   TRACE (vb->show();)
   TRACE (virtderived *vd = new virtderived ();)
   TRACE (vd->show();)
   TRACE (delete vb;)
   TRACE (vb = vd;)
   TRACE (vb->show();)
   TRACE (vd = dynamic_cast<virtderived*> (vb);)
   TRACE (vd->show();)
   TRACE (delete vd;)
   TRACE (return 0;)
}

//TEST// grind="valgrind --leak-check=full --show-reachable=yes"
//TEST// $grind virtual 1>virtual.out 2>&1
//TEST// mkpspdf virtual.ps virtual.cpp* virtual.out*

