CXX = g++
CPPFLAGS = -std=c++17 -Iinclude
TARGET = main
SRCS = src/main.cpp
OBJS = $(SRCS:src/%.cpp=build/%.o)

all: $(TARGET)

$(OBJS): | build

build:
	mkdir -p build

$(TARGET): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $^

build/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)