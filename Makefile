## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ##
##                   COLOR THEME                   ##
## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ##
DEFAULT=\033[0m 
## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ##
WHITE_FG=\033[37m 
RED_FG=\033[31m 
GREEN_FG=\033[32m 
YELLOW_FG=\033[33m 
BLUE_FG=\033[34m 
PURPLE_FG=\033[35m 
CYAN_FG=\033[36m 
BLACK_FG=\033[30m 
## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ##
WHITE_BG=\033[47m 
RED_BG=\033[41m 
GREEN_BG=\033[42m
YELLOW_BG=\033[43m  
BLUE_BG=\033[44m 
PURPLE_BG=\033[45m
CYAN_BG=\033[46m 
BLACK_BG=\033[40m 

## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ## 
##                   VARIABLES                     ## 
## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ## 
CC=g++
LIB_NAME=s21_containers.h
CC_FLAGS=-Wall -Werror -Wextra -std=c++17
FILES=*/*/s21_array.h
TEST_FILES=tests.cc
GCOV_FLAGS=-coverage 
LGTEST_FLAGS = -lgtest -lgtest_main -pthread
ifeq ($(OS), Linux)
  OPEN=xdg-open
else
  OPEN=open
endif

## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ## 
##                    COMMANDS                     ##
## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ## 
all: clean test

.PHONY: test
test:
	@echo "\n"
	@echo "$(BLACK_FG)$(GREEN_BG)                                                $(DEFAULT)"
	@echo "$(BLACK_FG)$(GREEN_BG)               CREATE TEST                      $(DEFAULT)"
	@echo "$(BLACK_FG)$(GREEN_BG)                                                $(DEFAULT)\n" 
	@$(CC) */*/*_test.cc -o test $(WILD) $(CC_FLAGS) $(LGTEST_FLAGS) -g
	@./test

gcov_report: clean
	@echo "$(BLACK_FG)$(CYAN_BG)                                                $(DEFAULT)"
	@echo "$(BLACK_FG)$(CYAN_BG)               CREATE REPORT                    $(DEFAULT)"
	@echo "$(BLACK_FG)$(CYAN_BG)                                                $(DEFAULT)\n" 
	@$(CC) $(CC_FLAGS) */*/*_test.cc $(LGTEST_FLAGS) $(GCOV_FLAGS) -o info
	@./info
	@lcov -t "info" -o gcovreport.info -c -d .
	@lcov --remove gcovreport.info '/usr/*' '*test*' --output-file gcovreport.info
	@genhtml -o report gcovreport.info
	@$(OPEN) report/index.html
	@echo "$(BLACK_FG)$(CYAN_BG)                                                $(DEFAULT)"
	@echo "$(BLACK_FG)$(CYAN_BG)               COMPLETE                         $(DEFAULT)"
	@echo "$(BLACK_FG)$(CYAN_BG)                                                $(DEFAULT)\n" 

style:
	clang-format -style=google -i */*/*.cc
	clang-format -style=google -i */*/*.h

clean:
	@rm -rf *.o *.gcda *.gcno *.info
	@rm -rf docs
	@rm -rf html
	@rm -rf latex
	@rm -f info
	@rm -f *.a
	@rm -f *.out
	@rm -rf report
	@rm -f test
	@rm -rf *.dSYM
	@echo "$(BLACK_FG)$(CYAN_BG)                                                $(DEFAULT)"
	@echo "$(BLACK_FG)$(CYAN_BG)               CLEAN DONE                       $(DEFAULT)"
	@echo "$(BLACK_FG)$(CYAN_BG)                                                $(DEFAULT)\n" 

.PHONY: git
git: style clean
	rm -rf report
	git add .
	git commit -m "commit"
	git push

dvi: clean
	@mkdir -p docs
	@doxygen Doxyfile
	@mv html latex docs
	@open docs/html/index.html
	@echo "$(BLACK_FG)$(PURPLE_BG)                                                $(DEFAULT)"
	@echo "$(BLACK_FG)$(PURPLE_BG)               CREATE DOXY                      $(DEFAULT)"
	@echo "$(BLACK_FG)$(PURPLE_BG)                                                $(DEFAULT)\n" 

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./test