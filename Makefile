# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:
.PHONY : .NOTPARALLEL

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /opt/stbxengine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/stbxengine

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /opt/stbxengine/CMakeFiles /opt/stbxengine/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /opt/stbxengine/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named sengine

# Build rule for target.
sengine: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 sengine
.PHONY : sengine

# fast build rule for target.
sengine/fast:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/build
.PHONY : sengine/fast

src/Commands.o: src/Commands.cpp.o
.PHONY : src/Commands.o

# target to build an object file
src/Commands.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Commands.cpp.o
.PHONY : src/Commands.cpp.o

src/Commands.i: src/Commands.cpp.i
.PHONY : src/Commands.i

# target to preprocess a source file
src/Commands.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Commands.cpp.i
.PHONY : src/Commands.cpp.i

src/Commands.s: src/Commands.cpp.s
.PHONY : src/Commands.s

# target to generate assembly for a file
src/Commands.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Commands.cpp.s
.PHONY : src/Commands.cpp.s

src/Console.o: src/Console.cpp.o
.PHONY : src/Console.o

# target to build an object file
src/Console.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Console.cpp.o
.PHONY : src/Console.cpp.o

src/Console.i: src/Console.cpp.i
.PHONY : src/Console.i

# target to preprocess a source file
src/Console.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Console.cpp.i
.PHONY : src/Console.cpp.i

src/Console.s: src/Console.cpp.s
.PHONY : src/Console.s

# target to generate assembly for a file
src/Console.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Console.cpp.s
.PHONY : src/Console.cpp.s

src/Control.o: src/Control.cpp.o
.PHONY : src/Control.o

# target to build an object file
src/Control.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Control.cpp.o
.PHONY : src/Control.cpp.o

src/Control.i: src/Control.cpp.i
.PHONY : src/Control.i

# target to preprocess a source file
src/Control.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Control.cpp.i
.PHONY : src/Control.cpp.i

src/Control.s: src/Control.cpp.s
.PHONY : src/Control.s

# target to generate assembly for a file
src/Control.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Control.cpp.s
.PHONY : src/Control.cpp.s

src/Engine.o: src/Engine.cpp.o
.PHONY : src/Engine.o

# target to build an object file
src/Engine.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Engine.cpp.o
.PHONY : src/Engine.cpp.o

src/Engine.i: src/Engine.cpp.i
.PHONY : src/Engine.i

# target to preprocess a source file
src/Engine.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Engine.cpp.i
.PHONY : src/Engine.cpp.i

src/Engine.s: src/Engine.cpp.s
.PHONY : src/Engine.s

# target to generate assembly for a file
src/Engine.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Engine.cpp.s
.PHONY : src/Engine.cpp.s

src/GUI.o: src/GUI.cpp.o
.PHONY : src/GUI.o

# target to build an object file
src/GUI.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUI.cpp.o
.PHONY : src/GUI.cpp.o

src/GUI.i: src/GUI.cpp.i
.PHONY : src/GUI.i

# target to preprocess a source file
src/GUI.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUI.cpp.i
.PHONY : src/GUI.cpp.i

src/GUI.s: src/GUI.cpp.s
.PHONY : src/GUI.s

# target to generate assembly for a file
src/GUI.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUI.cpp.s
.PHONY : src/GUI.cpp.s

src/GUIButton.o: src/GUIButton.cpp.o
.PHONY : src/GUIButton.o

# target to build an object file
src/GUIButton.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIButton.cpp.o
.PHONY : src/GUIButton.cpp.o

src/GUIButton.i: src/GUIButton.cpp.i
.PHONY : src/GUIButton.i

# target to preprocess a source file
src/GUIButton.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIButton.cpp.i
.PHONY : src/GUIButton.cpp.i

src/GUIButton.s: src/GUIButton.cpp.s
.PHONY : src/GUIButton.s

# target to generate assembly for a file
src/GUIButton.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIButton.cpp.s
.PHONY : src/GUIButton.cpp.s

src/GUIElement.o: src/GUIElement.cpp.o
.PHONY : src/GUIElement.o

# target to build an object file
src/GUIElement.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIElement.cpp.o
.PHONY : src/GUIElement.cpp.o

src/GUIElement.i: src/GUIElement.cpp.i
.PHONY : src/GUIElement.i

# target to preprocess a source file
src/GUIElement.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIElement.cpp.i
.PHONY : src/GUIElement.cpp.i

src/GUIElement.s: src/GUIElement.cpp.s
.PHONY : src/GUIElement.s

# target to generate assembly for a file
src/GUIElement.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIElement.cpp.s
.PHONY : src/GUIElement.cpp.s

src/GUIEntity.o: src/GUIEntity.cpp.o
.PHONY : src/GUIEntity.o

# target to build an object file
src/GUIEntity.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIEntity.cpp.o
.PHONY : src/GUIEntity.cpp.o

src/GUIEntity.i: src/GUIEntity.cpp.i
.PHONY : src/GUIEntity.i

# target to preprocess a source file
src/GUIEntity.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIEntity.cpp.i
.PHONY : src/GUIEntity.cpp.i

src/GUIEntity.s: src/GUIEntity.cpp.s
.PHONY : src/GUIEntity.s

# target to generate assembly for a file
src/GUIEntity.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIEntity.cpp.s
.PHONY : src/GUIEntity.cpp.s

src/GUIPanel.o: src/GUIPanel.cpp.o
.PHONY : src/GUIPanel.o

# target to build an object file
src/GUIPanel.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIPanel.cpp.o
.PHONY : src/GUIPanel.cpp.o

src/GUIPanel.i: src/GUIPanel.cpp.i
.PHONY : src/GUIPanel.i

# target to preprocess a source file
src/GUIPanel.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIPanel.cpp.i
.PHONY : src/GUIPanel.cpp.i

src/GUIPanel.s: src/GUIPanel.cpp.s
.PHONY : src/GUIPanel.s

# target to generate assembly for a file
src/GUIPanel.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/GUIPanel.cpp.s
.PHONY : src/GUIPanel.cpp.s

src/Keybinds.o: src/Keybinds.cpp.o
.PHONY : src/Keybinds.o

# target to build an object file
src/Keybinds.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Keybinds.cpp.o
.PHONY : src/Keybinds.cpp.o

src/Keybinds.i: src/Keybinds.cpp.i
.PHONY : src/Keybinds.i

# target to preprocess a source file
src/Keybinds.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Keybinds.cpp.i
.PHONY : src/Keybinds.cpp.i

src/Keybinds.s: src/Keybinds.cpp.s
.PHONY : src/Keybinds.s

# target to generate assembly for a file
src/Keybinds.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Keybinds.cpp.s
.PHONY : src/Keybinds.cpp.s

src/Menu.o: src/Menu.cpp.o
.PHONY : src/Menu.o

# target to build an object file
src/Menu.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Menu.cpp.o
.PHONY : src/Menu.cpp.o

src/Menu.i: src/Menu.cpp.i
.PHONY : src/Menu.i

# target to preprocess a source file
src/Menu.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Menu.cpp.i
.PHONY : src/Menu.cpp.i

src/Menu.s: src/Menu.cpp.s
.PHONY : src/Menu.s

# target to generate assembly for a file
src/Menu.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Menu.cpp.s
.PHONY : src/Menu.cpp.s

src/MenuItem.o: src/MenuItem.cpp.o
.PHONY : src/MenuItem.o

# target to build an object file
src/MenuItem.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/MenuItem.cpp.o
.PHONY : src/MenuItem.cpp.o

src/MenuItem.i: src/MenuItem.cpp.i
.PHONY : src/MenuItem.i

# target to preprocess a source file
src/MenuItem.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/MenuItem.cpp.i
.PHONY : src/MenuItem.cpp.i

src/MenuItem.s: src/MenuItem.cpp.s
.PHONY : src/MenuItem.s

# target to generate assembly for a file
src/MenuItem.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/MenuItem.cpp.s
.PHONY : src/MenuItem.cpp.s

src/Resolver.o: src/Resolver.cpp.o
.PHONY : src/Resolver.o

# target to build an object file
src/Resolver.cpp.o:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Resolver.cpp.o
.PHONY : src/Resolver.cpp.o

src/Resolver.i: src/Resolver.cpp.i
.PHONY : src/Resolver.i

# target to preprocess a source file
src/Resolver.cpp.i:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Resolver.cpp.i
.PHONY : src/Resolver.cpp.i

src/Resolver.s: src/Resolver.cpp.s
.PHONY : src/Resolver.s

# target to generate assembly for a file
src/Resolver.cpp.s:
	$(MAKE) -f CMakeFiles/sengine.dir/build.make CMakeFiles/sengine.dir/src/Resolver.cpp.s
.PHONY : src/Resolver.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... sengine"
	@echo "... src/Commands.o"
	@echo "... src/Commands.i"
	@echo "... src/Commands.s"
	@echo "... src/Console.o"
	@echo "... src/Console.i"
	@echo "... src/Console.s"
	@echo "... src/Control.o"
	@echo "... src/Control.i"
	@echo "... src/Control.s"
	@echo "... src/Engine.o"
	@echo "... src/Engine.i"
	@echo "... src/Engine.s"
	@echo "... src/GUI.o"
	@echo "... src/GUI.i"
	@echo "... src/GUI.s"
	@echo "... src/GUIButton.o"
	@echo "... src/GUIButton.i"
	@echo "... src/GUIButton.s"
	@echo "... src/GUIElement.o"
	@echo "... src/GUIElement.i"
	@echo "... src/GUIElement.s"
	@echo "... src/GUIEntity.o"
	@echo "... src/GUIEntity.i"
	@echo "... src/GUIEntity.s"
	@echo "... src/GUIPanel.o"
	@echo "... src/GUIPanel.i"
	@echo "... src/GUIPanel.s"
	@echo "... src/Keybinds.o"
	@echo "... src/Keybinds.i"
	@echo "... src/Keybinds.s"
	@echo "... src/Menu.o"
	@echo "... src/Menu.i"
	@echo "... src/Menu.s"
	@echo "... src/MenuItem.o"
	@echo "... src/MenuItem.i"
	@echo "... src/MenuItem.s"
	@echo "... src/Resolver.o"
	@echo "... src/Resolver.i"
	@echo "... src/Resolver.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

