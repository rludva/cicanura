#
# Simple Makefile for my Bunkai C with Cicanura Application Framework for C
#

# Target for test_runner..
test: ./bunkai_01/bunkai_ichi.o ./bunkai_01/test/test_bunkai_ichi.o ./core/test/test_collection.o ./core/test/test_strings.o ./core/test/test_ctest.o ./test_runner/test_runner.o ./core/source/collection.o ./core/source/strings.o ./core/source/ctest.o
	
	@if [ -e ./output/test_runner ]; \
	then \
		rm ./output/test_runner; \
	fi

	cc -o ./test_runner/test_runner \
		./bunkai_01/bunkai_ichi.o \
		./bunkai_01/test/test_bunkai_ichi.o \
		./core/test/test_collection.o \
		./core/test/test_strings.o \
		./core/test/test_ctest.o \
		./test_runner/test_runner.o \
		./core/source/ctest.o \
		./core/source/collection.o \
		./core/source/strings.o 

	@./test_runner/test_runner

# C Test Framework..
./core/source/ctest.o: ./core/source/ctest.c ./core/include/ctest.h ./core/source/strings.o ./core/source/collection.o

# Tests for the C Test Framework..
./core/test/test_ctest.o: ./core/test/test_ctest.c ./core/source/ctest.o ./core/source/collection.o ./core/source/strings.o

# Collection for objects..
./core/source/collection.o: ./core/source/collection.c ./core/include/collection.h

# Tests for the Collection..
./core/test/test_collection.o: ./core/test/test_collection.c ./core/source/collection.o ./core/source/ctest.o

# Simple Strings..
./soure/source/strings.o: ./core/source/strings.c ./core/include/strings.h

# Tests for the Strings..
./core/test/test_strings.o: ./core/test/test_strings.c ./core/source/strings.o ./core/source/ctest.o

# The Runner App for tests..
./test_runner/test_runner.o: ./test_runner/test_runner.c ./core/source/ctest.o ./core/test/test_collection.o ./core/test/test_strings.o ./core/test/test_ctest.o

# Bunkai Ichi
./bunkai_01/bunkai_ichi.o: ./bunkai_01/bunkai_ichi.c ./bunkai_01/include/bunkai_ichi.h

# Bunkai Ichi (test)
./bunkai_01/test/test_bunkai_ichi.o: ./bunkai_01/test/test_bunkai_ichi.c ./bunkai_01/bunkai_ichi.o

# Clean the outputs..
clean:
	@for soubor in ./core/source/strings.o \
./core/source/collection.o \
./core/source/ctest.o \
./core/test/test_strings.o \
./core/test/test_collection.o .\
/core/test/test_ctest.o \
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
