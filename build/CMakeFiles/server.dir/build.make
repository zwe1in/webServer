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
CMAKE_SOURCE_DIR = /home/zw/HttpServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zw/HttpServer/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/main.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/main.cpp.o -c /home/zw/HttpServer/main.cpp

CMakeFiles/server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/main.cpp > CMakeFiles/server.dir/main.cpp.i

CMakeFiles/server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/main.cpp -o CMakeFiles/server.dir/main.cpp.s

CMakeFiles/server.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/main.cpp.o.requires

CMakeFiles/server.dir/main.cpp.o.provides: CMakeFiles/server.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/main.cpp.o.provides

CMakeFiles/server.dir/main.cpp.o.provides.build: CMakeFiles/server.dir/main.cpp.o


CMakeFiles/server.dir/http/HandleMapper.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/http/HandleMapper.cpp.o: ../http/HandleMapper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/http/HandleMapper.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/http/HandleMapper.cpp.o -c /home/zw/HttpServer/http/HandleMapper.cpp

CMakeFiles/server.dir/http/HandleMapper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/http/HandleMapper.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/http/HandleMapper.cpp > CMakeFiles/server.dir/http/HandleMapper.cpp.i

CMakeFiles/server.dir/http/HandleMapper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/http/HandleMapper.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/http/HandleMapper.cpp -o CMakeFiles/server.dir/http/HandleMapper.cpp.s

CMakeFiles/server.dir/http/HandleMapper.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/http/HandleMapper.cpp.o.requires

CMakeFiles/server.dir/http/HandleMapper.cpp.o.provides: CMakeFiles/server.dir/http/HandleMapper.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/http/HandleMapper.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/http/HandleMapper.cpp.o.provides

CMakeFiles/server.dir/http/HandleMapper.cpp.o.provides.build: CMakeFiles/server.dir/http/HandleMapper.cpp.o


CMakeFiles/server.dir/http/HttpConn.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/http/HttpConn.cpp.o: ../http/HttpConn.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/http/HttpConn.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/http/HttpConn.cpp.o -c /home/zw/HttpServer/http/HttpConn.cpp

CMakeFiles/server.dir/http/HttpConn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/http/HttpConn.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/http/HttpConn.cpp > CMakeFiles/server.dir/http/HttpConn.cpp.i

CMakeFiles/server.dir/http/HttpConn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/http/HttpConn.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/http/HttpConn.cpp -o CMakeFiles/server.dir/http/HttpConn.cpp.s

CMakeFiles/server.dir/http/HttpConn.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/http/HttpConn.cpp.o.requires

CMakeFiles/server.dir/http/HttpConn.cpp.o.provides: CMakeFiles/server.dir/http/HttpConn.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/http/HttpConn.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/http/HttpConn.cpp.o.provides

CMakeFiles/server.dir/http/HttpConn.cpp.o.provides.build: CMakeFiles/server.dir/http/HttpConn.cpp.o


CMakeFiles/server.dir/http/HttpRequest.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/http/HttpRequest.cpp.o: ../http/HttpRequest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/http/HttpRequest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/http/HttpRequest.cpp.o -c /home/zw/HttpServer/http/HttpRequest.cpp

CMakeFiles/server.dir/http/HttpRequest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/http/HttpRequest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/http/HttpRequest.cpp > CMakeFiles/server.dir/http/HttpRequest.cpp.i

CMakeFiles/server.dir/http/HttpRequest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/http/HttpRequest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/http/HttpRequest.cpp -o CMakeFiles/server.dir/http/HttpRequest.cpp.s

CMakeFiles/server.dir/http/HttpRequest.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/http/HttpRequest.cpp.o.requires

CMakeFiles/server.dir/http/HttpRequest.cpp.o.provides: CMakeFiles/server.dir/http/HttpRequest.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/http/HttpRequest.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/http/HttpRequest.cpp.o.provides

CMakeFiles/server.dir/http/HttpRequest.cpp.o.provides.build: CMakeFiles/server.dir/http/HttpRequest.cpp.o


CMakeFiles/server.dir/http/HttpResponse.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/http/HttpResponse.cpp.o: ../http/HttpResponse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server.dir/http/HttpResponse.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/http/HttpResponse.cpp.o -c /home/zw/HttpServer/http/HttpResponse.cpp

CMakeFiles/server.dir/http/HttpResponse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/http/HttpResponse.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/http/HttpResponse.cpp > CMakeFiles/server.dir/http/HttpResponse.cpp.i

CMakeFiles/server.dir/http/HttpResponse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/http/HttpResponse.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/http/HttpResponse.cpp -o CMakeFiles/server.dir/http/HttpResponse.cpp.s

CMakeFiles/server.dir/http/HttpResponse.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/http/HttpResponse.cpp.o.requires

CMakeFiles/server.dir/http/HttpResponse.cpp.o.provides: CMakeFiles/server.dir/http/HttpResponse.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/http/HttpResponse.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/http/HttpResponse.cpp.o.provides

CMakeFiles/server.dir/http/HttpResponse.cpp.o.provides.build: CMakeFiles/server.dir/http/HttpResponse.cpp.o


CMakeFiles/server.dir/log/Log.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/log/Log.cpp.o: ../log/Log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server.dir/log/Log.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/log/Log.cpp.o -c /home/zw/HttpServer/log/Log.cpp

CMakeFiles/server.dir/log/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/log/Log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/log/Log.cpp > CMakeFiles/server.dir/log/Log.cpp.i

CMakeFiles/server.dir/log/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/log/Log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/log/Log.cpp -o CMakeFiles/server.dir/log/Log.cpp.s

CMakeFiles/server.dir/log/Log.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/log/Log.cpp.o.requires

CMakeFiles/server.dir/log/Log.cpp.o.provides: CMakeFiles/server.dir/log/Log.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/log/Log.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/log/Log.cpp.o.provides

CMakeFiles/server.dir/log/Log.cpp.o.provides.build: CMakeFiles/server.dir/log/Log.cpp.o


CMakeFiles/server.dir/server/Epoller.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/Epoller.cpp.o: ../server/Epoller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/server.dir/server/Epoller.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server/Epoller.cpp.o -c /home/zw/HttpServer/server/Epoller.cpp

CMakeFiles/server.dir/server/Epoller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server/Epoller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/server/Epoller.cpp > CMakeFiles/server.dir/server/Epoller.cpp.i

CMakeFiles/server.dir/server/Epoller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server/Epoller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/server/Epoller.cpp -o CMakeFiles/server.dir/server/Epoller.cpp.s

CMakeFiles/server.dir/server/Epoller.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/server/Epoller.cpp.o.requires

CMakeFiles/server.dir/server/Epoller.cpp.o.provides: CMakeFiles/server.dir/server/Epoller.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server/Epoller.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/server/Epoller.cpp.o.provides

CMakeFiles/server.dir/server/Epoller.cpp.o.provides.build: CMakeFiles/server.dir/server/Epoller.cpp.o


CMakeFiles/server.dir/server/Server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/Server.cpp.o: ../server/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/server.dir/server/Server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/server/Server.cpp.o -c /home/zw/HttpServer/server/Server.cpp

CMakeFiles/server.dir/server/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/server/Server.cpp > CMakeFiles/server.dir/server/Server.cpp.i

CMakeFiles/server.dir/server/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/server/Server.cpp -o CMakeFiles/server.dir/server/Server.cpp.s

CMakeFiles/server.dir/server/Server.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/server/Server.cpp.o.requires

CMakeFiles/server.dir/server/Server.cpp.o.provides: CMakeFiles/server.dir/server/Server.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server/Server.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/server/Server.cpp.o.provides

CMakeFiles/server.dir/server/Server.cpp.o.provides.build: CMakeFiles/server.dir/server/Server.cpp.o


CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o: ../mysql/SQLConnPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o -c /home/zw/HttpServer/mysql/SQLConnPool.cpp

CMakeFiles/server.dir/mysql/SQLConnPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/mysql/SQLConnPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/mysql/SQLConnPool.cpp > CMakeFiles/server.dir/mysql/SQLConnPool.cpp.i

CMakeFiles/server.dir/mysql/SQLConnPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/mysql/SQLConnPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/mysql/SQLConnPool.cpp -o CMakeFiles/server.dir/mysql/SQLConnPool.cpp.s

CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o.requires

CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o.provides: CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o.provides

CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o.provides.build: CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o


CMakeFiles/server.dir/mysql/SQLConnection.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/mysql/SQLConnection.cpp.o: ../mysql/SQLConnection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/server.dir/mysql/SQLConnection.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/mysql/SQLConnection.cpp.o -c /home/zw/HttpServer/mysql/SQLConnection.cpp

CMakeFiles/server.dir/mysql/SQLConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/mysql/SQLConnection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/mysql/SQLConnection.cpp > CMakeFiles/server.dir/mysql/SQLConnection.cpp.i

CMakeFiles/server.dir/mysql/SQLConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/mysql/SQLConnection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/mysql/SQLConnection.cpp -o CMakeFiles/server.dir/mysql/SQLConnection.cpp.s

CMakeFiles/server.dir/mysql/SQLConnection.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/mysql/SQLConnection.cpp.o.requires

CMakeFiles/server.dir/mysql/SQLConnection.cpp.o.provides: CMakeFiles/server.dir/mysql/SQLConnection.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/mysql/SQLConnection.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/mysql/SQLConnection.cpp.o.provides

CMakeFiles/server.dir/mysql/SQLConnection.cpp.o.provides.build: CMakeFiles/server.dir/mysql/SQLConnection.cpp.o


CMakeFiles/server.dir/mysql/test.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/mysql/test.cpp.o: ../mysql/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/server.dir/mysql/test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/mysql/test.cpp.o -c /home/zw/HttpServer/mysql/test.cpp

CMakeFiles/server.dir/mysql/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/mysql/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/mysql/test.cpp > CMakeFiles/server.dir/mysql/test.cpp.i

CMakeFiles/server.dir/mysql/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/mysql/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/mysql/test.cpp -o CMakeFiles/server.dir/mysql/test.cpp.s

CMakeFiles/server.dir/mysql/test.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/mysql/test.cpp.o.requires

CMakeFiles/server.dir/mysql/test.cpp.o.provides: CMakeFiles/server.dir/mysql/test.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/mysql/test.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/mysql/test.cpp.o.provides

CMakeFiles/server.dir/mysql/test.cpp.o.provides.build: CMakeFiles/server.dir/mysql/test.cpp.o


CMakeFiles/server.dir/time/TimeWheel.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/time/TimeWheel.cpp.o: ../time/TimeWheel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/server.dir/time/TimeWheel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/time/TimeWheel.cpp.o -c /home/zw/HttpServer/time/TimeWheel.cpp

CMakeFiles/server.dir/time/TimeWheel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/time/TimeWheel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zw/HttpServer/time/TimeWheel.cpp > CMakeFiles/server.dir/time/TimeWheel.cpp.i

CMakeFiles/server.dir/time/TimeWheel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/time/TimeWheel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zw/HttpServer/time/TimeWheel.cpp -o CMakeFiles/server.dir/time/TimeWheel.cpp.s

CMakeFiles/server.dir/time/TimeWheel.cpp.o.requires:

.PHONY : CMakeFiles/server.dir/time/TimeWheel.cpp.o.requires

CMakeFiles/server.dir/time/TimeWheel.cpp.o.provides: CMakeFiles/server.dir/time/TimeWheel.cpp.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/time/TimeWheel.cpp.o.provides.build
.PHONY : CMakeFiles/server.dir/time/TimeWheel.cpp.o.provides

CMakeFiles/server.dir/time/TimeWheel.cpp.o.provides.build: CMakeFiles/server.dir/time/TimeWheel.cpp.o


# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/main.cpp.o" \
"CMakeFiles/server.dir/http/HandleMapper.cpp.o" \
"CMakeFiles/server.dir/http/HttpConn.cpp.o" \
"CMakeFiles/server.dir/http/HttpRequest.cpp.o" \
"CMakeFiles/server.dir/http/HttpResponse.cpp.o" \
"CMakeFiles/server.dir/log/Log.cpp.o" \
"CMakeFiles/server.dir/server/Epoller.cpp.o" \
"CMakeFiles/server.dir/server/Server.cpp.o" \
"CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o" \
"CMakeFiles/server.dir/mysql/SQLConnection.cpp.o" \
"CMakeFiles/server.dir/mysql/test.cpp.o" \
"CMakeFiles/server.dir/time/TimeWheel.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/main.cpp.o
server: CMakeFiles/server.dir/http/HandleMapper.cpp.o
server: CMakeFiles/server.dir/http/HttpConn.cpp.o
server: CMakeFiles/server.dir/http/HttpRequest.cpp.o
server: CMakeFiles/server.dir/http/HttpResponse.cpp.o
server: CMakeFiles/server.dir/log/Log.cpp.o
server: CMakeFiles/server.dir/server/Epoller.cpp.o
server: CMakeFiles/server.dir/server/Server.cpp.o
server: CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o
server: CMakeFiles/server.dir/mysql/SQLConnection.cpp.o
server: CMakeFiles/server.dir/mysql/test.cpp.o
server: CMakeFiles/server.dir/time/TimeWheel.cpp.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zw/HttpServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/requires: CMakeFiles/server.dir/main.cpp.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/http/HandleMapper.cpp.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/http/HttpConn.cpp.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/http/HttpRequest.cpp.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/http/HttpResponse.cpp.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/log/Log.cpp.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/server/Epoller.cpp.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/server/Server.cpp.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/mysql/SQLConnPool.cpp.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/mysql/SQLConnection.cpp.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/mysql/test.cpp.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/time/TimeWheel.cpp.o.requires

.PHONY : CMakeFiles/server.dir/requires

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/zw/HttpServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zw/HttpServer /home/zw/HttpServer /home/zw/HttpServer/build /home/zw/HttpServer/build /home/zw/HttpServer/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

