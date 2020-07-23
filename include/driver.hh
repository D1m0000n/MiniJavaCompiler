#pragma once

#include <map>
#include <string>
#include <fstream>
#include <unordered_map>
#include "scanner.h"
#include "parser.hh"

#include "Program.h"
#include "../irtree/blocks/Block.h"

class Driver {
 public:
  Driver();
  int result;
  int parse(const std::string& f);
  void Evaluate();
  void PrintTree(const std::string& filename);

  void MakeBlocks();
  std::vector<IRT::Block> GetBlocksFromMethod(std::vector<IRT::Statement*>& statements); //// add args
  std::vector<IRT::Statement*> MakeStatementsSequence(IRT::Statement* statement);

  std::string file;
  bool trace_parsing;

  void scan_begin();
  void scan_end();

  bool trace_scanning;
  yy::location location;

  friend class Scanner;
  Scanner scanner;
  yy::parser parser;
  Program* program;

  std::unordered_map<std::string, std::vector<IRT::Statement*>> statements_sequence_;

 private:
  std::ifstream stream;

};
