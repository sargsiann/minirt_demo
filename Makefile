NAME = minirt

CC = cc

CFLAGS = #-Wall -Wextra -Werror

MLX_COMP_FLAGS = $(CFLAGS) -I/usr/include -Imlx_linux -O3

MLX_LNK_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

SRCS = $(wildcard *.c lib/*.c)

OBJS = $(SRCS:.c=.o)
	
%.o : %.c 
	$(CC) $(MLX_COMP_FLAGS) -c $< -o $@

all : $(NAME) Makefile minirt.h

$(NAME) : Makefile minirt.h $(OBJS)
	$(CC) $(OBJS) $(MLX_LNK_FLAGS) -o minirt

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf minirt

re : fclean all

Phony: all clean re fclean