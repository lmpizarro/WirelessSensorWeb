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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build

# Include any dependencies generated for this target.
include src/CMakeFiles/uno_SoftwareSerial.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/uno_SoftwareSerial.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/uno_SoftwareSerial.dir/flags.make

src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj: src/CMakeFiles/uno_SoftwareSerial.dir/flags.make
src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj: /usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj"
	cd /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build/src && /usr/bin/avr-g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj -c /usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp

src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.i"
	cd /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build/src && /usr/bin/avr-g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp > CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.i

src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.s"
	cd /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build/src && /usr/bin/avr-g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp -o CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.s

src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj.requires:
.PHONY : src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj.requires

src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj.provides: src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj.requires
	$(MAKE) -f src/CMakeFiles/uno_SoftwareSerial.dir/build.make src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj.provides.build
.PHONY : src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj.provides

src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj.provides.build: src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj

# Object files for target uno_SoftwareSerial
uno_SoftwareSerial_OBJECTS = \
"CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj"

# External object files for target uno_SoftwareSerial
uno_SoftwareSerial_EXTERNAL_OBJECTS =

src/libuno_SoftwareSerial.a: src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj
src/libuno_SoftwareSerial.a: src/CMakeFiles/uno_SoftwareSerial.dir/build.make
src/libuno_SoftwareSerial.a: src/CMakeFiles/uno_SoftwareSerial.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libuno_SoftwareSerial.a"
	cd /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build/src && $(CMAKE_COMMAND) -P CMakeFiles/uno_SoftwareSerial.dir/cmake_clean_target.cmake
	cd /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uno_SoftwareSerial.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/uno_SoftwareSerial.dir/build: src/libuno_SoftwareSerial.a
.PHONY : src/CMakeFiles/uno_SoftwareSerial.dir/build

src/CMakeFiles/uno_SoftwareSerial.dir/requires: src/CMakeFiles/uno_SoftwareSerial.dir/usr/share/arduino/libraries/SoftwareSerial/SoftwareSerial.cpp.obj.requires
.PHONY : src/CMakeFiles/uno_SoftwareSerial.dir/requires

src/CMakeFiles/uno_SoftwareSerial.dir/clean:
	cd /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build/src && $(CMAKE_COMMAND) -P CMakeFiles/uno_SoftwareSerial.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/uno_SoftwareSerial.dir/clean

src/CMakeFiles/uno_SoftwareSerial.dir/depend:
	cd /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/src /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build/src /home/lmpizarro/sketchbook/WirelessSensorWeb/Transmitter/build/src/CMakeFiles/uno_SoftwareSerial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/uno_SoftwareSerial.dir/depend

