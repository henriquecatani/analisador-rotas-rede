CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++17

TARGET = graphroute

SRCS = analiserotas.cpp
DEPS = graph.cpp

all: $(TARGET)

$(TARGET): $(SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean