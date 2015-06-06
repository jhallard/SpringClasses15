#include "util.h"

using namespace std;

string read_file(const string & fn) {

	std::ifstream infile (fn.c_str(), std::ifstream::binary);

	if(!infile) {
		throw runtime_error("error : " + fn + " : is not a valid" + \
			" filename\n");
	}
	// get size of file
	infile.seekg (0,infile.end);
	long size = infile.tellg();
	infile.seekg (0);

	// allocate memory for file content
	char* buffer = new char[size];

	// read content of infile
	infile.read (buffer,size);

	string ret(buffer);

	delete [] buffer;
	infile.close();

	return ret;
}

bool write_file(const string & fn, const string & data) {
   std::ofstream outfile (fn.c_str() ,std::ofstream::binary);

   if(!outfile) return false;

   outfile.write(data.c_str(), data.size());
   outfile.close();
   return true;
}

vector<string> split (const string& line, const string& delimiters) {
   vector<string> words;
   size_t end = 0;

   // Loop over the string, splitting out words, and for each word
   // thus found, append it to the output wordvec.
   for (;;) {
      size_t start = line.find_first_not_of (delimiters, end);
      if (start == string::npos) break;
      end = line.find_first_of (delimiters, start);
      words.push_back (line.substr (start, end - start));
   }
   return words;
}