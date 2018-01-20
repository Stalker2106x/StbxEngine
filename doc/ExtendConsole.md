## Extend Console ##

The Engine has a very flexible Console component.\n
It comes with default actions and commands included as follows:\n

<table>
<tr><th>command</th><th>action</th></tr>
<tr><td>bind</td><td>bind a command to a key</td></tr>
<tr><td>bindlist</td><td>show list of bound commands</td></tr>
<tr><td>clear</td><td>clear console screen</td></tr>
<tr><td>con_color</td><td>set color of console</td></tr>
<tr><td>con_cursor</td><td>set console cursor</td></tr>
<tr><td>cwd</td><td>print current working directory of executable</td></tr>
<tr><td>debuginfo</td><td>toggle show/hide debugInfo panel</td></tr>
<tr><td>echo</td><td>print text in console</td></tr>
<tr><td>exec</td><td>execute a file containing commands</td></tr>
<tr><td>exit</td><td>quit engine</td></tr>
<tr><td>find</td><td>find a command with given string</td></tr>
<tr><td>fps_max</td><td>set max FPS</td></tr>
<tr><td>fullscreen</td><td>toggle Fullscreen mode</td></tr>
<tr><td>gui_changescreen</td><td>change screen</td></tr>
<tr><td>gui_toggleelement</td><td>toggle GUI Element</td></tr>
<tr><td>help</td><td>show help</td></tr>
<tr><td>log_enable</td><td>toggle on/off logging of console</td></tr>
<tr><td>log_write</td><td>write To Log</td></tr>
<tr><td>log_file</td><td>setConLog</td></tr>
<tr><td>log_timestamp</td><td>timestampLog</td></tr>
<tr><td>screenshot</td><td>screenshot</td></tr>
<tr><td>toggleconsole</td><td>consoleToggle</td></tr>
<tr><td>unbind</td><td>unbind</td></tr>
<tr><td>unbindall</td><td>&unbindall</td></tr>
<tr><td>videomode</td><td>&windowSize</td></tr>
<tr><td>vsync</td><td>setVSync</td></tr>
</table>

To add commands to console, you must emplace your command and its function pointer to Commands::cmdMap\n

The following example shows how to add a simple "echoerror" command to console\n

    //Emplace your commands preferably before init of engine
    stb::Commands::cmdlist.emplace("echoerror", &echoerror);

    void echoerror(Engine &e, std::vector<std::string> *argv) //Every console command should have this signature
    {
	     if (argv && argv->size() < 1) //You can check argv "c-style"
	      e.console->output(COLOR_ERROR, "Nothing to echo");
	     else
	      e.console->output(COLOR_ERROR, (*argv)[0]); //You can access command arguments from within the vector
    }
