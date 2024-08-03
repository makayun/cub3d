# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 12:43:00 by mmakagon          #+#    #+#              #
#    Updated: 2024/06/28 11:48:06 by maxmakagono      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEF_COLOR	= \033[0;39m
GRAY		= \033[0;90m
GREEN		= \033[0;92m
CARROT	    = \033[38;5;160m

NAME = libft.a
CC = @clang
CFLAGS = -Wall -Wextra -Werror -I./
AR = @ar rc
RM = @rm -rf

UNAME = $(shell uname -s)
ifeq ($(UNAME),Darwin)
CFLAGS += -DMACOS
endif

FILES =	ft_atoi \
		ft_bzero \
		ft_calloc \
		ft_get_next_line \
		ft_isalnum \
		ft_isalpha \
		ft_isascii \
		ft_isdigit \
		ft_isprint \
		ft_isspace \
		ft_itoa \
		ft_lstadd_back \
		ft_lstadd_front \
		ft_lstclear \
		ft_lstdelone \
		ft_lstiter \
		ft_lstlast \
		ft_lstmap \
		ft_lstnew \
		ft_lstsize \
		ft_memchr \
		ft_memcmp \
		ft_memcpy \
		ft_memmove \
		ft_memset \
		ft_printf \
		ft_putchar_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_putstr_fd \
		ft_split \
		ft_strcat \
		ft_strchr \
		ft_strcmp \
		ft_strcpy \
		ft_strdup \
		ft_striteri \
		ft_strjoin \
		ft_strlcat \
		ft_strlcpy \
		ft_strlen \
		ft_strmapi \
		ft_strncmp \
		ft_strnstr \
		ft_strrchr \
		ft_strtrim \
		ft_substr \
		ft_tabfree \
		ft_tablen \
		ft_tolower \
		ft_toupper \

SRCS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p obj
	$(CC) -c $(CFLAGS) -o $@ $<
	@printf "$(GRAY)*$(DEF_COLOR)"

all: $(NAME)
	@echo "$(GREEN)\nLIBFT done!$(DEF_COLOR)"

$(NAME): libft.h $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_DIR)
	@echo "$(CARROT)LIBFT objects cleaned!$(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(CARROT)AND THE LIBFT LIBRARY FILE!!!$(DEF_COLOR)"

re: clean all
	@echo "$(CARROT)Dej pokoj!$(DEF_COLOR)"

.PHONY: all clean fclean re