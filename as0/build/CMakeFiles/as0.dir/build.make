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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/daniela_castorena/Github/381raylib/as0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/daniela_castorena/Github/381raylib/as0/build

# Include any dependencies generated for this target.
include CMakeFiles/as0.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/as0.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/as0.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/as0.dir/flags.make

CMakeFiles/as0.dir/main.cpp.o: CMakeFiles/as0.dir/flags.make
CMakeFiles/as0.dir/main.cpp.o: /Users/daniela_castorena/Github/381raylib/as0/main.cpp
CMakeFiles/as0.dir/main.cpp.o: CMakeFiles/as0.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/daniela_castorena/Github/381raylib/as0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/as0.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/as0.dir/main.cpp.o -MF CMakeFiles/as0.dir/main.cpp.o.d -o CMakeFiles/as0.dir/main.cpp.o -c /Users/daniela_castorena/Github/381raylib/as0/main.cpp

CMakeFiles/as0.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/as0.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daniela_castorena/Github/381raylib/as0/main.cpp > CMakeFiles/as0.dir/main.cpp.i

CMakeFiles/as0.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/as0.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daniela_castorena/Github/381raylib/as0/main.cpp -o CMakeFiles/as0.dir/main.cpp.s

# Object files for target as0
as0_OBJECTS = \
"CMakeFiles/as0.dir/main.cpp.o"

# External object files for target as0
as0_EXTERNAL_OBJECTS =

as0: CMakeFiles/as0.dir/main.cpp.o
as0: CMakeFiles/as0.dir/build.make
as0: /opt/homebrew/lib/libglfw.3.3.dylib
as0: CMakeFiles/as0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/daniela_castorena/Github/381raylib/as0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable as0"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/as0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/as0.dir/build: as0
.PHONY : CMakeFiles/as0.dir/build

CMakeFiles/as0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/as0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/as0.dir/clean

CMakeFiles/as0.dir/depend:
	cd /Users/daniela_castorena/Github/381raylib/as0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/daniela_castorena/Github/381raylib/as0 /Users/daniela_castorena/Github/381raylib/as0 /Users/daniela_castorena/Github/381raylib/as0/build /Users/daniela_castorena/Github/381raylib/as0/build /Users/daniela_castorena/Github/381raylib/as0/build/CMakeFiles/as0.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/as0.dir/depend

