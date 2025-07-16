DIR_HEADER=includes
DIR_SOURCE=srcs
DIR_OBJECT=obj
SOURCES = debug.c pnl.c t_map.c t_square.c parse_file.c ft_split.c strings.c benchmark.c main.c
SOURCES_BENCHMARK = debug.c pnl.c t_map.c t_square.c parse_file.c ft_split.c strings.c benchmark.c main_benchmark.c
EXECUTABLE=bsq
EXECUTABLE_BENCHMARK=bsq_benchmark
COMPILE=cc -Werror -Wextra -Wall

all: $(EXECUTABLE)

$(EXECUTABLE):
	@if [ ! -d "./$(DIR_OBJECT)" ]; then mkdir $(DIR_OBJECT); fi
	@for src in $(SOURCES); do \
		$(COMPILE) -c -I$(DIR_HEADER) -o $(DIR_OBJECT)/$${src%.c}.o $(DIR_SOURCE)/$$src; \
	done
	$(COMPILE) -o $@ $(DIR_OBJECT)/*.o

$(EXECUTABLE_BENCHMARK):
	@if [ ! -d "./$(DIR_OBJECT)" ]; then mkdir $(DIR_OBJECT); fi
	@for src in $(SOURCES_BENCHMARK); do \
		echo "Compiling $$src..."; \
		$(COMPILE) -c -I$(DIR_HEADER) -o $(DIR_OBJECT)/$${src%.c}.o $(DIR_SOURCE)/$$src; \
	done
	$(COMPILE) -o $@ $(DIR_OBJECT)/*.o

benchmark: $(EXECUTABLE_BENCHMARK)

clean:
	rm -f $(DIR_OBJECT)/*.o

fclean: clean
	rm -f $(EXECUTABLE) $(EXECUTABLE_BENCHMARK)

re: fclean all

.PHONY: clean fclean re all benchmark
