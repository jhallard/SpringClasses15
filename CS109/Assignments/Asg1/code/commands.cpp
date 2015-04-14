// $Id: commands.cpp,v 1.11 2014-06-11 13:49:31-07 - - $

#include "commands.h"
#include "debug.h"

commands::commands(): map ({
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
   {"rmr"    , fn_rmr    },
}){}

command_fn commands::at (const string& cmd) {
   // Note: value_type is pair<const key_type, mapped_type>
   // So: iterator->first is key_type (string)
   // So: iterator->second is mapped_type (command_fn)
   command_map::const_iterator result = map.find (cmd);
   if (result == map.end()) {
      throw yshell_exn (cmd + ": no such function");
   }
   return result->second;
}


void fn_cat (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   if(words.size() <= 1) {
      throw yshell_exn("cat: requires 1 or more filename args");
   }

   // go through all arguments and attempt to print them out
   for(auto & fn : wordvec(words.begin()+1, words.end())) {

      inode_ptr node = state.get_inode_from_path(fn);
      if(node->get_type() == DIR_INODE) {
         throw yshell_exn("cat: path-name leads to directory");
      }

      auto file_ptr = plain_file_ptr_of(node->get_contents());
      stringstream ss; ss << "";
      file_ptr->print_file(ss);

      std::cout << ss.str() << "\n";
   }
}

void fn_cd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   inode_ptr node = nullptr;

   if(words.size() != 2) {
      node = state.get_inode_from_path("/");
   }

   node = state.get_inode_from_path(words.at(1));

   if(node->get_type() == PLAIN_INODE) {
      throw yshell_exn("cd: path-name leads to file");
   }
   state.set_cwd(node);
}

void fn_echo (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   if(words.size() <= 1) {
      cout << "\n";
      return;
   }

   stringstream ss;
   for(auto & word : wordvec(words.begin()+1, words.end())) {
       ss << word << " ";
   }

   cout << ss.str() << endl;
}

bool is_number(const string & str) {
   for(auto x : str) {
      if(!isdigit(x)) {
         return false;
      }
   }
   return true;
}

void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   if(words.size() <= 1) {   
      exit_status::set (0);
   }
   else if(is_number(words[1])) {
      int res = atoi(words[1].c_str());
      exit_status::set (res);
   }
   else {
      exit_status::set (127);
   }
   throw ysh_exit_exn();
}

void fn_ls (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   stringstream ss; ss << "";

   // catch for the case with no arguments, call on cwd
   if(words.size() <= 1) {
      ss << state.get_cwd()->get_name() << ":" << "\n";
      state.get_cwd()->print_directory(ss);
      cout << ss.str() << "\n";
      return;
   }

   // else go through each argument and print out the contents
   for(auto & fn : wordvec(words.begin()+1, words.end())) {
      inode_ptr node = state.get_inode_from_path(fn);

      if(node->get_type() == DIR_INODE) {
         ss << fn << ":" << "\n";
         node->print_directory(ss);
      }
      else {
         node->print_description(ss, fn);
      }
   }
      cout << ss.str() << "\n";
}


void fn_lsr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   deque<dirent_pair> r_stack;

   stringstream ss; ss << "";

   // catch for the case with no arguments, call on cwd
   if(words.size() <= 1) {
      string temp = ".";
      state.get_cwd()->print_recursive(ss, r_stack, temp);
      cout << ss.str() << "\n";
      return;
   }

   for(auto & fn : wordvec(words.begin()+1, words.end())) {
      inode_ptr node = state.get_inode_from_path(fn);

      if(node->get_type() == DIR_INODE) {
         node->print_recursive(ss, r_stack, fn);
         r_stack.clear();
      }
      else {
         node->print_description(ss, fn);
      }
   }
      cout << ss.str() << "\n";
}



void fn_make (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   if(words.size() <= 1) {
      throw yshell_exn("make: requires a filename argument");
   }

   string new_fn = split(words[1], "/").back();
   
   inode_ptr parent = state.get_parent_from_path(words[1]);
   auto parent_dir = directory_ptr_of(parent->get_contents());

   parent_dir->mkfile(new_fn);

   // if there are words to insert into the file
   if(words.size() > 2) {
      auto new_node = parent_dir->get_subdirent(new_fn);
      auto new_file = plain_file_ptr_of(new_node->get_contents());
      new_file->writefile(wordvec(words.begin()+2, words.end()));
   }

}

void fn_mkdir (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   if(words.size() <= 1) {
      throw yshell_exn("mkdir: mkdir needs a dir-name argument");
   }

   wordvec parts = split(words[1], "/");

   if(!parts.size()) {
      throw yshell_exn("mkdir: /: Invalid directory name");
   }
   string new_dirname = parts.at(parts.size()-1);

   inode_ptr parent = state.get_parent_from_path(words[1]);
   auto parent_dir = directory_ptr_of(parent->get_contents());
   parent_dir->mkdir(new_dirname, parent);
}

void fn_prompt (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   if(words.size() <= 1) {
      state.set_prompt(" ");
      return;
   }

   stringstream ss; ss << "";

   for(auto & str : wordvec(words.begin()+1, words.end())) {
      ss << str << " ";
   }

   state.set_prompt(ss.str());

   return;
}

void fn_pwd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   stringstream ss;

   wordvec path_parts = {""};

   inode_ptr walker = state.get_cwd();

   // if we are already at the root there is no work to do
   if(walker->get_name() == state.get_root()->get_name()) {
      cout << "/" << endl;
      return;
   }

   while(walker->get_name() != state.get_root()->get_name()) {
      path_parts.push_back(walker->get_name());
      path_parts.push_back("/");

      auto contents = directory_ptr_of(walker->get_contents());
      walker = contents->get_subdirent("..");
   }

   // in case we were already at the root
   if(!path_parts.size()) {
      cout << "/" << endl;
      return;
   }

   reverse(path_parts.begin(), path_parts.end());

   for(auto & part : path_parts) {
      ss << part;
   }
   std::cout << ss.str() << endl;
}


// =======================================================
// ====================== @BUG ===========================
// =======================================================
// There is a bug in this function, technically if you can
// be in an empty directory, so you can call 'rm .' and it
// should delete the cwd and make the new cwd the parent.
// This works if you call 'rm /path/to/cwd' but not with
// 'rm .' for some reason.
// =======================================================
void fn_rm (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   if(words.size() != 2) {
      throw yshell_exn("rm: requires single file or dir. name");
   }

   // get the end of the path
   string tbd = split(words[1], "/").back();

   // get the node and its parent
   auto node = state.get_inode_from_path(words.at(1));
   auto parent = state.get_parent_from_path(words.at(1));

   bool deleting_cwd = false; // flag for if we are del. cws

   // make sure we don't delete a filled directory
   if(node->get_type() == DIR_INODE && 
   directory_ptr_of(node->get_contents())->to_vector().size()>2)
   {
      throw yshell_exn("rm: directory non-empty, cannot remove");
   }

   // if the directory to be deleted is the one we are in
   if(node->get_inode_nr() == state.get_cwd()->get_inode_nr()){
      deleting_cwd = true;
   }

   auto dir_ptr = directory_ptr_of(parent->get_contents());
   dir_ptr->remove(node->get_name());
   node = nullptr;

   if(deleting_cwd)
      state.set_cwd(parent);
}

void fn_rmr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   if(words.size() != 2) {
      throw yshell_exn("rmr: takes a single directory name argument");
   }

   if(words[1] == "/") {
      throw yshell_exn("rmr: /: Cannot delete root directory");
   }

   // get the end of the path
   string tbd = split(words[1], "/").back();

   auto parent = state.get_parent_from_path(words[1]);
   auto node = state.get_inode_from_path(words[1]);

   state.free_recursive(node);

   auto dir_ptr = directory_ptr_of(parent->get_contents());
   dir_ptr->remove(node->get_name());
   node = nullptr;

}

int exit_status_message() {
   int exit_status = exit_status::get();
   cout << execname() << ": exit(" << exit_status << ")" << endl;
   return exit_status;
}

