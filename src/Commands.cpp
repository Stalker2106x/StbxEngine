#include <fstream>
#include <memory>
#include "Commands.hh"
#include "Engine.hpp"
#include "utils.h"

#ifndef _MSC_VER
	#include <unistd.h>
#else
	#include <direct.h>
	#include <io.h>
#endif

using namespace stb;

aliasMap Commands::aliaslist;
cmdMap Commands::cmdlist = {
	{ "alias", &alias},
	{ "bind", &bindCommand },
	{ "bindlist", &bindList },
	{ "clear", &consoleClear },
	{ "con_color", &setConColor },
	{ "cwd", &printCWD },
	{ "debuginfo", &debugInfo },
	{ "echo", &echo },
	{ "exec", &execute },
	{ "exit", &quit },
	{ "find", &findCmd },
	{ "fps_max", &setMaxFPS },
	{ "fullscreen", &setFullscreen },
	{ "gui_toggleelement", &toggleGUIElement },
	{ "help", &help },
	{ "log_enable", &toggleConLog },
	{ "log_write", &writeToLog },
	{ "log_file", &setConLog },
	{ "log_timestamp", &timestampLog },
	{ "screenshot", &screenshot },
	{ "toggleconsole", &consoleToggle },
	{ "unbind", &unbind },
	{ "unbindall", &unbindall },
	{ "videomode", &windowSize },
	{ "vsync", &setVSync }
};

bool Commands::convertBool(std::string arg)
{
	std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
	if (arg == "true" || arg == "1")
		return (true);
	else if (arg == "false" || arg == "0")
		return (false);
	else
	{
		Engine::instance->console->output("Syntax: Invalid argument, expected boolean");
		throw std::invalid_argument("bool");
	}
	return (false);
}

argumentArray *Commands::getArgs(const std::string &command, argumentArray *argv)
{
	std::string buffer, arg;
	char delimiter;
	size_t pos;
	bool insert = false;

	if (command.find(' ') == std::string::npos) return (NULL); //If no word break, no args, leave...
	if (argv == NULL)
	{
		argv = new argumentArray(); //If argv is not set, allocate it
		insert = true; //Set inserting to true to prevent misordered args
	}
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
		if ((pos = buffer.find(delimiter)) != std::string::npos) //If arg is not last, extract it
			arg = buffer.substr(0, pos);
		else
			arg = buffer;
		if (insert)
			argv->push_front(arg);
		else
			argv->push_back(arg);
	}
	return (argv);
}

bool Commands::parseCmd(const std::string &cmd, argumentArray *argv)
{
	std::string command;
	bool alias = false;

	command = cmd.substr(0, cmd.find(' '));
	std::transform(command.begin(), command.end(), command.begin(), ::tolower);
	if (cmdlist.find(command) == cmdlist.end())
	{
		alias = true;
		if (aliaslist.find(command) == aliaslist.end())
		{
			Engine::console->output(command + ": Unknown command");
			return (false);
		}
	}
	getArgs(cmd, argv);
	if (alias)
		parseCmd(aliaslist[command], argv); //If command is aliased, reparse it
	else
		cmdlist[command](argv); //else, execute
	if (argv != NULL)
		delete (argv);
	return (true);
}

//
// Command functors
//

void Commands::alias(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 2)
	{
		Engine::console->output("alias: Missing argument");
		return;
	}
	std::string alias = (*argv)[0];
	std::string command = (*argv)[1];

	std::transform(alias.begin(), alias.end(), alias.begin(), ::tolower);
	std::transform(command.begin(), command.end(), command.begin(), ::tolower);
	aliaslist.emplace(alias, command);
}

void Commands::bindCommand(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 2)
	{
		Engine::console->output("bind: Missing argument");
		return;
	}
	std::string bind = (*argv)[0];
	std::string action = (*argv)[1];

	std::transform(bind.begin(), bind.end(), bind.begin(), ::tolower);
	std::transform(action.begin(), action.end(), action.begin(), ::tolower);
	if (!Engine::instance->keybinds->bind(bind, action))
		Engine::console->output("bind: Cannot bind key; key or action invalid?");
}

void Commands::bindList(argumentArray *)
{
	Engine::instance->keybinds->listAllBinds();
}

void Commands::consoleClear(argumentArray *)
{
	Engine::console->clear();
}

void Commands::consoleToggle(argumentArray *)
{
	Engine::console->toggle();
}

void Commands::debugInfo(argumentArray *)
{
	//none
}

void Commands::echo(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 1)
		Engine::console->output("");
	else
		Engine::console->output((*argv)[0]);
}

void Commands::execute(argumentArray *argv)
{
	std::ifstream ifs;
	std::string cmd;

	if (argv == NULL || argv->size() < 1)
	{
		Engine::console->output("exec: Nothing to execute");
		return;
	}
	ifs.open((*argv)[0]);
	if (!ifs.is_open())
	{
		Engine::console->output("exec: Cannot open \"" + (*argv)[0] + "\"");
		return;
	}
	while (std::getline(ifs, cmd))
		parseCmd(cmd);
}

void Commands::findCmd(argumentArray *argv)
{
	cmdMap::const_iterator iter;
	std::vector<std::string> available;

	if (argv == NULL || argv->size() < 1)
	{
		Engine::console->output("find: Nothing to search for");
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
	}
	if (available.empty())
		Engine::console->output("find: No commands found");
}

void Commands::toggleConLog(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 1)
	{
		Engine::console->output("log_enable: No param given");
		return;
	}
	bool v;

	try { v = convertBool((*argv)[0]); }
	catch (...) { return; }
	Engine::console->setLogEnabled(v);
}

void Commands::writeToLog(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 1)
	{
		Engine::console->output("log_write: Nothing to write");
		return;
	}
	Engine::console->writeToLog((*argv)[0]);
}

void Commands::setConLog(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 1)
	{
		Engine::console->output("log_file: No path given");
		return;
	}
	Engine::console->setLogFile((*argv)[0]);
}

void Commands::toggleGUIElement(argumentArray *argv)
{
	//none
}

void Commands::timestampLog(argumentArray *argv)
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

void Commands::printCWD(argumentArray *)
{
	char *cwd;

#ifndef _MSC_VER
	cwd = getcwd(NULL, 0);
#else
	cwd = _getcwd(NULL, 0);
#endif
	Engine::console->output(std::string(cwd));
	delete (cwd);
}

void Commands::quit(argumentArray *)
{
	Engine::instance->quit();
}

void Commands::screenshot(argumentArray *argv)
{
	static int id = 0;
	sf::Image shot;
	std::string file = "Data/screenshots/";

	shot = Engine::instance->capture();
	if (argv == NULL || argv->size() < 1)
		file += Engine::getTimestamp() + ".png";
	else
		file += (*argv)[0] + ".png";
	id++;
	if (!shot.saveToFile(file))
		Engine::console->output("screenshot: Unable to save screenshot");
}

void Commands::setConColor(argumentArray *argv)
{
	sf::Color cbg, cinput;

	if (argv == NULL || argv->size() < 2
		|| (*argv)[0].length() < 9 || (*argv)[1].length() < 9)
		Engine::console->output("con_color: Invalid colors or no colors given");
	cbg = convertColorCode((*argv)[0]);
	cinput = convertColorCode((*argv)[1]);
	Engine::console->setColor(cbg, cinput);
}

void Commands::setConCursor(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 1)
	{
		Engine::console->output("con_cursor: No char given");
		return;
	}
	//Engine::console->setCursor((*argv)[0][0]); TMP
}

void Commands::setMaxFPS(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 1)
	{
		Engine::console->output("fps_max: No value given");
		return;
	}
	Engine::instance->videoParamSet("FPS", atoi((*argv)[0].c_str()));
}

void Commands::setFullscreen(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 1)
	{
		Engine::instance->videoParamSet("TFULLSCREEN", false);
		return;
	}
	bool v;

	try { v = convertBool((*argv)[0]); }
	catch (...) { return; }
	Engine::instance->videoParamSet("FULLSCREEN", static_cast<int>(v));
}

void Commands::help(argumentArray *)
{
	Engine::console->output("Available commands: ");
	Engine::console->output("");
	for (cmdMap::const_iterator it = cmdlist.begin(); it != cmdlist.end(); it++)
	{
		Engine::console->output(it->first);
	}
}

void Commands::setVSync(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 1)
	{
		Engine::instance->videoParamSet("TVSYNC", false);
		return;
	}
	bool v;

	try { v = convertBool((*argv)[0]); }
	catch (...) { return; }
	Engine::instance->videoParamSet("VSYNC", v);
}

void Commands::unbind(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 1)
	{
		Engine::console->output("unbind: No key or action given");
		return;
	}
	if (!Engine::instance->keybinds->unbind((*argv)[0]))
		Engine::console->output("unbind: Unable to unbind key or action");
}

void Commands::unbindall(argumentArray *)
{
	Engine::instance->keybinds->unbindall();
}

void Commands::windowSize(argumentArray *argv)
{
	if (argv == NULL || argv->size() < 2)
	{
		Engine::console->output("videomode: Mode incorrect or no mode given");
		return;
	}
	Engine::instance->openWindow(atoi((*argv)[0].c_str()), atoi((*argv)[1].c_str()));
	Engine::console->initGraphics(*Engine::gui);
}