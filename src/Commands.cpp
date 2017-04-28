#include "Engine.hh"
#include "Commands.hh"

namespace Commands {

  cmdMap cmdlist = {
    {"clear", &consoleClear},
    {"echo", &echo},
    {"exec", &execute},
    {"exit", &quit},
    {"find", &findCmd},
    {"fps_max", &setMaxFPS},
    {"toggleconsole", &consoleToggle},
    {"videomode", &windowSize},
    {"vsync", &setVSync},
    {"cwd", &printCWD}
  };

  bool convertBool(std::string arg)
  {
    std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
    if (arg == "true")
      return (true);
    else
      return (false);
  }
  
  std::vector<std::string> *getArgs(std::string &command)
  {
    std::vector<std::string> *argv;
    std::string buffer;
    char delimiter;
    size_t pos;
    
    if (command.find(' ') == std::string::npos)
      return (NULL);
    argv = new std::vector<std::string>();
    buffer = command;
    while ((pos = buffer.find(' ')) != std::string::npos)
      {
	delimiter = ' ';
	while (buffer[pos] == ' ')
	  pos++;
	buffer = buffer.substr(pos, buffer.length() - pos);
	if (buffer[0] == '"')
	  {
	    buffer.erase(0, 1);
	    delimiter = '"';
	  }
	if ((pos = buffer.find(delimiter)) != std::string::npos)
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
	c.output(command+": Unknown command");
	return (false);
      }
    argv = getArgs(cmd);
    cmdlist[command](c, e, argv);
    return (true);
  }
  
  void consoleClear(Console &c, Engine &, std::vector<std::string> *)
  {
    c.clear();
  }

  void consoleToggle(Console &c, Engine &, std::vector<std::string> *)
  {
    c.toggle();
  }

  void echo(Console &c, Engine &, std::vector<std::string> *argv)
  {
    c.output((*argv)[0]);
  }
  
  void execute(Console &c, Engine &e, std::vector<std::string> *argv)
  {
    std::ifstream ifs;
    std::string cmd;
    
    if (argv == NULL || argv->size() < 1)
      {
	c.output("exec: Nothing to execute");
	return;
      }
    ifs.open((*argv)[0]);
    if (!ifs.is_open())
      {
	c.output("exec: Cannot open \""+(*argv)[0]+"\"");
	  return;
      }
    while (std::getline(ifs, cmd))
      parseCmd(c, e, cmd);
    delete (argv);
  }

  void findCmd(Console &c, Engine &, std::vector<std::string> *argv)
  {
    cmdMap::iterator iter;
    std::vector<std::string> available;

    if (argv == NULL || argv->size() < 1)
      {
	c.output("find: Nothing to search for");
	return;
      }
    for (iter = cmdlist.begin(); iter != cmdlist.end(); iter++)
      {
	if ((*iter).first.find((*argv)[0]) != std::string::npos)
	  available.push_back((*iter).first);
      }
    for (size_t i = 0; i < available.size(); i++)
      {
	c.output(available[i]);
	if (i < available.size() - 1)
	  c.insertLastOutput(", ");
      }
    if (available.empty())
      c.output("find: No commands found");
    delete (argv);
  }

  void printCWD(Console &c, Engine &, std::vector<std::string> *)
  {
    char *cwd = getcwd(NULL, 0);

    c.output(std::string(cwd));
    delete (cwd);
  }
  
  void quit(Console &, Engine &e, std::vector<std::string> *)
  {
    e.quit();
  }

  void setMaxFPS(Console &c, Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	c.output("fps_max: No value given");
	return;
      }
    e.videoParamSet("FPS", atoi((*argv)[0].c_str()));
  }

  void setVSync(Console &c, Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	c.output("vsync: No value given");
	return;
      }
    e.videoParamSet("VSYNC", convertBool((*argv)[0]));    
  }

  void windowSize(Console &c, Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 2)
      {
	c.output("videomode: Incorrect or no mode given");
	return;
      }
    e.openWindow(atoi((*argv)[0].c_str()), atoi((*argv)[1].c_str()));
    c.initGraphics(e.getWindowSize());
  }

}
