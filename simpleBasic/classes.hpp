#ifndef SIMPLE_BASIC_CLASSES_H
#define SIMPLE_BASIC_CLASSES_H

#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

const int ram_size = 128;

struct AssemblyCommand
{
  int ram_address;
  std::string command;
  int operand;
  int tag;
  bool is_resolved = true;
};

class VariableTable
{
public:
  int get_address (std::string name);
  bool has (std::string name);
  void define (std::string name, int address);

private:
  std::unordered_map<std::string, int> variables;
};

class Token
{
public:
  enum Types
  {
    NUMBER = '0',
    VAR_NAME,
    REM,
    INPUT,
    PRINT,
    GOTO,
    IF,
    LET,
    END,
    OP_PLUS = '+',
    OP_MINUS = '-',
    OP_MULT = '*',
    OP_DIVIDE = '/',
    OP_EQUAL = '=',
    OP_POWER = '^',
    OP_GT = '>',
    OP_LESS = '<',
    OPEN_BRACKET = '(',
    CLOSING_BRACKET = ')',
    EXIT_FLAG = 'q',
    EXPRESSION_END_FLAG = '\n',
    UNKNOWN = -1
  };

  int value;

  Token (Types t, int val);
  Token (Types t);
  Token (Types t, std::string n);

  static const std::unordered_map<Types, std::string> token_map;

  std::string string_value;
  Types type;

  static std::string get_token_name (Types type);
  static Types get_type_by_name (std::string name);

  bool is_operator () const;

  int precedence () const;

  bool
  operator== (const Token &other) const
  {
    return this->type == other.type;
  }
};

class TokenStream
{
public:
  TokenStream (std::istream &str);

  Token get_token ();
  void push_back (Token t);
  void ignore ();

private:
  std::istream stream;

  Token::Types previous_type;

  Token buffer;

  bool full;
};

class BasicCompiler
{
public:
  BasicCompiler (std::istream &in_stream, std::ostream &out_stream);

  int compile ();

private:
  int statement ();         // Handle REM, INPUT
  int var_declaration ();   // Handle LET
  int if_statement ();      // Handle IF
  void parse_expression (); // Handle expression "# [=><] 0"
  int global_statement ();  // Memory address -> statement

  int rem ();
  int input ();
  int output ();
  int go ();
  int end ();

  void create_variable (std::string name);
  void create_const_variable (std::string name, int value);
  void load_variable (std::string name);
  void write_command (std::string command, int operand, int tag = -1);

  void update_ram_address ();

  VariableTable variable_table;
  TokenStream token_stream;

  std::istream &in_stream;
  std::ostream &out_stream;

  std::vector<bool> used_memory;
  std::vector<int> tags;
  std::vector<AssemblyCommand> commands;

  std::string last_variable = "";

  int command_counter = 0;
  int current_address = 0;
  int variables_address = ram_size - 1;
};

#endif // SIMPLE_BASIC_CLASSES_H
