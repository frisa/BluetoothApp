# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jan/Repositories/BluetoothApp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jan/Repositories/BluetoothApp/build

# Include any dependencies generated for this target.
include CMakeFiles/btapp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/btapp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/btapp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/btapp.dir/flags.make

CMakeFiles/btapp.dir/program.cpp.o: CMakeFiles/btapp.dir/flags.make
CMakeFiles/btapp.dir/program.cpp.o: /home/jan/Repositories/BluetoothApp/program.cpp
CMakeFiles/btapp.dir/program.cpp.o: CMakeFiles/btapp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/jan/Repositories/BluetoothApp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/btapp.dir/program.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/btapp.dir/program.cpp.o -MF CMakeFiles/btapp.dir/program.cpp.o.d -o CMakeFiles/btapp.dir/program.cpp.o -c /home/jan/Repositories/BluetoothApp/program.cpp

CMakeFiles/btapp.dir/program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/btapp.dir/program.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/Repositories/BluetoothApp/program.cpp > CMakeFiles/btapp.dir/program.cpp.i

CMakeFiles/btapp.dir/program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/btapp.dir/program.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/Repositories/BluetoothApp/program.cpp -o CMakeFiles/btapp.dir/program.cpp.s

# Object files for target btapp
btapp_OBJECTS = \
"CMakeFiles/btapp.dir/program.cpp.o"

# External object files for target btapp
btapp_EXTERNAL_OBJECTS =

btapp: CMakeFiles/btapp.dir/program.cpp.o
btapp: CMakeFiles/btapp.dir/build.make
btapp: CMakeFiles/btapp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/jan/Repositories/BluetoothApp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable btapp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/btapp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/btapp.dir/build: btapp
.PHONY : CMakeFiles/btapp.dir/build

CMakeFiles/btapp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/btapp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/btapp.dir/clean

CMakeFiles/btapp.dir/depend:
	cd /home/jan/Repositories/BluetoothApp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jan/Repositories/BluetoothApp /home/jan/Repositories/BluetoothApp /home/jan/Repositories/BluetoothApp/build /home/jan/Repositories/BluetoothApp/build /home/jan/Repositories/BluetoothApp/build/CMakeFiles/btapp.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/btapp.dir/depend
