# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = "C:/Program Files (x86)/CMake 2.8/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files (x86)/CMake 2.8/bin/cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "C:/Program Files (x86)/CMake 2.8/bin/cmake-gui.exe"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/pastafarian/Dropbox/project/Strat3/strat3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/pastafarian/Dropbox/project/Strat3/win-build

# Include any dependencies generated for this target.
include CMakeFiles/cstrat3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cstrat3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cstrat3.dir/flags.make

CMakeFiles/cstrat3.dir/cml/main.cpp.obj: CMakeFiles/cstrat3.dir/flags.make
CMakeFiles/cstrat3.dir/cml/main.cpp.obj: CMakeFiles/cstrat3.dir/includes_CXX.rsp
CMakeFiles/cstrat3.dir/cml/main.cpp.obj: C:/Users/pastafarian/Dropbox/project/Strat3/strat3/cml/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:/Users/pastafarian/Dropbox/project/Strat3/win-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cstrat3.dir/cml/main.cpp.obj"
	C:/cygwin/bin/c++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cstrat3.dir/cml/main.cpp.obj -c C:/Users/pastafarian/Dropbox/project/Strat3/strat3/cml/main.cpp

CMakeFiles/cstrat3.dir/cml/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cstrat3.dir/cml/main.cpp.i"
	C:/cygwin/bin/c++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:/Users/pastafarian/Dropbox/project/Strat3/strat3/cml/main.cpp > CMakeFiles/cstrat3.dir/cml/main.cpp.i

CMakeFiles/cstrat3.dir/cml/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cstrat3.dir/cml/main.cpp.s"
	C:/cygwin/bin/c++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:/Users/pastafarian/Dropbox/project/Strat3/strat3/cml/main.cpp -o CMakeFiles/cstrat3.dir/cml/main.cpp.s

CMakeFiles/cstrat3.dir/cml/main.cpp.obj.requires:
.PHONY : CMakeFiles/cstrat3.dir/cml/main.cpp.obj.requires

CMakeFiles/cstrat3.dir/cml/main.cpp.obj.provides: CMakeFiles/cstrat3.dir/cml/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles/cstrat3.dir/build.make CMakeFiles/cstrat3.dir/cml/main.cpp.obj.provides.build
.PHONY : CMakeFiles/cstrat3.dir/cml/main.cpp.obj.provides

CMakeFiles/cstrat3.dir/cml/main.cpp.obj.provides.build: CMakeFiles/cstrat3.dir/cml/main.cpp.obj

CMakeFiles/cstrat3.dir/cml/cml.cpp.obj: CMakeFiles/cstrat3.dir/flags.make
CMakeFiles/cstrat3.dir/cml/cml.cpp.obj: CMakeFiles/cstrat3.dir/includes_CXX.rsp
CMakeFiles/cstrat3.dir/cml/cml.cpp.obj: C:/Users/pastafarian/Dropbox/project/Strat3/strat3/cml/cml.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:/Users/pastafarian/Dropbox/project/Strat3/win-build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cstrat3.dir/cml/cml.cpp.obj"
	C:/cygwin/bin/c++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cstrat3.dir/cml/cml.cpp.obj -c C:/Users/pastafarian/Dropbox/project/Strat3/strat3/cml/cml.cpp

CMakeFiles/cstrat3.dir/cml/cml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cstrat3.dir/cml/cml.cpp.i"
	C:/cygwin/bin/c++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E C:/Users/pastafarian/Dropbox/project/Strat3/strat3/cml/cml.cpp > CMakeFiles/cstrat3.dir/cml/cml.cpp.i

CMakeFiles/cstrat3.dir/cml/cml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cstrat3.dir/cml/cml.cpp.s"
	C:/cygwin/bin/c++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S C:/Users/pastafarian/Dropbox/project/Strat3/strat3/cml/cml.cpp -o CMakeFiles/cstrat3.dir/cml/cml.cpp.s

CMakeFiles/cstrat3.dir/cml/cml.cpp.obj.requires:
.PHONY : CMakeFiles/cstrat3.dir/cml/cml.cpp.obj.requires

CMakeFiles/cstrat3.dir/cml/cml.cpp.obj.provides: CMakeFiles/cstrat3.dir/cml/cml.cpp.obj.requires
	$(MAKE) -f CMakeFiles/cstrat3.dir/build.make CMakeFiles/cstrat3.dir/cml/cml.cpp.obj.provides.build
.PHONY : CMakeFiles/cstrat3.dir/cml/cml.cpp.obj.provides

CMakeFiles/cstrat3.dir/cml/cml.cpp.obj.provides.build: CMakeFiles/cstrat3.dir/cml/cml.cpp.obj

# Object files for target cstrat3
cstrat3_OBJECTS = \
"CMakeFiles/cstrat3.dir/cml/main.cpp.obj" \
"CMakeFiles/cstrat3.dir/cml/cml.cpp.obj"

# External object files for target cstrat3
cstrat3_EXTERNAL_OBJECTS =

cstrat3.exe: CMakeFiles/cstrat3.dir/cml/main.cpp.obj
cstrat3.exe: CMakeFiles/cstrat3.dir/cml/cml.cpp.obj
cstrat3.exe: CMakeFiles/cstrat3.dir/build.make
cstrat3.exe: CMakeFiles/cstrat3.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable cstrat3.exe"
	"C:/Program Files (x86)/CMake 2.8/bin/cmake.exe" -E remove -f CMakeFiles/cstrat3.dir/objects.a
	C:/cygwin/bin/ar.exe cr CMakeFiles/cstrat3.dir/objects.a @CMakeFiles/cstrat3.dir/objects1.rsp
	C:/cygwin/bin/c++.exe   -std=c++11 -O1 -O2 -O3    -Wl,--whole-archive CMakeFiles/cstrat3.dir/objects.a -Wl,--no-whole-archive  -o cstrat3.exe -Wl,--out-implib,libcstrat3.dll.a -Wl,--major-image-version,0,--minor-image-version,0  -LC:/Users/pastafarian/Dropbox/project/Strat3/win-build  

# Rule to build all files generated by this target.
CMakeFiles/cstrat3.dir/build: cstrat3.exe
.PHONY : CMakeFiles/cstrat3.dir/build

CMakeFiles/cstrat3.dir/requires: CMakeFiles/cstrat3.dir/cml/main.cpp.obj.requires
CMakeFiles/cstrat3.dir/requires: CMakeFiles/cstrat3.dir/cml/cml.cpp.obj.requires
.PHONY : CMakeFiles/cstrat3.dir/requires

CMakeFiles/cstrat3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cstrat3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cstrat3.dir/clean

CMakeFiles/cstrat3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/pastafarian/Dropbox/project/Strat3/strat3 C:/Users/pastafarian/Dropbox/project/Strat3/strat3 C:/Users/pastafarian/Dropbox/project/Strat3/win-build C:/Users/pastafarian/Dropbox/project/Strat3/win-build C:/Users/pastafarian/Dropbox/project/Strat3/win-build/CMakeFiles/cstrat3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cstrat3.dir/depend

