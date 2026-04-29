CXX = g++
BASE_CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
RELEASE_FLAGS = -O1 -DNDEBUG
DEBUG_FLAGS = -O0 -g
TARGET = programa
SRC = main.cpp objektinis_patikrinimai.cpp

all: release

release: CXXFLAGS = $(BASE_CXXFLAGS) $(RELEASE_FLAGS)
release: $(TARGET)

debug: CXXFLAGS = $(BASE_CXXFLAGS) $(DEBUG_FLAGS)
debug: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
