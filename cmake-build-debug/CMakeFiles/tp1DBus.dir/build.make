# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /home/marcos/CLion-2020.1/clion-2020.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/marcos/CLion-2020.1/clion-2020.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marcos/CLionProjects/tp1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcos/CLionProjects/tp1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tp1DBus.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tp1DBus.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tp1DBus.dir/flags.make

CMakeFiles/tp1DBus.dir/main.c.o: CMakeFiles/tp1DBus.dir/flags.make
CMakeFiles/tp1DBus.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/CLionProjects/tp1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tp1DBus.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tp1DBus.dir/main.c.o   -c /home/marcos/CLionProjects/tp1/main.c

CMakeFiles/tp1DBus.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1DBus.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marcos/CLionProjects/tp1/main.c > CMakeFiles/tp1DBus.dir/main.c.i

CMakeFiles/tp1DBus.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1DBus.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marcos/CLionProjects/tp1/main.c -o CMakeFiles/tp1DBus.dir/main.c.s

CMakeFiles/tp1DBus.dir/ClientCommand.c.o: CMakeFiles/tp1DBus.dir/flags.make
CMakeFiles/tp1DBus.dir/ClientCommand.c.o: ../ClientCommand.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/CLionProjects/tp1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/tp1DBus.dir/ClientCommand.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tp1DBus.dir/ClientCommand.c.o   -c /home/marcos/CLionProjects/tp1/ClientCommand.c

CMakeFiles/tp1DBus.dir/ClientCommand.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1DBus.dir/ClientCommand.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marcos/CLionProjects/tp1/ClientCommand.c > CMakeFiles/tp1DBus.dir/ClientCommand.c.i

CMakeFiles/tp1DBus.dir/ClientCommand.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1DBus.dir/ClientCommand.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marcos/CLionProjects/tp1/ClientCommand.c -o CMakeFiles/tp1DBus.dir/ClientCommand.c.s

CMakeFiles/tp1DBus.dir/FileReader.c.o: CMakeFiles/tp1DBus.dir/flags.make
CMakeFiles/tp1DBus.dir/FileReader.c.o: ../FileReader.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/CLionProjects/tp1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/tp1DBus.dir/FileReader.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tp1DBus.dir/FileReader.c.o   -c /home/marcos/CLionProjects/tp1/FileReader.c

CMakeFiles/tp1DBus.dir/FileReader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1DBus.dir/FileReader.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marcos/CLionProjects/tp1/FileReader.c > CMakeFiles/tp1DBus.dir/FileReader.c.i

CMakeFiles/tp1DBus.dir/FileReader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1DBus.dir/FileReader.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marcos/CLionProjects/tp1/FileReader.c -o CMakeFiles/tp1DBus.dir/FileReader.c.s

CMakeFiles/tp1DBus.dir/stringExtra.c.o: CMakeFiles/tp1DBus.dir/flags.make
CMakeFiles/tp1DBus.dir/stringExtra.c.o: ../stringExtra.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/CLionProjects/tp1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/tp1DBus.dir/stringExtra.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tp1DBus.dir/stringExtra.c.o   -c /home/marcos/CLionProjects/tp1/stringExtra.c

CMakeFiles/tp1DBus.dir/stringExtra.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1DBus.dir/stringExtra.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marcos/CLionProjects/tp1/stringExtra.c > CMakeFiles/tp1DBus.dir/stringExtra.c.i

CMakeFiles/tp1DBus.dir/stringExtra.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1DBus.dir/stringExtra.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marcos/CLionProjects/tp1/stringExtra.c -o CMakeFiles/tp1DBus.dir/stringExtra.c.s

# Object files for target tp1DBus
tp1DBus_OBJECTS = \
"CMakeFiles/tp1DBus.dir/main.c.o" \
"CMakeFiles/tp1DBus.dir/ClientCommand.c.o" \
"CMakeFiles/tp1DBus.dir/FileReader.c.o" \
"CMakeFiles/tp1DBus.dir/stringExtra.c.o"

# External object files for target tp1DBus
tp1DBus_EXTERNAL_OBJECTS =

tp1DBus: CMakeFiles/tp1DBus.dir/main.c.o
tp1DBus: CMakeFiles/tp1DBus.dir/ClientCommand.c.o
tp1DBus: CMakeFiles/tp1DBus.dir/FileReader.c.o
tp1DBus: CMakeFiles/tp1DBus.dir/stringExtra.c.o
tp1DBus: CMakeFiles/tp1DBus.dir/build.make
tp1DBus: CMakeFiles/tp1DBus.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcos/CLionProjects/tp1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable tp1DBus"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tp1DBus.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tp1DBus.dir/build: tp1DBus

.PHONY : CMakeFiles/tp1DBus.dir/build

CMakeFiles/tp1DBus.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tp1DBus.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tp1DBus.dir/clean

CMakeFiles/tp1DBus.dir/depend:
	cd /home/marcos/CLionProjects/tp1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcos/CLionProjects/tp1 /home/marcos/CLionProjects/tp1 /home/marcos/CLionProjects/tp1/cmake-build-debug /home/marcos/CLionProjects/tp1/cmake-build-debug /home/marcos/CLionProjects/tp1/cmake-build-debug/CMakeFiles/tp1DBus.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tp1DBus.dir/depend

