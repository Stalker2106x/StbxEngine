/*!
 * @file      Commands.hh
 * @brief     Contains definition of basic console commands
 *
 *            This file implements all the system console commands operations
 */

#ifndef COMMANDS_HH_
#define COMMANDS_HH_

#include <map>
#include <deque>

namespace stb {

	typedef std::deque<std::string> argumentArray;
	typedef void(*cmdFptr)(argumentArray *);
	typedef std::map<std::string, cmdFptr> cmdMap;
	typedef std::map<std::string, std::string> aliasMap;

	struct Commands {

		//Command Manipulation
		static bool convertBool(std::string arg);
		static argumentArray *getArgs(const std::string &command, argumentArray *argv);
		static bool parseCmd(const std::string &cmd, argumentArray *argv = NULL);

		//Command system functors
		static void alias(argumentArray *);
		static void bindCommand(argumentArray *);
		static void bindList(argumentArray *);
		static void consoleClear(argumentArray *);
		static void consoleToggle(argumentArray *);
		static void echo(argumentArray *);
		static void execute(argumentArray *);
		static void debugInfo(argumentArray *);
		static void findCmd(argumentArray *);
		static void toggleConLog(argumentArray *);
		static void writeToLog(argumentArray *argv);
		static void setConLog(argumentArray *argv);
		static void toggleGUIElement(argumentArray *argv);
		static void timestampLog(argumentArray *argv);
		static void printCWD(argumentArray *);
		static void quit(argumentArray *);
		static void screenshot(argumentArray *argv);
		static void setConColor(argumentArray *);
		static void setConCursor(argumentArray *);
		static void setMaxFPS(argumentArray *);
		static void setFullscreen(argumentArray *);
		static void help(argumentArray *);
		static void setVSync(argumentArray *);
		static void unbind(argumentArray *);
		static void unbindall(argumentArray *);
		static void windowSize(argumentArray *);

		static cmdMap cmdlist; //Association map
		static aliasMap aliaslist; //Association map
	};
}
#endif
