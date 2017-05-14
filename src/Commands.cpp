#include "Engine.hh"
#include "Commands.hh"
#include <unistd.h>

namespace Commands {

  cmdMap cmdlist = {
    {"bind", &bindCommand},
    {"bindlist", &bindList},
    {"clear", &consoleClear},
    {"con_maxline", &setLineCount},
    {"con_color", &setConColor},
    {"con_cursor", &setConCursor},
    {"cwd", &printCWD},
    {"echo", &echo},
    {"exec", &execute},
    {"exit", &quit},
    {"find", &findCmd},
    {"fps_max", &setMaxFPS},
    {"fullscreen", &setFullscreen},
    {"help", &help},
    {"log_enable", &toggleConLog},
    {"log_write", &writeToLog},
    {"log_file", &setConLog},
    {"screenshot", &screenshot},
    {"toggleconsole", &consoleToggle},
    {"unbind", &unbind},
    {"unbindall", &unbindall},
    {"videomode", &windowSize},
    {"vsync", &setVSync}
  };

  bool convertBool(Console &c, std::string &arg)
  {
    std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
    if (arg == "true" || arg == "1")
      return (true);
    else if (arg == "false" || arg == "0")
      return (false);
    else
      {
	c.output(COLOR_ERROR, "Syntax: Invalid argument, expected boolean");
	throw std::invalid_argument("bool");
      }
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
	if (buffer[0] == '"' || buffer[0] == '\'')
	  {
	    buffer.erase(0, 1);
	    delimiter = buffer[0];
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
	c.output(COLOR_ERROR+command+": Unknown command");
	return (false);
      }
    argv = getArgs(cmd);
    cmdlist[command](c, e, argv);
    return (true);
  }

  void bindCommand(Console &c, Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 2)
      {
	c.output(COLOR_ERROR, "bind: Missing argument");
	return;
      }
    if (!Engine::keybinds->bind((*argv)[1], (*argv)[0]))
      c.output(COLOR_ERROR, "bind: Cannot bind key; key or action invalid?");
  }

  void bindList(Console &c, Engine &, std::vector<std::string> *)
  {
    Engine::keybinds->listAllBinds(c);
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
	c.output(COLOR_ERROR, "exec: Nothing to execute");
	return;
      }
    ifs.open((*argv)[0]);
    if (!ifs.is_open())
      {
	c.output(COLOR_ERROR, "exec: Cannot open \""+(*argv)[0]+"\"");
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
	c.output(COLOR_ERROR, "find: Nothing to search for");
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

  void toggleConLog(Console &c, Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	c.output(COLOR_ERROR, "log_enable: No param given");
	return;
      }
    bool v;

    try { v = convertBool(c, (*argv)[0]); }
    catch (...) { return; }
    c.setLogEnabled(v);
  }
  
  void writeToLog(Console &c, Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	c.output(COLOR_ERROR, "log_write: Nothing to write");
	return;
      }
    c.writeToLog((*argv)[0]);
  }
  
  void setConLog(Console &c, Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	c.output(COLOR_ERROR, "log_file: No path given");
	return;
      }
    c.setLogFile((*argv)[0]);
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

  void screenshot(Console &c, Engine &e, std::vector<std::string> *argv)
  {
    static int id = 0;
    sf::Image shot;
    std::string file = "Data/screenshots/";

    shot = e.capture();
    if (argv == NULL || argv->size() < 1)
      file += Engine::getTimestamp()+".png";
    else
      file += (*argv)[0]+".png";
    id++;
    if (!shot.saveToFile(file))
      c.output(COLOR_ERROR, "screenshot: Unable to save screenshot");
  }

  void setLineCount(Console &c, Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	c.output(COLOR_ERROR, "con_maxline: No value given");
	return;
      }
    c.setLineCount(atoi((*argv)[0].c_str()));
    c.initGraphics(e.getWindowSize());
    delete (argv);
  }

  void setConColor(Console &c, Engine &, std::vector<std::string> *argv)
  {
    sf::Color cbg, cinput;
    
    if (argv == NULL || argv->size() < 2
	|| (*argv)[0].length() < 9 || (*argv)[1].length() < 9)
      c.output(COLOR_ERROR, "con_color: Invalid colors or no colors given");
    cbg = Console::convertColorCode((*argv)[0]);
    cinput = Console::convertColorCode((*argv)[1]);
    c.setColor(cbg, cinput);
    delete (argv);
  }

  void setConCursor(Console &c, Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	c.output(COLOR_ERROR, "con_cursor: No char given");
	return;
      }
    c.setCursor((*argv)[0][0]);
  }
  
  void setMaxFPS(Console &c, Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	c.output(COLOR_ERROR, "fps_max: No value given");
	return;
      }
    e.videoParamSet("FPS", atoi((*argv)[0].c_str()));
    delete (argv);
  }

  void setFullscreen(Console &c, Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	c.output(COLOR_ERROR, "fullscreen: No value given");
	return;
      }    
    bool v;

    try { v = convertBool(c, (*argv)[0]); }
    catch (...) { return; }
    e.videoParamSet("FULLSCREEN", static_cast<int>(v));
    delete (argv);
  }

  void help(Console &c, Engine &, std::vector<std::string> *)
  {
    c.output(COLOR_INFO, "Available commands: ");
    c.output("");
    for (cmdMap::iterator it = cmdlist.begin(); it != cmdlist.end(); it++)
      {
	c.insertLastOutput(it->first);
	if (std::next(it, 1) != cmdlist.end())
	  c.insertLastOutput(", ");
      }
  }
  
  void setVSync(Console &c, Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	c.output(COLOR_ERROR, "vsync: No value given");
	return;
      }
    bool v;

    try { v = convertBool(c, (*argv)[0]); }
    catch (...) { return; }
    e.videoParamSet("VSYNC", v);
    delete (argv);
  }

  void unbind(Console &c, Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	c.output(COLOR_ERROR, "unbind: No key or action given");
	return;
      }
    if (!e.keybinds->unbind((*argv)[0]))
      c.output(COLOR_ERROR, "unbind: Unable to unbind key or action");
  }

  void unbindall(Console &, Engine &e, std::vector<std::string> *)
  {
    e.keybinds->unbindall();
  }
  
  void windowSize(Console &c, Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 2)
      {
	c.output(COLOR_ERROR, "videomode: Mode incorrect or no mode given");
	return;
      }
    e.openWindow(atoi((*argv)[0].c_str()), atoi((*argv)[1].c_str()));
    c.initGraphics(e.getWindowSize());
    delete (argv);
  }

}
