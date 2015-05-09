// $Id: linknode.cpp,v 1.5 2015-04-23 16:37:58-07 - - $

#include <iostream>
using namespace std;

struct node;
struct link {
   node* next {};
   node* prev {};
};
struct node: link {
   int value {};
};

int main() {
   node* nn = new node();
   link* ll = nn;
   nn = static_cast<node*> (ll);
   cout << "nn = " << nn << ", sizeof = " << sizeof (node) << endl;
   cout << "ll = " << ll << ", sizeof = " << sizeof (link) << endl;
}

//TEST// linknode >linknode.out 2>&1
//TEST// mkpspdf linknode.ps linknode.cpp* linknode.out

