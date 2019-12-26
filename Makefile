SRC = passtrength.c

NAME = passtrength

all: NAME clean

NAME:
	@gcc -o $(NAME) $(SRC) lib.h -g
  
clean:
	@find -name "*.o" -delete -o -name -delete
  
fclean: clean
	@rm -f $(NAME)

re: fclean all
