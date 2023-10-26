SRCS = srcs/main.c \
	   srcs/read_args.c	\
	   srcs/read_args_range.c \
	   srcs/init_info.c \
	   srcs/init_philo_info.c \
	   srcs/create_threads.c \
	   srcs/threads.c \
	   srcs/actions.c \
	   srcs/actions_fork.c \
	   srcs/actions_output_message.c \
	   srcs/utils.c \
	   srcs/error.c

	   
OBJS = ${patsubst $(SRCS_DIR)%.c,  $(OBJS_DIR)%.o, $(SRCS)}

NAME = philo
CC = cc
SRCS_DIR = srcs/
OBJS_DIR = objs/
INCS_DIR = incs/

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(@D)
	${CC} ${CFLAGS} -I $(INCS_DIR) -c $< -o $@

#-g -fsanitize=thread
${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all: ${NAME};

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf ${NAME}
re: fclean
	make all

.PHONY: all clean fclean re