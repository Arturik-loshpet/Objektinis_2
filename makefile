CXX = g++
BASE_CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
RELEASE_FLAGS = -O2 -DNDEBUG
DEBUG_FLAGS = -O0 -g
TARGET = programa
TEST_TARGET = rule_of_five_test
SRC = main.cpp objektinis_patikrinimai.cpp
TEST_SRC = rule_of_five_test.cpp objektinis_patikrinimai.cpp

all: release

release: CXXFLAGS = $(BASE_CXXFLAGS) $(RELEASE_FLAGS)
release: $(TARGET)

debug: CXXFLAGS = $(BASE_CXXFLAGS) $(DEBUG_FLAGS)
debug: $(TARGET)

test: CXXFLAGS = $(BASE_CXXFLAGS) $(DEBUG_FLAGS)
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

$(TEST_TARGET): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) programa_test
