#include <fstream>
#include <iostream>
#include <string>

#include "classes.hpp"

int
main (int argc, char *argv[])
{
  if (argc < 3)
    {
      std::cerr << "Error - argument should be a path to source code file and "
                   "output file."
                << std::endl;
      return -1;
    }

  std::vector<std::string> all_arguments;
  all_arguments.assign (argv + 1, argv + argc);

  std::ifstream input_file (all_arguments[0]);
  std::ofstream output_file (all_arguments[1]);
  if (!input_file.is_open ())
    {
      std::cerr << "Error - Source code file is not available." << std::endl;
      return -1;
    }
  if (!output_file.is_open ())
    {
      std::cerr << "Error - Output file is not available." << std::endl;
      return -1;
    }

  BasicCompiler compiler (input_file, output_file);
  compiler.compile ();
  output_file.close ();
  input_file.close ();
}
