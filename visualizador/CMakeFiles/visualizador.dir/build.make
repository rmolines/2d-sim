# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/rmolines/github/2d-sim/visualizador

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rmolines/github/2d-sim/visualizador

# Include any dependencies generated for this target.
include CMakeFiles/visualizador.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/visualizador.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/visualizador.dir/flags.make

CMakeFiles/visualizador.dir/main.cpp.o: CMakeFiles/visualizador.dir/flags.make
CMakeFiles/visualizador.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rmolines/github/2d-sim/visualizador/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/visualizador.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/visualizador.dir/main.cpp.o -c /home/rmolines/github/2d-sim/visualizador/main.cpp

CMakeFiles/visualizador.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/visualizador.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rmolines/github/2d-sim/visualizador/main.cpp > CMakeFiles/visualizador.dir/main.cpp.i

CMakeFiles/visualizador.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/visualizador.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rmolines/github/2d-sim/visualizador/main.cpp -o CMakeFiles/visualizador.dir/main.cpp.s

CMakeFiles/visualizador.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/visualizador.dir/main.cpp.o.requires

CMakeFiles/visualizador.dir/main.cpp.o.provides: CMakeFiles/visualizador.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/visualizador.dir/build.make CMakeFiles/visualizador.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/visualizador.dir/main.cpp.o.provides

CMakeFiles/visualizador.dir/main.cpp.o.provides.build: CMakeFiles/visualizador.dir/main.cpp.o


CMakeFiles/visualizador.dir/visualizador.cpp.o: CMakeFiles/visualizador.dir/flags.make
CMakeFiles/visualizador.dir/visualizador.cpp.o: visualizador.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rmolines/github/2d-sim/visualizador/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/visualizador.dir/visualizador.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/visualizador.dir/visualizador.cpp.o -c /home/rmolines/github/2d-sim/visualizador/visualizador.cpp

CMakeFiles/visualizador.dir/visualizador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/visualizador.dir/visualizador.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rmolines/github/2d-sim/visualizador/visualizador.cpp > CMakeFiles/visualizador.dir/visualizador.cpp.i

CMakeFiles/visualizador.dir/visualizador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/visualizador.dir/visualizador.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rmolines/github/2d-sim/visualizador/visualizador.cpp -o CMakeFiles/visualizador.dir/visualizador.cpp.s

CMakeFiles/visualizador.dir/visualizador.cpp.o.requires:

.PHONY : CMakeFiles/visualizador.dir/visualizador.cpp.o.requires

CMakeFiles/visualizador.dir/visualizador.cpp.o.provides: CMakeFiles/visualizador.dir/visualizador.cpp.o.requires
	$(MAKE) -f CMakeFiles/visualizador.dir/build.make CMakeFiles/visualizador.dir/visualizador.cpp.o.provides.build
.PHONY : CMakeFiles/visualizador.dir/visualizador.cpp.o.provides

CMakeFiles/visualizador.dir/visualizador.cpp.o.provides.build: CMakeFiles/visualizador.dir/visualizador.cpp.o


# Object files for target visualizador
visualizador_OBJECTS = \
"CMakeFiles/visualizador.dir/main.cpp.o" \
"CMakeFiles/visualizador.dir/visualizador.cpp.o"

# External object files for target visualizador
visualizador_EXTERNAL_OBJECTS =

visualizador: CMakeFiles/visualizador.dir/main.cpp.o
visualizador: CMakeFiles/visualizador.dir/visualizador.cpp.o
visualizador: CMakeFiles/visualizador.dir/build.make
visualizador: CMakeFiles/visualizador.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rmolines/github/2d-sim/visualizador/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable visualizador"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/visualizador.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/visualizador.dir/build: visualizador

.PHONY : CMakeFiles/visualizador.dir/build

CMakeFiles/visualizador.dir/requires: CMakeFiles/visualizador.dir/main.cpp.o.requires
CMakeFiles/visualizador.dir/requires: CMakeFiles/visualizador.dir/visualizador.cpp.o.requires

.PHONY : CMakeFiles/visualizador.dir/requires

CMakeFiles/visualizador.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/visualizador.dir/cmake_clean.cmake
.PHONY : CMakeFiles/visualizador.dir/clean

CMakeFiles/visualizador.dir/depend:
	cd /home/rmolines/github/2d-sim/visualizador && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rmolines/github/2d-sim/visualizador /home/rmolines/github/2d-sim/visualizador /home/rmolines/github/2d-sim/visualizador /home/rmolines/github/2d-sim/visualizador /home/rmolines/github/2d-sim/visualizador/CMakeFiles/visualizador.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/visualizador.dir/depend

