NAME = libftprintf.a

SRCS = printf.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_NAME = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT_NAME) $(OBJS)
	cp $(LIBFT_NAME) $(NAME)
	ar -rcs $(NAME) $(OBJS)

$(LIBFT_NAME):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus