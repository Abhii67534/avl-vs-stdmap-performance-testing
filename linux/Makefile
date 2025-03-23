# Compiler and flags
CC = g++
CFLAGS = -std=c++11 -Wall

# Shared source files
COMMON = timer.cpp

# Targets
all: test_avl_linux test_std_map_linux

test_avl_linux: test_avl_linux.cpp AVLTree.cpp AVLTree.h $(COMMON)
	$(CC) $(CFLAGS) test_avl_linux.cpp AVLTree.cpp $(COMMON) -o test_avl_linux

test_std_map_linux: test_std_map_linux.cpp $(COMMON)
	$(CC) $(CFLAGS) test_std_map_linux.cpp $(COMMON) -o test_std_map_linux

clean:
	rm -f test_avl_linux test_std_map_linux *.o