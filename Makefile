#
# Simple Makefile for my Bunkai C with Cicanura Application Framework for C
#

all: pre-build main-build

pre-build:
	@echo ">>> PRE BUILD <<<"

post-build:
	@echo ">>> POST BUILD <<<"
	$(MAKE) --no-print-directory tests

main-build: target
	@$(MAKE) --no-print-directory post-build

# Run tests, just and only test runner!
tests: 
	@if [ ! -e ./test_runner/test_runner ]; \
	then \
		echo "Error: ./test_runner/test_runner is not exist!"; \
		echo ""; \
	fi

	@./test_runner/test_runner

# Target for test_runner..
target: \
	./bunkai_01/test/test_bunkai_ichi.o \
	./bunkai_01/bunkai_ichi.o \
	./core/test/test_collection.o \
	./core/source/collection.o \
	./core/test/test_strings.o \
	./core/source/strings.o \
	./core/test/test_ctest.o \
	./core/source/ctest.o \
	./test_runner/test_runner.o 
	
	# Remove test_runner if exists..
	@if [ -e ./test_runner/test_runner ]; \
	then \
		rm ./test_runner/test_runner; \
	fi

	# Build test_runner..
	cc -o ./test_runner/test_runner \
		./bunkai_01/test/test_bunkai_ichi.o \
		./bunkai_01/bunkai_ichi.o \
		./core/test/test_collection.o \
		./core/source/collection.o \
		./core/test/test_strings.o \
		./core/source/strings.o \
		./core/test/test_ctest.o \
		./core/source/ctest.o \
		./test_runner/test_runner.o

# Tests for the C Test Framework..
./core/test/test_ctest.o: \
	./core/test/test_ctest.c \
	./core/source/ctest.o \
	./core/source/collection.o \
	./core/source/strings.o

# C Test Framework..
./core/source/ctest.o: \
	./core/source/ctest.c \
	./core/include/ctest.h \
	./core/source/strings.o \
	./core/source/collection.o

# Tests for the Collection of objects..
./core/test/test_collection.o: \
	./core/test/test_collection.c \
	./core/source/collection.o \
	./core/source/ctest.o

# Collection of objects..
./core/source/collection.o: \
	./core/source/collection.c \
	./core/include/collection.h

# Tests for the Simple Strings..
./core/test/test_strings.o: \
	./core/test/test_strings.c \
	./core/source/strings.o \
	./core/source/ctest.o

# Simple Strings..
./soure/source/strings.o: \
	./core/source/strings.c \
	./core/include/strings.h

# The Runner App for tests..
./test_runner/test_runner.o: \
	./test_runner/test_runner.c \
	./core/test/test_ctest.o \
	./core/source/ctest.o \
	./core/test/test_collection.o \
	./core/test/test_strings.o

# Bunkai Ichi
./bunkai_01/bunkai_ichi.o: \
	./bunkai_01/bunkai_ichi.c \
	./bunkai_01/include/bunkai_ichi.h

# Bunkai Ichi (test)
./bunkai_01/test/test_bunkai_ichi.o: \
	./bunkai_01/test/test_bunkai_ichi.c \
	./bunkai_01/bunkai_ichi.o

# Clean the outputs..
clean:
	@for soubor in \
		./core/test/test_strings.o \
		./core/source/strings.o \
		./core/test/test_collection.o \
		./core/source/collection.o \
		./core/test/test_ctest.o \
		./core/source/ctest.o \
		./test_runner/test_runner.o \
		./test_runner/test_runner \
		./bunkai_01/bunkai_ichi.o \
		./bunkai_01/test/test_bunkai_ichi.o; \
	do \
		if [ -e $$soubor ]; \
		then \
			echo "Removing: $$soubor"; \
			rm $$soubor; \
		fi; \
	done
