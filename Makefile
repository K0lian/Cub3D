#run:
#	gcc main2.c parser.c parser2.c parser3.c parser4.c parser5.c rasschet.c gnl_utils.c jytrfcx.c move_main.c util_main.c utils1.c utils2.c risovka.c screen.c gnl.c fin_nahyi.c -lmlx -framework OpenGl -framework Appkit -g -Wall -Wextra -Werror 
#	./a.out map1.cub

# -fsanitize=address -g -Wall -Wextra -Werror

NAME = cub3D
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRCS =			main2.c\
			parser.c\
			parser2.c\
			parser3.c\
			parser4.c\
			parser5.c\
			rasschet.c\
			jytrfcx.c\
			move_main.c\
			util_main.c\
			utils1.c\
			utils2.c\
			risovka.c\
			screen.c\
			gnl.c\
			fin_nahyi.c\
			gnl_utils.c
OBJS = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) -lmlx -framework OpenGL -framework AppKit $^ -o $@
		
clean:
		rm -f $(OBJS) a.out

fclean:		clean
		rm -f $(NAME) 

re:		fclean all

.PHONY: all clean fclean re bonus
