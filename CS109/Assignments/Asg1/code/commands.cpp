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
}

void fn_cd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_echo (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   throw ysh_exit_exn();
}

void fn_ls (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_lsr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
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

   ss << "/";
   inode_ptr walker = state.get_cwd();

   while(walker->get_name() != state.get_root()->get_name()) {
      ss << walker->get_name() << "/";
      auto contents = directory_ptr_of(walker->get_contents());
      walker = contents->get_subdirent("..");
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

