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
CMAKE_SOURCE_DIR = /Users/daniela_castorena/Desktop/381raylib/as5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/daniela_castorena/Desktop/381raylib/as5/build

# Include any dependencies generated for this target.
include CMakeFiles/as5.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/as5.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/as5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/as5.dir/flags.make

CMakeFiles/as5.dir/src/VolumeControl.cpp.o: CMakeFiles/as5.dir/flags.make
CMakeFiles/as5.dir/src/VolumeControl.cpp.o: /Users/daniela_castorena/Desktop/381raylib/as5/src/VolumeControl.cpp
CMakeFiles/as5.dir/src/VolumeControl.cpp.o: CMakeFiles/as5.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/daniela_castorena/Desktop/381raylib/as5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/as5.dir/src/VolumeControl.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/as5.dir/src/VolumeControl.cpp.o -MF CMakeFiles/as5.dir/src/VolumeControl.cpp.o.d -o CMakeFiles/as5.dir/src/VolumeControl.cpp.o -c /Users/daniela_castorena/Desktop/381raylib/as5/src/VolumeControl.cpp

CMakeFiles/as5.dir/src/VolumeControl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/as5.dir/src/VolumeControl.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daniela_castorena/Desktop/381raylib/as5/src/VolumeControl.cpp > CMakeFiles/as5.dir/src/VolumeControl.cpp.i

CMakeFiles/as5.dir/src/VolumeControl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/as5.dir/src/VolumeControl.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daniela_castorena/Desktop/381raylib/as5/src/VolumeControl.cpp -o CMakeFiles/as5.dir/src/VolumeControl.cpp.s

CMakeFiles/as5.dir/src/main.cpp.o: CMakeFiles/as5.dir/flags.make
CMakeFiles/as5.dir/src/main.cpp.o: /Users/daniela_castorena/Desktop/381raylib/as5/src/main.cpp
CMakeFiles/as5.dir/src/main.cpp.o: CMakeFiles/as5.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/daniela_castorena/Desktop/381raylib/as5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/as5.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/as5.dir/src/main.cpp.o -MF CMakeFiles/as5.dir/src/main.cpp.o.d -o CMakeFiles/as5.dir/src/main.cpp.o -c /Users/daniela_castorena/Desktop/381raylib/as5/src/main.cpp

CMakeFiles/as5.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/as5.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daniela_castorena/Desktop/381raylib/as5/src/main.cpp > CMakeFiles/as5.dir/src/main.cpp.i

CMakeFiles/as5.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/as5.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daniela_castorena/Desktop/381raylib/as5/src/main.cpp -o CMakeFiles/as5.dir/src/main.cpp.s

CMakeFiles/as5.dir/src/raygui.cpp.o: CMakeFiles/as5.dir/flags.make
CMakeFiles/as5.dir/src/raygui.cpp.o: /Users/daniela_castorena/Desktop/381raylib/as5/src/raygui.cpp
CMakeFiles/as5.dir/src/raygui.cpp.o: CMakeFiles/as5.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/daniela_castorena/Desktop/381raylib/as5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/as5.dir/src/raygui.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/as5.dir/src/raygui.cpp.o -MF CMakeFiles/as5.dir/src/raygui.cpp.o.d -o CMakeFiles/as5.dir/src/raygui.cpp.o -c /Users/daniela_castorena/Desktop/381raylib/as5/src/raygui.cpp

CMakeFiles/as5.dir/src/raygui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/as5.dir/src/raygui.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daniela_castorena/Desktop/381raylib/as5/src/raygui.cpp > CMakeFiles/as5.dir/src/raygui.cpp.i

CMakeFiles/as5.dir/src/raygui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/as5.dir/src/raygui.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daniela_castorena/Desktop/381raylib/as5/src/raygui.cpp -o CMakeFiles/as5.dir/src/raygui.cpp.s

# Object files for target as5
as5_OBJECTS = \
"CMakeFiles/as5.dir/src/VolumeControl.cpp.o" \
"CMakeFiles/as5.dir/src/main.cpp.o" \
"CMakeFiles/as5.dir/src/raygui.cpp.o"

# External object files for target as5
as5_EXTERNAL_OBJECTS =

as5: CMakeFiles/as5.dir/src/VolumeControl.cpp.o
as5: CMakeFiles/as5.dir/src/main.cpp.o
as5: CMakeFiles/as5.dir/src/raygui.cpp.o
as5: CMakeFiles/as5.dir/build.make
as5: raylib-cpp/raylib/raylib/libraylib.a
as5: raylib-cpp/raylib/raylib/external/glfw/src/libglfw3.a
as5: CMakeFiles/as5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/daniela_castorena/Desktop/381raylib/as5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable as5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/as5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/as5.dir/build: as5
.PHONY : CMakeFiles/as5.dir/build

CMakeFiles/as5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/as5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/as5.dir/clean

CMakeFiles/as5.dir/depend:
	cd /Users/daniela_castorena/Desktop/381raylib/as5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/daniela_castorena/Desktop/381raylib/as5 /Users/daniela_castorena/Desktop/381raylib/as5 /Users/daniela_castorena/Desktop/381raylib/as5/build /Users/daniela_castorena/Desktop/381raylib/as5/build /Users/daniela_castorena/Desktop/381raylib/as5/build/CMakeFiles/as5.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/as5.dir/depend

