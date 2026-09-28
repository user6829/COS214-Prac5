# Compiler and Flags
CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -g
LDFLAGS  := 

# Target Executable
TARGET   := main

# Source and Object Files
SRCS     := $(wildcard *.cpp)
OBJS     := $(SRCS:.cpp=.o)

# Default Rule
all: $(TARGET)

# Link Executable
\((TARGET):\)(OBJS)
	\((CXX)\)(CXXFLAGS) -o \(@\)^ $(LDFLAGS)

# Compile C++ Source Files to Object Files
%.o: %.cpp
	\((CXX)\)(CXXFLAGS) -c \(< -o\)@

# Run the Application
run: $(TARGET)
	./$(TARGET)

# Check Memory Leaks using Valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Clean Build Artifacts
clean:
	rm -f \((OBJS)\)(TARGET)

.PHONY: all run valgrind clean