#ifndef COMMANDS_HH_
#define COMMANDS_HH_

#include <map>
#include <list>
#include <fstream>
#include <unistd.h>

class Engine;
class Console;

namespace Commands {

  typedef std::map<std::string, void (*)(Console &, Engine &, std::vector<std::string> *)> cmdMap;
  
  std::vector<std::string> *getArgs(std::string &command);
  bool parseCmd(Console &c, Engine &e, std::string);
  
  void consoleClear(Console &c, Engine &e, std::vector<std::string> *);
  void consoleToggle(Console &c, Engine &e, std::vector<std::string> *);
  void echo(Console &c, Engine &e, std::vector<std::string> *);
  void execute(Console &c, Engine &e, std::vector<std::string> *);
  void findCmd(Console &c, Engine &e, std::vector<std::string> *);
  void printCWD(Console &c, Engine &e, std::vector<std::string> *);
  void quit(Console &c, Engine &e, std::vector<std::string> *);
  void setMaxFPS(Console &c, Engine &e, std::vector<std::string> *);
  void setVSync(Console &c, Engine &e, std::vector<std::string> *);
  void windowSize(Console &c, Engine &e, std::vector<std::string> *);
  
}

#endif
