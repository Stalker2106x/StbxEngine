#include <fstream>
#include "Engine.hpp"
#include "Commands.hh"
#ifndef _MSC_VER
	#include <unistd.h>
#else
	#include <direct.h>
	#include <io.h>
#endif

namespace stb {
	namespace Commands {

		cmdMap cmdlist = {
			{ "bind", &bindCommand },
			{ "bindlist", &bindList },
			{ "clear", &consoleClear },
			{ "con_maxline", &setLineCount },
			{ "con_color", &setConColor },
			{ "con_cursor", &setConCursor },
			{ "cwd", &printCWD },
			{ "debuginfo", &debugInfo },
			{ "echo", &echo },
			{ "exec", &execute },
			{ "exit", &quit },
			{ "find", &findCmd },
			{ "fps_max", &setMaxFPS },
			{ "fullscreen", &setFullscreen },
			{ "gui_changescreen", &changeScreen },
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

		bool convertBool(std::string &arg)
		{
			std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
			if (arg == "true" || arg == "1")
				return (true);
			else if (arg == "false" || arg == "0")
				return (false);
			else
			{
				Engine::instance->console->output(COLOR_ERROR, "Syntax: Invalid argument, expected boolean");
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
				e.console->output(COLOR_ERROR + command + ": Unknown command");
				return (false);
			}
			argv = getArgs(cmd);
			cmdlist[command](e, argv);
			if (argv != NULL)
				delete (argv);
			return (true);
		}

		void bindCommand(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 2)
			{
				e.console->output(COLOR_ERROR, "bind: Missing argument");
				return;
			}
			std::string bind = (*argv)[0];
			std::string action = (*argv)[1];

			std::transform(bind.begin(), bind.end(), bind.begin(), ::tolower);
			std::transform(action.begin(), action.end(), action.begin(), ::tolower);
			if (!e.keybinds->bind(bind, action))
				e.console->output(COLOR_ERROR, "bind: Cannot bind key; key or action invalid?");
		}

		void bindList(Engine &e, std::vector<std::string> *)
		{
			e.keybinds->listAllBinds();
		}

		void consoleClear(Engine &e, std::vector<std::string> *)
		{
			e.console->clear();
		}

		void consoleToggle(Engine &e, std::vector<std::string> *)
		{
			e.console->toggle();
		}

		void debugInfo(Engine &e, std::vector<std::string> *)
		{
			GUIPanel *debugpanel;

			if ((debugpanel = static_cast<GUIPanel *>(e.gui->getElement("__debuginfo"))) != NULL)
				e.gui->removeElement("__debuginfo", true);
			else
			{
				debugpanel = e.gui->addPanel("__debuginfo", sf::Vector2i(150, 250), sf::Color(47, 79, 79, 150));
				debugpanel->addElement(new GUIIndicator<int>("Screen Width: ", e.getWindowSize().x));
				debugpanel->addElement(new GUIIndicator<int>("Screen Height: ", e.getWindowSize().y));
				debugpanel->addElement(new GUIIndicator<int>("FPS: ", e.getFramerate()));
				debugpanel->addElement(new GUIIndicator<float>("Mouse X: ", e.getMouse().x));
				debugpanel->addElement(new GUIIndicator<float>("Mouse Y: ", e.getMouse().y));
				debugpanel->addElement(new GUIIndicator<float>("Game Time: ", e.getElapsedSeconds()));
			}
		}

		void echo(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 1)
				e.console->output("");
			else
				e.console->output((*argv)[0]);
		}

		void execute(Engine &e, std::vector<std::string> *argv)
		{
			std::ifstream ifs;
			std::string cmd;

			if (argv == NULL || argv->size() < 1)
			{
				e.console->output(COLOR_ERROR, "exec: Nothing to execute");
				return;
			}
			ifs.open((*argv)[0]);
			if (!ifs.is_open())
			{
				e.console->output(COLOR_ERROR, "exec: Cannot open \"" + (*argv)[0] + "\"");
				return;
			}
			while (std::getline(ifs, cmd))
				parseCmd(e, cmd);
		}

		void findCmd(Engine &e, std::vector<std::string> *argv)
		{
			cmdMap::iterator iter;
			std::vector<std::string> available;

			if (argv == NULL || argv->size() < 1)
			{
				e.console->output(COLOR_ERROR, "find: Nothing to search for");
				return;
			}
			for (iter = cmdlist.begin(); iter != cmdlist.end(); iter++)
			{
				if ((*iter).first.find((*argv)[0]) != std::string::npos)
					available.push_back((*iter).first);
			}
			for (size_t i = 0; i < available.size(); i++)
			{
				e.console->output(available[i]);
				if (i < available.size() - 1)
					e.console->insertLastOutput(", ");
			}
			if (available.empty())
				e.console->output("find: No commands found");
		}

		void toggleConLog(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 1)
			{
				e.console->output(COLOR_ERROR, "log_enable: No param given");
				return;
			}
			bool v;

			try { v = convertBool((*argv)[0]); }
			catch (...) { return; }
			e.console->setLogEnabled(v);
		}

		void writeToLog(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 1)
			{
				e.console->output(COLOR_ERROR, "log_write: Nothing to write");
				return;
			}
			e.console->writeToLog((*argv)[0]);
		}

		void setConLog(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 1)
			{
				e.console->output(COLOR_ERROR, "log_file: No path given");
				return;
			}
			e.console->setLogFile((*argv)[0]);
		}

		void changeScreen(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 1)
			{
				e.console->output(COLOR_ERROR, "gui_changescreen: No id given");
				return;
			}
			e.gui->changeScreen((*argv)[0].c_str());
		}

		void toggleGUIElement(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 1)
			{
				e.console->output(COLOR_ERROR, "gui_toggleelement: No id given");
				return;
			}
			e.gui->toggleHideElement((*argv)[0].c_str());
		}

		void timestampLog(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 1)
			{
				e.console->setLogTimestamp(-1);
				return;
			}
			bool v;

			try { v = convertBool((*argv)[0]); }
			catch (...) { return; }
			e.console->setLogTimestamp(static_cast<int>(v));
		}

		void printCWD(Engine &e, std::vector<std::string> *)
		{
			char *cwd;

#ifndef _MSC_VER
			cwd = getcwd(NULL, 0);
#else
			cwd = _getcwd(NULL, 0);
#endif
			e.console->output(std::string(cwd));
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
				file += Engine::getTimestamp() + ".png";
			else
				file += (*argv)[0] + ".png";
			id++;
			if (!shot.saveToFile(file))
				e.console->output(COLOR_ERROR, "screenshot: Unable to save screenshot");
		}

		void setLineCount(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 1)
			{
				e.console->output(COLOR_ERROR, "con_maxline: No value given");
				return;
			}
			e.console->setLineCount(atoi((*argv)[0].c_str()));
			e.console->initGraphics(e.getWindowSize());
		}

		void setConColor(Engine &e, std::vector<std::string> *argv)
		{
			sf::Color cbg, cinput;

			if (argv == NULL || argv->size() < 2
				|| (*argv)[0].length() < 9 || (*argv)[1].length() < 9)
				e.console->output(COLOR_ERROR, "con_color: Invalid colors or no colors given");
			cbg = Console::convertColorCode((*argv)[0]);
			cinput = Console::convertColorCode((*argv)[1]);
			e.console->setColor(cbg, cinput);
		}

		void setConCursor(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 1)
			{
				e.console->output(COLOR_ERROR, "con_cursor: No char given");
				return;
			}
			e.console->setCursor((*argv)[0][0]);
		}

		void setMaxFPS(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 1)
			{
				e.console->output(COLOR_ERROR, "fps_max: No value given");
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

		void help(Engine &e, std::vector<std::string> *)
		{
			e.console->output(COLOR_INFO, "Available commands: ");
			e.console->output("");
			for (cmdMap::iterator it = cmdlist.begin(); it != cmdlist.end(); it++)
			{
				e.console->insertLastOutput(it->first);
				if (std::next(it, 1) != cmdlist.end())
					e.console->insertLastOutput(", ");
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
				e.console->output(COLOR_ERROR, "unbind: No key or action given");
				return;
			}
			if (!e.keybinds->unbind((*argv)[0]))
				e.console->output(COLOR_ERROR, "unbind: Unable to unbind key or action");
		}

		void unbindall(Engine &e, std::vector<std::string> *)
		{
			e.keybinds->unbindall();
		}

		void windowSize(Engine &e, std::vector<std::string> *argv)
		{
			if (argv == NULL || argv->size() < 2)
			{
				e.console->output(COLOR_ERROR, "videomode: Mode incorrect or no mode given");
				return;
			}
			e.openWindow(atoi((*argv)[0].c_str()), atoi((*argv)[1].c_str()));
			e.console->initGraphics(e.getWindowSize());
		}

	}
}