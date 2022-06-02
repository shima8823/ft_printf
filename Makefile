CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I ft_printf.h
NAME = libftprintf.a
SRCS = ft_printf.c libft/ft_strlen.c libft/ft_putnbr_fd.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) r $(NAME) $(OBJS)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all