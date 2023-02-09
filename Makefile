# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 22:09:06 by mes-sadk          #+#    #+#              #
#    Updated: 2023/02/09 18:02:17 by mes-sadk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = rec_cs

N_ORG = 

CC = c++ -std=c++98
INC = -I$(shell pwd)

RED = #\033[0;31m
GREEN =# \033[0;32m
NO_COLOR = #\033[0m

CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address

SRC_FILES = main_tests/main.cpp \
			main_tests/mmap.cpp \
			main_tests/mset.cpp \
			main_tests/mstk.cpp \
			main_tests/mvec.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.opp)

.PHONY: re fclean clean all _org  _rec REC ORG diff

%.opp:%.cpp  $(shell ls *.hpp) main_tests/test.hpp
	@${CC} ${CFLAGS} $(INC)  -o $@ -c $< -D LEET

all:  help ${NAME}


_org:  ${OBJ_FILES}
	@${CC} ${CFLAGS} ${SRC_FILES} -o org_cs ${INC} -D LEET=1
	@echo ${GREEN} ./org_cs ${NO_COLOR}

_rec:  ${OBJ_FILES}
	@${CC} ${CFLAGS} ${SRC_FILES} -o ${NAME} ${INC} -D LEET=1337
	@echo ${GREEN} ./${NAME} ${NO_COLOR}

ORG:  _org

REC:  _rec

diff: ORG REC
#@diff 

help:
	@echo ${RED}
	@echo "make ORG (ORIGINAL) or make REC (RECREATED)"
	@echo also you can make diff
	@echo $(NO_COLOR)

$(NAME): _rec

clean:
	@echo cleaning ...
	@rm -rf ${OBJ_FILES}
	@echo \e clean
	

fclean: clean
	@rm -rf rec_cs org_cs

re: fclean all

