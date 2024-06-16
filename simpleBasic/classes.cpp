#include "classes.hpp"

#include <iostream>
#include <stack>

const std::unordered_map<Token::Types, std::string> Token::token_map = {
  { Token::Types::VAR_NAME, "VAR_NAME" }, { Token::Types::REM, "REM" },
  { Token::Types::INPUT, "INPUT" },       { Token::Types::PRINT, "PRINT" },
  { Token::Types::GOTO, "GOTO" },         { Token::Types::IF, "IF" },
  { Token::Types::LET, "LET" },           { Token::Types::END, "END" }
};

Token::Token (Types t, int val) : type (t), value (val){};
Token::Token (Types t) : type (t), value (0){};
Token::Token (Types t, std::string n)
    : type (t), string_value (n), value (0){};

Token::Types
Token::get_type_by_name (std::string name)
{
  for (const auto &pair : token_map)
    {
      if (pair.second == name)
        {
          return pair.first;
        }
    }
  return Token::Types::UNKNOWN;
}

std::string
Token::get_token_name (Token::Types type)
{
  auto it = Token::token_map.find (type);
  if (it != Token::token_map.end ())
    {
      return it->second;
    }
  else
    {
      return "Unknown";
    }
}

bool
Token::is_operator () const
{
  return type == OP_PLUS || type == OP_MINUS || type == OP_MULT
         || type == OP_DIVIDE;
}

int
Token::precedence () const
{
  switch (type)
    {
    case OPEN_BRACKET:
    case CLOSING_BRACKET:
      return -1;
    case OP_MULT:
    case OP_DIVIDE:
      return 2;
    case OP_PLUS:
    case OP_MINUS:
      return 1;
    default:
      return 0;
    }
}

void
VariableTable::define (std::string name, int address)
{
  variables[name] = address;
}

int
VariableTable::get_address (std::string name)
{
  return variables[name];
}

bool
VariableTable::has (std::string name)
{
  return variables.find (name) != variables.end ();
}

TokenStream::TokenStream (std::istream &str)
    : stream (str.rdbuf ()), previous_type (Token::UNKNOWN), full (false),
      buffer (Token::EXIT_FLAG){};

Token
TokenStream::get_token ()
{
  if (full)
    {
      full = false;
      return buffer;
    }

  char ch;
  while (stream.get (ch))
    {
      if (ch != ' ' && ch != '\t' && ch != '\r')
        {
          break;
        }
    }

  if (stream.eof () || !stream)
    {
      return Token (Token::EXIT_FLAG);
    }

  switch (ch)
    {
    case '\n':
      return Token (Token::EXPRESSION_END_FLAG);
    case '(':
    case ')':
    case '=':
    case '+':
    case '-':
    case '>':
    case '<':
    case '*':
    case '/':
      return Token (static_cast<Token::Types> (ch));
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      {
        int val;
        stream.putback (ch);
        stream >> val;
        return Token (Token::Types::NUMBER, val);
      }
    default:
      if (isalpha (ch))
        {
          std::string str;
          stream.putback (ch);
          while (stream.get (ch) && (isalpha (ch) || isdigit (ch)))
            {
              {
                str += ch;
              }
            }

          stream.putback (ch);

          Token::Types token_type = Token::get_type_by_name (str);
          if (token_type != Token::UNKNOWN)
            {
              previous_type = token_type;
              return Token (token_type);
            }
          switch (previous_type)
            {
            case Token::INPUT:
            case Token::PRINT:
            case Token::LET:
            case Token::IF:
              return Token (Token::Types::VAR_NAME, str);
            }
          return Token (Token::UNKNOWN, str);
        }
      else
        {
          throw std::runtime_error ("Bad token");
        }
    }
}

void
TokenStream::push_back (Token t)
{
  if (full)
    {
      throw std::runtime_error ("push_back() -> full buffer");
    }
  buffer = t;
  full = true;
}

void
TokenStream::ignore ()
{
  Token token = get_token ();
  while (token.type != Token::EXPRESSION_END_FLAG
         && token.type != Token::EXIT_FLAG)
    {
      token = get_token ();
    }
}

BasicCompiler::BasicCompiler (std::istream &input_st, std::ostream &output_st)
    : in_stream (input_st), out_stream (output_st), token_stream (input_st),
      used_memory (ram_size, false), tags (ram_size, 0), last_variable (""),
      command_counter (0), current_address (0),
      variables_address (ram_size - 1)
{
}

void
BasicCompiler::parse_expression ()
{
  Token token = Token (Token::EXPRESSION_END_FLAG);
  std::stack<Token> operator_stack;
  std::vector<Token> output_queue;

  // Dijkstra's algorithm
  while ((token = token_stream.get_token ()).type
             != Token::Types::EXPRESSION_END_FLAG
         && token.type != Token::Types::EXIT_FLAG)
    {
      if (token.type == Token::Types::VAR_NAME)
        {
          output_queue.push_back (token);
        }
      else if (token.is_operator ())
        {
          while (!operator_stack.empty ()
                 && operator_stack.top ().precedence () > token.precedence ())
            {
              output_queue.push_back (operator_stack.top ());
              operator_stack.pop ();
            }

          operator_stack.push (token);
        }
      else if (token.type == Token::Types::OPEN_BRACKET)
        {
          operator_stack.push (token);
        }
      else if (token.type == Token::Types::CLOSING_BRACKET)
        {
          while (!operator_stack.empty ()
                 && operator_stack.top ().type != Token::Types::OPEN_BRACKET)
            {
              output_queue.push_back (operator_stack.top ());
              operator_stack.pop ();
            }

          if (!operator_stack.empty ()
              && operator_stack.top ().type == Token::Types::OPEN_BRACKET)
            {
              operator_stack.pop ();
            }
          else
            {
              throw std::runtime_error ("Mismatched parentheses");
            }
        }
      else
        {
          throw std::runtime_error ("Unexpected token in expression");
        }
    }

  while (!operator_stack.empty ())
    {
      output_queue.push_back (operator_stack.top ());
      operator_stack.pop ();
    }

  std::stack<Token> result = std::stack<Token> ();
  for (const auto &token : output_queue)
    {
      if (token.is_operator ())
        {
          auto op2 = result.top ();
          result.pop ();
          auto op1 = result.top ();
          result.pop ();

          load_variable (op1.string_value);

          if (token.type == Token::OP_PLUS)
            {
              write_command ("ADD",
                             variable_table.get_address (op2.string_value));
            }
          if (token.type == Token::OP_MINUS)
            {
              write_command ("SUB",
                             variable_table.get_address (op2.string_value));
            }
          if (token.type == Token::OP_MULT)
            {
              write_command ("MUL",
                             variable_table.get_address (op2.string_value));
            }
          if (token.type == Token::OP_DIVIDE)
            {
              write_command ("DIV",
                             variable_table.get_address (op2.string_value));
            }

          int address = variables_address - 1;

          std::string name = "tmp" + std::to_string (address);

          variable_table.define (name, address);
          result.push (Token (Token::VAR_NAME, name));
          write_command ("STORE", address);

          variables_address--;
        }
      else
        {
          result.push (token);
        }
    }
}

int
BasicCompiler::var_declaration ()
{
  Token token = token_stream.get_token ();

  if (token.type != Token::Types::VAR_NAME)
    {
      throw std::runtime_error ("Variable name expected in declaration");
    }

  std::string variable_name = token.string_value;

  token = token_stream.get_token ();

  if (token.type != Token::Types::OP_EQUAL)
    {
      throw std::runtime_error ("Expected '=' after variable name");
    }

  token = token_stream.get_token ();

  if (token == Token::NUMBER)
    {
      create_const_variable (variable_name, token.value);
    }
  else
    {
      token_stream.push_back (token);

      parse_expression ();

      if (variable_table.has (variable_name))
        {
          int address = variable_table.get_address (variable_name);

          write_command ("STORE", address);
        }
      else
        {
          variable_table.define (variable_name, variables_address);
        }
    }
  return 0;
}

int
BasicCompiler::if_statement ()
{
  Token variable = token_stream.get_token ();

  if (variable.type != Token::VAR_NAME)
    {
      throw std::runtime_error ("Variable name expected in declaration");
    }

  Token compare = token_stream.get_token ();

  if (compare.type != Token::OP_GT && compare.type != Token::OP_LESS)
    {
      throw std::runtime_error ("Expected > or < operator");
    }

  Token zero = token_stream.get_token ();

  if (zero.type != Token::NUMBER)
    {
      throw std::runtime_error ("0 expected after comparsion operator");
    }

  Token go = token_stream.get_token ();

  if (go.type != Token::GOTO)
    {
      throw std::runtime_error ("GOTO expected after compare expresson");
    }

  Token address = token_stream.get_token ();

  if (address.type != Token::NUMBER)
    {
      throw std::runtime_error ("address should be number");
    }

  load_variable (variable.string_value);

  if (compare.type == Token::OP_GT)
    {
      write_command ("JNS", -1, address.value);
    }
  else if (compare.type == Token::OP_LESS)
    {
      write_command ("JNEG", -1, address.value);
    }
  return 0;
}

int
BasicCompiler::global_statement ()
{
  Token token = token_stream.get_token ();

  if (token.type != Token::NUMBER)
    throw std::runtime_error ("Memory address expected");

  current_address = token.value;
  tags[current_address] = command_counter;
  return statement ();
}

int
BasicCompiler::rem ()
{
  token_stream.ignore ();
  return 0;
}

int
BasicCompiler::input ()
{
  Token token = token_stream.get_token ();
  if (token.type != Token::Types::VAR_NAME)
    {
      throw std::runtime_error ("Variable name expected in input command");
    }
  create_variable (token.string_value);
  return 0;
}

int
BasicCompiler::output ()
{
  Token variable = token_stream.get_token ();

  if (variable.type != Token::Types::VAR_NAME)
    {
      throw std::runtime_error ("Variable name expected in output command");
    }

  if (variable_table.has (variable.string_value) == false)
    {
      throw std::runtime_error ("Variable to output not found...");
    }

  write_command ("WRITE", variable_table.get_address (variable.string_value));
  return 0;
}

int
BasicCompiler::go ()
{
  Token token = token_stream.get_token ();

  if (token.type != Token::NUMBER)
    {
      throw std::runtime_error ("expected number after goto");
    }

  write_command ("JUMP", -1, token.value);
  return 0;
}

int
BasicCompiler::end ()
{
  write_command ("HALT", 0);
  return 0;
}

int
BasicCompiler::statement ()
{
  Token token = token_stream.get_token ();

  switch (token.type)
    {
    case Token::LET:
      return var_declaration ();
    case Token::REM:
      return rem ();
    case Token::INPUT:
      return input ();
    case Token::IF:
      return if_statement ();
    case Token::PRINT:
      return output ();
    case Token::GOTO:
      return go ();
    case Token::END:
      return end ();
    default:
      {
        token_stream.push_back (token);
        throw std::runtime_error ("Unknown statement!");
      }
    }
}

void
BasicCompiler::write_command (std::string command, int operand, int tag)
{
  AssemblyCommand sc_command;
  sc_command.command = command;
  sc_command.ram_address = command_counter;
  sc_command.operand = operand;
  sc_command.tag = tag;

  if (command == "JUMP" || command == "JNEG" || command == "JNS")
    {
      sc_command.is_resolved = false;
      sc_command.tag = tag;
    }
  commands.push_back (sc_command);
  command_counter++;
}

void
BasicCompiler::update_ram_address ()
{
  while (used_memory[variables_address])
    {
      variables_address--;
    }
}

void
BasicCompiler::create_const_variable (std::string name, int value)
{
  AssemblyCommand sc_command;
  sc_command.ram_address = command_counter;
  sc_command.command = "=";
  sc_command.operand = value;
  sc_command.tag = -1;

  commands.push_back (sc_command);
  used_memory[command_counter] = true;
  variable_table.define (name, command_counter);
  command_counter++;
}

void
BasicCompiler::create_variable (std::string name)
{
  update_ram_address ();

  AssemblyCommand sc_command;
  sc_command.command = "READ";
  sc_command.ram_address = command_counter;
  sc_command.operand = variables_address;
  sc_command.tag = -1;

  commands.push_back (sc_command);
  used_memory[variables_address] = true;
  variable_table.define (name, variables_address);
  command_counter++;
}

void
BasicCompiler::load_variable (std::string name)
{
  if (!variable_table.has (name))
    {
      throw std::runtime_error ("Variable not defined: " + name);
    }
  int address = variable_table.get_address (name);

  AssemblyCommand command;
  command.command = "LOAD";
  command.ram_address = command_counter;
  command.operand = address;
  command.tag = -1;

  commands.push_back (command);
  command_counter++;
}

int
BasicCompiler::compile ()
{
  int line = 0;
  try
    {
      while (in_stream)
        {
          line++;

          Token token = token_stream.get_token ();

          while (token.type == Token::Types::EXPRESSION_END_FLAG)
            {
              token = token_stream.get_token ();
            }

          if (token.type == Token::Types::EXIT_FLAG)
            {
              for (auto &cmd : commands)
                {
                  if (cmd.is_resolved)
                    {
                      out_stream << cmd.ram_address << " " << cmd.command
                                 << " " << cmd.operand << std::endl;
                    }
                  else
                    {
                      out_stream << cmd.ram_address << " " << cmd.command
                                 << " " << tags[cmd.tag] << std::endl;
                    }
                }

              return 0;
            }

          token_stream.push_back (token);

          global_statement ();
        }
    }
  catch (std::exception &e)
    {
      std::cout << "Line #" << line << "\nCalculation error: " << e.what ()
                << std::endl;
      return 1;
    }
  catch (...)
    {
      std::cout << "Line #" << line << "\nUnknown error!" << std::endl;
      return 2;
    }
  return 0;
}
