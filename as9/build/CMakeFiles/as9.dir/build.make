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
CMAKE_SOURCE_DIR = /Users/daniela_castorena/Desktop/381raylib/as9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/daniela_castorena/Desktop/381raylib/as9/build

# Include any dependencies generated for this target.
include CMakeFiles/as9.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/as9.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/as9.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/as9.dir/flags.make

CMakeFiles/as9.dir/src/as9.cpp.o: CMakeFiles/as9.dir/flags.make
CMakeFiles/as9.dir/src/as9.cpp.o: /Users/daniela_castorena/Desktop/381raylib/as9/src/as9.cpp
CMakeFiles/as9.dir/src/as9.cpp.o: CMakeFiles/as9.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/daniela_castorena/Desktop/381raylib/as9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/as9.dir/src/as9.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/as9.dir/src/as9.cpp.o -MF CMakeFiles/as9.dir/src/as9.cpp.o.d -o CMakeFiles/as9.dir/src/as9.cpp.o -c /Users/daniela_castorena/Desktop/381raylib/as9/src/as9.cpp

CMakeFiles/as9.dir/src/as9.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/as9.dir/src/as9.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daniela_castorena/Desktop/381raylib/as9/src/as9.cpp > CMakeFiles/as9.dir/src/as9.cpp.i

CMakeFiles/as9.dir/src/as9.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/as9.dir/src/as9.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daniela_castorena/Desktop/381raylib/as9/src/as9.cpp -o CMakeFiles/as9.dir/src/as9.cpp.s

# Object files for target as9
as9_OBJECTS = \
"CMakeFiles/as9.dir/src/as9.cpp.o"

# External object files for target as9
as9_EXTERNAL_OBJECTS =

as9: CMakeFiles/as9.dir/src/as9.cpp.o
as9: CMakeFiles/as9.dir/build.make
as9: raylib-cpp/raylib/raylib/libraylib.a
as9: raylib-cpp/raylib/raylib/external/glfw/src/libglfw3.a
as9: CMakeFiles/as9.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/daniela_castorena/Desktop/381raylib/as9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable as9"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/as9.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/as9.dir/build: as9
.PHONY : CMakeFiles/as9.dir/build

CMakeFiles/as9.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/as9.dir/cmake_clean.cmake
.PHONY : CMakeFiles/as9.dir/clean

CMakeFiles/as9.dir/depend:
	cd /Users/daniela_castorena/Desktop/381raylib/as9/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/daniela_castorena/Desktop/381raylib/as9 /Users/daniela_castorena/Desktop/381raylib/as9 /Users/daniela_castorena/Desktop/381raylib/as9/build /Users/daniela_castorena/Desktop/381raylib/as9/build /Users/daniela_castorena/Desktop/381raylib/as9/build/CMakeFiles/as9.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/as9.dir/depend

