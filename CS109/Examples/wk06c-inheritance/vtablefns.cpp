// $Id: vtablefns.cpp,v 1.26 2015-02-10 17:55:14-08 - - $

// Illustrate inheritance and virtual function tables.
// Print out the name of the function actually called.

#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;
#define TRACE(STMT) cout << "TRACE (" << #STMT << ")" << endl; STMT

string next() {
   static string name = "(0)";
   ++name[1];
   return name;
}

struct AAA {
   string aname;
   AAA (const AAA&) = delete;
   AAA& operator= (const AAA&) = delete;
   AAA(): aname(next()) { show ("AAA::AAA()" + aname) << endl; }
   virtual ~AAA() { show ("AAA::~AAA()" + aname) << endl; }
   virtual string f () const { return "AAA::f()" + aname; }
   virtual string g () const { return "AAA::g()" + aname; }
   ostream& show (const string& str) const;
};

struct BBB: public AAA {
   string bname;
   BBB(): bname(next()) { show ("BBB::BBB()" + aname + bname) << endl; }
   virtual ~BBB() { show ("BBB::~BBB()" + aname + bname) << endl; }
   virtual string f () const { return "BBB::f()" + aname + bname; }
};

struct CCC: public AAA {
   string cname;
   CCC(): cname(next()) { show ("CCC::CCC()" + aname + cname) << endl; }
   virtual ~CCC() { show ("CCC::~CCC()" + aname + cname) << endl; }
   virtual string g () const { return "CCC::g()" + aname + cname; }
};

ostream& AAA::show (const string& str) const {
   cout << this << "->" << str << ": typeid = \""
        << typeid (*this).name () << "\""; return cout;
   return cout;
}

void tester (const AAA& p) {
   p.show ("tester") << ": f = " << p.f() 
        << ", g = " << p.g() << endl << "." << endl;
}

int main() {
   TRACE (AAA a; tester (a);)
   TRACE (BBB b; tester (b);)
   TRACE (CCC c; tester (c);)
   TRACE (return 0;)
}

//TEST// grind="valgrind --leak-check=full --show-reachable=yes"
//TEST// $grind vtablefns >vtablefns.out 2>&1
//TEST// mkpspdf vtablefns.ps vtablefns.cpp* vtablefns.out*

