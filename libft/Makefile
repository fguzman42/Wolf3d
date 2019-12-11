# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/14 18:46:15 by pgobeil-          #+#    #+#              #
#    Updated: 2019/09/24 11:07:44 by pgobeil-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC=ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c \
ft_memdel.c \
ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c \
ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
ft_strsubcpy.c ft_putc_in_str.c ft_strdmpnfree.c\
ft_strcmp.c ft_strncmp.c ft_a_strcmp.c ft_atoi.c \
ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c\
ft_toupper.c ft_tolower.c ft_abs_val.c ft_min_val.c ft_max_val.c\
ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
ft_strtrim.c ft_strsplit.c \
ft_itoa.c ft_digit.c ft_pow.c ft_countwords.c\
ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putallstrs.c\
ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c\
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c err_ret.c

OBJ = $(SRC:.c=.o)

SRCDIR = srcs

OBJDIR = objs

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJS = $(addprefix $(OBJDIR)/, $(OBJ))

HEADER = -I includes

CC = gcc

CFLAGS = -c -Wall -Wextra -Werror

NAME = libft.a

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(OBJS): $(SRCS)
	/bin/mkdir -p $(OBJDIR) ;
	$(CC) $(CFLAGS) $(SRCS) $(HEADER) ;
	/bin/mv $(OBJ) $(OBJDIR)/

$(NAME): $(OBJS)
	ar rcs $@ $^
	ranlib $@

clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all