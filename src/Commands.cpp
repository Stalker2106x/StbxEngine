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
    size_t pos;
    
    if (command.find(' ') == std::string::npos)
      return (NULL);
    argv = new std::vector<std::string>();
    buffer = command;
    while ((pos = buffer.find(' ')) != std::string::npos)
      {
	while (buffer[pos] == ' ')
	  pos++;
	buffer = buffer.substr(pos, buffer.length() - pos);
	if ((pos = buffer.find(' ')) != std::string::npos)
	  argv->push_back(buffer.substr(0, pos));
	else
	  argv->push_back(buffer);
      }
    return (argv);
  }
  
  bool parseCmd(Console &c, Engine &e, std::string cmd)
  {
    std::vector<std::string> *argv;
    std::string command;

    command = cmd.substr(0, cmd.find(' '));
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    if (cmdlist.find(command) == cmdlist.end())
      {
	c.output(command+": Uknown command");
	return (false);
      }
    argv = getArgs(cmd);
    cmdlist[command](c, e, *argv);
    return (true);
  }
  
  void quit(Console &, Engine &e, std::vector<std::string> &)
  {
    e.quit();
  }

  void clear(Console &c, Engine &, std::vector<std::string> &)
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
