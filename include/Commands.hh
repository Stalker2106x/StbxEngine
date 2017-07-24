/*!
 * @file      Commands.hh
 * @brief     Contains definition of basic console commands
 *
 *            This file implements all the system console commands operations
 */

#ifndef COMMANDS_HH_
#define COMMANDS_HH_

#include <map>
#include <vector>

namespace stb {

	class Engine;
	class Console;

	namespace Commands {

		typedef std::map<std::string, void(*)(Engine &, std::vector<std::string> *)> cmdMap;
		extern cmdMap cmdlist;

		bool convertBool(std::string &arg);
		std::vector<std::string> *getArgs(std::string &command);
		bool parseCmd(Engine &e, std::string);

		void bindCommand(Engine &e, std::vector<std::string> *);
		void bindList(Engine &e, std::vector<std::string> *);
		void consoleClear(Engine &e, std::vector<std::string> *);
		void consoleToggle(Engine &e, std::vector<std::string> *);
		void echo(Engine &e, std::vector<std::string> *);
		void execute(Engine &e, std::vector<std::string> *);
		void debugInfo(Engine &e, std::vector<std::string> *);
		void findCmd(Engine &e, std::vector<std::string> *);
		void toggleConLog(Engine &, std::vector<std::string> *);
		void writeToLog(Engine &, std::vector<std::string> *argv);
		void setConLog(Engine &, std::vector<std::string> *argv);
		void toggleGUIElement(Engine &, std::vector<std::string> *argv);
		void timestampLog(Engine &, std::vector<std::string> *argv);
		void printCWD(Engine &e, std::vector<std::string> *);
		void quit(Engine &e, std::vector<std::string> *);
		void screenshot(Engine &e, std::vector<std::string> *argv);
		void setLineCount(Engine &e, std::vector<std::string> *);
		void setConColor(Engine &e, std::vector<std::string> *);
		void setConCursor(Engine &e, std::vector<std::string> *);
		void setMaxFPS(Engine &e, std::vector<std::string> *);
		void setFullscreen(Engine &e, std::vector<std::string> *);
		void help(Engine &e, std::vector<std::string> *);
		void setVSync(Engine &e, std::vector<std::string> *);
		void unbind(Engine &e, std::vector<std::string> *);
		void unbindall(Engine &e, std::vector<std::string> *);
		void windowSize(Engine &e, std::vector<std::string> *);

	}
}
#endif
