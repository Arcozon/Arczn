NAME =  Arczn

S_INIT =  parsOpt.c  parsOptArg.c  checkOptArg.c  parsBaseImg.c  genStart.c
D_INIT =  init/
INIT = $(addprefix $(D_INIT), $(S_INIT))

S_GEN =  random.c  ivy.c  petri.c  
D_GEN =  generation/
GEN = $(addprefix $(D_GEN), $(S_GEN))

S_COLOR =  applyColor.c  gradient.c
D_COLOR =  color/
COLOR = $(addprefix $(D_COLOR), $(S_COLOR))

S_OUTPUT =  print.c  frame.c  nColor.c  savePng.c
D_OUTPUT =  output/
OUTPUT = $(addprefix $(D_OUTPUT), $(S_OUTPUT))

S_UTILS =  random.c  color.c  hashtable.c  vector.c  fenwick_tree.c
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
FLAGS = -Wall -Wextra -Werror -MMD -g -O3
INC = inc/ $(D_SPNG)spng
INC_FLAGS =  $(addprefix -I, $(INC))
LIB_FLAGS = -L. -lspng -Wl,-rpath,$(shell pwd)/$(D_MESON_BUILD)  -Wl,-z,now -lm

RM =  rm -rf

MAKE += --no-print-directory

all:	$(NAME)

$(NAME):	$(OBJ)	$(SYML_SPNG_SO)
	$(CC) -o$@ $(OBJ) $(LIB_FLAGS)

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC_FLAGS) -c $< -o $@


$(SYML_SPNG_SO):	$(SPNG_SO)
	ln -s $< $@

$(SPNG_SO):
	meson setup $(MESON_BUILD_DIR) $(SPNG_DIR)
	meson compile -C $(MESON_BUILD_DIR)

clean:
	@$(RM) $(D_BUILD)

fclean: clean
	@$(RM) $(NAME) $(SYML_SPNG_SO)

re: fclean
	@$(MAKE) all

NAME_PARS = parsConfig
YACC_SRC =  config_parser.y
LEX_SRC	 =  config_lexer.l

D_GEN	   =  gen/
YACC_C_GEN =  $(D_GEN)$(YACC_SRC:.y=.c)
LEX_C_GEN  =  $(D_GEN)$(LEX_SRC:.l=.c)
INC_GEN	   =  $(YACC_C_GEN:.c=.h) 

YACC	=  bison -d #-Wother -Wconflicts-rr -Wconflicts-sr -Wcounterexamples 
LEX		=  flex

.DEFAULT_GOAL =  pars
pars:	$(NAME_PARS)

$(NAME_PARS):	$(YACC_C_GEN)	$(LEX_C_GEN)
	cc $^ -I$(D_GEN) -I$(D_SRC) -o $@

$(YACC_C_GEN): $(YACC_SRC)
	@mkdir -p $(@D)
	$(YACC) -o$@ -- $<

$(LEX_C_GEN): $(LEX_SRC) $(INC_GEN)
	@mkdir -p $(@D)
	$(LEX) -o$@ $<

DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))
-include $(DEPS)

.PHONY: re fclean clean all $(CC) $(FLAGS) $(RM)
