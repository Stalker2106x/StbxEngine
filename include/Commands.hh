#ifndef COMMANDS_HH_
#define COMMANDS_HH_

#include <map>
#include <list>
#include <fstream>

class Engine;
class Console;

namespace Commands {

  std::vector<std::string> *getArgs(std::string &command);
  bool parseCmd(Console &c, Engine &e, std::string);
  
  void quit(Console &c, Engine &e, std::vector<std::string> &);
  void clear(Console &c, Engine &e, std::vector<std::string> &);
  void execute(Console &c, Engine &e, std::vector<std::string> &);
  
}

#endif
