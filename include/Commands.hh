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

	struct Commands {

		typedef void(*cmdFptr)(std::vector<std::string> *);
		typedef std::map<std::string, cmdFptr> cmdMap;
		typedef std::map<std::string, std::string> aliasMap;
		static cmdMap cmdlist; //Association map
		static aliasMap aliaslist; //Association map

		//Command Manipulation
		static bool convertBool(std::string arg);
		static std::vector<std::string> *getArgs(const std::string &command, std::vector<std::string> *argv);
		static bool parseCmd(const std::string &cmd, std::vector<std::string> *argv = NULL);

		//Command system functors
		static void alias(std::vector<std::string> *);
		static void bindCommand(std::vector<std::string> *);
		static void bindList(std::vector<std::string> *);
		static void consoleClear(std::vector<std::string> *);
		static void consoleToggle(std::vector<std::string> *);
		static void echo(std::vector<std::string> *);
		static void execute(std::vector<std::string> *);
		static void debugInfo(std::vector<std::string> *);
		static void findCmd(std::vector<std::string> *);
		static void toggleConLog(std::vector<std::string> *);
		static void writeToLog(std::vector<std::string> *argv);
		static void setConLog(std::vector<std::string> *argv);
		static void toggleGUIElement(std::vector<std::string> *argv);
		static void timestampLog(std::vector<std::string> *argv);
		static void printCWD(std::vector<std::string> *);
		static void quit(std::vector<std::string> *);
		static void screenshot(std::vector<std::string> *argv);
		static void setConColor(std::vector<std::string> *);
		static void setConCursor(std::vector<std::string> *);
		static void setMaxFPS(std::vector<std::string> *);
		static void setFullscreen(std::vector<std::string> *);
		static void help(std::vector<std::string> *);
		static void setVSync(std::vector<std::string> *);
		static void unbind(std::vector<std::string> *);
		static void unbindall(std::vector<std::string> *);
		static void windowSize(std::vector<std::string> *);

	};
}
#endif
