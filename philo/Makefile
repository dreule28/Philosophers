NAME = philo
CC = cc
RM = rm -rf

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

OBJ_DIR = _obj
INC_DIRS := Includes
SRC_DIRS := src
HEADERS = -I

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

SRC_FILES := main.c utils.c init_table.c create_threads.c free_table.c utils2.c
SRC := $(addprefix src/, $(SRC_FILES))

################################################################################
###############               OBJECT FILES & RULES                ##############
################################################################################

OBJS := $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

# Compilation flags and linking options
CFLAGS := -Wall -Wextra -Werror -g -IIncludes -MMD -MP -pthread $(addprefix -I, $(INC_DIRS))
CFLAGS_SAN := $(CFLAGS) -fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[0;32mCompiling $(NAME)...\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[0;32mSuccessful Compilation of $(NAME)\033[0m"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo "\033[0;32mCompiling $<...\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@echo "\033[0;32mCleaning object files...\033[0m"
	@$(RM) $(OBJS)

fclean: clean
	@echo "\033[0;32mRemoving $(NAME)...\033[0m"
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@echo "\033[0;32mRemoved files succesfully \033[0m"

re: fclean all

.PHONY: all clean fclean re