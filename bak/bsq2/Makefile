DIR_HEADER=includes
DIR_SOURCE=srcs
DIR_OBJECT=objects
SOURCES = debug.c pnl.c t_map.c t_square.c parse_file.c ft_split.c strings.c main.c
SOURCE_FILES = $(addprefix $(DIR_SOURCE)/, $(SOURCES))
OBJECT_FILES = $(addprefix $(DIR_OBJECT)/, $(patsubst %.c, %.o, $(SOURCES)))
EXECUTABLE=bsq
COMPILE=cc -Werror -Wextra -Wall -fsanitize=address -g

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT_FILES)
	$(COMPILE) -o $@ $(OBJECT_FILES)

$(OBJECT_FILES): $(SOURCE_FILES)
	@if [ ! -d "./$(DIR_OBJECT)" ]; then mkdir $(DIR_OBJECT); fi 
	$(COMPILE) -c -I$(DIR_HEADER) -o $@ $(patsubst $(DIR_OBJECT)/%.o, $(DIR_SOURCE)/%.c, $@)

clean:
	rm -f $(OBJECT_FILES)

fclean: clean
	rm -f $(EXECUTABLE)

re: fclean all

.PHONY: clean fclean re all
