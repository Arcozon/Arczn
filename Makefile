NAME =  Arczn

S_PARG =  parsOpt.c  parsOptArg.c  checkOptArg.c  parsBaseImg.c
D_PARG =  pArg/
PARG = $(addprefix $(D_PARG), $(S_PARG))

S_GEN =  random.c  ivy.c  petri.c
D_GEN =  gen/
GEN = $(addprefix $(D_GEN), $(S_GEN))

S_PRINT =  print.c  frame.c  nColor.c  savePng.c
D_PRINT =  print/
PRINT = $(addprefix $(D_PRINT), $(S_PRINT))

S_UTILS =  random.c  color.c  hashtable.c  vector.c
D_UTILS =  utils/
UTILS = $(addprefix $(D_UTILS), $(S_UTILS))

SRC =  $(PARG)  $(GEN)  $(PRINT)  $(UTILS)  main.c  applyColor.c
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
LIB_FLAGS = -L. -lspng -Wl,-rpath,$(shell pwd)/$(D_MESON_BUILD)  -Wl,-z,now

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

DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))
-include $(DEPS)

.PHONY: re fclean clean all $(CC) $(FLAGS) $(RM)
