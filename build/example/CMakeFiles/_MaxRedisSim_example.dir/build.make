# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mcong/study/github/RedisSim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mcong/study/github/RedisSim/build

# Include any dependencies generated for this target.
include example/CMakeFiles/_MaxRedisSim_example.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/_MaxRedisSim_example.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/_MaxRedisSim_example.dir/flags.make

example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o: example/CMakeFiles/_MaxRedisSim_example.dir/flags.make
example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o: ../example/example.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mcong/study/github/RedisSim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o"
	cd /home/mcong/study/github/RedisSim/build/example && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o -c /home/mcong/study/github/RedisSim/example/example.cpp

example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_MaxRedisSim_example.dir/example.cpp.i"
	cd /home/mcong/study/github/RedisSim/build/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mcong/study/github/RedisSim/example/example.cpp > CMakeFiles/_MaxRedisSim_example.dir/example.cpp.i

example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_MaxRedisSim_example.dir/example.cpp.s"
	cd /home/mcong/study/github/RedisSim/build/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mcong/study/github/RedisSim/example/example.cpp -o CMakeFiles/_MaxRedisSim_example.dir/example.cpp.s

example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o.requires:

.PHONY : example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o.requires

example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o.provides: example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o.requires
	$(MAKE) -f example/CMakeFiles/_MaxRedisSim_example.dir/build.make example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o.provides.build
.PHONY : example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o.provides

example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o.provides.build: example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o


# Object files for target _MaxRedisSim_example
_MaxRedisSim_example_OBJECTS = \
"CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o"

# External object files for target _MaxRedisSim_example
_MaxRedisSim_example_EXTERNAL_OBJECTS =

bin/MaxRedisSim_example: example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o
bin/MaxRedisSim_example: example/CMakeFiles/_MaxRedisSim_example.dir/build.make
bin/MaxRedisSim_example: ../lib/libMaxRedisSim.so.1.0.0
bin/MaxRedisSim_example: example/CMakeFiles/_MaxRedisSim_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mcong/study/github/RedisSim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/MaxRedisSim_example"
	cd /home/mcong/study/github/RedisSim/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_MaxRedisSim_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/_MaxRedisSim_example.dir/build: bin/MaxRedisSim_example

.PHONY : example/CMakeFiles/_MaxRedisSim_example.dir/build

example/CMakeFiles/_MaxRedisSim_example.dir/requires: example/CMakeFiles/_MaxRedisSim_example.dir/example.cpp.o.requires

.PHONY : example/CMakeFiles/_MaxRedisSim_example.dir/requires

example/CMakeFiles/_MaxRedisSim_example.dir/clean:
	cd /home/mcong/study/github/RedisSim/build/example && $(CMAKE_COMMAND) -P CMakeFiles/_MaxRedisSim_example.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/_MaxRedisSim_example.dir/clean

example/CMakeFiles/_MaxRedisSim_example.dir/depend:
	cd /home/mcong/study/github/RedisSim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mcong/study/github/RedisSim /home/mcong/study/github/RedisSim/example /home/mcong/study/github/RedisSim/build /home/mcong/study/github/RedisSim/build/example /home/mcong/study/github/RedisSim/build/example/CMakeFiles/_MaxRedisSim_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/_MaxRedisSim_example.dir/depend

