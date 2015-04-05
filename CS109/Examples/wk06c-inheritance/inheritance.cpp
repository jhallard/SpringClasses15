// $Id: inheritance.cpp,v 1.29 2015-02-10 17:43:42-08 - - $

//
// Example using objects, with a base object and two derived objects.
//

#include <iostream>
#include <typeinfo>
#include <memory>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////////
// class object
/////////////////////////////////////////////////////////////////

class object {
   private:
      object (const object&) = delete;
      object& operator= (const object&) = delete;
      static unsigned next_id;;
   protected:
      const unsigned id;
      object(); // abstract class, so only derived can used ctor.
   public:
      virtual ~object(); // must be virtual
      virtual void print (ostream&) const;
};

ostream& operator<< (ostream& out, const object& obj) {
   obj.print (out);
   return out;
}

unsigned object::next_id = 0;

object::object(): id(++next_id) {
   cout << "Create: " << *this << endl;
}

object::~object() {
   cout << "Delete: " << *this << endl;
}

void object::print (ostream& out) const {
   out << "[" << static_cast<const void *const> (this) << "->"
       << typeid(*this).name() << "] id=" << id << ": ";
}


/////////////////////////////////////////////////////////////////
// class rectangle 
/////////////////////////////////////////////////////////////////

class rectangle: public object {
   private:
      size_t width;
      size_t height;
   public:
      rectangle (size_t width = 0, size_t height = 0);
      virtual ~rectangle();
      virtual void print (ostream&) const;
};

rectangle::rectangle (size_t width, size_t height):
            width(width), height(height) {
   cout << "Create: " << *this << endl;
}

rectangle::~rectangle() {
   cout << "Delete: " << *this << endl;
}

void rectangle::print (ostream& out) const {
   this->object::print (out);
   out << "rectangle: width=" << width << ", height=" << height;
}

/////////////////////////////////////////////////////////////////
// class circle 
/////////////////////////////////////////////////////////////////

class circle: public object {
   private:
      size_t diameter;
   public:
      circle (size_t diameter = 0);
      virtual ~circle();
      virtual void print (ostream&) const;
};

circle::circle (size_t diameter): diameter(diameter) {
   cout << "Create: " << *this << endl;
}

circle::~circle() {
   cout << "Delete: " << *this << endl;
}

void circle::print (ostream& out) const {
   this->object::print (out);
   out << "circle: " << "diameter=" << diameter;
}



/////////////////////////////////////////////////////////////////
// main
/////////////////////////////////////////////////////////////////

int main() {
   cout << "sizeof (object) = " << sizeof (object) << endl;
   cout << "sizeof (rectangle) = " << sizeof (rectangle) << endl;
   cout << "sizeof (circle) = " << sizeof (circle) << endl;

   vector<shared_ptr<object>> vec;
   // ERROR: v.push_back (new object());
   // ERROR: object o;
   vec.push_back (shared_ptr<object> (new circle ()));
   vec.push_back (shared_ptr<object> (new circle (10)));
   vec.push_back (shared_ptr<object> (new rectangle()));
   vec.push_back (shared_ptr<object> (new rectangle (5)));
   vec.push_back (shared_ptr<object> (new rectangle (8)));
   cout << endl;

   for (const auto& ptr: vec) {
      cout << "Object: " << *ptr << endl;
   }
   cout << endl;

   cout << "return 0" << endl;
   return 0;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes \
//TEST//       inheritance >inheritance.out 2>&1
//TEST// mkpspdf inheritance.ps inheritance.cpp* inheritance.out*
*/

