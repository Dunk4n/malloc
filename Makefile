# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niduches <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/19 14:57:17 by niduches          #+#    #+#              #
#    Updated: 2022/06/20 15:15:42 by niduches         ###   ########.fr        #
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

$(NAME): options $(OBJ)
	@$(MAKE) -C $(LIB_DIRECTORY) --no-print-directory
	@$(CC) -shared $(CFLAGS) -o $@ $(OBJ) ./libft/printf/*.o $(LDFLAGS)
	@echo "  BUILD    $@"
	@ln -f -s $@ libft_malloc.so
	@echo "  BUILD    libft_malloc.so"

re:	fclean	all

.PHONY: all options clean fclean re
