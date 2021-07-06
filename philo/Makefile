NAME 			= philo

HEADER			= philo.h

SRCS			=	main.c init.c read.c time.c memory.c

OBJS			= $(SRCS:.c=.o)
%.o:			%.c ${HEADER}
				$(CC) $(CFLAGS) -c -o $@ $<

RM				= rm -f
CFLAGS			= #-Wall -Werror -Wextra
INCLUDES		= ./philo.h

$(NAME):		$(OBJS) $(HEADER)
				gcc $(OBJS) -o ${NAME}

all:			$(NAME)
clean:
				$(RM) $(OBJS)		

fclean:			clean
				$(RM) $(NAME)
				
re:				fclean all
test:			all
.PHONY:			all clean fclean re

