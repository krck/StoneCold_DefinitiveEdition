# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Projects\StoneCold_DefinitiveEdition

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Projects\StoneCold_DefinitiveEdition\build\Release

# Include any dependencies generated for this target.
include CMakeFiles/stone_cold.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/stone_cold.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/stone_cold.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stone_cold.dir/flags.make

CMakeFiles/stone_cold.dir/src/Application.cpp.obj: CMakeFiles/stone_cold.dir/flags.make
CMakeFiles/stone_cold.dir/src/Application.cpp.obj: CMakeFiles/stone_cold.dir/includes_CXX.rsp
CMakeFiles/stone_cold.dir/src/Application.cpp.obj: ../../src/Application.cpp
CMakeFiles/stone_cold.dir/src/Application.cpp.obj: CMakeFiles/stone_cold.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stone_cold.dir/src/Application.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/stone_cold.dir/src/Application.cpp.obj -MF CMakeFiles\stone_cold.dir\src\Application.cpp.obj.d -o CMakeFiles\stone_cold.dir\src\Application.cpp.obj -c D:\Projects\StoneCold_DefinitiveEdition\src\Application.cpp

CMakeFiles/stone_cold.dir/src/Application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stone_cold.dir/src/Application.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\StoneCold_DefinitiveEdition\src\Application.cpp > CMakeFiles\stone_cold.dir\src\Application.cpp.i

CMakeFiles/stone_cold.dir/src/Application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stone_cold.dir/src/Application.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\StoneCold_DefinitiveEdition\src\Application.cpp -o CMakeFiles\stone_cold.dir\src\Application.cpp.s

# Object files for target stone_cold
stone_cold_OBJECTS = \
"CMakeFiles/stone_cold.dir/src/Application.cpp.obj"

# External object files for target stone_cold
stone_cold_EXTERNAL_OBJECTS =

x64/bin/stone_cold.exe: CMakeFiles/stone_cold.dir/src/Application.cpp.obj
x64/bin/stone_cold.exe: CMakeFiles/stone_cold.dir/build.make
x64/bin/stone_cold.exe: x64/lib/libsfml-graphics.a
x64/bin/stone_cold.exe: x64/lib/libsfml-window.a
x64/bin/stone_cold.exe: x64/lib/libsfml-system.a
x64/bin/stone_cold.exe: CMakeFiles/stone_cold.dir/linklibs.rsp
x64/bin/stone_cold.exe: CMakeFiles/stone_cold.dir/objects1.rsp
x64/bin/stone_cold.exe: CMakeFiles/stone_cold.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable x64\bin\stone_cold.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\stone_cold.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stone_cold.dir/build: x64/bin/stone_cold.exe
.PHONY : CMakeFiles/stone_cold.dir/build

CMakeFiles/stone_cold.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\stone_cold.dir\cmake_clean.cmake
.PHONY : CMakeFiles/stone_cold.dir/clean

CMakeFiles/stone_cold.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Projects\StoneCold_DefinitiveEdition D:\Projects\StoneCold_DefinitiveEdition D:\Projects\StoneCold_DefinitiveEdition\build\Release D:\Projects\StoneCold_DefinitiveEdition\build\Release D:\Projects\StoneCold_DefinitiveEdition\build\Release\CMakeFiles\stone_cold.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stone_cold.dir/depend
