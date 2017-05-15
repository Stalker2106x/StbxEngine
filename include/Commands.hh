#ifndef COMMANDS_HH_
#define COMMANDS_HH_

#include <map>
#include <list>
#include <fstream>

class Engine;
class Console;

namespace Commands {

  typedef std::map<std::string, void (*)(Console &, Engine &, std::vector<std::string> *)> cmdMap;
  extern cmdMap cmdlist;

  bool convertBool(Console &c, std::string &arg);
  std::vector<std::string> *getArgs(std::string &command);
  bool parseCmd(Console &c, Engine &e, std::string);

  void bindCommand(Console &c, Engine &e, std::vector<std::string> *);
  void bindList(Console &c, Engine &e, std::vector<std::string> *);
  void consoleClear(Console &c, Engine &e, std::vector<std::string> *);
  void consoleToggle(Console &c, Engine &e, std::vector<std::string> *);
  void echo(Console &c, Engine &e, std::vector<std::string> *);
  void execute(Console &c, Engine &e, std::vector<std::string> *);
  void findCmd(Console &c, Engine &e, std::vector<std::string> *);
  void toggleConLog(Console &c, Engine &, std::vector<std::string> *);
  void writeToLog(Console &c, Engine &, std::vector<std::string> *argv);
  void setConLog(Console &c, Engine &, std::vector<std::string> *argv);
  void printCWD(Console &c, Engine &e, std::vector<std::string> *);
  void quit(Console &c, Engine &e, std::vector<std::string> *);
  void screenshot(Console &c, Engine &e, std::vector<std::string> *argv);
  void setLineCount(Console &c, Engine &e, std::vector<std::string> *);
  void setConColor(Console &c, Engine &e, std::vector<std::string> *);
  void setConCursor(Console &c, Engine &e, std::vector<std::string> *);
  void setMaxFPS(Console &c, Engine &e, std::vector<std::string> *);
  void setFullscreen(Console &c, Engine &e, std::vector<std::string> *);
  void help(Console &c, Engine &e, std::vector<std::string> *);
  void setVSync(Console &c, Engine &e, std::vector<std::string> *);
  void unbind(Console &c, Engine &e, std::vector<std::string> *);
  void unbindall(Console &c, Engine &e, std::vector<std::string> *);
  void windowSize(Console &c, Engine &e, std::vector<std::string> *);

}

#endif
