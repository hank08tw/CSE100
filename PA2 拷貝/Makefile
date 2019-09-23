# Original by Sander
# Edited by Jonathan
# A simple makefile for CSE 100 P2

# === Directories ===
SRC=src
TEST=test
BUILD=build
OBJ=$(BUILD)/obj

# === Compiler options ===
# use g++ for everything
CC=g++

# MMD: automatically resolve included files
# g: include debugging symbols in the generated object file
# Wall: enable all warnings
# std: language standard to compile for
CXXFLAGS=-MMD -g -Wall -std=c++11
CXXFLAGS_OPTIMIZE=-MMD -O3 -Wall -std=c++11

# g: include debugging symbols in the generated executable
LDFLAGS=-g
LDFLAGS_NO_DEBUG=

# === Build targets ===
default: main2

main: init src_object.main src_object.Autocomplete
	$(call make_executable_from_object_file,main)
submit_main: init src_object_optimize.main src_object_optimize.Autocomplete
	$(call make_executable_from_object_file_no_debug,main)

main2: init src_object.main2 src_object.DocumentGenerator
	$(call make_executable_from_object_file,main2)
submit_main2: init src_object_optimize.main2 src_object_optimize.DocumentGenerator
	$(call make_executable_from_object_file_no_debug,main2)

test_autocomplete: init test_object.test_autocomplete src_object.Autocomplete
	$(call make_executable_from_object_file_and_test,$(TEST)/test_autocomplete)
test_document_generator: init test_object.test_document_generator src_object.DocumentGenerator
	$(call make_executable_from_object_file_and_test,$(TEST)/test_document_generator)

clean:
	rm -rf $(BUILD)

init:
	mkdir -p $(BUILD)/$(TEST)
	mkdir -p $(OBJ)/$(SRC)
	mkdir -p $(OBJ)/$(TEST)

src_object.%:
	# if build target is src_object.xyz then $@ == src_object.xyz, we want to extract filename xyz.
	$(call make_object_file_from_cpp_file,$(SRC)/$(call get_filename_from_object_target,$@))

src_object_optimize.%:
	$(call make_object_file_from_cpp_file_optimize,$(SRC)/$(call get_filename_from_object_target,$@))

test_object.%:
	$(call make_object_file_from_cpp_file,$(TEST)/$(call get_filename_from_object_target,$@))

# === Utility functions ===
make_object_file_from_cpp_file=$(CC) $(CXXFLAGS) -c $1.cpp -o $(OBJ)/$1.o
make_object_file_from_cpp_file_optimize=$(CC) $(CXXFLAGS_OPTIMIZE) -c $1.cpp -o $(OBJ)/$1.o

make_executable_from_object_file=$(shell $(CC) $(LDFLAGS) -o $(BUILD)/$1 $(wildcard $(OBJ)/$(SRC)/*.o))
make_executable_from_object_file_and_test=$(shell $(CC) $(LDFLAGS) -o $(BUILD)/$1 $(wildcard $(OBJ)/$(SRC)/*.o) $(wildcard $(OBJ)/$(TEST)/*.o))
make_executable_from_object_file_no_debug=$(shell $(CC) $(LDFLAGS_NO_DEBUG) -o $(BUILD)/$1 $(wildcard $(OBJ)/$(SRC)/*.o))

get_filename_from_object_target=$(shell echo $1 | cut -d'.' -f2)
