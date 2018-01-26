## Extend Console ##

The Engine has a very flexible Console component.\n
It comes with default actions and commands included described in next section.\n

### Default Commands ###

<table>
<tr><th>command</th><th>action</th></tr>
<tr><td>bind [string:key] [string:command]</td><td>bind a [command] to a [key]</td></tr>
<tr><td>bindlist</td><td>show list of bound commands</td></tr>
<tr><td>clear</td><td>clear console screen</td></tr>
<tr><td>con_color [string:color]</td><td>set color (hex format: "#RRGGBB") of console background</td></tr>
<tr><td>cwd</td><td>print current working directory of executable</td></tr>
<tr><td>debuginfo</td><td>toggle show/hide debugInfo panel</td></tr>
<tr><td>echo [string:message]</td><td>print [message] in console</td></tr>
<tr><td>exec [string:file]</td><td>execute a [file] line by line as commands</td></tr>
<tr><td>exit</td><td>quit engine to desktop</td></tr>
<tr><td>find [string:predicate]</td><td>find a command that contains the [predicate]</td></tr>
<tr><td>fps_max [integer:fps]</td><td>set maximum [fps] (frames per second) of window</td></tr>
<tr><td>fullscreen (boolean:toggle)</td><td>(toggle) Fullscreen mode on or off. (no parameter toggles opposite current state)</td></tr>
<tr><td>gui_toggleelement [string:id]</td><td>show/hide GUI Element of id [id]</td></tr>
<tr><td>help</td><td>show a list of all commands</td></tr>
<tr><td>log_enable (boolean:toggle)</td><td>(toggle) logging of console on or off (no parameter toggles opposite current state)</td></tr>
<tr><td>log_write [string:message]</td><td>write [message] to log</td></tr>
<tr><td>log_file [string:path]</td><td>set console log file [path]</td></tr>
<tr><td>log_timestamp (boolean:toggle)</td><td>(toggle) timestamp on or off in log file (no parameter toggles opposite current state)</td></tr>
<tr><td>screenshot</td><td>take a screenshot of the current scene</td></tr>
<tr><td>toggleconsole</td><td>show/hide console</td></tr>
<tr><td>unbind [string:key]</td><td>unbind given [key]</td></tr>
<tr><td>unbindall</td><td>unbind every bound key</td></tr>
<tr><td>videomode [string:resolution]</td><td>set [resolution] of window (format: "WIDTHxHEIGHT" with integer values)</td></tr>
<tr><td>vsync (boolean:toggle)</td><td>(toggle) Virtual Synchronisation on or off. (no parameter toggles opposite current state)</td></tr>
</table>

### Adding your own commands ###

To add commands to console, you must emplace your command and its function pointer to Commands::cmdlist\n

The following example shows how to add a simple "echoerror" command to console\n

    //Emplace your commands preferably before init of engine in case anything uses it inside init itself
    stb::Commands::cmdlist.emplace("echoerror", &echoerror);

    void echoerror(argumentArray *argv) //Every console command should have this signature, argumentArray is a simple std::deque<std::string>
    {
	     if (argv && argv->size() < 1) //You can check argv in "c-style"
	      Engine::console->output("Nothing to echo");
	     else
	      Engine::console->output((*argv)[0]); //You can access command arguments from within the argv deque
    }
