# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 22:09:06 by mes-sadk          #+#    #+#              #
#    Updated: 2023/02/11 10:50:58 by mes-sadk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = rec_cs

N_ORG = 

CC = c++ -std=c++98
INC = -I$(shell pwd)

RED = \033[0;31m
R_3 = \033[0;34m
GREEN = \033[0;32m
NO_COLOR = \033[0m

CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address
LEAKS = -D leaks=0

SRC_FILES = main_tests/main.cpp \
			main_tests/mmap.cpp \
			main_tests/mset.cpp \
			main_tests/mstk.cpp \
			main_tests/mvec.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.opp)

.PHONY: re fclean clean all _org  _rec REC ORG diff

%.opp:%.cpp  $(shell ls *.hpp) main_tests/test.hpp
	@${CC} ${CFLAGS} $(INC)  -o $@ -c $< -D LEET


help:
	@echo "$(R_3)"
	@echo "make ORG ($(GREEN)ORIGINAL$(R_3)) or make REC ($(GREEN)RECREATED$(R_3))"
	@echo also you can make diff
	@echo "$(NO_COLOR)"

all : help

_org:  ${OBJ_FILES}
	@${CC} ${CFLAGS} ${SRC_FILES} -o org_cs ${INC} -D LEET=1
	@echo "$(GREEN)" ./org_cs "$(NO_COLOR)" 

_rec:  ${OBJ_FILES}
	@${CC} ${CFLAGS} ${SRC_FILES} -o ${NAME} ${INC} -D LEET=1337 ${LEAKS}
	@echo "$(GREEN)" ./${NAME} "$(NO_COLOR)"

ORG:  _org

REC:  _rec

diff: ORG REC
#@diff 


$(NAME): _rec

clean:
	@echo cleaning ...
	@rm -rf ${OBJ_FILES}
	@echo \e clean
	

fclean: clean
	@rm -rf rec_cs org_cs

re: fclean all

