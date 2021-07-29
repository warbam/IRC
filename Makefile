SRCS_NAME		=		main.cpp 	\
						Server.cpp 	\
						User.cpp	\
						Channel.cpp	\
						
OBJS			=		${SRCS_NAME:.cpp=.o}

NAME			=		ircserv

RM				=		rm -f

CC				=		clang++

FLAGS			=		-Wall -Wextra -Werror -fsanitize=address

all:					$(NAME)

%.o: %.cpp				
	$(CC) $(FLAG) -c $< -o $@
	
$(NAME):				$(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean:					clean
	@$(RM) $(NAME)

re:                     fclean all