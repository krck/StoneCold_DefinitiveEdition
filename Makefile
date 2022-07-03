# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_BINARY_DIR = D:\Projects\StoneCold_DefinitiveEdition

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target package
package: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Run CPack packaging tool..."
	"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cpack.exe" --config ./CPackConfig.cmake
.PHONY : package

# Special rule for the target package
package/fast: package
.PHONY : package/fast

# Special rule for the target package_source
package_source:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Run CPack packaging tool for source..."
	"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cpack.exe" --config ./CPackSourceConfig.cmake D:/Projects/StoneCold_DefinitiveEdition/CPackSourceConfig.cmake
.PHONY : package_source

# Special rule for the target package_source
package_source/fast: package_source
.PHONY : package_source/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E echo "No interactive CMake dialog available."
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\" \"bin\" \"devel\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start D:\Projects\StoneCold_DefinitiveEdition\CMakeFiles D:\Projects\StoneCold_DefinitiveEdition\\CMakeFiles\progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start D:\Projects\StoneCold_DefinitiveEdition\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named stone_cold

# Build rule for target.
stone_cold: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 stone_cold
.PHONY : stone_cold

# fast build rule for target.
stone_cold/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\stone_cold.dir\build.make CMakeFiles/stone_cold.dir/build
.PHONY : stone_cold/fast

#=============================================================================
# Target rules for targets named sfml-system

# Build rule for target.
sfml-system: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 sfml-system
.PHONY : sfml-system

# fast build rule for target.
sfml-system/fast:
	$(MAKE) $(MAKESILENT) -f external\sfml\src\SFML\System\CMakeFiles\sfml-system.dir\build.make external/sfml/src/SFML/System/CMakeFiles/sfml-system.dir/build
.PHONY : sfml-system/fast

#=============================================================================
# Target rules for targets named sfml-main

# Build rule for target.
sfml-main: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 sfml-main
.PHONY : sfml-main

# fast build rule for target.
sfml-main/fast:
	$(MAKE) $(MAKESILENT) -f external\sfml\src\SFML\Main\CMakeFiles\sfml-main.dir\build.make external/sfml/src/SFML/Main/CMakeFiles/sfml-main.dir/build
.PHONY : sfml-main/fast

#=============================================================================
# Target rules for targets named sfml-window

# Build rule for target.
sfml-window: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 sfml-window
.PHONY : sfml-window

# fast build rule for target.
sfml-window/fast:
	$(MAKE) $(MAKESILENT) -f external\sfml\src\SFML\Window\CMakeFiles\sfml-window.dir\build.make external/sfml/src/SFML/Window/CMakeFiles/sfml-window.dir/build
.PHONY : sfml-window/fast

#=============================================================================
# Target rules for targets named sfml-network

# Build rule for target.
sfml-network: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 sfml-network
.PHONY : sfml-network

# fast build rule for target.
sfml-network/fast:
	$(MAKE) $(MAKESILENT) -f external\sfml\src\SFML\Network\CMakeFiles\sfml-network.dir\build.make external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/build
.PHONY : sfml-network/fast

#=============================================================================
# Target rules for targets named sfml-graphics

# Build rule for target.
sfml-graphics: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 sfml-graphics
.PHONY : sfml-graphics

# fast build rule for target.
sfml-graphics/fast:
	$(MAKE) $(MAKESILENT) -f external\sfml\src\SFML\Graphics\CMakeFiles\sfml-graphics.dir\build.make external/sfml/src/SFML/Graphics/CMakeFiles/sfml-graphics.dir/build
.PHONY : sfml-graphics/fast

#=============================================================================
# Target rules for targets named sfml-audio

# Build rule for target.
sfml-audio: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 sfml-audio
.PHONY : sfml-audio

# fast build rule for target.
sfml-audio/fast:
	$(MAKE) $(MAKESILENT) -f external\sfml\src\SFML\Audio\CMakeFiles\sfml-audio.dir\build.make external/sfml/src/SFML/Audio/CMakeFiles/sfml-audio.dir/build
.PHONY : sfml-audio/fast

src/Application.obj: src/Application.cpp.obj
.PHONY : src/Application.obj

# target to build an object file
src/Application.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\stone_cold.dir\build.make CMakeFiles/stone_cold.dir/src/Application.cpp.obj
.PHONY : src/Application.cpp.obj

src/Application.i: src/Application.cpp.i
.PHONY : src/Application.i

# target to preprocess a source file
src/Application.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\stone_cold.dir\build.make CMakeFiles/stone_cold.dir/src/Application.cpp.i
.PHONY : src/Application.cpp.i

src/Application.s: src/Application.cpp.s
.PHONY : src/Application.s

# target to generate assembly for a file
src/Application.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\stone_cold.dir\build.make CMakeFiles/stone_cold.dir/src/Application.cpp.s
.PHONY : src/Application.cpp.s

# Help Target
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all (the default if no target is provided)
	@echo ... clean
	@echo ... depend
	@echo ... edit_cache
	@echo ... install
	@echo ... install/local
	@echo ... install/strip
	@echo ... list_install_components
	@echo ... package
	@echo ... package_source
	@echo ... rebuild_cache
	@echo ... sfml-audio
	@echo ... sfml-graphics
	@echo ... sfml-main
	@echo ... sfml-network
	@echo ... sfml-system
	@echo ... sfml-window
	@echo ... stone_cold
	@echo ... src/Application.obj
	@echo ... src/Application.i
	@echo ... src/Application.s
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system

