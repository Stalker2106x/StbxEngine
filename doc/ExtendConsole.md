## Extend Console ##

The Engine has a Console component.\n
It comes with default actions and commands included\n
To add commands to console, you must emplace your command and its function pointer to Commands::cmdMap

The following example shows how to add a simple "echored" command to console
    Commands::cmdMap.emplace("echored", &echored);

    void echored(Engine &e, std::vector<std::string> *argv)
    {
	if (argv && argv->size() < 1)
	   Engine::console->output(COLOR_ERROR, "Nothing to echo");
	else
	   Engine::console->output(COLOR_ERROR, (*argv)[0]);
    }