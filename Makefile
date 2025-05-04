CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2


# all srcs here
SRCS  := aur.cpp lexer.cpp parse.cpp semantic.cpp error.cpp generator.cpp
OBJS  := $(SRCS:.cpp=.o)


TARGET := aur


.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

# Needs root..
.PHONY: install
install: $(TARGET)
	install -Dm755 $(TARGET) /usr/local/bin/$(TARGET)
