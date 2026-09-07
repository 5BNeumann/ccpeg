SOURCES = src/parse.c src/parsing_helpers.c src/peg_maybe.c src/peg_rule_manager.c src/string_view.c \
		src/parse_macro.c src/peg.c src/peg_public_api.c src/peg_rule_unparameterized.c src/utils.c \
		src/parse_micro.c src/peg_group.c src/peg_rule_container.c src/run.c
NAME	=	peggle_deluxe.a
BUILD_DIR = build/
INCLUDES = ./include
OBJECTS = $(SOURCES:src/%.c=$(BUILD_DIR)%.o)
CFLAGS = -Wall -Wextra -Werror -ggdb
LDFLAGS = libft.a -lreadline
CC = cc

all: $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(NAME): $(BUILD_DIR) $(OBJECTS)
	ar rv $(NAME) $(OBJECTS)

clean:
	-rm -f $(OBJECTS)
	make clean -C libft

fclean: clean
	-rm -f $(NAME)
	-rm -fr $(BUILD_DIR)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
