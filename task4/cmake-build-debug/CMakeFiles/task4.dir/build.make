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
CMAKE_SOURCE_DIR = /home/dmitry/fkn/os/task4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dmitry/fkn/os/task4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/task4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/task4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task4.dir/flags.make

CMakeFiles/task4.dir/main.c.o: CMakeFiles/task4.dir/flags.make
CMakeFiles/task4.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/fkn/os/task4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/task4.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/task4.dir/main.c.o   -c /home/dmitry/fkn/os/task4/main.c

CMakeFiles/task4.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/task4.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dmitry/fkn/os/task4/main.c > CMakeFiles/task4.dir/main.c.i

CMakeFiles/task4.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/task4.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dmitry/fkn/os/task4/main.c -o CMakeFiles/task4.dir/main.c.s

CMakeFiles/task4.dir/main.c.o.requires:

.PHONY : CMakeFiles/task4.dir/main.c.o.requires

CMakeFiles/task4.dir/main.c.o.provides: CMakeFiles/task4.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/task4.dir/build.make CMakeFiles/task4.dir/main.c.o.provides.build
.PHONY : CMakeFiles/task4.dir/main.c.o.provides

CMakeFiles/task4.dir/main.c.o.provides.build: CMakeFiles/task4.dir/main.c.o


CMakeFiles/task4.dir/structs.c.o: CMakeFiles/task4.dir/flags.make
CMakeFiles/task4.dir/structs.c.o: ../structs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/fkn/os/task4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/task4.dir/structs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/task4.dir/structs.c.o   -c /home/dmitry/fkn/os/task4/structs.c

CMakeFiles/task4.dir/structs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/task4.dir/structs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dmitry/fkn/os/task4/structs.c > CMakeFiles/task4.dir/structs.c.i

CMakeFiles/task4.dir/structs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/task4.dir/structs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dmitry/fkn/os/task4/structs.c -o CMakeFiles/task4.dir/structs.c.s

CMakeFiles/task4.dir/structs.c.o.requires:

.PHONY : CMakeFiles/task4.dir/structs.c.o.requires

CMakeFiles/task4.dir/structs.c.o.provides: CMakeFiles/task4.dir/structs.c.o.requires
	$(MAKE) -f CMakeFiles/task4.dir/build.make CMakeFiles/task4.dir/structs.c.o.provides.build
.PHONY : CMakeFiles/task4.dir/structs.c.o.provides

CMakeFiles/task4.dir/structs.c.o.provides.build: CMakeFiles/task4.dir/structs.c.o


CMakeFiles/task4.dir/linked_list.c.o: CMakeFiles/task4.dir/flags.make
CMakeFiles/task4.dir/linked_list.c.o: ../linked_list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/fkn/os/task4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/task4.dir/linked_list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/task4.dir/linked_list.c.o   -c /home/dmitry/fkn/os/task4/linked_list.c

CMakeFiles/task4.dir/linked_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/task4.dir/linked_list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dmitry/fkn/os/task4/linked_list.c > CMakeFiles/task4.dir/linked_list.c.i

CMakeFiles/task4.dir/linked_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/task4.dir/linked_list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dmitry/fkn/os/task4/linked_list.c -o CMakeFiles/task4.dir/linked_list.c.s

CMakeFiles/task4.dir/linked_list.c.o.requires:

.PHONY : CMakeFiles/task4.dir/linked_list.c.o.requires

CMakeFiles/task4.dir/linked_list.c.o.provides: CMakeFiles/task4.dir/linked_list.c.o.requires
	$(MAKE) -f CMakeFiles/task4.dir/build.make CMakeFiles/task4.dir/linked_list.c.o.provides.build
.PHONY : CMakeFiles/task4.dir/linked_list.c.o.provides

CMakeFiles/task4.dir/linked_list.c.o.provides.build: CMakeFiles/task4.dir/linked_list.c.o


# Object files for target task4
task4_OBJECTS = \
"CMakeFiles/task4.dir/main.c.o" \
"CMakeFiles/task4.dir/structs.c.o" \
"CMakeFiles/task4.dir/linked_list.c.o"

# External object files for target task4
task4_EXTERNAL_OBJECTS =

task4: CMakeFiles/task4.dir/main.c.o
task4: CMakeFiles/task4.dir/structs.c.o
task4: CMakeFiles/task4.dir/linked_list.c.o
task4: CMakeFiles/task4.dir/build.make
task4: CMakeFiles/task4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dmitry/fkn/os/task4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable task4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/task4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task4.dir/build: task4

.PHONY : CMakeFiles/task4.dir/build

CMakeFiles/task4.dir/requires: CMakeFiles/task4.dir/main.c.o.requires
CMakeFiles/task4.dir/requires: CMakeFiles/task4.dir/structs.c.o.requires
CMakeFiles/task4.dir/requires: CMakeFiles/task4.dir/linked_list.c.o.requires

.PHONY : CMakeFiles/task4.dir/requires

CMakeFiles/task4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/task4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/task4.dir/clean

CMakeFiles/task4.dir/depend:
	cd /home/dmitry/fkn/os/task4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dmitry/fkn/os/task4 /home/dmitry/fkn/os/task4 /home/dmitry/fkn/os/task4/cmake-build-debug /home/dmitry/fkn/os/task4/cmake-build-debug /home/dmitry/fkn/os/task4/cmake-build-debug/CMakeFiles/task4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/task4.dir/depend

