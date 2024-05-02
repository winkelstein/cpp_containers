CC=g++
#CFLAGS=-Wall -Wextra -Werror -std=c++17 -c
CFLAGS=-std=c++17 -c
LIBS=
GCOV_FLAGS=-coverage -fprofile-arcs -ftest-coverage

HEADERS=s21_containers.h s21_containersplus.h s21_containers/include/*.h s21_containers/iterators/*.h
TPP=$(wildcard s21_containers/impl/*.tpp)

TESTS_SRC_DIR=./tests/
TESTS_OBJS_DIR=./build/
TESTS_SOURCES=$(wildcard $(TESTS_SRC_DIR)*.cpp)
TESTS_OBJS=$(patsubst $(TESTS_SRC_DIR)%.cpp, $(TESTS_OBJS_DIR)%.o, $(TESTS_SOURCES))

TESTS_TARGET=$(TESTS_OBJS_DIR)s21_containers_tests.exe

DEV_LIBS=-lgtest -lpthread

all: test

test: $(HEADERS) $(TPP) $(TESTS_TARGET)
	@./$(TESTS_TARGET)

clean: clean_tests clean_gcov
	@printf "[CLEAN] \e[33mCleaned\e[0m\n"

rebuild: clean all

valgrind: $(TESTS_TARGET)
	@valgrind --tool=memcheck --leak-check=yes ./$(TESTS_TARGET)

gcov_report: test
	lcov -o tests.info -c -d .
	genhtml -o build/report tests.info
	open build/report/index.html

$(TESTS_TARGET): $(TARGET) $(TESTS_OBJS)
	@printf "[BUILD] \e[92mLinking objects\e[0m\n"
	@$(CC) -o $@ $(TESTS_OBJS) $(DEV_LIBS) $(GCOV_FLAGS)
	@printf "[BUILD] \e[95mBuilt target $@\e[0m\n"

$(TESTS_OBJS_DIR)%.o: $(TESTS_SRC_DIR)%.cpp
	@printf "[BUILD] \e[32mBuilding $< -> $@\e[0m\n"
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) $< -o $@

clean_tests:
	@rm -rf $(TESTS_OBJS) $(TESTS_TARGET)

clean_gcov:
	@rm -rf tests.info *.gcda *.gcno build/*