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
    {"log_timestamp", &timestampLog},
    {"screenshot", &screenshot},
    {"toggleconsole", &consoleToggle},
    {"unbind", &unbind},
    {"unbindall", &unbindall},
    {"videomode", &windowSize},
    {"vsync", &setVSync}
  };

  bool convertBool(std::string &arg)
  {
    std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
    if (arg == "true" || arg == "1")
      return (true);
    else if (arg == "false" || arg == "0")
      return (false);
    else
      {
	Engine::console->output(COLOR_ERROR, "Syntax: Invalid argument, expected boolean");
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
	if (pos >= buffer.length())
	  {
	    delete (argv);
	    return (NULL);
	  }
	buffer = buffer.substr(pos, buffer.length() - pos);
	if (buffer[0] == '"' || buffer[0] == '\'')
	  {
	    delimiter = buffer[0];
	    buffer.erase(0, 1);
	  }
	if ((pos = buffer.find(delimiter)) != std::string::npos)
	  argv->push_back(buffer.substr(0, pos));
	else
	  argv->push_back(buffer);
      }
    return (argv);
  }

  bool parseCmd(Engine &e, std::string cmd)
  {
    std::vector<std::string> *argv;
    std::string command;

    command = cmd.substr(0, cmd.find(' '));
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    if (cmdlist.find(command) == cmdlist.end())
      {
	Engine::console->output(COLOR_ERROR+command+": Unknown command");
	return (false);
      }
    argv = getArgs(cmd);
    cmdlist[command](e, argv);
    if (argv != NULL)
      delete (argv);
    return (true);
  }

  void bindCommand(Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 2)
      {
	Engine::console->output(COLOR_ERROR, "bind: Missing argument");
	return;
      }
    std::string bind = (*argv)[0];
    std::string action = (*argv)[1];

    std::transform(bind.begin(), bind.end(), bind.begin(), ::tolower);
    std::transform(action.begin(), action.end(), action.begin(), ::tolower);
    if (!Engine::keybinds->bind(bind, action))
      Engine::console->output(COLOR_ERROR, "bind: Cannot bind key; key or action invalid?");
  }

  void bindList(Engine &, std::vector<std::string> *)
  {
    Engine::keybinds->listAllBinds();
  }

  void consoleClear(Engine &, std::vector<std::string> *)
  {
    Engine::console->clear();
  }

  void consoleToggle(Engine &, std::vector<std::string> *)
  {
    Engine::console->toggle();
  }

  void echo(Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
	    Engine::console->output("");
    else
      Engine::console->output((*argv)[0]);
  }

  void execute(Engine &e, std::vector<std::string> *argv)
  {
    std::ifstream ifs;
    std::string cmd;

    if (argv == NULL || argv->size() < 1)
      {
	Engine::console->output(COLOR_ERROR, "exec: Nothing to execute");
	return;
      }
    ifs.open((*argv)[0]);
    if (!ifs.is_open())
      {
	Engine::console->output(COLOR_ERROR, "exec: Cannot open \""+(*argv)[0]+"\"");
	  return;
      }
    while (std::getline(ifs, cmd))
      parseCmd(e, cmd);
  }

  void findCmd(Engine &, std::vector<std::string> *argv)
  {
    cmdMap::iterator iter;
    std::vector<std::string> available;

    if (argv == NULL || argv->size() < 1)
      {
	Engine::console->output(COLOR_ERROR, "find: Nothing to search for");
	return;
      }
    for (iter = cmdlist.begin(); iter != cmdlist.end(); iter++)
      {
	if ((*iter).first.find((*argv)[0]) != std::string::npos)
	  available.push_back((*iter).first);
      }
    for (size_t i = 0; i < available.size(); i++)
      {
	Engine::console->output(available[i]);
	if (i < available.size() - 1)
	  Engine::console->insertLastOutput(", ");
      }
    if (available.empty())
      Engine::console->output("find: No commands found");
  }

  void toggleConLog(Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	Engine::console->output(COLOR_ERROR, "log_enable: No param given");
	return;
      }
    bool v;

    try { v = convertBool((*argv)[0]); }
    catch (...) { return; }
    Engine::console->setLogEnabled(v);
  }

  void writeToLog(Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	Engine::console->output(COLOR_ERROR, "log_write: Nothing to write");
	return;
      }
    Engine::console->writeToLog((*argv)[0]);
  }

  void setConLog(Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	Engine::console->output(COLOR_ERROR, "log_file: No path given");
	return;
      }
    Engine::console->setLogFile((*argv)[0]);
  }

  void timestampLog(Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	Engine::console->setLogTimestamp(-1);
	return;
      }
    bool v;

    try { v = convertBool((*argv)[0]); }
    catch (...) { return; }
    Engine::console->setLogTimestamp(static_cast<int>(v));
  }

  void printCWD(Engine &, std::vector<std::string> *)
  {
    char *cwd = getcwd(NULL, 0);

    Engine::console->output(std::string(cwd));
    delete (cwd);
  }

  void quit(Engine &e, std::vector<std::string> *)
  {
    e.quit();
  }

  void screenshot(Engine &e, std::vector<std::string> *argv)
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
      Engine::console->output(COLOR_ERROR, "screenshot: Unable to save screenshot");
  }

  void setLineCount(Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	Engine::console->output(COLOR_ERROR, "con_maxline: No value given");
	return;
      }
    Engine::console->setLineCount(atoi((*argv)[0].c_str()));
    Engine::console->initGraphics(e.getWindowSize());
  }

  void setConColor(Engine &, std::vector<std::string> *argv)
  {
    sf::Color cbg, cinput;

    if (argv == NULL || argv->size() < 2
	|| (*argv)[0].length() < 9 || (*argv)[1].length() < 9)
      Engine::console->output(COLOR_ERROR, "con_color: Invalid colors or no colors given");
    cbg = Console::convertColorCode((*argv)[0]);
    cinput = Console::convertColorCode((*argv)[1]);
    Engine::console->setColor(cbg, cinput);
  }

  void setConCursor(Engine &, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	Engine::console->output(COLOR_ERROR, "con_cursor: No char given");
	return;
      }
    Engine::console->setCursor((*argv)[0][0]);
  }

  void setMaxFPS(Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	Engine::console->output(COLOR_ERROR, "fps_max: No value given");
	return;
      }
    e.videoParamSet("FPS", atoi((*argv)[0].c_str()));
  }

  void setFullscreen(Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	e.videoParamSet("TFULLSCREEN", false);
	return;
      }
    bool v;

    try { v = convertBool((*argv)[0]); }
    catch (...) { return; }
    e.videoParamSet("FULLSCREEN", static_cast<int>(v));
  }

  void help(Engine &, std::vector<std::string> *)
  {
    Engine::console->output(COLOR_INFO, "Available commands: ");
    Engine::console->output("");
    for (cmdMap::iterator it = cmdlist.begin(); it != cmdlist.end(); it++)
      {
	Engine::console->insertLastOutput(it->first);
	if (std::next(it, 1) != cmdlist.end())
	  Engine::console->insertLastOutput(", ");
      }
  }

  void setVSync(Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	e.videoParamSet("TVSYNC", false);
	return;
      }
    bool v;

    try { v = convertBool((*argv)[0]); }
    catch (...) { return; }
    e.videoParamSet("VSYNC", v);
  }

  void unbind(Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 1)
      {
	Engine::console->output(COLOR_ERROR, "unbind: No key or action given");
	return;
      }
    if (!e.keybinds->unbind((*argv)[0]))
      Engine::console->output(COLOR_ERROR, "unbind: Unable to unbind key or action");
  }

  void unbindall(Engine &e, std::vector<std::string> *)
  {
    e.keybinds->unbindall();
  }

  void windowSize(Engine &e, std::vector<std::string> *argv)
  {
    if (argv == NULL || argv->size() < 2)
      {
	Engine::console->output(COLOR_ERROR, "videomode: Mode incorrect or no mode given");
	return;
      }
    e.openWindow(atoi((*argv)[0].c_str()), atoi((*argv)[1].c_str()));
    Engine::console->initGraphics(e.getWindowSize());
  }

}
