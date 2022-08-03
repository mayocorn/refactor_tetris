NAME    = tetris

SRCDIR  = ./src/
SRCS    = tetris.c action.c judge.c mino.c table.c 

OBJDIR  = ./obj/
OBJS    = $(addprefix $(OBJDIR), $(SRCS:%.c=%.o))
DEPS    = $(OBJS:%.o=%.d)

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
INCLUDE = -I./include/
LIBS    = -lncurses

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

-include $(DEPS)

.PHONY: all
all: $(NAME)

.PHONY: clean
clean: 
	rm -rf $(OBJDIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
