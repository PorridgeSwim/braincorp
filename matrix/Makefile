# Compiler
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++11 -Wall -Wextra -pthread

# Target executable name
TARGET=matrix_app

# Object files
OBJS=main.o matrix.o

# Rule for making the final target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule for making object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: clean