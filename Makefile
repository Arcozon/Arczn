NAME =  Arczn

S_INIT =  parsOpt.c  parsOptArg.c  checkOptArg.c  parsBaseImg.c  genStart.c
D_INIT =  init/
INIT = $(addprefix $(D_INIT), $(S_INIT))

S_PETRI =  Fn_chosePointDirection.c  Fn_getClusterWeight.c  Fn_getPointWeight.c  Fn_getPossibilityMask.c  Fn_removePoint.c
S_PETRI+=  petri.c  dataStructure.c  
D_PETRI =  petri/
PETRI = $(addprefix $(D_PETRI), $(S_PETRI))
S_GEN =  random.c  ivy.c  $(PETRI)
D_GEN =  generation/
GEN = $(addprefix $(D_GEN), $(S_GEN))

S_COLOR =  applyColor.c  gradient.c  mergeBackground.c
D_COLOR =  color/
COLOR = $(addprefix $(D_COLOR), $(S_COLOR))

S_OUTPUT =  print.c  frame.c  nColor.c  savePng.c
D_OUTPUT =  output/
OUTPUT = $(addprefix $(D_OUTPUT), $(S_OUTPUT))

S_UTILS =  random.c  color.c  hashtable.c  vector.c  fenwick_tree.c  debug.c
D_UTILS =  utils/
UTILS = $(addprefix $(D_UTILS), $(S_UTILS))

SRC =  $(INIT)  $(GEN)  $(COLOR)  $(OUTPUT)  $(UTILS)  main.c
D_SRC = src/

D_BUILD = .build/
OBJ =  $(addprefix $(D_BUILD), $(SRC:.c=.o))

D_SPNG	=  libspng/
D_MESON_BUILD =  $(D_SPNG)build/
SPNG_SO		  =  $(D_MESON_BUILD)$(SYML_SPNG_SO)
SYML_SPNG_SO =  libspng.so

CC =  cc
FLAGS = -Wall -Wextra -Werror -MMD -g -O3 -march=native
INC = inc/ $(D_SPNG)spng
INC_FLAGS =  $(addprefix -I, $(INC))
LIB_FLAGS = -L. -lspng -Wl,-rpath,$(shell pwd)  -Wl,-z,now -lm

RM =  rm -rf

MAKE += --no-print-directory

all:	$(NAME)

$(NAME):	$(SYML_SPNG_SO)  $(OBJ)
	$(CC) -o$@ $(OBJ) $(LIB_FLAGS)

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC_FLAGS) -c $< -o $@


$(SYML_SPNG_SO):
	$(MAKE) $(SPNG_SO)
	ln -s $(SPNG_SO) $@

$(SPNG_SO):
	meson setup $(D_MESON_BUILD) $(D_SPNG)
	meson compile -C $(D_MESON_BUILD)

clean:
	@$(RM) $(D_BUILD)

fclean: clean
	@$(RM) $(NAME)

re: fclean
	@$(MAKE) all

NAME_PARS = parsConfig
YACC_SRC =  config_parser.y
LEX_SRC	 =  config_lexer.l

D_GEN_PARS	   =  gen/
YACC_C_GEN =  $(D_GEN_PARS)$(YACC_SRC:.y=.c)
LEX_C_GEN  =  $(D_GEN_PARS)$(LEX_SRC:.l=.c)
INC_GEN	   =  $(YACC_C_GEN:.c=.h) 

YACC	=  bison -d -Wother -Wconflicts-rr -Wconflicts-sr -Wcounterexamples -v
LEX		=  flex

.DEFAULT_GOAL =  pars
pars:	$(NAME_PARS)
	clear
	@echo -e '\t\033[1;32m./$(NAME_PARS) <test.config\033[0m'
	@valgrind -q --leak-check=full --show-leak-kinds=all ./$(NAME_PARS) <test.config

$(NAME_PARS):	$(YACC_C_GEN)	$(LEX_C_GEN) $(D_BUILD)$(D_UTILS)random.o
	cc $^ -I. -I$(D_GEN_PARS) $(INC_FLAGS) -o $@

$(YACC_C_GEN): $(YACC_SRC)
	@mkdir -p $(@D)
	$(YACC) -o$@ -- $<

$(LEX_C_GEN): $(LEX_SRC) $(INC_GEN)
	@mkdir -p $(@D)
	$(LEX) -o$@ $<

DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))
-include $(DEPS)

.PHONY: re fclean clean all $(CC) $(FLAGS) $(RM)  $(SPNG_SO)
