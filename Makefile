NAME		:= pipex

OBJ_DIR		:=	./obj
SRC_DIR 	:=	./src
INC_DIR		:=	./include \
				./libft/include


CFLAGS	= -Wextra -Wall -Werror

ifdef DEBUG
CFLAGS +=-g
endif

INCLUDE		:= $(addprefix -I,$(INC_DIR))
LIBS		:= ./libft/libft.a 

SRCS		:= 		command.c \
					error_handling.c \
					heredoc.c \
					main.c \
					pipeloop.c \
					pipex_utils.c \
					pipex_split.c \

OBJS		:= 		$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
DEP			:=		$(OBJS:%.o=%.d)

#===============================================#
#=================== RECIPES ===================#
#===============================================#
-include $(DEP)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ 

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ./libft fclean

re: clean all

debug:
	$(MAKE) DEBUG=1

rebug: fclean
	$(MAKE) debug

.PHONY: all, clean, fclean, re