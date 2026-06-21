CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wl,--allow-multiple-definition

TARGET = graphroute

SRCS = analiserotas.cpp
DEPS = graph.cpp parser.cpp

all: $(TARGET)

$(TARGET): $(SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(DEPS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean