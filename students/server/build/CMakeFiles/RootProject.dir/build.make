# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server/build

# Include any dependencies generated for this target.
include CMakeFiles/RootProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RootProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RootProject.dir/flags.make

CMakeFiles/RootProject.dir/sources/main.cpp.o: CMakeFiles/RootProject.dir/flags.make
CMakeFiles/RootProject.dir/sources/main.cpp.o: ../sources/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RootProject.dir/sources/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RootProject.dir/sources/main.cpp.o -c /home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server/sources/main.cpp

CMakeFiles/RootProject.dir/sources/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RootProject.dir/sources/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server/sources/main.cpp > CMakeFiles/RootProject.dir/sources/main.cpp.i

CMakeFiles/RootProject.dir/sources/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RootProject.dir/sources/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server/sources/main.cpp -o CMakeFiles/RootProject.dir/sources/main.cpp.s

CMakeFiles/RootProject.dir/sources/main.cpp.o.requires:

.PHONY : CMakeFiles/RootProject.dir/sources/main.cpp.o.requires

CMakeFiles/RootProject.dir/sources/main.cpp.o.provides: CMakeFiles/RootProject.dir/sources/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/RootProject.dir/build.make CMakeFiles/RootProject.dir/sources/main.cpp.o.provides.build
.PHONY : CMakeFiles/RootProject.dir/sources/main.cpp.o.provides

CMakeFiles/RootProject.dir/sources/main.cpp.o.provides.build: CMakeFiles/RootProject.dir/sources/main.cpp.o


# Object files for target RootProject
RootProject_OBJECTS = \
"CMakeFiles/RootProject.dir/sources/main.cpp.o"

# External object files for target RootProject
RootProject_EXTERNAL_OBJECTS =

RootProject: CMakeFiles/RootProject.dir/sources/main.cpp.o
RootProject: CMakeFiles/RootProject.dir/build.make
RootProject: CMakeFiles/RootProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RootProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RootProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RootProject.dir/build: RootProject

.PHONY : CMakeFiles/RootProject.dir/build

CMakeFiles/RootProject.dir/requires: CMakeFiles/RootProject.dir/sources/main.cpp.o.requires

.PHONY : CMakeFiles/RootProject.dir/requires

CMakeFiles/RootProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RootProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RootProject.dir/clean

CMakeFiles/RootProject.dir/depend:
	cd /home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server /home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server /home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server/build /home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server/build /home/piotrek/Pulpit/ChatApp/projektzespolowy/students/server/build/CMakeFiles/RootProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RootProject.dir/depend

