# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_SOURCE_DIR = /home/ppi/dbt/pattern-dbt/vine-compare/stp-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/build

# Utility rule file for parser_headersmt2.

# Include the progress variables for this target.
include lib/Parser/CMakeFiles/parser_headersmt2.dir/progress.make

lib/Parser/CMakeFiles/parser_headersmt2: lib/Parser/parsesmt2.cpp
lib/Parser/CMakeFiles/parser_headersmt2: lib/Parser/lexsmt2.cpp


lib/Parser/parsesmt2.cpp: ../lib/Parser/smt2.lex
lib/Parser/parsesmt2.cpp: ../lib/Parser/smt2.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ppi/dbt/pattern-dbt/vine-compare/stp-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating parsesmt2.cpp, lexsmt2.cpp"
	cd /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/build/lib/Parser && /usr/bin/bison --debug -v -o /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/build/lib/Parser/parsesmt2.cpp -d -p smt2 /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/lib/Parser/smt2.y
	cd /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/build/lib/Parser && /usr/bin/flex -Ce -I -o/home/ppi/dbt/pattern-dbt/vine-compare/stp-master/build/lib/Parser/lexsmt2.cpp -Psmt2 /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/lib/Parser/smt2.lex

lib/Parser/lexsmt2.cpp: lib/Parser/parsesmt2.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate lib/Parser/lexsmt2.cpp

parser_headersmt2: lib/Parser/CMakeFiles/parser_headersmt2
parser_headersmt2: lib/Parser/parsesmt2.cpp
parser_headersmt2: lib/Parser/lexsmt2.cpp
parser_headersmt2: lib/Parser/CMakeFiles/parser_headersmt2.dir/build.make

.PHONY : parser_headersmt2

# Rule to build all files generated by this target.
lib/Parser/CMakeFiles/parser_headersmt2.dir/build: parser_headersmt2

.PHONY : lib/Parser/CMakeFiles/parser_headersmt2.dir/build

lib/Parser/CMakeFiles/parser_headersmt2.dir/clean:
	cd /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/build/lib/Parser && $(CMAKE_COMMAND) -P CMakeFiles/parser_headersmt2.dir/cmake_clean.cmake
.PHONY : lib/Parser/CMakeFiles/parser_headersmt2.dir/clean

lib/Parser/CMakeFiles/parser_headersmt2.dir/depend:
	cd /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ppi/dbt/pattern-dbt/vine-compare/stp-master /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/lib/Parser /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/build /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/build/lib/Parser /home/ppi/dbt/pattern-dbt/vine-compare/stp-master/build/lib/Parser/CMakeFiles/parser_headersmt2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/Parser/CMakeFiles/parser_headersmt2.dir/depend

