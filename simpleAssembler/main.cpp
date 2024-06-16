#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#define SC_MEMORY_SIZE 128

const std::unordered_map<std::string, int16_t> sc_supproted_commands
    = { { "NOP", 0x00 },   { "CPUINFO", 0x01 }, { "READ", 0x0A },
        { "WRITE", 0x0B }, { "LOAD", 0x14 },    { "STORE", 0x15 },
        { "ADD", 0x1E },   { "SUB", 0x1F },     { "DIVIDE", 0x20 },
        { "MUL", 0x21 },   { "JUMP", 0x28 },    { "JNEG", 0x29 },
        { "JZ", 0x2A },    { "HALT", 0x2B },    { "NOT", 0x33 },
        { "AND", 0x34 },   { "OR", 0x35 },      { "XOR", 0x36 },
        { "JNS", 0x37 },   { "JC", 0x38 },      { "JNC", 0x39 },
        { "JP", 0x3A },    { "JNP", 0x3B },     { "CHL", 0x3C },
        { "SHR", 0x3D },   { "RCL", 0x3E },     { "RCR", 0x3F },
        { "NEG", 0x40 },   { "ADDC", 0x41 },    { "SUBC", 0x42 },
        { "LOGLC", 0x43 }, { "LOGRC", 0x44 },   { "RCCL", 0x45 },
        { "RCCR", 0x46 },  { "MOVA", 0x47 },    { "MOVR", 0x48 },
        { "MOVCA", 0x49 }, { "MOVCR", 0x4A },   { "ADDC", 0x4B },
        { "SUBC", 0x4C },  { "=", -1 } };

auto sc_memory_dump = std::vector<int16_t> (SC_MEMORY_SIZE);

void parse_line (const std::string &line, const int line_numb);

void encode_line (int memory_dump_place, const std::string &command_key,
                  int16_t operand);

int16_t create_sc_command (int16_t sign, int16_t command, int16_t operand);

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      std::cerr << "Error - Argument should be a path to source code file."
                << std::endl;
      return -1;
    }
  if (argc > 3)
    {
      std::cerr << "Warning - Arguments after" << argv[2]
                << " would be ignored." << std::endl;
    }

  std::string input_filename = argv[1];
  std::ifstream input_file (input_filename);

  if (!input_file.is_open ())
    {
      std::cerr << "Error - Input file is not available.\nPath: "
                << input_filename << std::endl;
      return -1;
    }

  std::string line;
  int line_numb = 1;

  while (getline (input_file, line))
    {
      if (size_t comment = line.find (';'); comment != std::string::npos)
        {
          line = line.substr (0, comment);
        }
      if (!line.empty ())
        {
          parse_line (line, line_numb);
        }
      line_numb++;
    }

  std::string output_filename = argc >= 3 ? argv[2] : "out.o";
  std::ofstream output_file (output_filename, std::ios::binary);

  if (!output_file)
    {
      std::cerr << "Error - Output file is not available.\nPath: "
                << output_filename << std::endl;
      return 1;
    }

  for (int i = 0; i < SC_MEMORY_SIZE; i++)
    {
      output_file.write (reinterpret_cast<const char *> (&sc_memory_dump[i]),
                         sizeof (sc_memory_dump[0]));
    }
  output_file.close ();
  input_file.close ();
}

void
parse_line (const std::string &line, const int line_numb)
{
  std::stringstream basic_stringstream (line);
  std::vector<std::string> tokens;
  std::string token;

  while (getline (basic_stringstream, token, ' '))
    {
      if (!token.empty ())
        {
          tokens.push_back (token);
        }
    }

  if (tokens.size () != 3)
    {
      std::cerr << "Error - Invalid command at line " << line_numb << "."
                << std::endl
                << line << std::endl;
      exit (-1);
    }

  const int memory_dump_place = stoi (tokens[0]);
  const std::string command = tokens[1];
  const int16_t operand = stoi (tokens[2]);

  encode_line (memory_dump_place, command, operand);
}

void
encode_line (int memory_dump_place, const std::string &command_key,
             int16_t operand)
{
  if (sc_supproted_commands.find (command_key) == sc_supproted_commands.end ())
    {
      std::cerr << "Error - \"" << command_key << "\" is unknown command."
                << std::endl;
      exit (-1);
    }

  if (command_key == "=")
    {
      sc_memory_dump[memory_dump_place] = operand;
    }
  else
    {
      const int16_t command_code = sc_supproted_commands.at (command_key);
      sc_memory_dump[memory_dump_place]
          = create_sc_command (0, command_code, operand);
    }
}

int16_t
create_sc_command (int16_t sign, int16_t command, int16_t operand)
{
  int16_t simple_computer_command = sign << 14;
  command = command << 7;

  simple_computer_command |= command;
  simple_computer_command |= operand;

  return simple_computer_command;
}
