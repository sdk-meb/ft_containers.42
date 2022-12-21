NAME = containers

CC = c++
INC = -I$(shell pwd)
RED = \033[0;31m
GREEN = \033[0;32m
NO_COLOR = \033[0m

CFLAGS = -Wall -Wextra -Werror -std=c++98


SRC_FILES = test.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.opp)

ORDR = a


%.opp:%.cpp  $(shell ls *.hpp)
	@${CC} ${CFLAGS} $(INC)  -o $@ -c $<

all: ${NAME}

$(NAME): ${OBJ_FILES}
	@${CC} ${CFLAGS} ${OBJ_FILES} -o ${NAME} 
	@echo "${GREEN} • Now you can run the exucitable file ./${NAME}${NO_COLOR}"

clean:
	@rm -rf ${OBJ_FILES}
	@echo "${RED} • ALL object files are deleted${NO_COLOR}"

fclean: clean
	@rm -rf ${NAME}
	@echo "${RED} • The executed file is removed${NO_COLOR}"

re: fclean all

.PHONY: re fclean clean all