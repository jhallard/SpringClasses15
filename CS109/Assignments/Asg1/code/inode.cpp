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
  if(dirents.find(filename) == dirents.end()) {
    throw yshell_exn("remove arg not present in map");
  }
  dirents.erase(filename);
  DEBUGF ('i', filename);
}

inode& directory::mkdir (const string& dirname, inode_ptr parent) {
  
  if(dirents.find(dirname) != dirents.end()) {
    throw yshell_exn("directory already exists");
  }

  inode_ptr new_node = make_shared<inode>(DIR_INODE);
  dirents.insert({dirname, new_node});

  auto dir_ptr = directory_ptr_of(new_node->get_contents());
  dir_ptr->init(new_node, parent);

  return *new_node;
}

inode& directory::mkfile (const string& filename) {

  if(dirents.find(filename) != dirents.end()) {
    throw yshell_exn("file already exists");
  }

  inode_ptr new_node = make_shared<inode>(PLAIN_INODE);
  dirents.insert({filename, new_node});

  return *new_node;
}

// @func - init
// @info - initializes a new directory with the two links to itself
// and its parent directory.
// @note - This is only to be called explicitely on the root by
// the inode_state ctor, otherwise it will be called auto-lly
// be the directory::mkdir function when a sub-dir is made.
void directory::init(inode_ptr current, inode_ptr parent) {
  if(current == nullptr || parent == nullptr) {
    throw invalid_argument("directory init() arguments null");
  }
  dirents.insert({".", current});
  dirents.insert({"..", parent});
}

// @func - get_subdirent
// @info - given a string get a ptr to a subdirectory of this directory
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

// takes in a string and parses it to return a pointer to the
// appropriate inode that it is referncing
inode_ptr inode_state::get_inode_from_path(const string & path) {

  inode_ptr iter = get_parent_from_path(path);

  directory_ptr iter_dir = directory_ptr_of(iter->get_contents());

  wordvec parts = split(path, "/");

  iter = iter_dir->get_subdirent(parts.at(parts.size()-1));

  return iter;
}

// takes a string representing a complete path and returns a ptr
// to the parent of the inode represented by the path. Useful for
// the mkdir and makefile functions where a given path doesn't
// fully exist yet, only up until the parent.
inode_ptr inode_state::get_parent_from_path(const string & path) {
  inode_ptr iter = cwd;

  if(path.at(0) == '/') {
    iter = root;
  }

  directory_ptr iter_dir = directory_ptr_of(iter->get_contents());

  wordvec parts = split(path, "/");

  // we use this loop to follow all of the directories between the curr
  // and the parent of the final inode we want to point to. Throws 
  // yshell_exns if it discovers the path is invalid.
  for(auto & part : wordvec(parts.begin(), parts.end()-1)) {
    iter = iter_dir->get_subdirent(part);

    // subdirectory doesn't exist
    if(iter == nullptr) {
      throw yshell_exn("invalid path name.");
    }

    // a filename should only be the final part of the path, not
    // in the middle somewhere.
    if(iter->get_type() == PLAIN_INODE) {
      throw yshell_exn("invalid path name.");
    }

    iter_dir = directory_ptr_of(iter->get_contents());
  }

  return iter;
}


inode_ptr inode_state::get_cwd() const {
  return cwd;
}
void inode_state::set_cwd(inode & new_cwd) {
  *cwd = new_cwd;
}

inode_ptr inode_state::get_root() const {
  return root;
}



// === === === === //
// ==== OTHER ==== //
// === === === === //
ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}

