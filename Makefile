NAME = minirt

DEPS = Makefile minirt.h

CFLAGS = 

MLX_CMP_FLAGS = -I/usr/include -Imlx_linux -O3

MLX_LN_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

%.o : %.c
	cc $(MLX_CMP_FLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS) $(DEPS)
	$(CC) $(OBJS) $(MLX_LN_FLAGS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re