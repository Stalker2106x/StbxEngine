#include "Engine.hh"
#include "Commands.hh"

namespace Commands {

  std::map<std::string, void (*)(Console &, Engine &, std::vector<std::string> &)> cmdlist = {
    {"exit", &quit},
    {"clear", &clear},
    {"exec", &execute}
  };

  std::vector<std::string> *getArgs(std::string &command)
  {
    std::vector<std::string> *argv;
    std::string buffer;
    int pos;
    
    if (command.find(' ') == std::string::npos)
      return (NULL);
    argv = new std::vector<std::string>();
    buffer = command;
    while ((pos = buffer.find(' ')) != std::string::npos)
      {
	buffer = buffer.substr(pos + 2, buffer.length() - pos);
	std::cout << buffer << "\n";
	if ((pos = buffer.find(' ')) != std::string::npos)
	  argv->push_back(buffer.substr(0, pos));
	else
	  argv->push_back(buffer);
      }
    command = command.substr(0, command.find(' '));
    return (argv);
  }
  
  bool parseCmd(Console &c, Engine &e, std::string cmd)
  {
    std::vector<std::string> *argv;

    argv = getArgs(cmd);
    if (cmdlist.find(cmd) == cmdlist.end())
      {
	c.output(cmd+": Uknown command");
	return (false);
      }
    cmdlist[cmd](c, e, *argv);
    return (true);
  }
  
  void quit(Console &c, Engine &e, std::vector<std::string> &argv)
  {
    e.quit();
  }

  void clear(Console &c, Engine &e, std::vector<std::string> &argv)
  {
    c.clear();
  }

  void execute(Console &c, Engine &e, std::vector<std::string> &argv)
  {
    std::ifstream ifs;
    std::string cmd;
    
    if (&argv == NULL || argv.size() < 1)
      c.output("exec: Nothing to execute");
    ifs.open(argv[0]);
    if (!ifs.is_open())
      {
	c.output("exec: Cannot open \""+argv[0]+"\"");
	  return;
      }
    while (std::getline(ifs, cmd))
      parseCmd(c, e, cmd);
    delete (&argv);
  }
  
}
