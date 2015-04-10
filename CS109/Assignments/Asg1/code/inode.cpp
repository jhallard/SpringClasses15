// $Id: inode.cpp,v 1.12 2014-07-03 13:29:57-07 - - $

#include <iostream>
#include <stdexcept>

using namespace std;

#include "debug.h"
#include "inode.h"





// ============ === === ============ //
// ============= INODE ============= //
// ============ === === ============ //

int inode::next_inode_nr {1};

inode::inode(inode_t init_type):
   inode_nr (next_inode_nr++), type (init_type)
{
   switch (type) {
      case PLAIN_INODE:
           contents = make_shared<plain_file>();
           break;
      case DIR_INODE:
           contents = make_shared<directory>();
           break;
   }
   DEBUGF ('i', "inode " << inode_nr << ", type = " << type);
}

int inode::get_inode_nr() const {
   DEBUGF ('i', "inode = " << inode_nr);
   return inode_nr;
}

// ---------------- // custom functions // ---------------- // 

file_base_ptr inode::get_contents() const {
  return contents;
}

inode_t inode::get_type() const {
  return type;
}





// =========== === === =========== //
// ============ PLAIN ============ //
// =========== === === =========== //
plain_file_ptr plain_file_ptr_of (file_base_ptr ptr) {
   plain_file_ptr pfptr = dynamic_pointer_cast<plain_file> (ptr);
   if (pfptr == nullptr) throw invalid_argument ("plain_file_ptr_of");
   return pfptr;
}

directory_ptr directory_ptr_of (file_base_ptr ptr) {
   directory_ptr dirptr = dynamic_pointer_cast<directory> (ptr);
   if (dirptr == nullptr) throw invalid_argument ("directory_ptr_of");
   return dirptr;
}


size_t plain_file::size() const {
   size_t size {0};
   DEBUGF ('i', "size = " << size);
   return size;
}

const wordvec& plain_file::readfile() const {
   DEBUGF ('i', data);
   return data;
}

void plain_file::writefile (const wordvec& words) {
   DEBUGF ('i', words);
}






// ============ === === ============ //
// ============= DIREC ============= //
// ============ === === ============ //

size_t directory::size() const {
   size_t size {0};
   DEBUGF ('i', "size = " << size);
   return size;
}

void directory::remove (const string& filename) {
   DEBUGF ('i', filename);
}

inode& directory::mkdir (const string& dirname, inode_ptr parent) {
  
  if(dirents.find(dirname) != dirents.end()) {
    throw new yshell_exn("directory already exists");
  }
 
  inode_ptr new_node = make_shared<inode>(DIR_INODE);
  dirents.insert({dirname, new_node});
  directory_ptr new_dir = directory_ptr_of(new_node->get_contents());
  new_dir->init(parent, new_node);

  return *new_node;
}

inode& directory::mkfile (const string& filename) {
  if(dirents.find(filename) != dirents.end()) {
    throw new yshell_exn("file already exists");
  }
  inode_ptr new_node = make_shared<inode>(PLAIN_INODE);
  dirents.insert({filename, new_node});

  return *new_node;
}

void directory::init(inode_ptr current, inode_ptr parent) {
  if(current == nullptr || parent == nullptr) {
    throw invalid_argument("directory init() arguments null");
  }
  dirents.insert({".", current});
  dirents.insert({"..", parent});
}

inode_ptr directory::get_subdirent(string fn) const {
  if(dirents.find(fn) == dirents.end()) {
    return nullptr;
  }
  return dirents.at(fn);
}





// ========== === === ========== //
// =========== STATE =========== //
// ========== === === ========== //

inode_state::inode_state() {

  // initialize the root inode_ptr
  root = make_shared<inode>(DIR_INODE);
  directory_ptr root_dir = directory_ptr_of(root->get_contents());

  // set the '.' and '..' to both point to itself.
  root_dir->init(root, root);

  // since we are just starting, set the cwd to point to the root
  cwd = root;

  DEBUGF ('i', "root = " << root << ", cwd = " << cwd
          << ", prompt = \"" << prompt << "\"");
}





// === === === === //
// ==== OTHER ==== //
// === === === === //
ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}

