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
CMAKE_BINARY_DIR = D:\Projects\StoneCold_DefinitiveEdition\build\Debug

# Include any dependencies generated for this target.
include external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.make

# Include the progress variables for this target.
include external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/progress.make

# Include the compile flags for this target's objects.
include external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj: ../../external/sfml/src/SFML/Network/Ftp.cpp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj -MF CMakeFiles\sfml-network.dir\Ftp.cpp.obj.d -o CMakeFiles\sfml-network.dir\Ftp.cpp.obj -c D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Ftp.cpp

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/Ftp.cpp.i"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Ftp.cpp > CMakeFiles\sfml-network.dir\Ftp.cpp.i

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/Ftp.cpp.s"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Ftp.cpp -o CMakeFiles\sfml-network.dir\Ftp.cpp.s

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj: ../../external/sfml/src/SFML/Network/Http.cpp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj -MF CMakeFiles\sfml-network.dir\Http.cpp.obj.d -o CMakeFiles\sfml-network.dir\Http.cpp.obj -c D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Http.cpp

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/Http.cpp.i"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Http.cpp > CMakeFiles\sfml-network.dir\Http.cpp.i

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/Http.cpp.s"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Http.cpp -o CMakeFiles\sfml-network.dir\Http.cpp.s

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj: ../../external/sfml/src/SFML/Network/IpAddress.cpp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj -MF CMakeFiles\sfml-network.dir\IpAddress.cpp.obj.d -o CMakeFiles\sfml-network.dir\IpAddress.cpp.obj -c D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\IpAddress.cpp

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/IpAddress.cpp.i"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\IpAddress.cpp > CMakeFiles\sfml-network.dir\IpAddress.cpp.i

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/IpAddress.cpp.s"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\IpAddress.cpp -o CMakeFiles\sfml-network.dir\IpAddress.cpp.s

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj: ../../external/sfml/src/SFML/Network/Packet.cpp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj -MF CMakeFiles\sfml-network.dir\Packet.cpp.obj.d -o CMakeFiles\sfml-network.dir\Packet.cpp.obj -c D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Packet.cpp

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/Packet.cpp.i"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Packet.cpp > CMakeFiles\sfml-network.dir\Packet.cpp.i

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/Packet.cpp.s"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Packet.cpp -o CMakeFiles\sfml-network.dir\Packet.cpp.s

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj: ../../external/sfml/src/SFML/Network/Socket.cpp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj -MF CMakeFiles\sfml-network.dir\Socket.cpp.obj.d -o CMakeFiles\sfml-network.dir\Socket.cpp.obj -c D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Socket.cpp

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/Socket.cpp.i"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Socket.cpp > CMakeFiles\sfml-network.dir\Socket.cpp.i

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/Socket.cpp.s"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Socket.cpp -o CMakeFiles\sfml-network.dir\Socket.cpp.s

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj: ../../external/sfml/src/SFML/Network/SocketSelector.cpp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj -MF CMakeFiles\sfml-network.dir\SocketSelector.cpp.obj.d -o CMakeFiles\sfml-network.dir\SocketSelector.cpp.obj -c D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\SocketSelector.cpp

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/SocketSelector.cpp.i"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\SocketSelector.cpp > CMakeFiles\sfml-network.dir\SocketSelector.cpp.i

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/SocketSelector.cpp.s"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\SocketSelector.cpp -o CMakeFiles\sfml-network.dir\SocketSelector.cpp.s

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj: ../../external/sfml/src/SFML/Network/TcpListener.cpp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj -MF CMakeFiles\sfml-network.dir\TcpListener.cpp.obj.d -o CMakeFiles\sfml-network.dir\TcpListener.cpp.obj -c D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\TcpListener.cpp

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/TcpListener.cpp.i"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\TcpListener.cpp > CMakeFiles\sfml-network.dir\TcpListener.cpp.i

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/TcpListener.cpp.s"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\TcpListener.cpp -o CMakeFiles\sfml-network.dir\TcpListener.cpp.s

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj: ../../external/sfml/src/SFML/Network/TcpSocket.cpp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj -MF CMakeFiles\sfml-network.dir\TcpSocket.cpp.obj.d -o CMakeFiles\sfml-network.dir\TcpSocket.cpp.obj -c D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\TcpSocket.cpp

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/TcpSocket.cpp.i"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\TcpSocket.cpp > CMakeFiles\sfml-network.dir\TcpSocket.cpp.i

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/TcpSocket.cpp.s"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\TcpSocket.cpp -o CMakeFiles\sfml-network.dir\TcpSocket.cpp.s

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj: ../../external/sfml/src/SFML/Network/UdpSocket.cpp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj -MF CMakeFiles\sfml-network.dir\UdpSocket.cpp.obj.d -o CMakeFiles\sfml-network.dir\UdpSocket.cpp.obj -c D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\UdpSocket.cpp

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/UdpSocket.cpp.i"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\UdpSocket.cpp > CMakeFiles\sfml-network.dir\UdpSocket.cpp.i

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/UdpSocket.cpp.s"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\UdpSocket.cpp -o CMakeFiles\sfml-network.dir\UdpSocket.cpp.s

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj: ../../external/sfml/src/SFML/Network/Win32/SocketImpl.cpp
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj -MF CMakeFiles\sfml-network.dir\Win32\SocketImpl.cpp.obj.d -o CMakeFiles\sfml-network.dir\Win32\SocketImpl.cpp.obj -c D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Win32\SocketImpl.cpp

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.i"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Win32\SocketImpl.cpp > CMakeFiles\sfml-network.dir\Win32\SocketImpl.cpp.i

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.s"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network\Win32\SocketImpl.cpp -o CMakeFiles\sfml-network.dir\Win32\SocketImpl.cpp.s

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/sfml-network.rc.obj: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/sfml-network.rc.obj: external/sfml/src/SFML/Network/sfml-network.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building RC object external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/sfml-network.rc.obj"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && C:\msys64\mingw64\bin\windres.exe -O coff $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network\sfml-network.rc CMakeFiles\sfml-network.dir\sfml-network.rc.obj

# Object files for target sfml-network
sfml__network_OBJECTS = \
"CMakeFiles/sfml-network.dir/Ftp.cpp.obj" \
"CMakeFiles/sfml-network.dir/Http.cpp.obj" \
"CMakeFiles/sfml-network.dir/IpAddress.cpp.obj" \
"CMakeFiles/sfml-network.dir/Packet.cpp.obj" \
"CMakeFiles/sfml-network.dir/Socket.cpp.obj" \
"CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj" \
"CMakeFiles/sfml-network.dir/TcpListener.cpp.obj" \
"CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj" \
"CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj" \
"CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj" \
"CMakeFiles/sfml-network.dir/sfml-network.rc.obj"

# External object files for target sfml-network
sfml__network_EXTERNAL_OBJECTS =

x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/sfml-network.rc.obj
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/build.make
x64/bin/sfml-network-d-3.dll: x64/lib/libsfml-system-d.a
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/linklibs.rsp
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/objects1.rsp
x64/bin/sfml-network-d-3.dll: external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Projects\StoneCold_DefinitiveEdition\build\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX shared library ..\..\..\..\..\x64\bin\sfml-network-d-3.dll"
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\sfml-network.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/build: x64/bin/sfml-network-d-3.dll
.PHONY : external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/build

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/clean:
	cd /d D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network && $(CMAKE_COMMAND) -P CMakeFiles\sfml-network.dir\cmake_clean.cmake
.PHONY : external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/clean

external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Projects\StoneCold_DefinitiveEdition D:\Projects\StoneCold_DefinitiveEdition\external\sfml\src\SFML\Network D:\Projects\StoneCold_DefinitiveEdition\build\Debug D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network D:\Projects\StoneCold_DefinitiveEdition\build\Debug\external\sfml\src\SFML\Network\CMakeFiles\sfml-network.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : external/sfml/src/SFML/Network/CMakeFiles/sfml-network.dir/depend

