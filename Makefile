CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = spell_checker
SRC = spell_checker.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

.PHONY: all clean 