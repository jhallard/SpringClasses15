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
      throw yshell_exn("requires 1 or more filename arguments");
   }

   for(auto & fn : wordvec(words.begin()+1, words.end())) {

      inode_ptr node = state.get_inode_from_path(fn);

      if(node->get_type() == DIR_INODE) {
         throw yshell_exn("path-name leads to directory, not file");
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

   if(words.size() <= 1) {
      throw yshell_exn("needs a dirname argument");
   }

   inode_ptr node = state.get_inode_from_path(words.at(1));

   if(node->get_type() == PLAIN_INODE) {
      throw yshell_exn("path-name leads to file, not directory");
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

void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
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
      // r_stack.push_back({".", state.get_cwd()});
      // ss << state.get_cwd()->get_name() << ":" << "\n";
      state.get_cwd()->print_recursive(ss, r_stack);
      cout << ss.str() << "\n";
      return;
   }

   for(auto & fn : wordvec(words.begin()+1, words.end())) {

      inode_ptr node = state.get_inode_from_path(fn);

      if(node->get_type() == DIR_INODE) {
         // r_stack.push_back({"fn", node});
         // ss << fn << ":" << "\n";
         node->print_recursive(ss, r_stack);
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
      throw yshell_exn("make needs a filename argument");
   }

   wordvec parts = split(words[1], "/");
   string new_fn = parts.at(parts.size()-1);
   
   inode_ptr parent = state.get_parent_from_path(words[1]);
   auto parent_dir = directory_ptr_of(parent->get_contents());

   parent_dir->mkfile(new_fn);

   // if there are words to insert into the file
   if(words.size() > 2) {
      auto new_node = parent_dir->get_subdirent(new_fn);
      auto new_file = plain_file_ptr_of(new_node->get_contents());

      // the first two strings are the command and filename,
      // omit those from the file text.
      new_file->writefile(wordvec(words.begin()+2, words.end()));
   }

}

void fn_mkdir (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   if(words.size() <= 1) {
      throw yshell_exn("mkdir needs a dirname argument");
   }

   wordvec parts = split(words[1], "/");
   string new_dirname = parts.at(parts.size()-1);

   inode_ptr parent = state.get_parent_from_path(words[1]);
   auto parent_dir = directory_ptr_of(parent->get_contents());
   parent_dir->mkdir(new_dirname, parent);
}

void fn_prompt (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_pwd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);

   stringstream ss;

   wordvec path_parts = {"/"};

   inode_ptr walker = state.get_cwd();

   while(walker->get_name() != state.get_root()->get_name()) {
      path_parts.push_back(walker->get_name());
      path_parts.push_back("/");

      auto contents = directory_ptr_of(walker->get_contents());
      walker = contents->get_subdirent("..");
   }

   reverse(path_parts.begin(), path_parts.end());

   for(auto & part : path_parts) {
      ss << part;
   }
   std::cout << ss.str() << endl;
}

void fn_rm (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_rmr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

int exit_status_message() {
   int exit_status = exit_status::get();
   cout << execname() << ": exit(" << exit_status << ")" << endl;
   return exit_status;
}

