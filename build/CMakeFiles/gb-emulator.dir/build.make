# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/joost/Documents/projects/gb-emulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joost/Documents/projects/gb-emulator/build

# Include any dependencies generated for this target.
include CMakeFiles/gb-emulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gb-emulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gb-emulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gb-emulator.dir/flags.make

CMakeFiles/gb-emulator.dir/main.c.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/main.c.o: /home/joost/Documents/projects/gb-emulator/main.c
CMakeFiles/gb-emulator.dir/main.c.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/joost/Documents/projects/gb-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gb-emulator.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/main.c.o -MF CMakeFiles/gb-emulator.dir/main.c.o.d -o CMakeFiles/gb-emulator.dir/main.c.o -c /home/joost/Documents/projects/gb-emulator/main.c

CMakeFiles/gb-emulator.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/gb-emulator.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/joost/Documents/projects/gb-emulator/main.c > CMakeFiles/gb-emulator.dir/main.c.i

CMakeFiles/gb-emulator.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/gb-emulator.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/joost/Documents/projects/gb-emulator/main.c -o CMakeFiles/gb-emulator.dir/main.c.s

CMakeFiles/gb-emulator.dir/registers.c.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/registers.c.o: /home/joost/Documents/projects/gb-emulator/registers.c
CMakeFiles/gb-emulator.dir/registers.c.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/joost/Documents/projects/gb-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/gb-emulator.dir/registers.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/registers.c.o -MF CMakeFiles/gb-emulator.dir/registers.c.o.d -o CMakeFiles/gb-emulator.dir/registers.c.o -c /home/joost/Documents/projects/gb-emulator/registers.c

CMakeFiles/gb-emulator.dir/registers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/gb-emulator.dir/registers.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/joost/Documents/projects/gb-emulator/registers.c > CMakeFiles/gb-emulator.dir/registers.c.i

CMakeFiles/gb-emulator.dir/registers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/gb-emulator.dir/registers.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/joost/Documents/projects/gb-emulator/registers.c -o CMakeFiles/gb-emulator.dir/registers.c.s

# Object files for target gb-emulator
gb__emulator_OBJECTS = \
"CMakeFiles/gb-emulator.dir/main.c.o" \
"CMakeFiles/gb-emulator.dir/registers.c.o"

# External object files for target gb-emulator
gb__emulator_EXTERNAL_OBJECTS =

gb-emulator: CMakeFiles/gb-emulator.dir/main.c.o
gb-emulator: CMakeFiles/gb-emulator.dir/registers.c.o
gb-emulator: CMakeFiles/gb-emulator.dir/build.make
gb-emulator: CMakeFiles/gb-emulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/joost/Documents/projects/gb-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable gb-emulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gb-emulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gb-emulator.dir/build: gb-emulator
.PHONY : CMakeFiles/gb-emulator.dir/build

CMakeFiles/gb-emulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gb-emulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gb-emulator.dir/clean

CMakeFiles/gb-emulator.dir/depend:
	cd /home/joost/Documents/projects/gb-emulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joost/Documents/projects/gb-emulator /home/joost/Documents/projects/gb-emulator /home/joost/Documents/projects/gb-emulator/build /home/joost/Documents/projects/gb-emulator/build /home/joost/Documents/projects/gb-emulator/build/CMakeFiles/gb-emulator.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/gb-emulator.dir/depend

