NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c\
		parse.c\
		init.c\
		routine.c\
		time_utils.c\
		monitoring.c
OBJDIR = obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) compiled successfully"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing object files"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Removing $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
