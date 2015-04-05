// $Id: node.cpp,v 1.6 2013-08-13 15:55:43-07 - - $

#include <iostream>
using namespace std;

class foo {
public:
   foo() { cout << "foo()" << endl; }
};

class node {
public:
   foo f;
   node *p;
   node *n;
public:
   node():p(0),n(0){}
};

int main() {
   node *p = new node();
   cout << p->p << p->n << endl;
}

