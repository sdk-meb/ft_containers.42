NAME = containers
NAME = 

CC = c++
INC = -I$(shell pwd)
RED = \033[0;31m
GREEN = \033[0;32m
NO_COLOR = \033[0m

CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address


SRC_FILES = main_map.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.opp)

ORDR = a


%.opp:%.cpp  $(shell ls *.hpp)
	@${CC} ${CFLAGS} $(INC)  -o $@ -c $<

all: ${NAME}

$(NAME):
	@${CC} main_map.cpp ${CFLAGS} 2> re
	@time ./${NAME}
	@echo exit status 

clean:
	@rm -rf ${OBJ_FILES}
	@echo "${RED} • ALL object files are deleted${NO_COLOR}"

fclean: clean
	@rm -rf ${NAME}
	@echo "${RED} • The executed file is removed${NO_COLOR}"

re: fclean all

.PHONY: re fclean clean all