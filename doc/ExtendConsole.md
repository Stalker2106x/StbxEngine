## Extend Console ##

The Engine has a Console component.\n
It comes with default actions and commands included\n
To add commands to console, you must emplace your command and its function pointer to Commands::cmdMap\n

The following example shows how to add a simple "echoerror" command to console\n

    //In your engine constructor for example:
    stb::Commands::cmdlist.emplace("echored", &echored);

    void echored(Engine &e, std::vector<std::string> *argv) //Every console command should have this signature
    {
	if (argv && argv->size() < 1)
	   e.console->output(COLOR_ERROR, "Nothing to echo");
	else
	   e.console->output(COLOR_ERROR, (*argv)[0]);
    }