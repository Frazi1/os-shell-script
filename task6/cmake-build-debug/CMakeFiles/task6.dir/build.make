# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/dmitry/Downloads/clion-2017.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/dmitry/Downloads/clion-2017.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dmitry/fkn/os/task6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dmitry/fkn/os/task6/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/task6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/task6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task6.dir/flags.make

CMakeFiles/task6.dir/main.c.o: CMakeFiles/task6.dir/flags.make
CMakeFiles/task6.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/fkn/os/task6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/task6.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/task6.dir/main.c.o   -c /home/dmitry/fkn/os/task6/main.c

CMakeFiles/task6.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/task6.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dmitry/fkn/os/task6/main.c > CMakeFiles/task6.dir/main.c.i

CMakeFiles/task6.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/task6.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dmitry/fkn/os/task6/main.c -o CMakeFiles/task6.dir/main.c.s

CMakeFiles/task6.dir/main.c.o.requires:

.PHONY : CMakeFiles/task6.dir/main.c.o.requires

CMakeFiles/task6.dir/main.c.o.provides: CMakeFiles/task6.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/task6.dir/build.make CMakeFiles/task6.dir/main.c.o.provides.build
.PHONY : CMakeFiles/task6.dir/main.c.o.provides

CMakeFiles/task6.dir/main.c.o.provides.build: CMakeFiles/task6.dir/main.c.o


# Object files for target task6
task6_OBJECTS = \
"CMakeFiles/task6.dir/main.c.o"

# External object files for target task6
task6_EXTERNAL_OBJECTS =

task6: CMakeFiles/task6.dir/main.c.o
task6: CMakeFiles/task6.dir/build.make
task6: CMakeFiles/task6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dmitry/fkn/os/task6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable task6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/task6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task6.dir/build: task6

.PHONY : CMakeFiles/task6.dir/build

CMakeFiles/task6.dir/requires: CMakeFiles/task6.dir/main.c.o.requires

.PHONY : CMakeFiles/task6.dir/requires

CMakeFiles/task6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/task6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/task6.dir/clean

CMakeFiles/task6.dir/depend:
	cd /home/dmitry/fkn/os/task6/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dmitry/fkn/os/task6 /home/dmitry/fkn/os/task6 /home/dmitry/fkn/os/task6/cmake-build-debug /home/dmitry/fkn/os/task6/cmake-build-debug /home/dmitry/fkn/os/task6/cmake-build-debug/CMakeFiles/task6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/task6.dir/depend

