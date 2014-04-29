#include <getopt.h>
#include <cstdio>
#include <iostream>
#include "sevine.h"

using namespace std;
using namespace divine;

int main(int argc, char* argv[]) {  
  bool write_out=false;

  static const option longopts[]={
    {"writeout",0,0,'w'},
    {NULL,0,0,0}
  };
  char c;
  opterr = 0;
  while ((c = getopt_long(argc, argv, "w", longopts, NULL)) != -1) {
    switch (c) {
    case 'w': write_out = true; break;
    case '?': cerr <<"skipping unknown switch -"<<(char)optopt<<endl;break;
    }
  }

  if (argc<optind) //no parameter given
    {
      cerr << "No input file given!" << endl;
      return system_t::ERR_FILE_NOT_OPEN;
    }
  else
    {      
      system_t *sys=0;

      bool recognized = false;
      int file_opening=0;
      
      char * filename = argv[optind];
      int filename_length = strlen(filename);
      if (filename_length>=8 && strcmp(filename+filename_length-8,".probdve")==0)
	{
	  sys = new dve_prob_explicit_system_t(gerr);
	  file_opening = sys->read(argv[optind]);
	  recognized = true;
	}

      if (filename_length>=4 && strcmp(filename+filename_length-4,".dve")==0)
	{
	  sys = new dve_system_t(gerr);
	  file_opening = sys->read(argv[optind]);
	  recognized = true;
	}
	  
      if (filename_length>=2 && strcmp(filename+filename_length-2,".b")==0)
	{
	  sys = new bymoc_explicit_system_t(gerr);
	  file_opening = sys->read(argv[optind]);
	  recognized = true;
	}

      if (filename_length>=4 && strcmp(filename+filename_length-4,".bio")==0)
	{
	  sys = new affine_explicit_system_t(gerr);
	  file_opening = sys->read(argv[optind]);
	  recognized = true;
	}

      if (!recognized)
	{
	  cerr << "File not recognized. Supported extensions are .b, .dve, and .probdve" << endl;
	  return 1;
	}

      if (file_opening==system_t::ERR_FILE_NOT_OPEN)
	cerr << "File not opened" << endl;
      else if (file_opening)
	cerr << "Syntax error" << endl;
      else if (!write_out)
	{
	  cout << "OK" << endl;
	}
      else
	{
	  ostringstream out;
	  sys->write(out);
	  cerr<<out.str();
	}       
	
      return file_opening;
    }
}
