CXX = g++
BASE_CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
RELEASE_FLAGS = -O3 -DNDEBUG
DEBUG_FLAGS = -O0 -g
TARGET = programa
SRC = main.cpp objektinis_patikrinimai.cpp
HEADERS = funkcijos.h library.h patikrinimai.h

all: release

release: CXXFLAGS = $(BASE_CXXFLAGS) $(RELEASE_FLAGS)
release: $(TARGET)

debug: CXXFLAGS = $(BASE_CXXFLAGS) $(DEBUG_FLAGS)
debug: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
