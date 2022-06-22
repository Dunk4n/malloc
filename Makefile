# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niduches <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/19 14:57:17 by niduches          #+#    #+#              #
#    Updated: 2021/09/13 15:24:14 by niduches         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC			=	gcc

SRC_DIRECTORY	=	./src/
INC_DIRECTORY	=	./include/
LIB_DIRECTORY	=	./libft/

BUILD_DIRECTORY	=	build

SRC_FILE_NAME	=	malloc.c		\

SRC			=	$(addprefix $(SRC_DIRECTORY),$(SRC_FILE_NAME))

NAME		=	libft_malloc_${HOSTTYPE}.so

OBJ			=	$(SRC:%.c=$(BUILD_DIRECTORY)/%.o)

CFLAGS		=	-I$(INC_DIRECTORY) -Wall -Wextra -Werror -fPIC

LDFLAGS		=	-L$(LIB_DIRECTORY) -lft

all:	$(NAME)

options:
	@echo "  CC       $(CC)"
	@echo "  CFLAGS   $(CFLAGS)"
	@echo "  LDFLAGS  $(LDFLAGS)"

$(BUILD_DIRECTORY)/%.o: %.c $(INC)
	@mkdir -p $(@D)
	@echo "  CC       $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIB_DIRECTORY) clean --no-print-directory
	@echo "  RM       $(BUILD_DIRECTORY)"
	@rm -rf $(BUILD_DIRECTORY)

fclean: clean
	@$(MAKE) -C $(LIB_DIRECTORY) fclean --no-print-directory
	@echo "  RM       $(NAME)"
	@rm -f $(NAME)
	@rm -f libft_malloc.so
	@rm -f test0
	@rm -f test1
	@rm -f test2
	@rm -f test3
	@rm -f test4
	@rm -f test5

$(NAME): options $(OBJ)
	@$(MAKE) -C $(LIB_DIRECTORY) --no-print-directory
	@$(CC) -shared $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)
	@echo "  BUILD    $@"
	@ln -f -s $@ libft_malloc.so
	@echo "  BUILD    libft_malloc.so"

TEST: re
	gcc -o test0 test0.c -L. -lft_malloc
	gcc -o test1 test1.c -L. -lft_malloc
	gcc -o test2 test2.c -L. -lft_malloc
	gcc -o test3 test3.c -L. -lft_malloc
	gcc -o test4 test4.c -L. -lft_malloc
	gcc -o test5 test5.c -L. -lft_malloc

re:	fclean	all

.PHONY: all options clean fclean re debug fdebug
